/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Petr Konstantin Milev           */
/***********************************/


/* library for I/O routines        */
#include <stdio.h>

/* library for memory routines     */
#include <stdlib.h>

//my headers
#include "pgmError.h"
#include "pgmUtility.h"
// ERROR CODES 


/* check for correct number of arguments */
int argCountError(int argc, char *usage){
	if (argc != 3)	
	{ /* wrong arg count */

		if(argc == 1){ /* print an error message        */
			printf("Usage: %s", usage);
			exit(0);
		}else{
			printf("ERROR: Bad Argument Count");
			/* and return an error code      */
			return EXIT_WRONG_ARG_COUNT;
		}
	}
	return EXIT_NO_ERRORS;
}
/* check for correct number of arguments */
int reduceArgCountError(int argc, char *usage){
	if (argc != 4)	
	{ /* wrong arg count */

		if(argc == 1){ /* print an error message        */
			printf("Usage: %s", usage);
		}else{
			printf("ERROR: Bad Argument Count\n");
		}		
		/* and return an error code      */
		return EXIT_WRONG_ARG_COUNT;
	}
   	return EXIT_NO_ERRORS;
}

/* if file exists */
int fileNameError(FILE *inputFile, char *filename){
	if (inputFile == NULL){
    		// print err msg
		printf("ERROR: Bad File Name (%s)\n", filename);
		/* if it fails, return error code        */
		return EXIT_BAD_FILE_NAME;
	}
    return EXIT_NO_ERRORS;
}
/* sanity check on the magic number      */
int magicNumberError(FILE *inputFile,unsigned short magic_Number, char *filename){ 
	if (magic_Number != MAGIC_NUMBER_ASCII_PGM && magic_Number != MAGIC_NUMBER_RAW_PGM)
		{ /* failed magic number check   */
		/* be tidy: close the file       */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Magic Number (%s)", filename);	
		
		/* and return                    */
		return EXIT_BAD_MAGIC_NUMBER;
		} /* failed magic number check   */
    return EXIT_NO_ERRORS; // succeeds check
}
/* bad comment line error, where null == error            */
//todo: deal with comment line error
int commentLineError(FILE *inputFile, char *commentLine, char *filename){
	if (commentLine == NULL)
		{ /* NULL comment read   */
			/* free memory           */
		free(commentLine);
			/* close file            */
		fclose(inputFile);

			/* print an error message */
		printf("ERROR: Bad Comment Line (%s)", filename);	
		
			/* and return            */
		return EXIT_BAD_COMMENT_LINE;
	} /* NULL comment read   */
    return EXIT_NO_ERRORS;
}

/* sanity checks on size        */
    /* must read exactly three values        */
int dimensionsError(FILE *inputFile, int width, int height, char *filename)
	{
	if 	(
		(width 	< MIN_IMAGE_DIMENSION) 	||
		(width 	> MAX_IMAGE_DIMENSION) 	||
		(height < MIN_IMAGE_DIMENSION) 	||
		(height > MAX_IMAGE_DIMENSION) 
		)
		{ /* failed size sanity check    */
		/* free up the memory            */

		/* be tidy: close file pointer   */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Bad Dimensions (%s)", filename);	
		
		/* and return                    */
		return EXIT_BAD_DIMENSIONS;
		} /* failed size sanity check    */
    return EXIT_NO_ERRORS;
}
/* check greys */
int maxGrayValueError(FILE *inputFile, int maxGray, char *filename){
    if(maxGray != 255){ // upon fail
        //freeing memory 
        
        free(inputFile);

        printf("ERROR: Bad Max Gray Value (%s)", filename);

    	return EXIT_BAD_MAX_GRAY_VALUE;
    }
    return EXIT_NO_ERRORS;
}
	/* sanity check for memory allocation    */
int imageMallocError(FILE *inputFile, unsigned char *imageData, char *filename){
	if (imageData == NULL)
		{ /* malloc failed */
		/* free up memory                */
		
		/* close file pointer            */
		fclose(inputFile);

		/* print an error message */
		printf("ERROR: Image Malloc Failed (%s)", filename);	
		
		/* return error code             */
		return EXIT_BAD_IMAGE_MALLOC;
		} /* malloc failed */
	return EXIT_NO_ERRORS;
}
/* sanity check	                 */
int badDataError(FILE *inputFile,  unsigned char **imageData, int height, int scanCount, int grayValue, char *filename){
	if ((scanCount != 1) || (grayValue < 0) || (grayValue > 255))
		{ /* fscanf failed */
		/* free memory           */
		
		for (int i = 0; i < height; i++){
			free(imageData[i]);
		}
		free(imageData);

		/* close file            */
		fclose(inputFile);

		/* print error message   */
		printf("ERROR: Bad Data (%s)", filename);	
		
		/* and return            */
		return EXIT_BAD_DATA;
	} /* fscanf failed */
	return EXIT_NO_ERRORS;
}
	/* check whether file opening worked     */
int outputFailedError(FILE *outputFile, unsigned char **imageData, int height, char *filename){
	if (outputFile == NULL)
		{ /* NULL output file */
		/* free memory                   */
		
		for (int i = 0; i < height; i++){
			free(imageData[i]);
		}
		free(imageData);

		/* print an error message        */
		printf("ERROR: Output Failed (%s)", filename);	

		/* return an error code          */
		return EXIT_OUTPUT_FAILED;
		} /* NULL output file */
	return EXIT_NO_ERRORS;
}
	/* check that dimensions wrote correctly */
	// todo: do a better check for checking if data was written correctly
int outputDimensionError(unsigned char **imageData, int nBytesWritten, int height, char *filename){ 
	if (nBytesWritten < 0)
	{ /* dimensional write failed    */
		/* free memory                   */
		
		for (int i = 0; i < height; i++){
			free(imageData[i]);
		}
		free(imageData);

		/* print an error message        */
		printf("ERROR: Output Failed (%s)", filename);	

		/* return an error code          */
		return EXIT_OUTPUT_FAILED;
	} /* dimensional write failed    */
	return EXIT_NO_ERRORS;
}
