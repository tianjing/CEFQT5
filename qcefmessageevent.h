#ifndef QCEFMESSAGEEVENT_H
#define QCEFMESSAGEEVENT_H

#include <QEvent>

class QCefMessageEvent : public QEvent
{
public:
	static const QEvent::Type MessageEventType;

	QCefMessageEvent(const QString & name, const QVariantList & args);
	~QCefMessageEvent();

	QString name() const;
	QVariantList args() const;

private:
	QString name_;
	QVariantList args_;	
};

#endif // QCEFMESSAGEEVENT_H
