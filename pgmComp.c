/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Petr Konstantin Milev           */
/***********************************/

/***********************************/
/* pgmComp                         */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

// error handling routines
#include "pgmError.h"
#include "pgmUtility.h"
int compare(pgm *imageLeft, pgm *imageRight);


#define EXIT_NO_ERRORS 0

/***********************************/
/* main routine                    */
/*                                 */
/* CLI parameters:                 */
/* argv[0]: executable name        */
/* argv[1]: input file name        */
/* argv[2]: input file name        */
/* returns 0 on success            */
/* non-zero error code on fail     */
/***********************************/

int main(int argc, char **argv)
	{ /* main() */
	int isError = 0; 

	/* check for correct number of arguments */
	isError = argCountError(argc, "./pgmComp inputImage.pgm inputImage.pgm"); 
	if(isError != 0) 	return isError;

	pgm imageLeft;
    pgm imageRight;

	// read in imageLeft
	isError = readFile(argv[1], &imageLeft);
	if(isError != 0) 	return isError;
	
    // read in imageRight
	isError = readFile(argv[2], &imageRight);
	if(isError != 0) 	return isError;

    // because values are stored as (unsigned char *) 
        // so the binary and ascii values are automatically comparable
    int isDifferent = compare(&imageLeft, &imageRight);

	printf("%s", (isDifferent)? "DIFFERENT": "IDENTICAL");
	return EXIT_NO_ERRORS;
	
	} /* main() */

// return 0 if identical and 1 if different
int compare(pgm *imageLeft, pgm *imageRight){
    // compare dimensions
    if ( (imageLeft->width != imageRight->width)
        && (imageLeft->height != imageRight->height)
        && (imageLeft->maxGray != imageRight->maxGray)
        ){
        return 1; // different
    }
    // compare image data
    for(int i = 0; i < imageLeft->height; i++){
        for(int j = 0; j < imageLeft->width; j++){
            if(imageLeft->imageData[i][j] != imageRight->imageData[i][j]){
                return 1; // different
            }
        }
    }
    
    return 0; //identical
}
