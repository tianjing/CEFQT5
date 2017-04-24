#include "stdafx.h"
#include "QCefClientApp.h"


QCefClientApp::QCefClientApp()
{
}

void QCefClientApp::OnContextInitialized()
{
	CEF_REQUIRE_UI_THREAD();
}
