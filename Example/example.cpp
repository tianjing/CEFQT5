#include "stdafx.h"
#include "example.h"
#include "QCefClient.h"
#include "MysGetResourceHandler.h"
#include <QtWidgets/QMdiArea.h>
Example::Example(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->DefaultUrl_ = "file:///"+qApp->applicationDirPath()+ "/../www/index.html";
	SetupUi();
}

Example::~Example()
{
	//webview_->~QCefWebView();
}
void Example::SetupUi() {
	webview_ = new QCefWebView(this);
	webview_->load(QUrl(DefaultUrl_));
	CListenerAgent<Example, QGefResourceEventArgs&>* agent = new CListenerAgent<Example, QGefResourceEventArgs&>(this, &Example::OnGetResource);
	webview_->RequestHandler().GetResourceEvent += agent;
	this->setCentralWidget(webview_);
	
	connect (ui.action_2, SIGNAL(triggered(bool)),this ,SLOT(action_2_triggered(bool)) );
	connect(ui.action_test, SIGNAL(triggered(bool)), this, SLOT(action_jstest_triggered(bool)));

}
void Example::OnGetResource(QGefResourceEventArgs& args)
{
	qDebug() << "OnGetResource:"<< args.URL;
	if (args.URL == "")
	{
		args.UseHandler = true;
		args.setResourceHandler(new MysGetResourceHandler());
	}
}
void Example::action_2_triggered(bool is)
{
	Example * window = new Example();
	window->resize(1024, 768);
	//window->DefaultUrl_ = "http://127.0.0.1:8080/EmptyProject/platform/login.jsp";
	window->show();
}

void Example::action_jstest_triggered(bool is)
{
	webview_->ExecuteJavaScript("test();");
}