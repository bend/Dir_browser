/*
 * =====================================================================================
 *
 *       Filename:  print.h
 *
 *    Description:  prints the dir or file on screen
 *
 *        Version:  1.0
 *        Created:  05.05.2011 10:56:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
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

_PROTOTYPE( int print_dir, (char* path, struct dirent *ent, unsigned int rec_level, status* state )						);
_PROTOTYPE( int print_file, (char* path, struct dirent *ent, unsigned int rec_level, status* state)						);
_PROTOTYPE( int print_size, (char* path, status* state)																	);
_PROTOTYPE( int print_total, (status *state)																);

_PROTOTYPE( int print_mode, (char* path, status* state )													);
#endif
