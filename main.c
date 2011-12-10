
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

#define VERSION "v0.3.4"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>

#include "browsedir.h"
#include "print.h"
#include "status.h"
#include "global.h"
#include "opt.h"

PRIVATE void usage(){
    printf("Usage : browsed [options] path\n");
    printf("Options :\n");
    printf("   | --help\t\t\t: Display this help\n");
    printf("-a | --hidden\t\t\t: Display hidden files\n");
    printf("-A | --no-hidden\t\t: Hide hidden files\n");
    printf("-c | --color\t\t\t: Color display\n");
    printf("-C | --no-color\t\t\t: No color\n");
    printf("-h | --human-readable\t\t: Human readable\n");
    printf("-v | --verbose\t\t\t: Verbose\n");
    printf("-V | --no-verbose\t\t: No verbose\n");
    printf("-m | --mode\t\t\t: Mode display\n");
    printf("-M | --no-mode\t\t\t: No mode display\n");
    printf("-l | --list\t\t\t: Nested display\n");
    printf("-L | --tree\t\t\t: No nested display\n");
    printf("-f | --follow-links\t\t: Follow links and non regular files\n");
    printf("-F | --no-follow-links\t\t: Do not follow links and non regular files\n");
    printf("-t | --total\t\t\t: Total display\n");
    printf("-T | --no-total\t\t\t: No total display\n");
    printf("-d | --depth depth\t\t: Maximum recursion  depth \n");
    printf("-y | --file-symbol symbol\t: Represent file with symbol\n");
    printf("-z | --folder-symbol symbol\t: Represent folder with symbol\n");
    printf("-s | --size \t\t\t: Display size for each file\n");
    printf("-S | --no-size\t\t\t: Hide size for each file\n");
}

PRIVATE void version(){
    printf("browsed %s\n",VERSION);
    printf("http://bend.github.com/Dir_browser\n");
    printf("Author : Ben D.\n");
    printf("dbapps2@gmail.com\n");
    printf("Licensed under  GNU GENERAL PUBLIC LICENSE Version 3\n");
}

PRIVATE int parse_opt(int argc, char** argv, status* state)
{
    int c;
    static struct option long_options[] = {
        {"version", no_argument, NULL, 0},
        {"help", no_argument, NULL, 1},
        {"hidden", no_argument, NULL, 'a'},
        {"color", no_argument, NULL, 'c'},
        {"size", no_argument, NULL, 's'},
        {"human-readable", no_argument, NULL, 'h'},
        {"verbose", no_argument, NULL, 'v'},
        {"mode", no_argument, NULL, 'm'},
        {"tree", no_argument, NULL, 'l'},
        {"follow-links", no_argument, NULL, 'f'},
        {"total", no_argument, NULL, 't'},
        {"depth", required_argument, NULL, 'd'},
        {"file-symbol", required_argument, NULL, 'y'},
        {"folder-symbol", required_argument, NULL, 'z'},
        {"no-hidden", no_argument, NULL, 'A'},
        {"no-color", no_argument, NULL, 'C'},
        {"no-size", no_argument, NULL, 'S'},
        {"no-verbose", no_argument, NULL, 'V'},
        {"no-mode", no_argument, NULL, 'M'},
        {"list", no_argument, NULL, 'L'},
        {"no-follow-links", no_argument, NULL, 'F'},
        {"no-total", no_argument, NULL, 'T'},
        {NULL, 0, NULL, 0}
    };
    int option_index = 0;
    
    while ((c = getopt_long (argc, argv, "sSaAcChHvVmMlLfFtTd:Dy:z:0", long_options, &option_index)) != -1)    /*Parse arguments*/
    {
        switch (c)
        {
            case 0:
                version();
                exit(0);
                break;
            case 1:
                usage();
                exit(0);
                break;
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
                usage();
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
