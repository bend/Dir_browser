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

_PUBLIC int alloc_status(status **stat)
{
	*stat = malloc(sizeof(status));
	if(*stat == NULL){
		perror("Malloc failed");
		return FAILURE;
	}
	(*stat)->nb_folders = 0;
	(*stat)->nb_files   = 0;
	(*stat)->size_byte  = 0;
	return SUCCESS;
}

_PUBLIC int browse_dir(char* path, unsigned int rec_level, status *stat)
{
	DIR *dir = opendir(path);
	struct dirent *ent;
	if (dir != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			char* buffer;
			if(build_path(path, ent->d_name, &buffer) == FAILURE)
				return FAILURE;
			if( !strcmp(ent->d_name,".") ==0 && !strcmp(ent->d_name, "..") == 0){
				if(ent->d_type == DT_DIR ){					/* Directory */
					print_dir(path, ent, rec_level);
					stat->nb_folders++;
					browse_dir(buffer, rec_level+1, stat);
				}else{
					print_file(path, ent, rec_level);
					stat->nb_files++;
				}
			}
			free(buffer);
		}
	} else {
		perror ("browsed: ");
		return FAILURE;
	}
	closedir(dir);	
	return SUCCESS;
}

_PRIVATE int build_path(char* path, char* filename, char** res)
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
