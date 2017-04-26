#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QtWidgets/QMainWindow>
#include "qcefresourceevent.h"
#include "ui_example.h"
#include "qcefwebview.h"

class Example : public QMainWindow
{
	Q_OBJECT

public:
	Example(QWidget *parent = 0);
	~Example();
	void OnGetResource(QGetResourceEventArgs& args);
	void OnProcessRequest(QProcessRequestEventArgs& args);
	void OnGetResponseHeaders(QGetResponseHeadersEventArgs& args);
	void OnReadResponse(QReadResponseEventArgs& args);

private:
	void SetupUi();
	QCefWebView* webview_;
	Ui::ExampleClass ui;

};

#endif // EXAMPLE_H
