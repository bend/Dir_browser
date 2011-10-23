/*
 * =====================================================================================
 *
 *       Filename:  opt.h
 *
 *    Description:  Options select when running the prog
 *
 *        Version:  1.0
 *        Created:  17.05.2011 22:07:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
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
};


_PROTOTYPE(int alloc_options, (options** opt) 	);

_PROTOTYPE(void free_options, (options* opt)  	);

#endif
