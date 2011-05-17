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


PUBLIC int browse_dir(char* path, unsigned int rec_level, status *state)
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
					print_dir(path, ent, rec_level,state);
					state->nb_folders++;
					browse_dir(buffer, rec_level+1, state);
				}else{
					print_file(path, ent, rec_level,state);
					state->nb_files++;
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

