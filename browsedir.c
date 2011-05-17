/*
 * =====================================================================================
 *
 *       Filename:  browsedir.c
 *
 *    Description:  Browses the dir an prints  it.
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
			if (build_path(path, ent->d_name, &buffer) == FAILURE)
				return FAILURE;
			if (!strcmp(ent->d_name,".") ==0 && !strcmp(ent->d_name, "..") == 0) {
				if (ent->d_type == DT_DIR ) {					/* Directory */
					print_dir(path, ent, rec_level,state);
					state->nb_folders++;
					if (browse_dir(buffer, rec_level+1, state) == FAILURE)
						return FAILURE;
				} else {
					if (print_file(path, ent, rec_level,state) == FAILURE)
						return FAILURE;
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

PUBLIC int start_browse(char* path, unsigned int rec_level, status *state)
{
	struct stat file_status;
	if (stat(path, &file_status) >0) {
		perror("Stat failed");
		return FAILURE;		
	}
	/* Check if file or Folder */
	if (file_status.st_mode & S_IFDIR) {
		return browse_dir(path, rec_level, state); /* it's a folder */
	}

	/* it's a file , so we print it */
	printf("%s ", path);	
	if (print_mode(path) == FAILURE)
		return -1;
	if (print_size(path, state) == FAILURE)
		return -1;
	state->nb_files++;
	return SUCCESS;
	}	

	
