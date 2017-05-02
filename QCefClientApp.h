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

	virtual void OnBeforeCommandLineProcessing(
		const CefString& process_type,
		CefRefPtr<CefCommandLine> command_line) OVERRIDE{
		//command_line->AppendSwitch("process-per-site");
		//command_line->AppendSwitch("single-process");
	}
private:
	IMPLEMENT_REFCOUNTING(QCefClientApp);
};
