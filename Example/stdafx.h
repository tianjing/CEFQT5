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



#ifdef QCefWebView_LIB
# define QCefWebView_EXPORT Q_DECL_EXPORT
#else
# define QCefWebView_EXPORT Q_DECL_IMPORT
#endif
