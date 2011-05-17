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

PUBLIC int main(int argc, char** argv)
{
	if(argc>1){
		status *stat;
		if(alloc_status(&stat) == FAILURE)
			return EXIT_FAILURE;
		if(	browse_dir(argv[1], 0, stat) == FAILURE)
			return EXIT_FAILURE;
		print_total(stat);
		free(stat);
	}else printf("Please provide filename\n");
	return 1;
}

