
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

#include "utils.h"

PUBLIC int build_path(char* path, char* filename, char** res)
{
    *res = malloc(sizeof(char) * MAX_PATH);

    if (*res == NULL)
    {
        perror("Malloc failed");
        return FAILURE;
    }
    strcpy(*res, path);
    if(strlen((path)) != 1 || path[0] != '/')
        strcat(*res, "/");
    strcat(*res, filename);
    return SUCCESS;
}

PUBLIC int parse_mode(mode_t mode, char** parsed)
{
    char temp[] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
    *parsed = malloc(sizeof(char) * 10);

    if (*parsed == NULL)
    {
        perror("Malloc failed");
        return FAILURE;
    }

    if (mode & S_IRUSR) temp[0] = 'r';

    if (mode & S_IWUSR) temp[1] = 'w';

    if (mode & S_IXUSR) temp[2] = 'x';

    if (mode & S_IRGRP) temp[3] = 'r';

    if (mode & S_IWGRP) temp[4] = 'w';

    if (mode & S_IXGRP) temp[5] = 'x';

    if (mode & S_IROTH) temp[6] = 'r';

    if (mode & S_IWOTH) temp[7] = 'w';

    if (mode & S_IXOTH) temp[8] = 'x';

    strncpy(*parsed, temp, 10);
    return SUCCESS;
}

PUBLIC int size_convert(unsigned long size, char** converted)
{
    double conv_size;
    *converted = malloc(sizeof(char) * 256);

    if (*converted == NULL)
    {
        perror("Malloc failed");
        return FAILURE;
    }

    /* Check if is Tera */
    if ((size / 1e12) > 1)
    {
        conv_size = size / 1e12;
        gcvt(conv_size, 5, *converted);
        strncat(*converted, " TB", 3);
    }

    else if ((size / 1e9) > 1)
    {
        conv_size = size / 1e9;
        gcvt(conv_size, 5, *converted);
        strncat(*converted, " GB", 3);
    }

    else if (size / 1e6 > 1)
    {
        conv_size = size / 1e6;
        gcvt(conv_size, 5, *converted);
        strncat(*converted, " MB", 3);
    }

    else if (size / 1e3 > 1)
    {
        conv_size = size / 1e3;
        gcvt(conv_size, 5, *converted);
        strncat(*converted, " KB", 3);
    }

    else
    {
        conv_size = size;
        gcvt(conv_size, 5, *converted);
        strncat(*converted, " B", 3);
    }

    return SUCCESS;
}
