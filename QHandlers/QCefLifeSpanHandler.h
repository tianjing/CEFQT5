#pragma once
#include "Delegate\DelegateExt.h"



class QCefLifeSpanHandler :public CListener {
public:
	CEvent<CEventArgs&> AfterCreatedEvent;
	CEvent<CEventArgs&> DoCloseEvent;
	CEvent<CEventArgs&> BeforeCloseEvent;

};