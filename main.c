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
	unsigned long nb_files=0, nb_folders=0, size=0;
	if(argc>1){
		browse_dir(argv[1], 0,&nb_files,&nb_folders);
		print_total(nb_files, nb_folders, size);
	}else printf("Please provide filename\n");
	return 1;
}

