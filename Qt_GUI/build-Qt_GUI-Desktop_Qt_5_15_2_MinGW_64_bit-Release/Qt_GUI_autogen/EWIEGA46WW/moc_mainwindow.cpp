/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../Qt_GUI/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[23];
    char stringdata0[357];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "button_inst"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "inst"
QT_MOC_LITERAL(4, 29, 14), // "update_message"
QT_MOC_LITERAL(5, 44, 7), // "message"
QT_MOC_LITERAL(6, 52, 8), // "draw_img"
QT_MOC_LITERAL(7, 61, 3), // "arr"
QT_MOC_LITERAL(8, 65, 11), // "update_text"
QT_MOC_LITERAL(9, 77, 5), // "shape"
QT_MOC_LITERAL(10, 83, 1), // "s"
QT_MOC_LITERAL(11, 85, 28), // "on_EyeDropper_button_clicked"
QT_MOC_LITERAL(12, 114, 7), // "checked"
QT_MOC_LITERAL(13, 122, 22), // "on_Save_button_clicked"
QT_MOC_LITERAL(14, 145, 32), // "on_horizontalSlider_valueChanged"
QT_MOC_LITERAL(15, 178, 5), // "value"
QT_MOC_LITERAL(16, 184, 24), // "on_Rotate_button_clicked"
QT_MOC_LITERAL(17, 209, 24), // "on_Flip_h_button_clicked"
QT_MOC_LITERAL(18, 234, 24), // "on_Flip_v_button_clicked"
QT_MOC_LITERAL(19, 259, 24), // "on_Larger_button_clicked"
QT_MOC_LITERAL(20, 284, 25), // "on_Smaller_button_clicked"
QT_MOC_LITERAL(21, 310, 21), // "on_Roi_button_clicked"
QT_MOC_LITERAL(22, 332, 24) // "on_Recall_button_clicked"

    },
    "MainWindow\0button_inst\0\0inst\0"
    "update_message\0message\0draw_img\0arr\0"
    "update_text\0shape\0s\0on_EyeDropper_button_clicked\0"
    "checked\0on_Save_button_clicked\0"
    "on_horizontalSlider_valueChanged\0value\0"
    "on_Rotate_button_clicked\0"
    "on_Flip_h_button_clicked\0"
    "on_Flip_v_button_clicked\0"
    "on_Larger_button_clicked\0"
    "on_Smaller_button_clicked\0"
    "on_Roi_button_clicked\0on_Recall_button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   87,    2, 0x0a /* Public */,
       6,    1,   90,    2, 0x0a /* Public */,
       8,    1,   93,    2, 0x0a /* Public */,
      11,    1,   96,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    1,  100,    2, 0x08 /* Private */,
      16,    1,  103,    2, 0x08 /* Private */,
      17,    0,  106,    2, 0x08 /* Private */,
      18,    0,  107,    2, 0x08 /* Private */,
      19,    0,  108,    2, 0x08 /* Private */,
      20,    0,  109,    2, 0x08 /* Private */,
      21,    1,  110,    2, 0x08 /* Private */,
      22,    0,  113,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void, QMetaType::QByteArray,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->button_inst((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->update_message((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->draw_img((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 3: _t->update_text((*reinterpret_cast< shape(*)>(_a[1]))); break;
        case 4: _t->on_EyeDropper_button_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_Save_button_clicked(); break;
        case 6: _t->on_horizontalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->on_Rotate_button_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_Flip_h_button_clicked(); break;
        case 9: _t->on_Flip_v_button_clicked(); break;
        case 10: _t->on_Larger_button_clicked(); break;
        case 11: _t->on_Smaller_button_clicked(); break;
        case 12: _t->on_Roi_button_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->on_Recall_button_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::button_inst)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::button_inst(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
