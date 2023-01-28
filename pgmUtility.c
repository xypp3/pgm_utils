#include <stdio.h>
#include <stdlib.h>

#include "pgmUtility.h"
#include "pgmError.h"


// disable warnings for strol(const char *n, ...)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpointer-sign"

// code vvvvvvvv
int initPgm(pgm *image, int width, int height, int maxGray){
    image->width = width; // width init
    image->height = height; // height init
    image->maxGray = maxGray; // maxGray init
    // number of columns
    image->imageData = (unsigned char **) malloc(height * sizeof(unsigned char *));
    for (int i = 0; i < height; i++){
        // length of rows
        image->imageData[i] = (unsigned char *) malloc(width * sizeof(unsigned char));
    }
    
    return EXIT_NO_ERRORS;
}

int readFile(char *filename, pgm *image){
    /* init values*/
    int isError = 0;
    // open file
    FILE *inputFile = fopen(filename, "r");
        // sanity check
    isError = fileNameError(inputFile, filename);
    if(isError != 0)	return isError;
    // read magic num
    isError = readMagicNum(inputFile, image, filename);
    if (isError != 0)   return isError;
    // read head data
    isError = readHeaderData(inputFile, image);
    if (isError != 0)   return isError;
    // check dimensions
    isError = dimensionsError(inputFile, image->width, image->height, filename);
    if (isError != 0)   return isError;
    // check grey value
    isError = maxGrayValueError(inputFile, image->maxGray, filename);
    if (isError != 0)   return isError;
    // read pgm image data
    isError = readImageData(inputFile, image, filename);
    if (isError != 0)   return isError;
    
    fclose(inputFile);

    return EXIT_NO_ERRORS;
}


int readMagicNum(FILE *inputFile, pgm *image, char *filename){
    int isError = 0;
     /* read magic num */
    unsigned char magic_chars[2] = {'0', '0'};

    // read magic num
    magic_chars[0] = getc(inputFile);
    magic_chars[1] = getc(inputFile);
    image->magic_number = *((unsigned short *) magic_chars); // 0x3250 or 0x3550
        // check if magic num correct
    isError = magicNumberError(inputFile, image->magic_number, filename);
    if(isError != 0)	return isError;
    // flag if binary file 
    image->isBinary = ( image->magic_number == 0x3550 ); 
    
    return EXIT_NO_ERRORS;
}


int readHeaderData(FILE *inputFile, pgm *image){
    int isError = 0;

    // get all comments before width, height, and maxGray
    isError = checkComment(inputFile);
    if ( isError != 0 ) return isError;
    
    fscanf(inputFile, " %u %u ", &image->width, &image->height);
    
    // get all commments before maxGray
    isError = checkComment(inputFile);
    if ( isError != 0 ) return isError;

    fscanf(inputFile, " %u ", &image->maxGray);
    
    return EXIT_NO_ERRORS;
}


int readImageData(FILE *inputFile,  pgm *image, char *filename){
    int isError = 0;

    // min calloc/malloc amount is 8bytes because 64bit system
        // number of columns
    image->imageData = (unsigned char **) malloc(image->height * sizeof(unsigned char *));
    isError = imageMallocError(inputFile, (char *) image->imageData, filename);
	if(isError != 0)	return isError;
    
    for (int i = 0; i < image->height; i++){
        // length of rows
        image->imageData[i] = (unsigned char *) malloc(image->width * sizeof(unsigned char));
        isError = imageMallocError(inputFile, image->imageData[i], filename);
	    if(isError != 0)	return isError;
    }

    int image_exit_code = 0;
    if (image->isBinary){
        image_exit_code = readBinary(image, inputFile);
    }else{
        image_exit_code = readAscii(image, inputFile, filename);
    }

    if (image_exit_code != EXIT_NO_ERRORS){
        return image_exit_code;
    }
    

    return image_exit_code;
}

int checkComment(FILE *input){
    // get next char
    char nextChar;
    fscanf(input, " %c", &nextChar);

    // check if comment line
    while(nextChar == '#'){
        int commentLen = 0;
        // read comment line
        while (getc(input) != '\n'){
            if(commentLen >= 128) 
                return EXIT_BAD_COMMENT_LINE; // comment line error
            commentLen++;
        }
        // get first char in next line
        fscanf(input, " %c", &nextChar);
    }
    
    fseek(input, -1, SEEK_CUR); // move pointer back by 1
    return EXIT_NO_ERRORS;
}


int writeFile(char *filename, pgm *image){
    int isError = 0;
    
    /* open a file for writing               */
	FILE *outputFile = fopen(filename, "w");

	/* check whether file opening worked     */
	isError = outputFailedError(outputFile, image->imageData, image->height, filename);
	if(isError != 0)	return isError;

	/* write magic number, size & gray value */
	int nBytesWritten = fprintf(outputFile, "%s\n%d %d\n%d\n", 
        ((image->isBinary)? "P5": "P2"), image->width
        , image->height, image->maxGray)
        ;
	/* check that dimensions wrote correctly */
	isError = outputDimensionError( image->imageData, nBytesWritten, image->height, filename);
	if(isError != 0)	return isError;

    if (image->isBinary){
        writeBinary(image, outputFile);
    }else{
        writeAscii(image, outputFile);
    }
    
    // after writing close file
    fclose(outputFile);

    return EXIT_NO_ERRORS; /* per gray value */

}

int writeBinary(pgm *image, FILE *output){
    for(int i = 0; i < image->height; i++){
        // writes data row by row
        fwrite(image->imageData[i], 1, image->width, output);
        free(image->imageData[i]); // freeing each row
    }
    free(image->imageData); // free all columns
    return EXIT_NO_ERRORS;
}

int writeAscii(pgm *image, FILE *output){
    for(int i = 0; i < image->height; i++){ // height
        // write a row
        for(int j = 0; j < image->width; j++){
            char endChar = (j+1<image->width?' ':'\n'); // space or newline
            fprintf(output, "%d%c", image->imageData[i][j], endChar);
        }
        free(image->imageData[i]); // freeing each row
    }
    free(image->imageData); // free all columns
    return EXIT_NO_ERRORS;
}

int readBinary(pgm *image, FILE *input){
    for (int i = 0; i < image->height; i++){ // read each row
        int dataRead = fread(image->imageData[i], 1, image->width, input);

        // check for too little data
        if (dataRead != image->width){	
		    return EXIT_BAD_DATA;
        }
    }
    // TODO: too much data (fix code below)
    
    if (fgetc(input) != EOF){ // check if there is too much data	
		return EXIT_BAD_DATA;
    }
    return EXIT_NO_ERRORS;
}

int readAscii(pgm *image, FILE *input, char *filename){
    int isError = 0;
    // read row by row then column by column
    for(int i = 0; i < image->height; i++){
        for (int j = 0; j < image->width; j++){
            unsigned int data;
            int charFound = fscanf(input, "%u ",  &data);
            // too little data error
            isError = badDataError(input, image->imageData, image->height, charFound, image->maxGray, filename);
            if ( isError != 0 ) return isError;
            // add data if no errors
            image->imageData[i][j] = (unsigned char) data;
        }
    }

    char lastChar;
    if (fscanf(input, " %c", &lastChar) > 0)
        return badDataError(input, image->imageData, image->height, 0, image->maxGray, filename);
    
    return EXIT_NO_ERRORS;
}