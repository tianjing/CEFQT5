#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <QtWidgets/QMainWindow>
#include "ui_example.h"
#include "qcefwebview.h"
#include <QtConcurrent/QtConcurrent>
#include "MessageBoxFromOtherThread.h"

class Example : public QMainWindow
{
	Q_OBJECT

public:
	Example(QWidget *parent = 0);
	
	~Example();
	void ShowMessage(QString p_Text) {
		MessageBoxFromOtherThread::show(QString::fromLocal8Bit("ÌבÊ¾"), p_Text);
	}

	void OnGetResource(QGefResourceEventArgs& args);
	void OnAddressChange(QAddressChangeEventArgs& args) {
		//this do not blocking thread 
		qDebug() << "OnAddressChange";
		QString dd = "OnAddressChange";
		QtConcurrent::run([this,dd](){
			Example::ShowMessage(dd);
		});
		
	}
	void OnTitleChange(QTitleChangeEventArgs& args) {
		//this do not blocking thread
		qDebug() << "OnTitleChange";
		QString dd = "OnTitleChange";
		QtConcurrent::run([this, dd]() {
			Example::ShowMessage(dd);
		});
	}

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
