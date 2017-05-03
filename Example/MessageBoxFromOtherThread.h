#pragma once
#include <QtCore>
#include <QtWidgets>



class MessageBoxFromOtherThread : public QObject
{
	Q_OBJECT

private:
	const QString m_title;
	const QString m_message;

public:
	MessageBoxFromOtherThread(const QString &title, const QString &message) :
		m_title(title),
		m_message(message)

	{

	}

	static void show(const QString &title, const QString &message) {

		QEventLoop eventLoop;
		auto messageBox = new MessageBoxFromOtherThread(title, message);
		connect(messageBox, SIGNAL(destroyed()), &eventLoop, SLOT(quit()));
		messageBox->readyShow();
		eventLoop.exec();
	}

private:
	void readyShow(void) {

		this->moveToThread(qApp->thread());
		QTimer::singleShot(0, this, SLOT(onShow()));

	}

	private slots:
	void onShow(void) {

		QMessageBox::information(NULL, m_title, m_message);
		this->deleteLater();


	}
};

