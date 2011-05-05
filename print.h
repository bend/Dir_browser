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


_PROTOTYPE( void print_dir, (char* path, struct dirent *ent, unsigned int rec_level )						);
_PROTOTYPE( void print_file, (char* path, struct dirent *ent, unsigned int rec_level)						);
_PROTOTYPE( void print_size, (char* path)																	);
_PROTOTYPE( void print_total, (unsigned long nb_files, unsigned long nb_folders, unsigned long byte_size)	);

#endif
