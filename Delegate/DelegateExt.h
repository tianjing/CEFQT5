#pragma once

#include <list>
#include <iostream>
using namespace std;

/*Declaration*/

template<typename ArgsT>
class CEvent;

/*A sample arguments class*/
class CEventArgs
{
private:
	void* _args;
public:
	CEventArgs(void* args)
	{
		_args = args;
	};

	void* GetArgs()
	{
		return _args;
	}
};

/*
The responsibility of ICallback interface is to Dispose
*/
class IDispose
{
public:
	/*Dispose, free memory*/
	virtual void Dispose() = 0;
};

/*The responsibility of IListener interface is to add ICallback into
CListener which implement this interface.*/
class IListener
{
public:
	/*Add ICallback*/
	virtual void AddListenerCallback(IDispose* agent) = 0;
	/*When CListener is disposed, it will notify this event to all ICallback which has been added*/
	virtual void NotifyDispose() = 0;
	/*Remove the IDispose from list*/
	virtual void Remove(IDispose* agent) = 0;
};

/*
The responsibility of IListenerAgent is:
1.When event has been fired, notify the listener to execute the event handler which has been subscribed
2.When CListenerAgent is being subscribed on event, set the event instance
*/
template<typename ArgsT>
class IListenerAgent : virtual public IDispose
{
public:
	/*Fire the event*/
	virtual void Fire(ArgsT) = 0;
	/*Set the event instance*/
	virtual void SetEventCallback(CEvent<ArgsT>* pEvent) = 0;
};


/*
This class help Observer class to manage the CListenerAgent class which subscribe to CEvent
Since CListener is inherited by user's observer class, so when initialize the CListenerAgent,
CListenerAgent will call IListener->AddListenerCallback(this), to register itself to CListener.
When CListener's destructor is called, it will notify all CListenerAgent that it managed to
dispose themselves

Note: User's observer class must inherit from this class if it want to be listenable.
*/
class CListener : public IListener
{
private:
	list<IDispose *> _agents;
public:
	CListener()
	{
	}

	virtual ~CListener()
	{
		NotifyDispose();
	};

private:

	/*IListener*/

	/*Add ICallback(CListenerAgent) and manage them*/
	virtual void AddListenerCallback(IDispose* agent)
	{
		if (agent != NULL)
		{
			_agents.push_back(agent);
		}
	}

	/*When destructor, notify all ICallback(CListenerAgent) to dispose themselves*/
	virtual void NotifyDispose()
	{
		list<IDispose*>::iterator it, end;
		IDispose* temp;

		it = _agents.begin();
		end = _agents.end();

		for (it; it != end; )
		{
			temp = *it;
			it++;
			temp->Dispose();
		}
	}

	/*Remove the agent from list*/
	virtual void Remove(IDispose* agent)
	{
		_agents.remove(agent);
	}
};

/*
The core class.This class set up a link between CEvent and CListener.
This class implement IListenerAgent<ArgsT> and ICallback
*/
template<typename ObserverT, typename ArgsT>
class CListenerAgent : virtual public IListenerAgent<ArgsT>
{

private:
	/*The type of observer's handler which is to handle the event when event arise*/
	typedef void (ObserverT::*ObserverDelegate)(ArgsT);

	/*Two function pointers*/
	ObserverDelegate _pObserverDelegate;

	/*CListenerAgent keep these pointer to keep the contact between CEvent and observer*/
	/*These two pointers point to the same memory area, of course, their value may not be equal.*/
	ObserverT* _pObserver;
	IListener* _pListener;

	/*This point to the event instance which subscribe on*/
	CEvent<ArgsT>* _pEvent;
public:
	/*Default Constructor*/
	CListenerAgent()
	{
		_pEvent = NULL;
		_pObserverDelegate = NULL;
		_pObserver = NULL;
	}

	/*Constructor*/
	CListenerAgent(ObserverT* observer, ObserverDelegate d)
	{
		_pObserver = observer;
		_pListener = (IListener*)_pObserver;
		_pObserverDelegate = d;
		_pEvent = NULL;

		/*Register itself to CListener,*/
		_pListener->AddListenerCallback((IDispose*)this);
	}


private:

	/*Destructor.Notify the CEvent to remove itself from the list*/
	virtual ~CListenerAgent()
	{
		/*remove the agent from event*/
		if (_pEvent != NULL)
		{
			(*_pEvent) -= ((IListenerAgent<ArgsT>*)this);
		}

		/*remove the agent from listener*/
		if (_pListener != NULL)
		{
			_pListener->Remove((IDispose*)this);
		}
	}

	/*IListenerAgent*/
	/*Notify the observer to handle the event*/
	virtual void Fire(ArgsT args)
	{
		if (_pObserver != NULL)
		{
			(_pObserver->*_pObserverDelegate)(args);
		}
	}

	/*Keep the CEvent instance*/
	void SetEventCallback(CEvent<ArgsT>* pEvent)
	{
		_pEvent = pEvent;
	}

	/*IDispose*/
	virtual void Dispose()
	{
		delete this;
	}
};

/*
CEvent class has 3 responsibility:
1.Provide the friendly operator like C#
2.When event arise, notify all listeners
3.When disposed, notify all CListenerAgent
*/
template<typename ArgsT>
class CEvent
{
private:
	/*Class member handler type, use IListenerAgent to complete the work*/
	typedef IListenerAgent<ArgsT>* Listener;
	/*Global or static handler type*/
	typedef void(*StaticListener)(ArgsT);

	/*Hold all class member handlers in a list*/
	list<Listener> _listeners;
	/*Hold all global or static handlers in a list*/
	list<StaticListener> _staticListeners;

public:
	/*Default constructor*/
	CEvent()
	{
	}

	/*Default destructor*/
	virtual ~CEvent()
	{
		qDebug() << "~CEvent()";
		list<Listener>::iterator it, end;

		Listener temp;

		it = _listeners.begin();
		end = _listeners.end();

		for (it; it != end;)
		{
			temp = *it;
			it++;

			((IDispose*)temp)->Dispose();
		}

		_listeners.clear();
		_staticListeners.clear();
	}

	/*Subscribe class member listener*/
	void operator+=(const Listener listener)
	{
		Subscribe(listener);
	};
	void operator=(CEvent& cevent)
	{
		list<Listener>::iterator  it, end;
		
		it = cevent._listeners.begin();
		end = cevent._listeners.end();
		
		for (it; it != end; it++)
		{
			this->Subscribe(*it);
		}
		cevent._listeners.clear();

		list<StaticListener>::iterator  it1, end1;
		it1 = cevent._staticListeners.begin();
		end1 = cevent._staticListeners.end();

		for (it1; it1 != end1; it1++)
		{
			this->Subscribe(*it1);
		}
	}
	/*Subscribe global or static listener*/
	void operator+=(const StaticListener listener)
	{
		Subscribe(listener);
	}

	/*Unsubscribe class member listener*/
	void operator-=(const Listener listener)
	{
		Unsubscribe(listener);
	};

	/*Unsubscribe class member listener*/
	void operator-=(const StaticListener listener)
	{
		Unsubscribe(listener);
	}

	/*Fire the event*/
	void operator()(ArgsT args)
	{
		FireEvent(args);
	}

private:

	/*Unsubscribe the listener if be found in list*/
	void Unsubscribe(Listener listener)
	{
		_listeners.remove(listener);
	}

	/*Unsubscribe the listener if be found in list*/
	void Unsubscribe(StaticListener listener)
	{
		_staticListeners.remove(listener);
	}

	/*Fire the event*/
	void FireEvent(ArgsT args)
	{
		list<Listener>::iterator it, end;

		it = _listeners.begin();
		end = _listeners.end();

		for (it; it != end; it++)
		{
			((Listener)*it)->Fire(args);
		}

		list<StaticListener>::iterator it2, end2;

		it2 = _staticListeners.begin();
		end2 = _staticListeners.end();

		for (it2; it2 != end2; it2++)
		{
			(*it2)(args);
		}
	}

	/*Subscribe the listener if not be found in list*/
	void Subscribe(Listener listener)
	{
		if (listener != NULL)
		{
			list<Listener>::iterator it, end;

			it = _listeners.begin();
			end = _listeners.end();
			
			for (it; it != end; it++)
			{
				if ((*it) == listener)
				{
					return;
				}
			}

			listener->SetEventCallback(this);
			_listeners.push_back(listener);
		}
	};

	/*Subscribe the listener if not be found in list*/
	void Subscribe(StaticListener listener)
	{
		if (listener != NULL)
		{
			list<StaticListener>::iterator it, end;

			it = _staticListeners.begin();
			end = _staticListeners.end();

			for (it; it != end; it++)
			{
				if ((*it) == listener)
				{
					return;
				}
			}

			_staticListeners.push_back(listener);
		}
	};
};