/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Petr Konstantin Milev           */
/***********************************/

/***********************************/
/* pgmReduce                       */
/***********************************/

/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

// error handling routines
#include "pgmError.h"
#include "pgmUtility.h"

int reduce(pgm *image, pgm *smaller, int reduceFactor);


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
    int reduceFactor = 0;

    /* check for correct number of arguments */
    if (argc == 1){
        printf("Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm");
        return EXIT_NO_ERRORS;
    }else if(argc != 4){
        printf("ERROR: Bad Argument Count");
			/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
    }
    

    reduceFactor = atoi(argv[2]); // (int) str
    // sanity check of reduce factor
    if (reduceFactor <= 0){
        printf("ERROR: Miscellaneous (%s)", "reduce factor must be greater than zero");
        return EXIT_MISCELLANEOUS;
    }

    pgm image;
    pgm smaller;
    // read in image
    isError = readFile(argv[1], &image);
    if(isError != 0) 	return isError;

    smaller.magic_number = image.magic_number;
    smaller.isBinary = image.isBinary;

    isError = reduce(&image, &smaller, reduceFactor);
    if(isError != 0) 	return isError;

    // write out image file
    isError = writeFile(argv[3], &smaller);
        // writeFunction automatically converts to base 10 if flagged as bin
    if(isError != 0) 	return isError;

    printf("REDUCED");
    return 0;

} /* main() */

int reduce(pgm *image, pgm *smaller, int reduceFactor){
    // init smaller pgm 
        // (x + reduceFactor - 1) / reduceFactor == ceil(x/reduceFactor)
    int reducedWidth = (image->width + reduceFactor - 1) / reduceFactor;
    int reducedHeight = (image->height + reduceFactor - 1) / reduceFactor;

    initPgm(smaller, reducedWidth, reducedHeight, image->maxGray);
    // init loops
    int xSmaller = 0;
    int ySmaller = 0;
    for (int i = 0; i < image->height; i+=reduceFactor){
        // skip to only N columns, where N = reduceFactor
        for (int j = 0; j < image->width; j+=reduceFactor){
            // skip to only N rows, where N = reduceFactor
            (smaller->imageData[ySmaller][xSmaller]) = (image->imageData[i][j]);
            xSmaller ++;
        }
        xSmaller = 0;
        ySmaller ++;
    }
    
    
    
    return EXIT_NO_ERRORS;
}
