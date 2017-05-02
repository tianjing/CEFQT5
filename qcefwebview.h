#ifndef QCEFWEBVIEW_H
#define QCEFWEBVIEW_H

#include "qcefclienthandler.h"
#include "qcefmessageevent.h"
#include "QHandlers\QCefRequestHandler.h"
#include "QHandlers\QCefDisplayHandler.h"
#include "QHandlers\QCefLifeSpanHandler.h"
class QCefWebView_EXPORT QCefWebView :
	public QWidget,
	public QCefClientHandler::Listener
{
	Q_OBJECT

public:
	enum BrowserState
	{
		kNone,
		kCreating,
		kCreated
	};

	static const QString kUrlBlank;
	QCefWebView(QWidget *parent);
	virtual ~QCefWebView();

	void load(const QUrl & url);
	void setHtml(const QString & html, const QUrl & baseUrl = QUrl());

	QUrl url() const;
	virtual QCefRequestHandler& RequestHandler()override
	{
		return requesthandler_;
	}
	virtual QCefDisplayHandler& DisplayHandler() override{
		return displayhandler_;
	}
	virtual QCefLifeSpanHandler& LifeSpanHandler() override {
		return lifeSpanHandler_;
	}

	virtual void ExecuteJavaScript(QString p_FrameName, QString p_Code) {
		CefRefPtr<CefFrame> frame = NULL;
		if (p_FrameName.size()>0) {
			frame = GetBrowser()->GetFrame(CefString(p_FrameName.toStdWString().c_str()));
		}
		else {
			frame = GetBrowser()->GetFrame(CefString(""));
		}
		if (frame)
		{
			CefString code = CefString(p_Code.toStdWString());
			CefString url = CefString("");
			frame->ExecuteJavaScript(code, url, 0);
		}
	}
	virtual void ExecuteJavaScript(QString p_Code)  {
		ExecuteJavaScript("", p_Code);
	}

	virtual void GetFrameNames(std::vector<QString>& p_Names) {
		std::vector<QString> result;
		std::vector<CefString> names;
		GetBrowser()->GetFrameNames(names);
		std::vector<CefString>::iterator begin, end;
		begin=names.begin();
		end = names.end();
		for (; begin != end; ++begin) {
			p_Names.push_back(QString::fromStdWString(begin->ToWString()));
		}

	}

protected:
	virtual void resizeEvent(QResizeEvent * event) override;
	virtual void closeEvent(QCloseEvent * event) override;
	virtual void showEvent(QShowEvent * event) override;
	virtual void customEvent(QEvent * event) override;

	virtual void OnAfterCreated(CEventArgs&);


private:
	void SetupUi();
	bool CreateBrowser(const QSize & size);
	CefRefPtr<CefBrowser> GetBrowser() const;
	void ResizeBrowser(const QSize & size);
	bool BrowserLoadUrl(const QUrl & url);

	QCefRequestHandler requesthandler_ = QCefRequestHandler();;
	QCefDisplayHandler displayhandler_ = QCefDisplayHandler();;
	QCefLifeSpanHandler lifeSpanHandler_= QCefLifeSpanHandler();
	BrowserState browserState_;
	bool needResize_;
	bool needLoad_;
	QUrl url_;
	QMutex mutex_;
	QCefClientHandler* g_handler1 = new QCefClientHandler();
	Q_DISABLE_COPY(QCefWebView);
};

#endif // QCEFWEBVIEW_H
