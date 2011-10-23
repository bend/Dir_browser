/*
 * =====================================================================================
 *
 *       Filename:  status.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05.05.2011 12:23:54
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */

#include "status.h"

PUBLIC int alloc_status(status** stat)
{
    *stat = malloc(sizeof(status));

    if (*stat == NULL)
    {
        perror("Malloc failed");
        return FAILURE;
    }

    (*stat)->nb_folders = 0;
    (*stat)->nb_files   = 0;
    (*stat)->size_byte  = 0;

    if (alloc_options(&((*stat)->opt)) == FAILURE)
        return FAILURE;

    return SUCCESS;
}

PUBLIC void free_status(status* stat)
{
    free_options(stat->opt);
    free(stat);
}
