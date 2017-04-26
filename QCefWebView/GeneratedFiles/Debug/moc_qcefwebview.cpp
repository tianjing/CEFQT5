/****************************************************************************
** Meta object code from reading C++ file 'QCefWebView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "stdafx.h"
#include "../../../QCefWebView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QCefWebView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_QCefWebView_t {
    QByteArrayData data[20];
    char stringdata0[187];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QCefWebView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QCefWebView_t qt_meta_stringdata_QCefWebView = {
    {
QT_MOC_LITERAL(0, 0, 11), // "QCefWebView"
QT_MOC_LITERAL(1, 12, 12), // "titleChanged"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 5), // "title"
QT_MOC_LITERAL(4, 32, 10), // "urlChanged"
QT_MOC_LITERAL(5, 43, 3), // "url"
QT_MOC_LITERAL(6, 47, 11), // "loadStarted"
QT_MOC_LITERAL(7, 59, 12), // "loadFinished"
QT_MOC_LITERAL(8, 72, 2), // "ok"
QT_MOC_LITERAL(9, 75, 15), // "navStateChanged"
QT_MOC_LITERAL(10, 91, 9), // "canGoBack"
QT_MOC_LITERAL(11, 101, 12), // "canGoForward"
QT_MOC_LITERAL(12, 114, 11), // "getResource"
QT_MOC_LITERAL(13, 126, 18), // "QCefResourceEvent&"
QT_MOC_LITERAL(14, 145, 1), // "e"
QT_MOC_LITERAL(15, 147, 4), // "back"
QT_MOC_LITERAL(16, 152, 7), // "forward"
QT_MOC_LITERAL(17, 160, 6), // "reload"
QT_MOC_LITERAL(18, 167, 4), // "stop"
QT_MOC_LITERAL(19, 172, 14) // "RequestHandler"

    },
    "QCefWebView\0titleChanged\0\0title\0"
    "urlChanged\0url\0loadStarted\0loadFinished\0"
    "ok\0navStateChanged\0canGoBack\0canGoForward\0"
    "getResource\0QCefResourceEvent&\0e\0back\0"
    "forward\0reload\0stop\0RequestHandler"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QCefWebView[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       6,    0,   75,    2, 0x06 /* Public */,
       7,    1,   76,    2, 0x06 /* Public */,
       9,    2,   79,    2, 0x06 /* Public */,
      12,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    0,   87,    2, 0x0a /* Public */,
      16,    0,   88,    2, 0x0a /* Public */,
      17,    0,   89,    2, 0x0a /* Public */,
      18,    0,   90,    2, 0x0a /* Public */,
      19,    0,   91,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QUrl,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,   10,   11,
    QMetaType::Void, 0x80000000 | 13,   14,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QCefWebView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QCefWebView *_t = static_cast<QCefWebView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->titleChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->urlChanged((*reinterpret_cast< const QUrl(*)>(_a[1]))); break;
        case 2: _t->loadStarted(); break;
        case 3: _t->loadFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->navStateChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 5: _t->getResource((*reinterpret_cast< QCefResourceEvent(*)>(_a[1]))); break;
        case 6: _t->back(); break;
        case 7: _t->forward(); break;
        case 8: _t->reload(); break;
        case 9: _t->stop(); break;
        case 10: _t->RequestHandler(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (QCefWebView::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCefWebView::titleChanged)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (QCefWebView::*_t)(const QUrl & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCefWebView::urlChanged)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (QCefWebView::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCefWebView::loadStarted)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (QCefWebView::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCefWebView::loadFinished)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (QCefWebView::*_t)(bool , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCefWebView::navStateChanged)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (QCefWebView::*_t)(QCefResourceEvent & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&QCefWebView::getResource)) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject QCefWebView::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_QCefWebView.data,
      qt_meta_data_QCefWebView,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *QCefWebView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QCefWebView::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_QCefWebView.stringdata0))
        return static_cast<void*>(const_cast< QCefWebView*>(this));
    if (!strcmp(_clname, "QCefClientHandler::Listener"))
        return static_cast< QCefClientHandler::Listener*>(const_cast< QCefWebView*>(this));
    return QWidget::qt_metacast(_clname);
}

int QCefWebView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void QCefWebView::titleChanged(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void QCefWebView::urlChanged(const QUrl & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void QCefWebView::loadStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void QCefWebView::loadFinished(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void QCefWebView::navStateChanged(bool _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void QCefWebView::getResource(QCefResourceEvent & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_END_MOC_NAMESPACE
