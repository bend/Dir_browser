/*
 * =====================================================================================
 *
 *       Filename:  global.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  04.05.2011 16:39:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Ben D. (BD), dbapps2@gmail.com
 *        Company:  dbapps
 *
 * =====================================================================================
 */
#ifndef __GLOBAL_H__
#define __GLOBAL_H__
#define _PROTOTYPE( function,  params  )			function params 
#define _PUBLIC
#define _PRIVATE

#define SUCCESS										0		/* Success code */
#define FAILURE										-1		/* Failure code */
#define MAX_PATH									4096	/* Maximum length of the path */
#define DIR_SYM										"+"		/* The directory symbol */
#define FILE_SYM									"|"		/* The File symbol */
#define TAB											"    "	/* The default tabultation */

#endif
