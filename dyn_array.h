/*
 * =====================================================================================
 *
 *       Filename:  dyn_array.h
 *
 *    Description: a dynamic array implementation
 *
 *        Version:  1.0
 *        Created:  18.05.2011 17:35:38
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */


#include "global.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dyn_array dyn_array;
struct dyn_array {
	unsigned int length;
	unsigned int size;
	char**	tab;
};

_PROTOTYPE( int alloc_array, ( dyn_array** arr, unsigned int init_size) );

_PROTOTYPE( void free_array, ( dyn_array* arr) );

_PROTOTYPE( int add_item, ( dyn_array* arr, char* item) );

_PROTOTYPE( int get_item, (dyn_array* arr, unsigned int i, char** item) );


