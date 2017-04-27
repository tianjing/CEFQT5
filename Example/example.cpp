#include "stdafx.h"
#include "example.h"
#include "QCefClient.h"
#include "MysGetResourceHandler.h"
Example::Example(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	SetupUi();
}

Example::~Example()
{

}
QString url = "http://localhost:8080/EmptyProject/platform/login.jsp";
void Example::SetupUi() {
	webview_ = new QCefWebView(this);
	webview_->load(QUrl(url));
	CListenerAgent<Example, QGefResourceEventArgs&>* agent = new CListenerAgent<Example, QGefResourceEventArgs&>(this, &Example::OnGetResource);
	webview_->RequestHandler().GetResourceEvent += agent;
	this->setCentralWidget(webview_);
}
void Example::OnGetResource(QGefResourceEventArgs& args)
{
	qDebug() << "OnGetResource:"<< args.URL;
	if (args.URL == url)
	{
		args.UseHandler = true;
		args.setResourceHandler(new MysGetResourceHandler());
	}
}
