
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
#include "print.h"

PRIVATE int print_dir(char* path, struct dirent* ent, unsigned int rec_level, status* state)
{
    int i;
    char* abs_path;

    if (state->opt->display == FILE_ONLY || state->opt->verbose == OFF)
        return SUCCESS;			/* No display on directories */

    if (state->opt->level_ind == ON)
    {
        for (i = 0; i < rec_level; i++)
            printf(TAB);
    }

    else
    {
        if (build_path(path, ent->d_name, &abs_path) == FAILURE)
            return FAILURE;

        if (state->opt->color == ON) 	/* Color on */
            printf("%s%s ", RED, abs_path);

        else							/* Color off */
            printf("%s%s ", NONE, abs_path);

        if (state->opt->mode == ON)  	/* Mode on */
        {
            if (build_path(path, ent->d_name, &abs_path) == FAILURE)
                return FAILURE;

            if (print_mode(abs_path, state) == FAILURE)
                return FAILURE;

            printf("\n");
        }

        else printf("\n");

        free(abs_path);
        return SUCCESS;
    }

    if (state->opt->color == ON) 	/* Color on */
        printf("%s%c %s ", RED, state->opt->dir_sym, ent->d_name);

    else							/* Color off */
        printf("%s%c %s ", NONE, state->opt->dir_sym, ent->d_name);

    if (state->opt->mode == ON)  	/* Mode on */
    {
        if (build_path(path, ent->d_name, &abs_path) == FAILURE)
            return FAILURE;

        if (print_mode(abs_path, state) == FAILURE)
            return FAILURE;

        free(abs_path);
        printf("\n");
    }

    else printf("\n");

    return SUCCESS;
}

PRIVATE int print_file(char* path, struct dirent* ent, unsigned int rec_level, status* state)
{
    int i;
    char* abs_path;

    if (state->opt->verbose == ON && state->opt->level_ind == ON
            && state->opt->display != DIR_ONLY )
    {
        for (i = 1; i < rec_level + 1; i++)
            printf("%s", TAB);
    }

    else
    {
        if (build_path(path, ent->d_name, &abs_path) == FAILURE)
            return FAILURE;

        if (state->opt->verbose == ON && state->opt->display != DIR_ONLY)
        {
            if (state->opt->color == ON)
                printf("%s%s ", BLUE, abs_path);

            else
                printf("%s%s ", NONE, abs_path);
        }

        if (state->opt->mode == ON && state->opt->display != DIR_ONLY &&
                state->opt->verbose == ON)
        {
            if (print_mode(abs_path, state) == FAILURE)
                return FAILURE;
        }

        if (print_size(abs_path, state) == FAILURE)
            return FAILURE;

        free(abs_path);
        return SUCCESS;
    }

    if (state->opt->verbose == ON && state->opt->display != DIR_ONLY)
    {
        if (state->opt->color == ON)
            printf("%s%c %s ", BLUE, state->opt->file_sym, ent->d_name);

        else
            printf("%s%c %s ", NONE, state->opt->file_sym, ent->d_name);
    }

    if (build_path(path, ent->d_name, &abs_path) == FAILURE)
        return FAILURE;

    if (state->opt->mode == ON && state->opt->display != DIR_ONLY &&
            state->opt->verbose == ON)
    {
        if (print_mode(abs_path, state) == FAILURE)
            return FAILURE;
    }

    if (print_size(abs_path, state) == FAILURE)
        return FAILURE;

    free(abs_path);
    return SUCCESS;
}


PRIVATE int print_size(char* path, status* state)
{
    struct stat file_status;
    char* size_conv;

    if (stat(path, &file_status) < 0)
    {
        fprintf(stderr, "Stat failed: %s\n", path);
        return FAILURE;
    }

    state->size_byte += (long)file_status.st_size;

    if (state->opt->verbose == OFF || state->opt->display == DIR_ONLY)
        return SUCCESS;

    if (state->opt->d_size == OFF)
    {
        printf("\n");
        return SUCCESS;
    }

    if (state->opt->hr == ON)
    {
        if (size_convert(file_status.st_size, &size_conv) == FAILURE)
            return FAILURE;

        if (state->opt->color == ON)
            printf("%s- %s\n", YELLOW, size_conv);

        else
            printf("%s- %s\n", NONE, size_conv);

        free(size_conv);
    }

    else
    {
        if (state->opt->color == ON)
            printf("%s- %ld\n", YELLOW, (long)file_status.st_size);

        else
            printf("%s- %ld\n", NONE, (long)file_status.st_size);
    }

    return SUCCESS;
}

PRIVATE int print_mode(char* path, status* state)
{
    char* parsed_mode;
    struct stat file_status;

    if (stat(path, &file_status) < 0)
    {
        fprintf(stderr, "Stat failed: %s\n", path);
        return FAILURE;
    }

    if (parse_mode(file_status.st_mode, &parsed_mode) == FAILURE)
    {
        return FAILURE;
    }

    if (state->opt->color == ON)
        printf("%s[ %s ] ", GREEN, parsed_mode);

    else
        printf("%s[ %s ] ", NONE, parsed_mode);

    free(parsed_mode);
    return SUCCESS;
}

PRIVATE int print_total(status* state)
{
    char* total;

    if (state->opt->hr == ON)
    {
        if (size_convert(state->size_byte, &total) == FAILURE)
            return FAILURE;

        printf("%s\nTotal:\n\t%ld Files\n\t%ld Folders\nSize:\t%s\n", DEFAULT, state->nb_files, state->nb_folders, total);
    }

    else
        printf("%s\nTotal:\n\t%ld Files\n\t%ld Folders\nSize:\t%ld\n", NONE, state->nb_files, state->nb_folders, state->size_byte);

    return SUCCESS;
}
