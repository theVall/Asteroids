/****************************************************************************
** Meta object code from reading C++ file 'RenderFrame.hpp'
**
** Created:
**      by: The Qt Meta Object Compiler version 62 (Qt 4.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "view/RenderFrame.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RenderFrame.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RenderFrame[] = {

 // content:
       4,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x0a,
      30,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_RenderFrame[] = {
    "RenderFrame\0\0callPlayerName()\0"
    "setAccepted()\0"
};

const QMetaObject RenderFrame::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_RenderFrame,
      qt_meta_data_RenderFrame, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RenderFrame::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RenderFrame::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RenderFrame::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RenderFrame))
        return static_cast<void*>(const_cast< RenderFrame*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int RenderFrame::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: callPlayerName(); break;
        case 1: setAccepted(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
