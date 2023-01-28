/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Petr Konstantin Milev           */
/***********************************/

/***********************************/
/* pgmEcho                         */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

// error handling routines
// #include "pgmEcho.h"
#include "pgmError.h"
#include "pgmUtility.h"


#define EXIT_NO_ERRORS 0

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: output file name       */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int main(int argc, char **argv)
	{ /* main() */
	int isError = 0;

	/* check for correct number of arguments */
	isError = argCountError(argc, "./pgmEcho inputImage.pgm outputImage.pgm"); 
	if(isError != 0) 	return isError;

	pgm image;

	// read in image
	isError = readFile(argv[1], &image);
	if(isError != 0) 	return isError;

	// write out image file
	isError = writeFile(argv[2], &image);
	if(isError != 0) 	return isError;

	printf("ECHOED");
	return 0;
	
	} /* main() */
