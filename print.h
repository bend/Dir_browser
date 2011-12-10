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


#ifndef __PRINT_H__
#define __PRINT_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "color.h"
#include "browsedir.h"
#include "status.h"
#include "utils.h"
#include "opt.h"

_PROTOTYPE( int print_dir, (char* path, struct dirent* ent, unsigned int rec_level, status* state )						);
_PROTOTYPE( int print_file, (char* path, struct dirent* ent, unsigned int rec_level, status* state)						);
_PROTOTYPE( int print_size, (char* path, status* state)																	);
_PROTOTYPE( int print_total, (status* state)																);

_PROTOTYPE( int print_mode, (char* path, status* state )													);
#endif
