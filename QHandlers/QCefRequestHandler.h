#pragma once
#include "Delegate\DelegateExt.h"
class QReadResponseEventArgs : public CEventArgs
{
public:
	QReadResponseEventArgs(QString url) :CEventArgs(this) {
		URL = url;
		Data_Out = NULL;
		Bytes_To_Read = 0;
		UseContinue = false;
		UseCancel = false; 
	}
	~QReadResponseEventArgs() {}
	QString URL;
	QByteArray Data_Out; int Bytes_To_Read;
	bool UseContinue; bool UseCancel; bool ReturnValue;
 };

class QProcessRequestEventArgs : public CEventArgs
{
public:
	QProcessRequestEventArgs(QString url) :CEventArgs(this) {
		URL = url;

		UseContinue = false;
		UseCancel = false;
	}
	~QProcessRequestEventArgs() {}
	QString URL;
	bool ReturnValue; bool UseContinue; bool UseCancel;
};
class QGetResponseHeadersEventArgs : public CEventArgs
{
public:
	QGetResponseHeadersEventArgs(QString url) :CEventArgs(this) {
		URL = url;
	}
	~QGetResponseHeadersEventArgs() {}
	QString URL; QString RedirectUrl; QString StatusText; QString MimeType;
	qint64 Response_Length; int Status;
};
 class QCefGetResourceHandler :public CListener {
 public :
	 QCefGetResourceHandler() {
		 
	 }

	 ~QCefGetResourceHandler() {
		 qDebug() << "~QCefGetResourceHandler";
	 }
	 CEvent<QProcessRequestEventArgs&> ProcessRequestEvent = CEvent<QProcessRequestEventArgs&>();
	 CEvent<QGetResponseHeadersEventArgs&> GetResponseHeadersEvent = CEvent<QGetResponseHeadersEventArgs&>();
	 CEvent<QReadResponseEventArgs&> ReadResponseEvent = CEvent<QReadResponseEventArgs&>();
 };

 class QGefResourceEventArgs : public CEventArgs
 {
 public:
	 QGefResourceEventArgs() :CEventArgs(this) {}
	 QGefResourceEventArgs(QString url) :CEventArgs(this)
	 {
		 URL = url;
		 UseHandler = false;
	 }
	 ~QGefResourceEventArgs() {
		 qDebug() << "~QGetResourceEventArgs";
	 }
	 QString URL; bool UseHandler = false; const QCefGetResourceHandler* ResourceHandler;

	 const QCefGetResourceHandler* getResourceHandler() {
		 return ResourceHandler;
	 }
	 void setResourceHandler(const QCefGetResourceHandler* handler)
	 {
		 ResourceHandler = handler;
	 }
 };

 class QCefRequestHandler :public CListener {
 public:
	 CEvent<QGefResourceEventArgs&> GetResourceEvent;
 };