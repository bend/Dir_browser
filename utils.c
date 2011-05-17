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

PRIVATE int build_path(char* path, char* filename, char** res)
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

PRIVATE int parse_mode(mode_t mode, char** parsed){
	char temp[] = {'-','-','-','-','-','-','-','-','-'};
	*parsed = malloc(sizeof(char) * 9);
	if (*parsed == NULL) {
		perror("Malloc failed");
		return -1;
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
	strncpy(*parsed, temp, 9);
	return 0;
}	
