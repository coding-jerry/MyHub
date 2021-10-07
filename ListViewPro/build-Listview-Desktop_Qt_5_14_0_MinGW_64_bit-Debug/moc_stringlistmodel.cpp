/****************************************************************************
** Meta object code from reading C++ file 'stringlistmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../Listview/stringlistmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'stringlistmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_StringListModel_t {
    QByteArrayData data[18];
    char stringdata0[181];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_StringListModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_StringListModel_t qt_meta_stringdata_StringListModel = {
    {
QT_MOC_LITERAL(0, 0, 15), // "StringListModel"
QT_MOC_LITERAL(1, 16, 19), // "rcvDirectoryUpdated"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 12), // "QStringList&"
QT_MOC_LITERAL(4, 50, 11), // "newFileList"
QT_MOC_LITERAL(5, 62, 11), // "delFileList"
QT_MOC_LITERAL(6, 74, 14), // "rcvFileUpdated"
QT_MOC_LITERAL(7, 89, 4), // "path"
QT_MOC_LITERAL(8, 94, 4), // "data"
QT_MOC_LITERAL(9, 99, 11), // "QModelIndex"
QT_MOC_LITERAL(10, 111, 5), // "index"
QT_MOC_LITERAL(11, 117, 4), // "role"
QT_MOC_LITERAL(12, 122, 10), // "dataForQml"
QT_MOC_LITERAL(13, 133, 3), // "row"
QT_MOC_LITERAL(14, 137, 14), // "textInsertRows"
QT_MOC_LITERAL(15, 152, 8), // "position"
QT_MOC_LITERAL(16, 161, 4), // "rows"
QT_MOC_LITERAL(17, 166, 14) // "textRemoveRows"

    },
    "StringListModel\0rcvDirectoryUpdated\0"
    "\0QStringList&\0newFileList\0delFileList\0"
    "rcvFileUpdated\0path\0data\0QModelIndex\0"
    "index\0role\0dataForQml\0row\0textInsertRows\0"
    "position\0rows\0textRemoveRows"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_StringListModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x0a /* Public */,
       6,    1,   59,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
       8,    2,   62,    2, 0x02 /* Public */,
       8,    1,   67,    2, 0x22 /* Public | MethodCloned */,
      12,    2,   70,    2, 0x02 /* Public */,
      12,    1,   75,    2, 0x22 /* Public | MethodCloned */,
      14,    2,   78,    2, 0x02 /* Public */,
      17,    2,   83,    2, 0x02 /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, QMetaType::QString,    7,

 // methods: parameters
    QMetaType::QVariant, 0x80000000 | 9, QMetaType::Int,   10,   11,
    QMetaType::QVariant, 0x80000000 | 9,   10,
    QMetaType::QVariant, QMetaType::Int, QMetaType::Int,   13,   11,
    QMetaType::QVariant, QMetaType::Int,   13,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   15,   16,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int,   15,   16,

       0        // eod
};

void StringListModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<StringListModel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->rcvDirectoryUpdated((*reinterpret_cast< QStringList(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2]))); break;
        case 1: _t->rcvFileUpdated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 3: { QVariant _r = _t->data((*reinterpret_cast< const QModelIndex(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 4: { QVariant _r = _t->dataForQml((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 5: { QVariant _r = _t->dataForQml((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QVariant*>(_a[0]) = std::move(_r); }  break;
        case 6: { bool _r = _t->textInsertRows((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 7: { bool _r = _t->textRemoveRows((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject StringListModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_StringListModel.data,
    qt_meta_data_StringListModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *StringListModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *StringListModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_StringListModel.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int StringListModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
