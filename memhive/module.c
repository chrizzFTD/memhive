#include "memhive.h"
#include "map.h"


static struct PyModuleDef_Slot module_slots[] = {
    {Py_mod_exec, module_exec},
    {Py_mod_multiple_interpreters, Py_MOD_PER_INTERPRETER_GIL_SUPPORTED},
    {0, NULL},
};


static struct PyModuleDef _module = {
    PyModuleDef_HEAD_INIT,      /* m_base */
    "_memhive",                 /* m_name */
    NULL,                       /* m_doc */
    -1,                         /* m_size */
    NULL,                       /* m_methods */
    NULL,                       /* m_slots */
    NULL,                       /* m_traverse */
    NULL,                       /* m_clear */
    NULL,                       /* m_free */
};


static int
module_exec(PyObject *m)
{
#define CREATE_TYPE(m, tp, spec, base)                                  \
    do {                                                                \
        tp = (PyTypeObject *)PyType_FromMetaclass(NULL, m, spec,        \
                                                  (PyObject *)base);    \
        if (tp == NULL) {                                               \
            return -1;                                                  \
        }                                                               \
    } while (0)



    if (
        (PyType_Ready(&MemHive_Type) < 0) ||
        (PyType_Ready(&MemHiveProxy_Type) < 0)
    )
    {
        return 0;
    }

    if ((PyType_Ready(&_Map_Type) < 0) ||
        (PyType_Ready(&_MapMutation_Type) < 0) ||
        (PyType_Ready(&_Map_ArrayNode_Type) < 0) ||
        (PyType_Ready(&_Map_BitmapNode_Type) < 0) ||
        (PyType_Ready(&_Map_CollisionNode_Type) < 0) ||
        (PyType_Ready(&_MapKeys_Type) < 0) ||
        (PyType_Ready(&_MapValues_Type) < 0) ||
        (PyType_Ready(&_MapItems_Type) < 0) ||
        (PyType_Ready(&_MapKeysIter_Type) < 0) ||
        (PyType_Ready(&_MapValuesIter_Type) < 0) ||
        (PyType_Ready(&_MapItemsIter_Type) < 0))
    {
        return 0;
    }

    Py_INCREF(&MemHive_Type);
    if (PyModule_AddObject(m, "_MemHive", (PyObject *)&MemHive_Type) < 0) {
        Py_DECREF(&MemHive_Type);
        return NULL;
    }

    Py_INCREF(&MemHiveProxy_Type);
    if (PyModule_AddObject(m, "_MemHiveProxy", (PyObject *)&MemHiveProxy_Type) < 0) {
        Py_DECREF(&MemHiveProxy_Type);
        return NULL;
    }

    Py_INCREF(&_Map_Type);
    if (PyModule_AddObject(m, "Map", (PyObject *)&_Map_Type) < 0) {
        Py_DECREF(&_Map_Type);
        return NULL;
    }

    return m;
}
