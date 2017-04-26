#pragma once
#include "Delegate\DelegateExt.h"
class QReadResponseEventArgs : public CEventArgs
{
public:
	QReadResponseEventArgs(QString url) :CEventArgs(this) {
		URL = url;
		Data_Out = NULL;
		Bytes_To_Read = 0;
		Bytes_Read = 0;
		UseContinue = false;
		UseCancel = false;
	}
	~QReadResponseEventArgs() {}
	QString URL;
	void* Data_Out; int Bytes_To_Read; int Bytes_Read; 
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
 class QCefGetResourceHandler {
 public :
	 QCefGetResourceHandler() {
		 
	 }

	 ~QCefGetResourceHandler() {}
	 CEvent<QProcessRequestEventArgs&> ProcessRequest = CEvent<QProcessRequestEventArgs&>();
	 CEvent<QGetResponseHeadersEventArgs&> GetResponseHeaders = CEvent<QGetResponseHeadersEventArgs&>();
	 CEvent<QReadResponseEventArgs&> ReadResponse = CEvent<QReadResponseEventArgs&>();
 };


 class QGetResourceEventArgs : public CEventArgs
 {
 public:
	 QGetResourceEventArgs() :CEventArgs(this) {}
	 QGetResourceEventArgs(QString url) :CEventArgs(this)
	 {
		 URL = url;
		 UseHandler = false;
	 }
	 ~QGetResourceEventArgs() {
		 qDebug() << "~QGetResourceEventArgs";
	 }
	 QString URL; bool UseHandler = false; QCefGetResourceHandler& ResourceHandler = QCefGetResourceHandler();

	 QCefGetResourceHandler getResourceHandler() {
		 return ResourceHandler;
	 }
 };

 class QCetRequestHandler {
 public:
	 CEvent<QGetResourceEventArgs&> GetResource;
 };