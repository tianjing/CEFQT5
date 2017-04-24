#include "stdafx.h"
#include "qcefwebview.h"
#include "QCefClientHandler.h"
#include "qcefmessageevent.h"

extern CefRefPtr<QCefClientHandler> g_handler;

const QString QCefWebView::kUrlBlank = "https://www.baidu.com";

QCefWebView::QCefWebView(QWidget *parent) : 
	QWidget(parent),
	browserState_(kNone),
	needResize_(false),
	needLoad_(false)
{
	setAttribute(Qt::WA_NativeWindow, true);
	setAttribute(Qt::WA_DontCreateNativeAncestors, true);
}

QCefWebView::~QCefWebView()
{
	// empty destructor
}

void QCefWebView::load(const QUrl& url)
{
	url_ = url;
	
	switch (browserState_) {
		case kNone:
			CreateBrowser(size());
			break;

		case kCreating:
			needLoad_ = true;
			break;

		default:
			BrowserLoadUrl(url);
	}
}

void QCefWebView::setHtml(const QString& html, const QUrl& baseUrl)
{
	if (GetBrowser().get()) {
		QUrl url = baseUrl.isEmpty() ? this->url() : baseUrl;

		if (!url.isEmpty()) {
			auto frame = GetBrowser()->GetMainFrame();
			frame->LoadStringW(CefString(html.toStdWString()),
							   CefString(url.toString().toStdWString()));
		}
	}
}

QUrl QCefWebView::url() const
{
	if (GetBrowser().get()) {
		auto url = GetBrowser()->GetMainFrame()->GetURL();
		return QUrl(QString::fromStdWString(url.ToWString()));
	}
	return QUrl();
}

void QCefWebView::back()
{
	auto browser = GetBrowser();

	if (browser.get()) {
		browser->GoBack();
	}
}

void QCefWebView::forward()
{
	auto browser = GetBrowser();

	if (browser.get()) {
		browser->GoForward();
	}
}

void QCefWebView::reload()
{
	auto browser = GetBrowser();

	if (browser.get()) {
		browser->Reload();
	}
}

void QCefWebView::stop()
{
	auto browser = GetBrowser();

	if (browser.get()) {
		browser->StopLoad();
	}
}

void QCefWebView::resizeEvent(QResizeEvent* e)
{
	switch (browserState_) {
		case kNone:
			CreateBrowser(e->size());
			break;

		case kCreating:
			needResize_ = true;
			break;

		default:
			ResizeBrowser(e->size());
	}
}

void QCefWebView::closeEvent(QCloseEvent* e)
{
	if (auto handlerInstance = g_handler) {
		if (handlerInstance->IsClosing()) {
			auto browser = handlerInstance->GetBrowser();
			if (browser.get()) {
				browser->GetHost()->CloseBrowser(false);
			}
		}
	}
	e->accept();
}

void QCefWebView::showEvent(QShowEvent* /* e */)
{
	CreateBrowser(size());
}

void QCefWebView::customEvent(QEvent* e)
{
	//if (e->type() == QCefMessageEvent::MessageEventType) {
	//	QCefMessageEvent * event = dynamic_cast<QCefMessageEvent*>(e);
	//	QString name = event->name();
	//	QVariantList args = event->args();

	//	// TODO: emit something
	//}
}

void QCefWebView::OnAddressChange(const QString& url)
{
	emit urlChanged(QUrl(url));
}

void QCefWebView::OnTitleChange(const QString& title)
{
	emit titleChanged(title);
}

void QCefWebView::SetLoading(bool isLoading)
{
	if (isLoading) {
		if (!needLoad_ && !url_.isEmpty()) {
			emit loadStarted();
		}
		else {
			if (needLoad_) {
				needLoad_ = false;
			}
			else if (!url_.isEmpty()) {
				emit loadFinished(true);
			}
		}
	}
}

void QCefWebView::SetNavState(bool canGoBack, bool canGoForward)
{
	emit navStateChanged(canGoBack, canGoForward);
}

void QCefWebView::OnAfterCreated()
{
	browserState_ = kCreated;
	if (needResize_) {
		ResizeBrowser(size());
		needResize_ = false;
	}
}

void QCefWebView::OnMessageEvent(QCefMessageEvent* e)
{
	QCoreApplication::postEvent(this, e, Qt::HighEventPriority);
}

bool QCefWebView::CreateBrowser(const QSize& size)
{
	if (browserState_ != kNone || size.isEmpty()) {
		return false;
	}

	mutex_.lock();
	if (browserState_ != kNone) {
		mutex_.unlock();
		return false;
	}

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = size.width();
	rect.bottom = size.height();
	
	CefWindowInfo windowInfo;
	CefBrowserSettings browserSettings;

#ifdef _WIN32
	windowInfo.SetAsChild(reinterpret_cast<HWND>(this->winId()), rect);
#else
#error Implement getting window handler for other OSes!
#endif

	g_handler->setListener(this);

	QString url = url_.isEmpty() ? kUrlBlank : url_.toString();
	CefBrowserHost::CreateBrowser(windowInfo,
								  g_handler.get(),
								  CefString(url.toStdWString()),
								  browserSettings,
								  nullptr);
	browserState_ = kCreating;
	mutex_.unlock();
	
	return true;
}

CefRefPtr<CefBrowser> QCefWebView::GetBrowser() const
{
	CefRefPtr<CefBrowser> browser = nullptr;
	if (g_handler.get()) {
		browser = g_handler->GetBrowser();
	}

	return browser;
}

void QCefWebView::ResizeBrowser(const QSize& size)
{
	if (g_handler.get()) {
		if (g_handler->GetBrowser()) {
			auto windowHandle = 
				g_handler->GetBrowser()->GetHost()->GetWindowHandle();

			if (windowHandle) {
#ifdef _WIN32
				auto hdwp = BeginDeferWindowPos(1);
				hdwp = DeferWindowPos(hdwp,
									  windowHandle,
									  nullptr,
									  0,
									  0,
									  size.width(),
									  size.height(),
									  SWP_NOZORDER);
				EndDeferWindowPos(hdwp);
#else
#error Implement for other OSes!
#endif
			}
		}
	}
}

bool QCefWebView::BrowserLoadUrl(const QUrl& url)
{
	if (!url.isEmpty() && GetBrowser()) {
		CefString cefurl(url_.toString().toStdWString());
		GetBrowser()->GetMainFrame()->LoadURL(cefurl);
		return true;
	}
	return false;
}
