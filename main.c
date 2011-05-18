/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  Main file for browsed
 *
 *        Version:  1.0
 *        Created:  05.05.2011 11:24:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "browsedir.h"
#include "print.h"
#include "status.h"
#include "global.h"
#include "opt.h"

PUBLIC int main(int argc, char** argv)
{
	if(argc>1){
		status *state;
		if (alloc_status(&state) == FAILURE)
			return EXIT_FAILURE;
		if (start_browse(argv[1], 0, state) == FAILURE)
			return EXIT_FAILURE;
		if (state->opt->d_total == ON)
			print_total(state);
		free(state);
	}else printf("Please provide filename\n");
	return EXIT_SUCCESS;
}

