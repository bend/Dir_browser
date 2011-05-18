/*
 * =====================================================================================
 *
 *       Filename:  opt.c
 *
 *    Description:  Options select
 *
 *        Version:  1.0
 *        Created:  17.05.2011 23:50:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */

#include "opt.h"

PUBLIC int alloc_options(options** opt) 
{
	*opt = malloc(sizeof(options));
	if (*opt == NULL) {
		perror("Malloc failed");
		return FAILURE;
	}
	(*opt)->color = ON;			/* color is on by default */
	(*opt)->hr = ON;			/* hr on by default */
	(*opt)->verbose = ON;		/* verbose on by defaut */
	(*opt)->mode = ON;			/* mode is on by default */
	(*opt)->level_ind = ON;		/* indent on by default */
	(*opt)->depth = OFF;		/* no max_depth by default */
	(*opt)->display = BOTH;		/* display all files by default */
	(*opt)->dir_sym = DIR_SYM; 	/* default symbol */
	(*opt)->file_sym = FILE_SYM;/* default symbol */
	(*opt)->follow_link = OFF;	/* do not follow links */
	(*opt)->d_hidden = OFF;		/* do not display hidden files/folders by default */
	(*opt)->d_total = ON;		/* display grand total */
	return SUCCESS;
}

PUBLIC void free_options(options* opt)
{
	free(opt);
}
