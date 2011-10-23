/*
 * =====================================================================================
 *
 *       Filename:  status.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05.05.2011 12:23:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */

#ifndef __STATUS_H__
#define __STATUS_H__

#include "global.h"
#include "opt.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct status status;

struct status
{
    unsigned long nb_files;
    unsigned long nb_folders;
    unsigned long size_byte;
    options* opt;
};

_PROTOTYPE( int alloc_status, (status** stat)		);

_PROTOTYPE( void free_status, (status* stat)		);
#endif
