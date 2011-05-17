/*
 * =====================================================================================
 *
 *       Filename:  print.c
 *
 *    Description:  prints the dir or file on screen
 *
 *        Version:  1.0
 *        Created:  05.05.2011 11:01:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */

#include "print.h"

PRIVATE void print_dir(char* path, struct dirent *ent, unsigned int rec_level, status* state)
{
	int i;
	for (i=0; i<rec_level; i++)
		printf(TAB);
	printf("%s%s %s\n",RED,DIR_SYM,ent->d_name);
}

PRIVATE int print_file(char * path, struct dirent *ent, unsigned int rec_level, status* state)
{
	int i;
	char* abs_path;
	for (i=1; i<rec_level+1; i++)
		printf("  ");
	printf("%s%s %s ",BLUE,FILE_SYM,ent->d_name);
	if (build_path(path, ent->d_name, &abs_path) == FAILURE)
		return FAILURE;
	if (print_mode(abs_path) == FAILURE)
		return FAILURE;	
	if (print_size(abs_path, state) == FAILURE)
		return FAILURE;
	free(abs_path);
	return SUCCESS;
}

PRIVATE int print_total(status *state)
{
	char* total;
	if (size_convert(state->size_byte, &total) == FAILURE)
		return FAILURE;
	printf("%s\nTotal:\n\t%ld Files\n\t%ld Folders\nSize:\t%s\n",WHITE,state->nb_files,state->nb_folders, total);
	return SUCCESS;
}

PRIVATE int print_size(char* path, status* state) 
{
	struct stat file_status;
	char* size_conv;
	if (stat(path, &file_status) >0) {
		perror("Stat failed");
		return FAILURE;		
	}
	state->size_byte+=(long)file_status.st_size;
	if (size_convert(file_status.st_size, &size_conv) == FAILURE)
		return FAILURE;
	printf("%s- %s\n", YELLOW,size_conv);
	free(size_conv);
	return SUCCESS;
}

PRIVATE int print_mode(char* path)
{
	char* parsed_mode;
	struct stat file_status;
	if (stat(path, &file_status) >0) {
		perror("Stat failed");
		return FAILURE;		
	}
	if (parse_mode(file_status.st_mode, &parsed_mode) == FAILURE){
		perror("Parse mode failed");
		return FAILURE;
	}
	printf("%s[ %s ] ",GREEN,parsed_mode);
	free(parsed_mode);
	return SUCCESS;
}
