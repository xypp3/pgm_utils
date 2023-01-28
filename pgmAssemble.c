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

int placeTile(pgm *tile, pgm *big, int yOffset, int xOffset);

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

    if (argc == 1){
		printf("Usage: ./pgmAssemble outputImage.pgm width height (row column inputImage.pgm)+");
		
		return 0;
	}
	else if ((argc - 1) % 3 != 0 && argc <= 6){
		printf("ERROR: Bad Argument Count");
			/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	}
	int width = atoi(argv[2]);
    // dimension check
    if (width < 1 || MAX_IMAGE_DIMENSION < width){
		printf("ERROR: Bad Dimensions (%s)", argv[1]);
		return EXIT_BAD_DIMENSIONS;
	}
	
	int height = atoi(argv[3]);
    // dimension check
    if (height < 1 || MAX_IMAGE_DIMENSION < height){
		printf("ERROR: Bad Dimensions (%s)", argv[1]);
		return EXIT_BAD_DIMENSIONS;
	}

	// assemble first tile
	pgm firstTile;
	isError = readFile(argv[6], &firstTile);
	if( isError != 0 )	return isError;
	// set up bIIIIIIg tile
	pgm big;
	initPgm(&big, width, height, firstTile.maxGray);
	big.magic_number = firstTile.magic_number;
	big.isBinary = firstTile.isBinary;
	
	// assemble tiles of tiles
	int tile_row = 0;
	int tile_column = 0;
	// while loop setup
	int argi = 4; // first arguement to inspec
	while(argv[argi] != NULL){
		switch (argi % 3){
			case 0: ; // ';' fixes statement not label err
				// get tile
				pgm tile;
				isError = readFile(argv[argi], &tile);
				if( isError != 0 )	return isError;

				// place tile in BIG
				isError = placeTile(&tile, &big, tile_row, tile_column);
				if( isError != 0 )	return isError;
				break;
			case 1:
				tile_row = atoi(argv[argi]); // top left pixel to insert
				// row within possible tile rows
				if (tile_row < 0){
					printf("ERROR: Bad Layout");
					return EXIT_BAD_LAYOUT;
				}
				break;
			case 2:
				tile_column = atoi(argv[argi]); // top left pixel to insert
				// col within possible tile col
				if (tile_column < 0){
					printf("ERROR: Bad Layout");
					return EXIT_BAD_LAYOUT;
				}
				break;
			
			default:
				break;
		}
		argi ++; // get next arguement
	}

	// // write assembled BIG pgm to file
	isError = writeFile(argv[1], &big);
	if( isError != 0 )	return isError;

	printf("ASSEMBLED");
	return 0;
} /* main() */

int placeTile(pgm *tile, pgm *big, int yOffset, int xOffset){
	for (int y = 0; y < tile->height; y++){
		for (int x = 0; x < tile->width; x++){
			if(		(y + yOffset < big->height) && (x + xOffset < big->width)		)
				big->imageData[yOffset + y][xOffset + x] = tile->imageData[y][x];
			else
				break;
		}
	}
	return EXIT_NO_ERRORS;
}
