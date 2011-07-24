/*
 * =====================================================================================
 *
 *       Filename:  utils.c
 *
 *    Description:  Utils for the browse dir
 *
 *        Version:  1.0
 *        Created:  17.05.2011 17:02:00
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */
#include "utils.h"

PUBLIC int build_path(char* path, char* filename, char** res)
{
	*res = malloc(sizeof(char)*MAX_PATH);
	if(*res == NULL){
		perror("Malloc failed");
		return FAILURE;
	}
	strcpy(*res, path);
	strcat(*res, "/");
	strcat(*res, filename);
	return SUCCESS;
}

PUBLIC int parse_mode(mode_t mode, char** parsed)
{
	char temp[] = {'-','-','-','-','-','-','-','-','-','\0'};
	*parsed = malloc(sizeof(char) * 10);
	if (*parsed == NULL) {
		perror("Malloc failed");
		return FAILURE;
	}

	if (mode & S_IRUSR) temp[0] = 'r';
	if (mode & S_IWUSR) temp[1] = 'w';
	if (mode & S_IXUSR) temp[2] = 'x';
	
	if (mode & S_IRGRP) temp[3] = 'r';
	if (mode & S_IWGRP) temp[4] = 'w';
	if (mode & S_IXGRP) temp[5] = 'x';
	
	if (mode & S_IROTH) temp[6] = 'r';
	if (mode & S_IWOTH) temp[7] = 'w';
	if (mode & S_IXOTH) temp[8] = 'x';
	strncpy(*parsed, temp, 10);
	return SUCCESS;
}	

PUBLIC int size_convert(unsigned long size, char** converted)
{
	double conv_size;
	*converted = malloc(sizeof(char) * 256);
	if (*converted == NULL) {
		perror("Malloc failed");
		return FAILURE;
	}

	/* Check if is Tera */
	if ((size / 1e12) > 1) {
		conv_size = size / 1e12;
		gcvt(conv_size, 5, *converted);
		strncat(*converted, " TB",3);
	} else if ((size / 1e9) >1) {
		conv_size = size / 1e9;
		gcvt(conv_size, 5, *converted);
		strncat(*converted, " GB",3);
	} else if (size / 1e6 > 1) {
		conv_size = size / 1e6;
		gcvt(conv_size, 5, *converted);
		strncat(*converted, " MB",3);
	} else if (size / 1e3 > 1){
		conv_size = size / 1e3;
		gcvt(conv_size, 5, *converted);
		strncat(*converted, " KB",3);
	} else {
		conv_size = size;
		gcvt(conv_size, 5, *converted);
		strncat(*converted, " B",3);
	}
	return SUCCESS;
}
