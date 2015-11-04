/*
 * Python object definition of the libfsntfs update (or change) journal
 *
 * Copyright (C) 2010-2015, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pyfsntfs_error.h"
#include "pyfsntfs_libcerror.h"
#include "pyfsntfs_libcstring.h"
#include "pyfsntfs_libfsntfs.h"
#include "pyfsntfs_python.h"
#include "pyfsntfs_unused.h"
#include "pyfsntfs_update_journal.h"

PyMethodDef pyfsntfs_update_journal_object_methods[] = {

	/* Functions to access the update journal */

	{ "read_usn_record",
	  (PyCFunction) pyfsntfs_update_journal_read_usn_record,
	  METH_NOARGS,
	  "read_usn_record() -> String\n"
	  "\n"
	  "Reads USN record data." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pyfsntfs_update_journal_object_get_set_definitions[] = {

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyfsntfs_update_journal_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pyfsntfs.update_journal",
	/* tp_basicsize */
	sizeof( pyfsntfs_update_journal_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pyfsntfs_update_journal_free,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pyfsntfs update journal object (wraps libfsntfs_update_journal_t)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pyfsntfs_update_journal_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pyfsntfs_update_journal_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pyfsntfs_update_journal_init,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Creates a new pyfsntfs update journal object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pyfsntfs_update_journal_new(
           libfsntfs_update_journal_t *update_journal,
           PyObject *volume_object )
{
	pyfsntfs_update_journal_t *pyfsntfs_update_journal = NULL;
	static char *function                              = "pyfsntfs_update_journal_new";

	if( update_journal == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid update journal.",
		 function );

		return( NULL );
	}
	pyfsntfs_update_journal = PyObject_New(
	                           struct pyfsntfs_update_journal,
	                           &pyfsntfs_update_journal_type_object );

	if( pyfsntfs_update_journal == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize update journal.",
		 function );

		goto on_error;
	}
	if( pyfsntfs_update_journal_init(
	     pyfsntfs_update_journal ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize update journal.",
		 function );

		goto on_error;
	}
	pyfsntfs_update_journal->update_journal = update_journal;
	pyfsntfs_update_journal->volume_object  = volume_object;

	Py_IncRef(
	 pyfsntfs_update_journal->volume_object );

	return( (PyObject *) pyfsntfs_update_journal );

on_error:
	if( pyfsntfs_update_journal != NULL )
	{
		Py_DecRef(
		 (PyObject *) pyfsntfs_update_journal );
	}
	return( NULL );
}

/* Intializes an update journal object
 * Returns 0 if successful or -1 on error
 */
int pyfsntfs_update_journal_init(
     pyfsntfs_update_journal_t *pyfsntfs_update_journal )
{
	static char *function = "pyfsntfs_update_journal_init";

	if( pyfsntfs_update_journal == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid update journal.",
		 function );

		return( -1 );
	}
	/* Make sure libfsntfs update journal is set to NULL
	 */
	pyfsntfs_update_journal->update_journal = NULL;

	return( 0 );
}

/* Frees an update journal object
 */
void pyfsntfs_update_journal_free(
      pyfsntfs_update_journal_t *pyfsntfs_update_journal )
{
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pyfsntfs_update_journal_free";
	int result                  = 0;

	if( pyfsntfs_update_journal == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid update journal.",
		 function );

		return;
	}
	if( pyfsntfs_update_journal->update_journal == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid update journal - missing libfsntfs update journal.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pyfsntfs_update_journal );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfsntfs_update_journal_free(
	          &( pyfsntfs_update_journal->update_journal ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfsntfs_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free update journal.",
		 function );

		libcerror_error_free(
		 &error );
	}
	if( pyfsntfs_update_journal->volume_object != NULL )
	{
		Py_DecRef(
		 pyfsntfs_update_journal->volume_object );
	}
	ob_type->tp_free(
	 (PyObject*) pyfsntfs_update_journal );
}

/* Reads an USN record
 * Returns a Python object holding the data if successful or NULL on error
 */
PyObject *pyfsntfs_update_journal_read_usn_record(
           pyfsntfs_update_journal_t *pyfsntfs_update_journal,
           PyObject *arguments PYFSNTFS_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error  = NULL;
	PyObject *string_object   = NULL;
	static char *function     = "pyfsntfs_update_journal_read_usn_record";
	char *usn_record_data     = NULL;
	size_t cluster_block_size = 0;
	ssize_t read_count        = 0;
	int result                = 0;

	if( pyfsntfs_update_journal == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid update journal.",
		 function );

		return( NULL );
	}
	if( pyfsntfs_update_journal->update_journal == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid update journal - missing libfsntfs update journal.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = libfsntfs_volume_get_cluster_block_size(
	          pyfsntfs_update_journal->update_journal,
	          &cluster_block_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pyfsntfs_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve cluster block size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( ( cluster_block_size == 0 )
	 || ( cluster_block_size > (size_t) SSIZE_MAX ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid argument read size value exceeds maximum.",
		 function );

		return( NULL );
	}
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 NULL,
	                 cluster_block_size );

	usn_record_data = PyBytes_AsString(
	                   string_object );
#else
	/* Note that a size of 0 is not supported
	 */
	string_object = PyString_FromStringAndSize(
	                 NULL,
	                 cluster_block_size );

	usn_record_data = PyString_AsString(
	                   string_object );
#endif
	Py_BEGIN_ALLOW_THREADS

	read_count = libfsntfs_update_journal_read_usn_record(
	              pyfsntfs_update_journal->update_journal,
	              (uint8_t *) usn_record_data,
	              (size_t) cluster_block_size,
	              &error );

	Py_END_ALLOW_THREADS

	if( read_count <= -1 )
	{
		pyfsntfs_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to read data.",
		 function );

		libcerror_error_free(
		 &error );

		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	/* Need to resize the string here in case cluster_block_size was not fully read.
	 */
#if PY_MAJOR_VERSION >= 3
	if( _PyBytes_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#else
	if( _PyString_Resize(
	     &string_object,
	     (Py_ssize_t) read_count ) != 0 )
#endif
	{
		Py_DecRef(
		 (PyObject *) string_object );

		return( NULL );
	}
	return( string_object );
}

