
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

#ifndef __BROWSEDIR_H__
#define __BROWSEDIR_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "global.h"
#include "print.h"
#include "status.h"
#include "utils.h"
#include "color.h"
#include "search.h"
#include "executor.h"

_PROTOTYPE( int browse_dir, (char* path, unsigned int rec_level, status* state , search_pattern* pattern)	);

_PROTOTYPE( int start_browse, (char* path, unsigned int rec_level, status* state, search_pattern* pattern )	);

_PROTOTYPE( struct dirent* preload_dir, (char* path, int* size )	);

#endif
