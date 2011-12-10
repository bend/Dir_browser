
/*
 *   Copyright © Ben D.
 *   dbapps2@gmail.com
 *
 *   This is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __STATUS_H__
#define __STATUS_H__

#include "global.h"
#include "opt.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct status status;

struct status
{
    unsigned long nb_files;
    unsigned long nb_folders;
    unsigned long size_byte;
    options* opt;
};

_PROTOTYPE( int alloc_status, (status** stat)		);

_PROTOTYPE( void free_status, (status* stat)		);
#endif
