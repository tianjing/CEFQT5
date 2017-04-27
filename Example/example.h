#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QtWidgets/QMainWindow>
#include "ui_example.h"
#include "qcefwebview.h"

class Example : public QMainWindow
{
	Q_OBJECT

public:
	Example(QWidget *parent = 0);
	~Example();
	void OnGetResource(QGefResourceEventArgs& args);


private:
	void SetupUi();
	QCefWebView* webview_;
	Ui::ExampleClass ui;

};

#endif // EXAMPLE_H
