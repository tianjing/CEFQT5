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
	
}
void Example::SetupUi() {
	webview_ = new QCefWebView(this);
	webview_->load(QUrl(DefaultUrl_));
	CListenerAgent<Example, QGefResourceEventArgs&>* agent = new CListenerAgent<Example, QGefResourceEventArgs&>(this, &Example::OnGetResource);
	webview_->RequestHandler().GetResourceEvent += agent;
	
	CListenerAgent<Example, QAddressChangeEventArgs&>* agent1 = new CListenerAgent<Example, QAddressChangeEventArgs&>(this, &Example::OnAddressChange);
	webview_->DisplayHandler().AddressChangeEvent += agent1;

	CListenerAgent<Example, QTitleChangeEventArgs&>* agent2 = new CListenerAgent<Example, QTitleChangeEventArgs&>(this, &Example::OnTitleChange);
	webview_->DisplayHandler().TitleChangeEvent += agent2;

	
	this->setCentralWidget(webview_);
	
	connect (ui.action_2, SIGNAL(triggered(bool)),this ,SLOT(action_2_triggered(bool)) );
	connect(ui.action_test, SIGNAL(triggered(bool)), this, SLOT(action_jstest_triggered(bool)));
	connect(ui.action_framejs, SIGNAL(triggered(bool)), this, SLOT(action_framejs_triggered(bool)));
}
void Example::OnGetResource(QGefResourceEventArgs& args)
{
	qDebug() << "OnGetResource:"<< args.URL;
	if (args.URL != "")
	{
		args.UseHandler = true;
		args.setResourceHandler(new MysGetResourceHandler());
	}
}
void Example::action_2_triggered(bool is)
{
	Example * window = new Example();
	window->resize(1024, 768);
	window->show();
}

void Example::action_jstest_triggered(bool is)
{
	webview_->ExecuteJavaScript(QString("testindex();"));
}

void Example::action_framejs_triggered(bool is)
{
	webview_->ExecuteJavaScript(QString("fdafdas"),QString("test();"));
}