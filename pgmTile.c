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
#include <string.h>

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
    int tileNumber = 0;

	/* check for correct number of arguments */
	if (argc == 1){
		printf("Usage: ./pgmTile inputImage.pgm tiling_factor outputImage_<row>_<column>.pgm");
		return 0;
	}
	else if (argc != 4){
		printf("ERROR: Bad Argument Count");
			/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	}
	

    // get tiling factor
    tileNumber = atoi(argv[2]);
    // sanity check of reduce factor
    if (tileNumber <= 0){
        printf("ERROR: Miscellaneous %s", "tiling factor must be greater than zero");
        return EXIT_MISCELLANEOUS;
    }

	//check correct format AND get output filename string
	const char template[20] = "_<row>_<column>.pgm";
	int finalIndex = 18; // template[19] = '\0'
	int lenFileName = strlen(argv[3]);
	if (20 <= lenFileName){ // len(template) < len(argv[3])
		// check if output file, contains right pattern "_<row>_<column>.pgm"
		for (int i = lenFileName - 1; i >= 0; i--){
			if (finalIndex == -1){
				argv[3][i+1] = '\0'; // removes pattern from filename
				break;
			}else if (template[finalIndex] != argv[3][i]){
				return fileNameError(NULL, argv[3]);
			}
			finalIndex --;
		}
	}else{
		printf("ERROR: Miscellaneous (wrong tile template)");
		return EXIT_MISCELLANEOUS;
	}
	
    
	pgm image;
	// read in image
	isError = readFile(argv[1], &image);
	if(isError != 0) 	return isError;
    
	for (int yOffset = 0; yOffset < tileNumber; yOffset ++){
		for (int xOffset = 0; xOffset < tileNumber; xOffset ++){
			// set up tile
			pgm tile;
			tile.isBinary = image.isBinary;
			tile.magic_number = image.magic_number;
			int tileX = image.width / (tileNumber);
			int tileY = image.height / (tileNumber);
			initPgm(&tile, tileX, tileY, image.maxGray);
			// get tile image data
			for (int yRelative = 0; yRelative < tileY; yRelative++){
				for (int xRelative = 0; xRelative < tileX; xRelative++){
					tile.imageData[yRelative][xRelative] = image.imageData[(yOffset * tileY) + yRelative][(xOffset * tileX) + xRelative];
				}
			}
			// create tile filename
			char *filename = (char *) malloc(strlen(argv[3]) + 15); // max 5 digit row, max 5 digit col, 5 chars for formatting
			sprintf(filename, "%s_%i_%i.pgm", argv[3], yOffset, xOffset);

			// printf("%i %i %s ", yOffset*tileY, xOffset*tileX, filename);
			
			// write to tile file
			isError = writeFile(filename, &tile);
			if (isError != 0)	 return isError;
			
		}
	}

	printf("TILED");
	return 0;
	
} /* main() */
