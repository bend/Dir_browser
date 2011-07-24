/*
 * =====================================================================================
 *
 *       Filename:  print.c
 *
 *    Description:  prints the dir or file on screen
 *
 *        Version:  1.0
 *        Created:  05.05.2011 11:01:13
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */

#include "print.h"

PRIVATE int print_dir(char* path, struct dirent *ent, unsigned int rec_level, status* state)
{
	int i;
	if (state->opt->display == FILE_ONLY || state->opt->verbose == OFF) 
		return SUCCESS;			/* No display on directories */
	if (state->opt->level_ind == ON){
		for (i=0; i<rec_level; i++)
			printf(TAB);
	}
	if (state->opt->color == ON) 	/* Color on */
		printf("%s%c %s ",RED,state->opt->dir_sym,ent->d_name);
	else							/* Color off */
		printf("%s%c %s ",DEFAULT,state->opt->dir_sym,ent->d_name);
	if (state->opt->mode == ON){	/* Mode on */
		char* abs_path;
		if (build_path(path, ent->d_name, &abs_path) == FAILURE)
			return FAILURE;
		if (print_mode(abs_path,state) == FAILURE)
			return FAILURE;
		free(abs_path);
		printf("\n");
	}else printf("\n");
	return SUCCESS;
}

PRIVATE int print_file(char * path, struct dirent *ent, unsigned int rec_level, status* state)
{
	int i;
	char* abs_path;
	if (state->opt->verbose == ON && state->opt->level_ind == ON 
			&& state->opt->display != DIR_ONLY ) {
		for (i=1; i<rec_level+1; i++)
			printf("%s",TAB);
	}

	if (state->opt->verbose == ON && state->opt->display != DIR_ONLY) {
		if (state->opt->color ==ON)
			printf("%s%c %s ",BLUE,state->opt->file_sym,ent->d_name);
		else 
			printf("%s%c %s ",DEFAULT,state->opt->file_sym,ent->d_name);
	}

	if (build_path(path, ent->d_name, &abs_path) == FAILURE)
		return FAILURE;
	if (state->opt->mode == ON && state->opt->display != DIR_ONLY && 
			state->opt->verbose == ON) {
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
	if (stat(path, &file_status) <0) {
		perror("Stat failed");
		return FAILURE;		
	}
	state->size_byte+=(long)file_status.st_size;
	if (state->opt->verbose == OFF || state->opt->display == DIR_ONLY)
	   return SUCCESS;
	if (state->opt->hr == ON) {
		if (size_convert(file_status.st_size, &size_conv) == FAILURE)
			return FAILURE;
		if (state->opt->color == ON)
			printf("%s- %s\n", YELLOW,size_conv);
		else 
			printf("%s- %s\n", DEFAULT,size_conv);
		free(size_conv);
	} else {
		if (state->opt->color == ON)
			printf("%s- %ld\n", YELLOW, (long)file_status.st_size); 
		else
			printf("%s- %ld\n", DEFAULT, (long)file_status.st_size); 
	}
		return SUCCESS;
}

PRIVATE int print_mode(char* path, status *state)
{
	char* parsed_mode;
	struct stat file_status;
	if (stat(path, &file_status) <0) {
		perror("Stat failed");
		return FAILURE;		
	}
	if (parse_mode(file_status.st_mode, &parsed_mode) == FAILURE){
		perror("Parse mode failed");
		return FAILURE;
	}
	if (state->opt->color == ON)
		printf("%s[ %s ] ",GREEN,parsed_mode);
	else
		printf("%s[ %s ] ",DEFAULT,parsed_mode);
	free(parsed_mode);
	return SUCCESS;
}

PRIVATE int print_total(status *state)
{
	char* total;
	if (state->opt->hr == ON){
		if (size_convert(state->size_byte, &total) == FAILURE)
			return FAILURE;
		printf("%s\nTotal:\n\t%ld Files\n\t%ld Folders\nSize:\t%s\n",DEFAULT,state->nb_files,state->nb_folders, total);
	} else 
		printf("%s\nTotal:\n\t%ld Files\n\t%ld Folders\nSize:\t%ld\n",DEFAULT,state->nb_files,state->nb_folders, state->size_byte);
	return SUCCESS;
}