
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


PUBLIC int alloc_search_pattern(search_pattern** sp, char type, char* pattern)
{
    int len, i;
    *sp = malloc(sizeof(search_pattern));

    if (*sp == NULL)
        return FAILURE;

    switch (type)
    {
        case TYPE_ALL:
            (*sp)->search_type = TYPE_ALL;
            break;

        case TYPE_F:
            (*sp)->search_type = TYPE_F;
            break;

        case TYPE_D:
            (*sp)->search_type = TYPE_D;
            break;

        case TYPE_N:
            (*sp)->search_type = TYPE_N;

            if (pattern[0] == '*')
            {
                (*sp)->is_suffix = true;
                len = strlen(pattern);

                for (i = 0; i < len; ++i)
                {
                    pattern[i] = pattern[i + 1];
                }
            }

            else (*sp)->is_suffix = false;

            if (pattern[strlen(pattern) - 1 ] == '*')
            {
                (*sp)->is_prefix = true;
                pattern[strlen(pattern) - 1] = '\0';
            }

            else (*sp)->is_prefix = false;

            (*sp)->pattern = pattern;
            break;
    };

    return SUCCESS;
}


PUBLIC void free_search_pattern(search_pattern* sp)
{
    free(sp->pattern);
    free(sp);
}

PUBLIC bool is_searched(search_pattern* sp, struct dirent* ent)
{
    switch (sp->search_type)
    {
        case TYPE_ALL:
            return true;

        case TYPE_F:
            return ent->d_type == DT_REG;

        case TYPE_D:
            return ent->d_type == DT_DIR;

        case TYPE_N:
            return is_filename_match(sp, ent->d_name);
    }

    return false;
}

PRIVATE bool is_filename_match(search_pattern* sp, char* filename)
{
    int i, j;
    bool ok = false;
    if(sp->is_suffix && sp->is_prefix)
    {   
        if(strstr(filename, sp->pattern) == NULL)
            return false;
        return true;
    }
    if (sp->is_suffix)
    {
        /* looking for *pattern */
        for (i = strlen(sp->pattern) - 1, j = strlen(filename) - 1; i > 0 && j > 0; --i, --j)
        {
            if (filename[j] != sp->pattern[i])
            {
                ok = false;
                break;
            }

            else ok = true;
        }

        if (ok) return true;
    }

    if (sp->is_prefix)
    {
        /* looking for pattern* */
        for (i = 0, j = 0; i < strlen(sp->pattern) && j < strlen(filename); ++i , ++j)
        {
            if (filename[j] != sp->pattern[i])
                return false;
        }

        return true;
    }

    if (strcmp(sp->pattern, filename) == 0)
        return true;

    return false;
}
