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

_PRIVATE void print_dir(char* path, struct dirent *ent, unsigned int rec_level)
{
	int i;
	for(i=0; i<rec_level;i++)
		printf(TAB);
	printf("%s %s ",DIR_SYM,ent->d_name);
	print_size(path);
}

_PRIVATE void print_file(char * path, struct dirent *ent, unsigned int rec_level)
{
	int i;
	for( i=1; i<rec_level+1;i++)
		printf("  ");
	printf("%s %s ",FILE_SYM,ent->d_name);
	print_size(path);
}

_PRIVATE void print_total(unsigned long nb_files, unsigned long nb_folders, unsigned long byte_size)
{
	byte_size=1;
	printf("\nTotal:\n\t%ld Files\n\t%ld Folders\n",nb_files,nb_folders);
}

_PRIVATE void print_size( char* path){
	struct stat file_status;
	stat(path, &file_status);
	printf("- %d Bytes\n", (int)file_status.st_size);
}
