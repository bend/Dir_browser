/*
 * =====================================================================================
 *
 *       Filename:  browsedir.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03.05.2011 12:37:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */

#ifndef __BROWSEDIR_H__
#define __BROWSEDIR_H__
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

#include "global.h"
#include "print.h"
#include "status.h"

_PROTOTYPE( int browse_dir, (char* path, unsigned int rec_level, status* stat )		);

_PROTOTYPE( int build_path, (char* path, char* filename, char** res )				);


#endif
