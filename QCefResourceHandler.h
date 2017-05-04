#pragma once
#ifndef QCEFRESOURCEHANDLER_H
#define QCEFRESOURCEHANDLER_H

#include "stdafx.h"
#include <include/wrapper/cef_resource_manager.h>
#include <include/cef_base.h>
#include <QHandlers\QCefRequestHandler.h>
class QCefWebView_EXPORT QCefResourceHandler :public CefResourceHandler {
public:
	QCefResourceHandler(const QString& url,const QCefGetResourceHandler* ResourceHandler) {
		url_ = url;
		ResourceHandler_ = const_cast<QCefGetResourceHandler*>(ResourceHandler);

	};
	virtual ~QCefResourceHandler() { qDebug() << "~QCefResourceHandler()"; };
	virtual bool ProcessRequest(CefRefPtr<CefRequest> request,
		CefRefPtr<CefCallback> callback)OVERRIDE {
		qDebug() << "ProcessRequest";
		
		QProcessRequestEventArgs args = QProcessRequestEventArgs(new QCefRequest(request),new QCefCallback(callback));

		ResourceHandler_->ProcessRequestEvent(args);
		return args.ReturnValue;
	};


	virtual void GetResponseHeaders(CefRefPtr<CefResponse> response,
		int64& response_length,
		CefString& redirectUrl) OVERRIDE {
		qDebug() << "GetResponseHeaders";
		QGetResponseHeadersEventArgs args = QGetResponseHeadersEventArgs(new QCefResponse(response));
		ResourceHandler_->GetResponseHeadersEvent(args);

		if ("" != args.RedirectUrl)
		{
			redirectUrl = CefString(args.RedirectUrl.toStdWString());
		}
		response_length = args.Response_Length;
		qDebug() << QCefUtil::ToString( response->GetMimeType());
		qDebug() << response->GetStatus();
	};

	virtual bool ReadResponse(void* data_out,
		int bytes_to_read,
		int& bytes_read,
		CefRefPtr<CefCallback> callback)OVERRIDE {
		
		qDebug() << "ReadResponse:"<<url_; 
		QReadResponseEventArgs args = QReadResponseEventArgs(new QCefCallback(callback));
		ResourceHandler_->ReadResponseEvent(args);

		if (args.ReturnValue)
		{
			QByteArray bytes = args.Data_Out;
			bytes_read = bytes.length();
			memcpy(data_out, bytes.constData(), bytes_read);
			return true;
		}
		return false;
	
	};

	virtual void Cancel()OVERRIDE {};



private:
	QCefGetResourceHandler* ResourceHandler_;
	QString url_;

	IMPLEMENT_REFCOUNTING(QCefResourceHandler);
};
#endif // QCEFRESOURCEHANDLER_H