/*
 * =====================================================================================
 *
 *       Filename:  utils.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  17.05.2011 17:02:41
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */

#ifndef __UTILS_H__
#define __UTILS_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>



#include "global.h"
#include "print.h"
#include "status.h"

_PROTOTYPE( int build_path, (char* path, char* filename, char** res )				);

_PROTOTYPE( int parse_mode, (mode_t mode, char** parsed)							);

#endif
