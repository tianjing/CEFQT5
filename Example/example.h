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

public slots:
	void action_2_triggered(bool is);
	void action_jstest_triggered(bool is);
	void action_framejs_triggered(bool is);
protected:
	virtual void closeEvent(QCloseEvent *event) override {
		//webview_->close();
		//webview_->~QCefWebView();
	}
private:
	void SetupUi();
	QCefWebView* webview_;
	Ui::ExampleClass ui; 
	QString DefaultUrl_ = "http://www.baidu.com";
};

#endif // EXAMPLE_H
