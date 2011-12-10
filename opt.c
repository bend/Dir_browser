
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

#include "opt.h"

PUBLIC int alloc_options(options** opt)
{
    *opt = malloc(sizeof(options));

    if (*opt == NULL)
    {
        perror("Malloc failed");
        return FAILURE;
    }

    (*opt)->color = OFF;		/* color is off by default */
    (*opt)->hr = OFF;			/* hr off by default */
    (*opt)->verbose = ON;		/* verbose on by defaut */
    (*opt)->mode = OFF;			/* mode is off by default */
    (*opt)->level_ind = ON;		/* indent on by default */
    (*opt)->depth = OFF;		/* no max_depth by default */
    (*opt)->display = BOTH;		/* display all files by default */
    (*opt)->dir_sym = DIR_SYM; 	/* default symbol */
    (*opt)->file_sym = FILE_SYM;/* default symbol */
    (*opt)->follow_link = OFF;	/* do not follow links */
    (*opt)->d_hidden = OFF;		/* do not display hidden files/folders by default */
    (*opt)->d_total = ON;		/* display grand total */
    (*opt)->d_size = ON;        /* display the size of each file */
    return SUCCESS;
}

PUBLIC void free_options(options* opt)
{
    free(opt);
}
