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
_PUBLIC int main(int argc, char** argv)
{
	if(argc>1){
		status *stat;
		alloc_status(&stat);
		browse_dir(argv[1], 0, stat);
	}else printf("Please provide filename\n");
	return 1;
}

