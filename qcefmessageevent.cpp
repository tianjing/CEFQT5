#include "stdafx.h"
#include "qcefmessageevent.h"

const QEvent::Type QCefMessageEvent::MessageEventType = static_cast<QEvent::Type>(QEvent::registerEventType());

QCefMessageEvent::QCefMessageEvent(const QString& name, const QVariantList& args) :
	QEvent(MessageEventType),
	name_(name),
	args_(args)
{

}

QCefMessageEvent::~QCefMessageEvent()
{

}

QString QCefMessageEvent::name() const
{
	return name_;
}

QVariantList QCefMessageEvent::args() const
{
	return args_;
}
