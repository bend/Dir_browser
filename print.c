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

_PRIVATE void print_dir(char* path, struct dirent *ent, unsigned int rec_level, status* stat)
{
	int i;
	for(i=0; i<rec_level;i++)
		printf(TAB);
	printf("%s %s ",DIR_SYM,ent->d_name);
	print_size(path,stat);
}

_PRIVATE void print_file(char * path, struct dirent *ent, unsigned int rec_level, status* stat)
{
	int i;
	for( i=1; i<rec_level+1;i++)
		printf("  ");
	printf("%s %s ",FILE_SYM,ent->d_name);
	print_size(path,stat);
}

_PRIVATE void print_total(status *stat)
{
	printf("\nTotal:\n\t%ld Files\n\t%ld Folders\nSize:\n\t%ld\n",stat->nb_files,stat->nb_folders,stat->size_byte);
}

_PRIVATE void print_size( char* path, status* s){
	struct stat file_status;
	stat(path, &file_status);
	s->size_byte+=(long)file_status.st_size;
	printf("- %d Bytes\n", (int)file_status.st_size);
}
