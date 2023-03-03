/****************************************************************************
** Meta object code from reading C++ file 'whatsprog_thread.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../whatsprog_thread.h"
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'whatsprog_thread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
namespace {
struct qt_meta_stringdata_WhatsProg_Thread_t {
    uint offsetsAndSizes[24];
    char stringdata0[17];
    char stringdata1[22];
    char stringdata2[1];
    char stringdata3[22];
    char stringdata4[24];
    char stringdata5[16];
    char stringdata6[12];
    char stringdata7[2];
    char stringdata8[14];
    char stringdata9[13];
    char stringdata10[17];
    char stringdata11[18];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_WhatsProg_Thread_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_WhatsProg_Thread_t qt_meta_stringdata_WhatsProg_Thread = {
    {
        QT_MOC_LITERAL(0, 16),  // "WhatsProg_Thread"
        QT_MOC_LITERAL(17, 21),  // "signExibeNovaMensagem"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 21),  // "signExibeNovaConversa"
        QT_MOC_LITERAL(62, 23),  // "signReexibeMensRecebida"
        QT_MOC_LITERAL(86, 15),  // "signReexibeErro"
        QT_MOC_LITERAL(102, 11),  // "std::string"
        QT_MOC_LITERAL(114, 1),  // "S"
        QT_MOC_LITERAL(116, 13),  // "signErroSalva"
        QT_MOC_LITERAL(130, 12),  // "signEncerrar"
        QT_MOC_LITERAL(143, 16),  // "slotIniciaThread"
        QT_MOC_LITERAL(160, 17)   // "slotEncerraThread"
    },
    "WhatsProg_Thread",
    "signExibeNovaMensagem",
    "",
    "signExibeNovaConversa",
    "signReexibeMensRecebida",
    "signReexibeErro",
    "std::string",
    "S",
    "signErroSalva",
    "signEncerrar",
    "slotIniciaThread",
    "slotEncerraThread"
};
#undef QT_MOC_LITERAL
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_WhatsProg_Thread[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   62,    2, 0x06,    1 /* Public */,
       3,    0,   63,    2, 0x06,    2 /* Public */,
       4,    0,   64,    2, 0x06,    3 /* Public */,
       5,    1,   65,    2, 0x06,    4 /* Public */,
       8,    1,   68,    2, 0x06,    6 /* Public */,
       9,    0,   71,    2, 0x06,    8 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
      10,    0,   72,    2, 0x0a,    9 /* Public */,
      11,    0,   73,    2, 0x0a,   10 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject WhatsProg_Thread::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WhatsProg_Thread.offsetsAndSizes,
    qt_meta_data_WhatsProg_Thread,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_WhatsProg_Thread_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<WhatsProg_Thread, std::true_type>,
        // method 'signExibeNovaMensagem'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'signExibeNovaConversa'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'signReexibeMensRecebida'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'signReexibeErro'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string, std::false_type>,
        // method 'signErroSalva'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const std::string, std::false_type>,
        // method 'signEncerrar'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotIniciaThread'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'slotEncerraThread'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void WhatsProg_Thread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WhatsProg_Thread *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signExibeNovaMensagem(); break;
        case 1: _t->signExibeNovaConversa(); break;
        case 2: _t->signReexibeMensRecebida(); break;
        case 3: _t->signReexibeErro((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 4: _t->signErroSalva((*reinterpret_cast< std::add_pointer_t<std::string>>(_a[1]))); break;
        case 5: _t->signEncerrar(); break;
        case 6: _t->slotIniciaThread(); break;
        case 7: _t->slotEncerraThread(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WhatsProg_Thread::*)();
            if (_t _q_method = &WhatsProg_Thread::signExibeNovaMensagem; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WhatsProg_Thread::*)();
            if (_t _q_method = &WhatsProg_Thread::signExibeNovaConversa; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WhatsProg_Thread::*)();
            if (_t _q_method = &WhatsProg_Thread::signReexibeMensRecebida; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WhatsProg_Thread::*)(const std::string );
            if (_t _q_method = &WhatsProg_Thread::signReexibeErro; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WhatsProg_Thread::*)(const std::string );
            if (_t _q_method = &WhatsProg_Thread::signErroSalva; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WhatsProg_Thread::*)();
            if (_t _q_method = &WhatsProg_Thread::signEncerrar; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 5;
                return;
            }
        }
    }
}

const QMetaObject *WhatsProg_Thread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WhatsProg_Thread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WhatsProg_Thread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WhatsProg_Thread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void WhatsProg_Thread::signExibeNovaMensagem()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WhatsProg_Thread::signExibeNovaConversa()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WhatsProg_Thread::signReexibeMensRecebida()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WhatsProg_Thread::signReexibeErro(const std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void WhatsProg_Thread::signErroSalva(const std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void WhatsProg_Thread::signEncerrar()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
