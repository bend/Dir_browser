/*
 * =====================================================================================
 *
 *       Filename:  browsedir.c
 *
 *    Description:  Browses the dir an prints  it.@
 *
 *        Version:  1.0
 *        Created:  03.05.2011 10:32:49
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */

#include "browsedir.h"

_PUBLIC void browse_dir(char* path, unsigned int rec_level, long *nb_files, long *nb_folders)
{
	DIR *dir = opendir(path);
	struct dirent *ent;
	if (dir != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			char* buffer = build_path(path, ent->d_name);
			if( !strcmp(ent->d_name,".") ==0 && !strcmp(ent->d_name, "..") == 0){
				if(ent->d_type == DT_DIR ){					/* Directory */
					print_dir(path, ent, rec_level);
					++*(nb_folders);
					browse_dir(buffer, rec_level+1,nb_files,nb_folders);
				}else{
					print_file(path, ent, rec_level);
					(*nb_files)++;
				}
			}
			free(buffer);
		}
	} else {
		/* could not open directory */
		perror ("browsed: ");
		exit(-1);
	}
	closedir(dir);	
}

_PRIVATE char* build_path(char* path, char* filename)
{
	char* buffer;
	buffer = malloc(sizeof(char)*MAX_PATH);
	if(buffer == NULL){
		perror("Malloc failed");
		exit(-1);
	}
	strcpy(buffer, path);
	strcat(buffer, "/");
	strcat(buffer, filename);
	return buffer;
}

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

_PRIVATE void print_total(long nb_files, long nb_folders)
{
	printf("\nTotal:\n\t%ld Files\n\t%ld Folders\n",nb_files,nb_folders);
}

_PRIVATE void print_size( char* path){
	struct stat file_status;
	stat(path, &file_status);
	printf("- %d Bytes\n", (int)file_status.st_size);
}

_PUBLIC int main(int argc, char** argv)
{
	long nb_files=0, nb_folders=0;
	if(argc>1){
		browse_dir(argv[1], 0,&nb_files,&nb_folders);
		print_total(nb_files, nb_folders);
	}else printf("Please provide filename\n");
	return 1;
}

