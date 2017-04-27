#pragma once
#include "Delegate\DelegateExt.h"
class QAddressChangeEventArgs : public CEventArgs
{
public:
	QAddressChangeEventArgs(QString& url) :CEventArgs(this) {
		URL = url;
	}
	~QAddressChangeEventArgs() {}
	QString URL;
};
class QTitleChangeEventArgs : public CEventArgs
{
public:
	QTitleChangeEventArgs(QString& title) :CEventArgs(this) {
		Title = title;
	}
	~QTitleChangeEventArgs() {}
	QString Title;
};

class QCefDisplayHandler:public CListener{
public:
	CEvent<QAddressChangeEventArgs&> AddressChangeEvent;
	CEvent<QTitleChangeEventArgs&> TitleChangeEvent;
};

