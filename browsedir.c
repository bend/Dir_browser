/*
 *   Copyright © Ben D.
 *   dbapps2@gmail.com
 *
 *   This is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "browsedir.h"


PUBLIC int browse_dir(char* path, unsigned int rec_level, status* state, search_pattern* pattern)
{
    int *size = malloc(sizeof(int));
    int i;
    struct dirent* ent;
    struct dirent* dirs_ent;
    dirs_ent = preload_dir(path, size);

    if(dirs_ent != NULL )
    {
        i = 0;
        while (i< *size)
        {
            char* buffer;
            ent = &dirs_ent[i];

            if (build_path(path, ent->d_name, &buffer) == FAILURE)
                continue;

            if (!strcmp(ent->d_name, ".") == 0 && !strcmp(ent->d_name, "..") == 0 	/* Check that it's not the current dir, parent dir */
                    && (ent->d_name[0] != '.' || state->opt->d_hidden == ON))  		/* And if it is hidden and we don't want to display it */
            {
                if (ent->d_type == DT_DIR) /* Directory */
                {
                    print_dir(path, ent, rec_level, state);
                    state->nb_folders++;

                    if (state->opt->depth < rec_level)
                        return SUCCESS;	 /* Max depth reached */

                    if (browse_dir(buffer, rec_level + 1, state, pattern) == FAILURE)
                        continue;
                }

                else
                {
                    if (ent->d_type == DT_LNK && state->opt->follow_link == OFF)	/* don't follow simlink*/
                        return SUCCESS;

                    if (print_file(path, ent, rec_level, state) == FAILURE){
                        ++i;
                        free(buffer);
                        continue;
                    }
                    state->nb_files++;
                }
            }

            free(buffer);
            ++i;
        }
    }
    free(size);
    free(dirs_ent);

    return SUCCESS;
}

PUBLIC int start_browse(char* path, unsigned int rec_level, status* state, search_pattern* pattern)
{
    struct stat file_status;

    if (stat(path, &file_status) < 0)
    {
        fprintf(stderr, "Stat failed: %s\n", path);
        return FAILURE;
    }

    /* Check if file or Folder */
    if (file_status.st_mode & S_IFDIR)
    {
        return browse_dir(path, rec_level, state, pattern); /* it's a folder */
    }

    /* it's a file , so we print it */
    if (state->opt->color == ON)
        printf("%s%s ", BLUE, path);

    else
        printf("%s ", path);

    if (state->opt->mode == ON && state->opt->verbose == ON)
    {
        if (print_mode(path, state) == FAILURE)
            return -1;
    }

    if (print_size(path, state) == FAILURE)
        return -1;

    state->nb_files++;
    return SUCCESS;
}


PRIVATE struct dirent* preload_dir(char* path, int* size)
{
    DIR* dir;
    struct dirent* dirs_ent;
    int i = 0;
    *size = 0;
    /* First get Size */
    if((dir = opendir(path)) == NULL)
        return NULL;
    while ( readdir(dir) != NULL)
        ++(*size);
    rewinddir(dir);
    /* Put all the dirent in an array */
    dirs_ent = malloc(*size*sizeof(struct dirent));
    if(dirs_ent == NULL){
        perror("Malloc failed");
        return NULL;
    }
    while(i < *size)
    {
        dirs_ent[i] = *readdir(dir);
        ++i;
    }
    closedir(dir);
    return dirs_ent;
}

