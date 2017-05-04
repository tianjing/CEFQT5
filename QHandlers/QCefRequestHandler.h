#pragma once
#include "Delegate\DelegateExt.h"
#include "QEntity.h"
class QReadResponseEventArgs : public CEventArgs
{
public:
	QReadResponseEventArgs(const QCefCallback* p_Callback) :CEventArgs(this) {
		Callback = const_cast<QCefCallback*>(p_Callback);
		Data_Out = NULL;
		Bytes_To_Read = 0;

	}
	~QReadResponseEventArgs() {
		qDebug() << "~QReadResponseEventArgs()";
	}
	QString URL;
	QByteArray Data_Out; int Bytes_To_Read;
	bool ReturnValue;
	QCefCallback* Callback;
 };

class QProcessRequestEventArgs : public CEventArgs
{
public:
	QProcessRequestEventArgs(const QCefRequest* p_QRequest, const QCefCallback* p_QCefCallback) :CEventArgs(this) {
		Callback = const_cast<QCefCallback*>(p_QCefCallback);
		Request = const_cast<QCefRequest*>(p_QRequest);
		ReturnValue = false;
	}

	~QProcessRequestEventArgs() {
		qDebug() << "~QProcessRequestEventArgs()";
	}
	bool ReturnValue;
	QCefRequest* Request;
	QCefCallback* Callback;
};
class QGetResponseHeadersEventArgs : public CEventArgs
{
public:
	QGetResponseHeadersEventArgs(const QCefResponse* p_Response) :CEventArgs(this)
	{
		Response = const_cast<QCefResponse*>(p_Response);
	}

	~QGetResponseHeadersEventArgs() {
		qDebug() << "~QGetResponseHeadersEventArgs()";
	}
	QString RedirectUrl;
	qint64 Response_Length; 
	QCefResponse* Response;
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
		 qDebug() << "~QGetResourceEventArgs()";
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