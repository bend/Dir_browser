
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

#ifndef __OPT_H__
#define __OPT_H__

#include "global.h"
#include <stdlib.h>
#include <stdio.h>

#define 	ON			1		/* option is on */
#define 	OFF 		-1		/* option is off */
#define 	DIR_ONLY	1		/* Display only directories */
#define 	FILE_ONLY	2		/* Display only files */
#define 	BOTH		3		/* Display both */

typedef struct options options;

struct options
{
    char color;			/* display output in colors	*/
    char hr;			/* display human readable size */
    char verbose;		/* show browsed files */
    char mode;			/* display mode */
    char level_ind;		/* indent depth level */
    int depth;			/* recursive depth */
    char display;		/* Display only type of file can Be*/
    char dir_sym; 		/* the dir symbol */
    char file_sym;		/* the file symbol */
    char follow_link;	/* follow links */
    char d_hidden;		/* display hidden file if OFF, file will not be counted and size will not be part of total*/
    char d_total;		/* display a grand total */
    char d_size;        /* display size for each file*/
    char execute_command; /* exectute a command for each file and dir */
    char* command;      /* command to execute */
};


_PROTOTYPE(int alloc_options, (options** opt) 	);

_PROTOTYPE(void free_options, (options* opt)  	);

#endif
