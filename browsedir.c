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
				continue;
			if (!strcmp(ent->d_name,".") ==0 && !strcmp(ent->d_name, "..") == 0 	/* Check that it's not the current dir, parent dir */
					&& (ent->d_name[0] != '.' || state->opt->d_hidden == ON)) {		/* And if it is hidden and we don't want to display it */
				if (ent->d_type == DT_DIR ) {										/* Directory */
					print_dir(path, ent, rec_level,state);
					state->nb_folders++;
					if (state->opt->depth < rec_level)
						return SUCCESS;												/* Max depth reached */
					if (browse_dir(buffer, rec_level+1, state) == FAILURE)
						continue;
				} else {
					if (ent->d_type == DT_LNK && state->opt->follow_link == OFF)	/* don't follow simlink*/
						return SUCCESS;
					if (print_file(path, ent, rec_level,state) == FAILURE)
						continue;
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
	if (stat(path, &file_status) <0) {
		perror("Error: ");
		return FAILURE;		
	}
	/* Check if file or Folder */
	if (file_status.st_mode & S_IFDIR) {
		return browse_dir(path, rec_level, state); /* it's a folder */
	}

	
	/* it's a file , so we print it */
	if (state->opt->color == ON)
		printf("%s%s ",BLUE, path);
	else 
		printf("%s ", path);
	if (state->opt->mode == ON && state->opt->verbose == ON) {	
		if (print_mode(path, state) == FAILURE)
			return -1;
	}
	if (print_size(path, state) == FAILURE)
		return -1;
	state->nb_files++;
	return SUCCESS;
	}	

	
