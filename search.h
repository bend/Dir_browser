
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

#ifndef __SEARCH_H__
#define __SEARCH_H__
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <dirent.h>
#include <string.h>
#include "global.h"

typedef struct search_pattern search_pattern;

struct search_pattern
{
    bool is_suffix;
    bool is_prefix;
    char search_type;
    char* pattern;
};

_PROTOTYPE(int alloc_search_pattern, (search_pattern** sp, char type, char* pattern ));

_PROTOTYPE(void free_search_pattern, (search_pattern* sp) );

_PROTOTYPE(bool is_searched, (search_pattern* pattern, struct dirent* ent));

_PROTOTYPE(bool is_filename_match, (search_pattern* sp, char* filename));

#endif
