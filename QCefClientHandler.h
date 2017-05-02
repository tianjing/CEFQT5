#pragma once

#include "qcefmessageevent.h"
#include "QCefResourceHandler.h"
#include "QHandlers\QCefRequestHandler.h"
#include "QHandlers\QCefDisplayHandler.h"
#include "QHandlers\QCefLifeSpanHandler.h"
class QCefWebView_EXPORT QCefClientHandler :
	public CefClient,
	public CefDisplayHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler, 
	public CefRequestHandler
{
public:
	class Listener
	{
	public:
		virtual ~Listener() {};
		virtual QCefRequestHandler& RequestHandler()=0;
		virtual QCefDisplayHandler& DisplayHandler()= 0;
		virtual QCefLifeSpanHandler& LifeSpanHandler() = 0;
	};

	QCefClientHandler();
	virtual ~QCefClientHandler();

	// CefClient methods
	virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE{
		return this;
	}
	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE{
		return this;
	}
	virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE{
		return this;
	}
	// CefRequestHandler methods
	virtual CefRefPtr<CefRequestHandler> GetRequestHandler() OVERRIDE {
		return this;
	}

	virtual CefRefPtr<CefResourceHandler> GetResourceHandler(
		CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefRequest> request)OVERRIDE {
		if (listener_)
		{
			QString url = QString::fromStdWString(request->GetURL().ToWString());
			QGefResourceEventArgs args =QGefResourceEventArgs(url);

			listener_->RequestHandler().GetResourceEvent(args);
			if (args.UseHandler)
			{
				qDebug() << "listener_ getResourceHandler";
				                                          
				return CefRefPtr<QCefResourceHandler>(new QCefResourceHandler(url, args.getResourceHandler()));
			}
		}
		return NULL;
	}

// overridden methods
public:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;//CefLifeSpanHandler
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;//CefLifeSpanHandler
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;//CefLifeSpanHandler
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
							 CefRefPtr<CefFrame> frame,
							 ErrorCode errorCode,
							 const CefString& errorText,
							 const CefString& failedUrl) OVERRIDE;//CefLoadHandler
	
	void CloseAllBrowsers(bool force_close);

	virtual void OnAddressChange(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		const CefString& url) {
		QAddressChangeEventArgs args = QAddressChangeEventArgs(QString::fromStdWString(url.ToWString()));
		listener_->DisplayHandler().AddressChangeEvent(args);
	}

	virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
		const CefString& title) {
		QTitleChangeEventArgs args = QTitleChangeEventArgs(QString::fromStdWString(title.ToWString()));
		listener_->DisplayHandler().TitleChangeEvent(args);
	}

// getters and setters
public:

	bool IsClosing() const
	{
		return isClosing_; 
	};

	CefRefPtr<CefBrowser> GetBrowser()
	{
		return browser_;
	}

	void setListener(Listener* listener)
	{
		listener_ = listener;
	}
	Listener* listener() const
	{
		return listener_;
	}

protected:

	// child browser window
	CefRefPtr<CefBrowser> Browser_;

	// list of any popup browser windows, only accessed on CEF UI thread
	typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
	BrowserList popupBrowsers_;

	// Number of currently existing browser windows. The application will exit
	// when the number of windows reaches 0.
	int browserCount_=0;

private:
	//typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
	//BrowserList browserList_;

	bool isClosing_;

	// The child browser window
	CefRefPtr<CefBrowser> browser_;

	// Listener interface
	Listener* listener_;

	// Startup URL
	std::string startupUrl_;

	// The child browser id
	int browserId_;

	IMPLEMENT_REFCOUNTING(QCefClientHandler);
};

