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
#include <getopt.h>
#include <string.h>

#include "browsedir.h"
#include "print.h"
#include "status.h"
#include "global.h"
#include "opt.h"

PRIVATE void print_help(){
    printf("Usage : browsed [options] path\n");
    printf("Options :\n");
    printf("-a : Display hidden files\n");
    printf("-A : Hide hidden files\n");
    printf("-c : Color display\n");
    printf("-C : No color\n");
    printf("-h : Human readable\n");
    printf("-H : No human readable\n");
    printf("-v : Verbose\n");
    printf("-V : No verbose\n");
    printf("-m : Mode display\n");
    printf("-M : No mode display\n");
    printf("-l : Nested display\n");
    printf("-L : No nested display\n");
    printf("-f : Follow links and non regular files\n");
    printf("-F : Do not follow links and non regular files\n");
    printf("-t : Total display\n");
    printf("-T : No total display\n");
    printf("-d depth : Maximum recursion  depth \n");
    printf("-D : No maximum recursion depth\n");
    printf("-y symbol : Represent file with symbol\n");
    printf("-z symbol : Represent folder with symbol\n");
    printf("-s : Display size for each file\n");
    printf("-S : Hide size for each file\n");

}

PRIVATE int parse_opt(int argc, char** argv, status* state)
{
    int c;

    while ((c = getopt (argc, argv, "sSaAcChHvVmMlLfFtTd:Dy:z:")) != -1)    /*Parse arguments*/
    {
        switch (c)
        {
            case 'a':		/* show hidden files/folders */
                state->opt->d_hidden = ON;
                break;

            case 'c':		/* display with colors */
                state->opt->color = ON;
                break;

            case 's':       /* display size for each file */
                state->opt->d_size = ON;
                break;

            case 'h':		/* human readable */
                state->opt->hr = ON;
                break;

            case 'v':		/* verbose */
                state->opt->verbose = ON;
                break;

            case 'm':		/* mode display */
                state->opt->mode = ON;
                break;

            case 'l':		/* indent */
                state->opt->level_ind = ON;
                break;

            case 'f':		/* follow links */
                state->opt->follow_link = ON;
                break;

            case 't':		/* display total */
                state->opt->d_total = ON;
                break;

            case 'd':		/* depth */
                state->opt->depth = strtol((char*)optarg, NULL, 10);
                break;

            case 'y':		/* file symbol */
                state->opt->file_sym = ((char*)optarg)[0];
                break;

            case 'z':		/* folder symbol */
                state->opt->dir_sym = ((char*)optarg)[0];
                break;

            case 'A':		/* show hidden files/folders */
                state->opt->d_hidden = OFF;
                break;

            case 'C':		/* display with colors */
                state->opt->color = OFF;
                break;

            case 'S':       /* hide size for each file */
                state->opt->d_size = OFF;
                break;

            case 'H':		/* human readable */
                state->opt->hr = OFF;
                break;

            case 'V':		/* verbose */
                state->opt->verbose = OFF;
                break;

            case 'M':		/* mode display */
                state->opt->mode = OFF;
                break;

            case 'L':		/* indent */
                state->opt->level_ind = OFF;
                break;

            case 'F':		/* follow links */
                state->opt->follow_link = OFF;
                break;

            case 'T':		/* display total */
                state->opt->d_total = OFF;
                break;

            case 'D':		/* depth */
                state->opt->depth = OFF;
                break;

            default:
                print_help();
                return FAILURE;
                break;
        }
    }

    return SUCCESS;
}



PUBLIC int main(int argc, char** argv)
{
    status* state;
    char path[MAX_PATH];
    int len = 0;

    if (alloc_status(&state) == FAILURE)
        return EXIT_FAILURE;

    if (parse_opt(argc, argv, state) == FAILURE)
        return EXIT_FAILURE;

    /* if no path provided take the current one */
    if (argc == 1)
    {
        strncpy(path, ".\0", 2);
        len = 1;
    }

    /* check that the last arg is not an option */
    else
    {
        strncpy(path, argv[argc - 1], strlen(argv[argc - 1]));
        len = strlen(argv[argc - 1]);
        path[len ] = '\0';

        if (path[0] == '-')
            strncpy(path, ".\0", 2);
    }
    
    if (start_browse(path, 0, state) == FAILURE)
        return EXIT_FAILURE;

    if (state->opt->d_total == ON)
        print_total(state);

    free(state);
    return EXIT_SUCCESS;
}
