#pragma once

class QCefClientApp :
	public CefApp,
	public CefBrowserProcessHandler
{
public:
	QCefClientApp();

	// CefApp methods:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() OVERRIDE{ return this; }

	// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized() OVERRIDE;

private:
	IMPLEMENT_REFCOUNTING(QCefClientApp);
};
