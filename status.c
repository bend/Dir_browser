
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

#include "status.h"

PUBLIC int alloc_status(status** stat)
{
    *stat = malloc(sizeof(status));

    if (*stat == NULL)
    {
        perror("Malloc failed");
        return FAILURE;
    }

    (*stat)->nb_folders = 0;
    (*stat)->nb_files   = 0;
    (*stat)->size_byte  = 0;

    if (alloc_options(&((*stat)->opt)) == FAILURE)
        return FAILURE;

    return SUCCESS;
}

PUBLIC void free_status(status* stat)
{
    free_options(stat->opt);
    free(stat);
}
