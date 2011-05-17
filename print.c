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
	for(i=0; i<rec_level;i++)
		printf(TAB);
	printf("%s %s\n",DIR_SYM,ent->d_name);
}

PRIVATE void print_file(char * path, struct dirent *ent, unsigned int rec_level, status* state)
{
	int i;
	char* abs_path;
	for( i=1; i<rec_level+1;i++)
		printf("  ");
	printf("%s %s ",FILE_SYM,ent->d_name);
	build_path(path, ent->d_name, &abs_path);
	print_mode(abs_path);
	print_size(abs_path, state);
	free(abs_path);
}

PRIVATE void print_total(status *state)
{
	printf("\nTotal:\n\t%ld Files\n\t%ld Folders\nSize:\n\t%ld\n",state->nb_files,state->nb_folders,state->size_byte);
}

PRIVATE int print_size(char* path, status* state){
	struct stat file_status;
	if (stat(path, &file_status) >0) {
		perror("Stat failed");
		return -1;		
	}
	state->size_byte+=(long)file_status.st_size;
	printf("- %d Bytes\n", (int)file_status.st_size);
	return 0;
}

PRIVATE int print_mode(char* path){
	char* parsed_mode;
	struct stat file_status;
	if (stat(path, &file_status) >0) {
		perror("Stat failed");
		return -1;		
	}
	if (parse_mode(file_status.st_mode, &parsed_mode) == -1){
		perror("Parse mode failed");
		return -1;
	}
	printf("[ %s ] ",parsed_mode);
	free(parsed_mode);
	return 0;
}
