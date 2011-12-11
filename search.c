
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

#include "search.h"


int search_pattern_alloc(search_pattern** sp, char* pattern)
{
    *sp = malloc(sizeof(search_pattern));
    if(*sp == NULL)
        return FAILURE;
    if(pattern[0] == '*')
        (*sp)->is_suffix = true;
    else (*sp)->is_suffix = false;
    if(pattern[strlen(pattern) -1 ] == '*')
        (*sp)->is_prefix = true;
    else (*sp)->is_prefix = false;

    return SUCCESS;

}


void search_pattern_free(search_pattern *sp)
{
    free(sp->pattern);
    free(sp);
}

bool is_searched(search_pattern* pattern, char* filename)
{

    return false;
}

