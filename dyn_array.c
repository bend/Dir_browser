/*
 * =====================================================================================
 *
 *       Filename:  dyn_array.c
 *
 *    Description:  a dynamic array implementation
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

#include "dyn_array.h"

PUBLIC int alloc_array(dyn_array** arr, unsigned int init_size)
{
	*arr = malloc(sizeof(dyn_array));
	if (*arr == NULL) {
		perror("Malloc failed");
		return FAILURE;
	}
	(*arr)->tab = malloc( sizeof(char) * init_size);
	if ((*arr)->tab == NULL) {
		perror("Malloc failed");
		return FAILURE;
	}
	(*arr)->length = 0;
	(*arr)->size = init_size;
	return SUCCESS;
}

PUBLIC void free_array(dyn_array* arr){
	free(arr->tab);
	free(arr);
}

PUBLIC int add_item(dyn_array* arr, char* item){
	if (arr->length == arr->size) {
		arr->tab = realloc(arr->tab, arr->size * 2 );
		if (arr->tab == NULL) {
			perror("Malloc failed");
			return FAILURE;
		}
		arr->size = arr->size*2;
	}
	arr->tab[arr->length] = item;
	arr->length++;
	return SUCCESS;
}

PUBLIC int get_item(dyn_array* arr, unsigned int i, char** item) {
	*item = malloc( sizeof(char) * MAX_PATH);
	if (*item == NULL) {
		perror("Malloc failed");
		return FAILURE;
	}
	strcpy(*item, arr->tab[i]);
	return SUCCESS;
}
