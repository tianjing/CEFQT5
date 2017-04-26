#include "stdafx.h"
#include "example.h"
#include "QCefClient.h"

Example::Example(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	SetupUi();
}

Example::~Example()
{

}
void Example::SetupUi() {
	webview_ = new QCefWebView(this);
	CListenerAgent<Example, QGetResourceEventArgs&>* agent = new CListenerAgent<Example, QGetResourceEventArgs&>(this, &Example::OnGetResource);
	webview_->RequestHandler().GetResource += agent;
	this->setCentralWidget(webview_);
}
void Example::OnGetResource(QGetResourceEventArgs& args)
{
	qDebug() << "OnGetResource:"<< args.URL;
	if (args.URL == "http://www.baidu.com/")
	{
		args.UseHandler = true;
		args.ResourceHandler.ProcessRequest += new CListenerAgent<Example, QProcessRequestEventArgs&>(this, &Example::OnProcessRequest);
		args.ResourceHandler.GetResponseHeaders += new CListenerAgent<Example, QGetResponseHeadersEventArgs&>(this, &Example::OnGetResponseHeaders);
		args.ResourceHandler.ReadResponse += new CListenerAgent<Example, QReadResponseEventArgs&>(this, &Example::OnReadResponse);
	
	}
}
//CefRefPtr<QCefResourceHandler> hander(new QCefResourceHandler);
void  Example::OnReadResponse(QReadResponseEventArgs& args)
{
	qDebug() << "OnGetResource:" << args.URL;
	std::string data = "<html><body><h1>Hello CEF</h1></body></html>";
	args.Bytes_Read = data.length();
	memcpy(args.Data_Out, data.c_str(), data.length());
	
	args.ReturnValue = true;
}
void  Example::OnProcessRequest(QProcessRequestEventArgs& args)
{
	args.UseContinue = true;
	args.ReturnValue = true;
}
void  Example::OnGetResponseHeaders(QGetResponseHeadersEventArgs& args)
{
	args.Response_Length = -1;
	args.MimeType = "text/html";
	args.Status = 200;

}