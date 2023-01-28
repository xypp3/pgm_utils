/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Petr Konstantin Milev           */
/***********************************/

/***********************************/
/* pgm2b                           */
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
	isError = argCountError(argc, "./pgma2b inputImage.pgm outputImage.pgm"); 
	if(isError != 0) 	return isError;

	pgm image;

	// read in image
	isError = readFile(argv[1], &image);
	if(isError != 0) 	return isError;

    if(image.isBinary){
        printf("ERROR: Bad Magic Number (%s)", argv[1]);
		return EXIT_BAD_MAGIC_NUMBER;
    }

    image.isBinary = 1; // set flag to binary 

	// write out image file
	isError = writeFile(argv[2], &image);
        // writeFunction automatically converts to base 10 if flagged as bin
	if(isError != 0) 	return isError;

	printf("CONVERTED");
	exit(0);
	
	} /* main() */
