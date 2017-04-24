#ifndef STDAFX_H
#define STDAFX_H
// STL

#include <list>
#include <set>
#include <sstream>
#include <string>

// Qt

#include <QtWidgets>
#include <QMainWindow>

// Windows header must be after Qt!

#ifdef _WIN32
#include <Windows.h>
#endif // _WIN32

// Chromium Embedded Framework 3

#include <include/base/cef_bind.h>
#include <include/cef_app.h>
#include <include/cef_browser.h>
#include <include/cef_client.h>
#include <include/cef_command_line.h>
#ifdef _WIN32
#include <include/cef_sandbox_win.h>
#endif // _WIN32
#include <include/wrapper/cef_closure_task.h>
#include <include/wrapper/cef_helpers.h>


#ifdef QCefWebView_LIB
# define QCefWebView_EXPORT Q_DECL_EXPORT
#else
# define QCefWebView_EXPORT Q_DECL_IMPORT
#endif

#endif // STDAFX_H