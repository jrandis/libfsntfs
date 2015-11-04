/*
 * Update (or change) journal functions
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

#if !defined( _LIBFSNTFS_INTERNAL_UPDATE_JOURNAL_H )
#define _LIBFSNTFS_INTERNAL_UPDATE_JOURNAL_H

#include <common.h>
#include <types.h>

#include "libfsntfs_extern.h"
#include "libfsntfs_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct libfsntfs_internal_update_journal libfsntfs_internal_update_journal_t;

struct libfsntfs_internal_update_journal
{
	/* The IO handle
	 */
	libfsntfs_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* The MFT entry
	 */
	libfsntfs_mft_entry_t *mft_entry;

	/* The directory entry
	 */
	libfsntfs_directory_entry_t *directory_entry;

	/* The $J $DATA attribute
	 */
	libfsntfs_attribute_t *data_attribute;

	/* The $J data stream
	 */
	libfsntfs_data_stream_t *data_stream;

	/* The data offset
	 */
	off64_t data_offset;

	/* The data size
	 */
	size64_t data_size;

	/* The number of extents
	 */
	int number_of_extents;

	/* The extent index
	 */
	int extent_index;

	/* The extent offset
	 */
	off64_t extent_offset;

	/* The extent size
	 */
	size64_t extent_size;

	/* The extent flags
	 */
	uint32_t extent_flags;

	/* The cluster block data
	 */
	uint8_t *cluster_block_data;

	/* The cluster block (data) offset
	 */
	size_t cluster_block_offset;
};

int libfsntfs_update_journal_initialize(
     libfsntfs_update_journal_t **update_journal,
     libfsntfs_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     libfsntfs_mft_entry_t *mft_entry,
     libfsntfs_directory_entry_t *directory_entry,
     libfsntfs_attribute_t *data_attribute,
     libcerror_error_t **error );

LIBFSNTFS_EXTERN \
int libfsntfs_update_journal_free(
     libfsntfs_update_journal_t **update_journal,
     libcerror_error_t **error );

/* TODO add get offset */

LIBFSNTFS_EXTERN \
ssize_t libfsntfs_update_journal_read_usn_record(
         libfsntfs_update_journal_t *update_journal,
         uint8_t *usn_record_data,
         size_t usn_record_data_size,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

