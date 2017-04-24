#pragma once

#include "qcefmessageevent.h"

class QCefClientHandler :
	public CefClient,
	public CefDisplayHandler,
	public CefLifeSpanHandler,
	public CefLoadHandler
{
public:
	class Listener
	{
	public:
		virtual ~Listener() {};

		virtual void OnAddressChange(const QString & url) = 0;
		virtual void OnTitleChange(const QString & title) = 0;
		virtual void SetLoading(bool isLoading) = 0;
		virtual void SetNavState(bool canGoBack, bool canGoForward) = 0;
		virtual void OnAfterCreated() = 0;
		virtual void OnMessageEvent(QCefMessageEvent * e) = 0;
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
	
// overridden methods
public:
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
							 CefRefPtr<CefFrame> frame,
							 ErrorCode errorCode,
							 const CefString& errorText,
							 const CefString& failedUrl) OVERRIDE;
	
	void CloseAllBrowsers(bool force_close);

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
	void SetLoading(bool isLoading);
	void SetNavState(bool canGoBack, bool canGoForward);

	// child browser window
	CefRefPtr<CefBrowser> Browser_;

	// list of any popup browser windows, only accessed on CEF UI thread
	typedef std::list<CefRefPtr<CefBrowser>> BrowserList;
	BrowserList popupBrowsers_;

	// Number of currently existing browser windows. The application will exit
	// when the number of windows reaches 0.
	static int browserCount_;

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

