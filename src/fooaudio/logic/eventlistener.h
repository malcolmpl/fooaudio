/*********************************************************************************
* Copyright (c) 2009 Dariusz Mikulski <dariusz.mikulski@gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
**********************************************************************************/

#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <QEvent>
#include <QObject>
#include <QSharedPointer>

#include "applicationlogic.h"

class DefaultQObjectClass : public QObject
{
    Q_OBJECT
};

class BaseEventProcessor
{
protected:
    bool Event(QEvent *)
    {
        return false;
    }
};

template <class T1, class T2>
class EventProcessor : public T2
{
public:
    virtual ~EventProcessor() {}

protected:
    virtual bool Event(QEvent *event)
    {
        T1 *e = dynamic_cast<T1 *>(event);
        if(e)
        {
            this->handleEvent(e);
            return true;
        }
        return T2::Event(event);
    }

    virtual void handleEvent(T1 *event) = 0;
};

template <typename E>
class EventListener : public DefaultQObjectClass, public E
{
public:
    EventListener()
    {
        QObject *o = dynamic_cast<QObject*>(this);
        if(o)
        {
            o->installEventFilter(o);
        }
    }

    bool eventFilter(QObject *, QEvent *e)
    {
        return EventListener::Event(e);
    }
};

template <typename E>
class EventListener1 : public EventListener<EventProcessor<E, BaseEventProcessor> >
{
};

template <typename E1, typename E2>
class EventListener2 : public EventListener<EventProcessor<E1, EventProcessor<E2, BaseEventProcessor> > >
{
};

template <class T1>
class Event : public QEvent
{
    T1 m_type1;
public:
    Event(const Event &e) : QEvent(QEvent::User)
    {
        m_type1 = e;
    }

    Event(T1 t1) : QEvent(QEvent::User)
    {
        m_type1 = t1;
    }

    T1 type1()
    {
        return m_type1;
    }
};

template <class T1, class T2>
class Event2 : public QEvent
{
    T1 m_type1;
    T2 m_type2;
public:
    Event2(const Event2 &e) : QEvent(QEvent::User)
    {
        m_type1 = e;
    }

    Event2(T1 t1, T2 t2) : QEvent(QEvent::User)
    {
        m_type1 = t1;
        m_type2 = t2;
    }

    T1 type1() { return m_type1; }
    T2 type2() { return m_type2; }
};

#define CreateEvent(NAME, T1) class NAME : public Event<T1> { public: NAME(T1 t1) : Event<T1>(t1) {} };
#define CreateEvent2(NAME, T1, T2) class NAME : public Event2<T1, T2> { public: NAME(T1 t1, T2 t2) : Event2<T1, T2>(t1, t2) {} };

#define PostEvent(CONTROLLER, EVENT) \
{ \
    QObject *o = qobject_cast<QObject *>(ApplicationLogic::getInstance()->getController(QString(#CONTROLLER))); \
    QApplication::postEvent(o, EVENT); \
}

#endif // EVENTLISTENER_H
