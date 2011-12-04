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


PRIVATE struct dirent** preloadDir(char* path, int* size)
{
    DIR* dir;
    struct dirent** dirsEnt;
    int i = 0;
    *size = 0;
    /* First get Size */
    if((dir = opendir(path)) == NULL)
        return NULL;
    while ( readdir(dir) != NULL)
        ++(*size);
    rewinddir(dir);
    /* Put all the dirent in an array */
    dirsEnt = malloc(*size*sizeof(struct dirent));
    while(i < *size)
    {
        dirsEnt[i] = readdir(dir);
        ++i;
    }
    printf("Nb subs : %d", *size);
    return dirsEnt;
}

PUBLIC int browse_dir(char* path, unsigned int rec_level, status* state)
{
    int size;
    struct dirent* ent;
    DIR* dir;
    struct dirent** dirsEnt;
    int i = 0;
    size = 0;
    
    /* First get Size */
    if((dir = opendir(path)) == NULL){
        perror("OpenDir failred: ");
        return FAILURE;
    }
    while ( readdir(dir) != NULL)
        ++size;
    rewinddir(dir);
    /* Put all the dirent in an array */
    dirsEnt = malloc(size*sizeof(struct dirent));
    while(i < size)
    {
        dirsEnt[i] = readdir(dir);
        ++i;
    }
    
    if(dirsEnt != NULL && *dirsEnt != NULL)
    {
        i = 0;
        while (i< size)
        {
            char* buffer;
            ent = dirsEnt[i];
            printf("ent->dname : %s\n", ent->d_name);

            if (build_path(path, ent->d_name, &buffer) == FAILURE)
                continue;
            printf("NEw path : %s", path);

            if (!strcmp(ent->d_name, ".") == 0 && !strcmp(ent->d_name, "..") == 0 	/* Check that it's not the current dir, parent dir */
                    && (ent->d_name[0] != '.' || state->opt->d_hidden == ON))  		/* And if it is hidden and we don't want to display it */
            {
                if (ent->d_type == DT_DIR )  										/* Directory */
                {
                    print_dir(path, ent, rec_level, state);
                    state->nb_folders++;

                    if (state->opt->depth < rec_level)
                        return SUCCESS;	 /* Max depth reached */

                    if (browse_dir(buffer, rec_level + 1, state) == FAILURE)
                        continue;
                }

                else
                {
                    if (ent->d_type == DT_LNK && state->opt->follow_link == OFF)	/* don't follow simlink*/
                        return SUCCESS;

                    if (print_file(path, ent, rec_level, state) == FAILURE)
                        continue;

                    state->nb_files++;
                }
            }

            free(buffer);
            ++i;
        }
    }

    return SUCCESS;
}

PUBLIC int start_browse(char* path, unsigned int rec_level, status* state)
{
    struct stat file_status;

    if (stat(path, &file_status) < 0)
    {
        perror("Error: ");
        return FAILURE;
    }

    /* Check if file or Folder */
    if (file_status.st_mode & S_IFDIR)
    {
        return browse_dir(path, rec_level, state); /* it's a folder */
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


