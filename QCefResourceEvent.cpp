#include "stdafx.h"
#include"QCefResourceEvent.h"
#include <QMetaType>

const QEvent::Type QCefResourceEvent::MessageEventType = static_cast<QEvent::Type>(QEvent::registerEventType());

QCefResourceEvent::QCefResourceEvent() :QEvent(MessageEventType) {
	handler_ = CefRefPtr<QCefResourceHandler>();
}
QCefResourceEvent::QCefResourceEvent(const QString & url) :
	QEvent(MessageEventType),url_(url){
	handler_ = CefRefPtr<QCefResourceHandler>();
}
QCefResourceEvent::~QCefResourceEvent() {
}

QString QCefResourceEvent::url() const {
	return url_;
}
CefRefPtr<QCefResourceHandler> QCefResourceEvent::handler()const {
	return handler_;
}
void QCefResourceEvent::setHandler(const CefRefPtr<QCefResourceHandler>& handler)  {
	handler_ = handler;
}