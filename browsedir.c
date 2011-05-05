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

_PUBLIC void browse_dir(char* path, unsigned int rec_level, unsigned long *nb_files, unsigned long *nb_folders)
{
	DIR *dir = opendir(path);
	struct dirent *ent;
	if (dir != NULL) {
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
