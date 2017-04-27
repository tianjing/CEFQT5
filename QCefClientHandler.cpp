#include "stdafx.h"
#include "QCefClientHandler.h"
#include "qcefmessageevent.h"
#include <QDebug>
int QCefClientHandler::browserCount_ = 0;

QCefClientHandler::QCefClientHandler() :
	isClosing_(false),
	browserId_(0)
{
	if (startupUrl_.empty()) {
		startupUrl_ = "https://www.baidu.com";
	}
}

QCefClientHandler::~QCefClientHandler()
{
}

void QCefClientHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	if (!browser_.get()) {
		// We need to keep the main child window, but not popup windows
		browser_ = browser;
		browserId_ = browser->GetIdentifier();
		if (listener_) {
			listener_->LifeSpanHandler().AfterCreatedEvent(CEventArgs(NULL));
		}
	}
	else if (browser->IsPopup()) {
		// add to the list of popup browsers
		popupBrowsers_.push_back(browser);
	}

	browserCount_++;
}

bool QCefClientHandler::DoClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	// Closing the main window requires special handling. See the DoClose()
	// documentation in the CEF header for a detailed destription of this
	// process.
	if (browserId_ == browser->GetIdentifier()) {
		if (listener_) {
			listener_->LifeSpanHandler().DoCloseEvent(CEventArgs(NULL));
		}
		// Notify the browser that the parent window is about to close.
		// browser->GetHost()->ParentWindowWillClose();
		
		// Set a flag to indicate that the window close should be allowed.
		isClosing_ = true;

	}

	// Allow the close. For windowed browsers this will result in the OS close
	// event being sent.
	return false;
}

void QCefClientHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser)
{
	CEF_REQUIRE_UI_THREAD();

	if (browserId_ == browser->GetIdentifier()) {
		// Free the browser pointer so that the browser can be destroyed
		if (listener_) {
			listener_->LifeSpanHandler().BeforeCloseEvent(CEventArgs(NULL));
		}
		browser_ = nullptr;
	}
	else if (browser->IsPopup()) {
		// Remove from the browser popup list.
		BrowserList::iterator bit = popupBrowsers_.begin();
		for (; bit != popupBrowsers_.end(); ++bit) {
			if ((*bit)->IsSame(browser)) {
				popupBrowsers_.erase(bit);
				break;
			}
		}
	}

	if (--browserCount_ == 0) {
		// NotifyAllBrowsersClosed();
	}
}

void QCefClientHandler::OnLoadError(CefRefPtr<CefBrowser> browser, 
									CefRefPtr<CefFrame> frame, 
									ErrorCode errorCode, 
									const CefString& errorText, 
									const CefString& failedUrl)
{
	CEF_REQUIRE_UI_THREAD();

	// Don't display an error for downloaded files.
	if (errorCode == ERR_ABORTED)
		return;

	// Display a load error message.
	std::stringstream ss;
	ss << "<html><body bgcolor=\"white\">"
		"<h2>Failed to load URL " << std::string(failedUrl) <<
		" with error " << std::string(errorText) << " (" << errorCode <<
		").</h2></body></html>";
	frame->LoadString(ss.str(), failedUrl);
}

void QCefClientHandler::CloseAllBrowsers(bool force_close)
{
	if (!CefCurrentlyOn(TID_UI)) {
		// Execute on the UI thread.
		CefPostTask(TID_UI,
					base::Bind(&QCefClientHandler::CloseAllBrowsers, this, force_close));
		return;
	}

	if (!popupBrowsers_.empty()) {
		// Request that any popup browsers close.
		BrowserList::const_iterator it = popupBrowsers_.begin();
		for (; it != popupBrowsers_.end(); ++it) {
			(*it)->GetHost()->CloseBrowser(force_close);
		}
		return;
	}

	if (browser_.get()) {
		// Request that the main browser close.
		browser_->GetHost()->CloseBrowser(force_close);
	}
}

