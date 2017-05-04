#pragma once
#include "stdafx.h"
#include <QHandlers\QCefRequestHandler.h>
class MysGetResourceHandler :public QCefGetResourceHandler {
public:
	MysGetResourceHandler():QCefGetResourceHandler(){
		angetReadResponse_ = new CListenerAgent<MysGetResourceHandler, QReadResponseEventArgs&>(this, &MysGetResourceHandler::OnReadResponse);
		angetProcessReques_ = new CListenerAgent<MysGetResourceHandler, QProcessRequestEventArgs&>(this, &MysGetResourceHandler::OnProcessRequest);
		angetGetResponseHeaders_ = new CListenerAgent<MysGetResourceHandler, QGetResponseHeadersEventArgs&>(this, &MysGetResourceHandler::OnGetResponseHeaders);


		this->ReadResponseEvent += angetReadResponse_;
		this->ProcessRequestEvent += angetProcessReques_;
		this->GetResponseHeadersEvent += angetGetResponseHeaders_;
	}
	~MysGetResourceHandler()
	{
		qDebug() << "~MysGetResourceHandler()";
		this->ReadResponseEvent -= angetReadResponse_;
		this->ProcessRequestEvent -= angetProcessReques_;
		this->GetResponseHeadersEvent -= angetGetResponseHeaders_;
	}

	CListenerAgent<MysGetResourceHandler, QReadResponseEventArgs&>*angetReadResponse_;
	CListenerAgent<MysGetResourceHandler, QProcessRequestEventArgs&>*angetProcessReques_;
	CListenerAgent<MysGetResourceHandler, QGetResponseHeadersEventArgs&>*angetGetResponseHeaders_;
	int ReadResponsecount = 0;

	void OnReadResponse(QReadResponseEventArgs& args) 
	{
		if (ReadResponsecount == 0) {
			qDebug() << "OnReadResponse:" << args.URL;
			std::string data = "<html><body><h1>Hello CEF</h1></body></html>";
			void* datad;

			args.Data_Out = QByteArray(data.c_str());
			args.ReturnValue = true;
			ReadResponsecount++;
		}
		else
		{
			args.ReturnValue = false;
		}
	}
	void  OnProcessRequest(QProcessRequestEventArgs& args)	{
		qDebug() << "OnProcessRequest:"<< args.Request->GetURL();
		args.Callback->Continue();
		args.ReturnValue = true;
	}
	void OnGetResponseHeaders(QGetResponseHeadersEventArgs& args)
	{
		qDebug() << "OnGetResponseHeaders()";
		args.Response_Length = -1;
		args.Response->SetMimeType("text/html");
		args.Response->SetStatus(200);
		
	}


};