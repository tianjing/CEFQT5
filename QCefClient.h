#pragma once

#ifndef QCEFCLIENT_H
#define QCEFCLIENT_H

QCefWebView_EXPORT int QCefInit(int &argc, char ** argv);

QCefWebView_EXPORT void QCefQuit();

QCefWebView_EXPORT QString AppGetWorkingDirectory();

#endif // QCEFCLIENT_H