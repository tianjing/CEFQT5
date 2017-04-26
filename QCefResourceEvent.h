#pragma once
#ifndef QCEFRESOURCEEVENT_H
#define QCEFRESOURCEEVENT_H

#include <QEvent>
#include "qcefresourcehandler.h"


class QCefWebView_EXPORT QCefResourceEvent : public QEvent
{
public:
	static const QEvent::Type MessageEventType;
	QCefResourceEvent();
	QCefResourceEvent(const QString& url);
	~QCefResourceEvent();

	QString url() const;
	CefRefPtr<QCefResourceHandler> handler() const;
	void setHandler(const CefRefPtr<QCefResourceHandler>& handler) ;

private:
	QString url_;
	CefRefPtr<QCefResourceHandler> handler_;
};



#endif // QCEFRESOURCEEVENT_H
