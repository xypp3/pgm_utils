/***********************************/
/* COMP 1921M Programming Project  */
/* 2021-22 Spring Semester         */
/*                                 */
/* Petr Konstantin Milev           */
/***********************************/

// defintions 
    // errors
#define EXIT_NO_ERRORS 0
#define EXIT_WRONG_ARG_COUNT 1
#define EXIT_BAD_FILE_NAME 2
#define EXIT_BAD_MAGIC_NUMBER 3
#define EXIT_BAD_COMMENT_LINE 4
#define EXIT_BAD_DIMENSIONS 5
#define EXIT_BAD_MAX_GRAY_VALUE 6
#define EXIT_BAD_IMAGE_MALLOC 7
#define EXIT_BAD_DATA 8
#define EXIT_OUTPUT_FAILED 9
#define EXIT_BAD_LAYOUT 10
#define EXIT_MISCELLANEOUS 100
    // other key def
#define MAGIC_NUMBER_RAW_PGM 0x3550
#define MAGIC_NUMBER_ASCII_PGM 0x3250
#define MIN_IMAGE_DIMENSION 1
#define MAX_IMAGE_DIMENSION 65535
#define MAX_COMMENT_LINE_LENGTH 128


/* check for correct number of arguments */
int argCountError(int argc, char *usage);
int reduceArgCountError(int argc, char *usage);
/* if file exists */
int fileNameError(FILE *inputFile, char *filename);
/* sanity check on the magic number      */
int magicNumberError(FILE *inputFile,unsigned short magic_Number, char *filename);
/* bad comment line error, where null == error            */
int commentLineError(FILE *inputFile,  char * commentLine, char *filename);
/* sanity checks on size        */
    /* must read exactly three values        */
int dimensionsError(FILE *inputFile, int width, int heigth, char *filename);
/* check greys */
int maxGrayValueError(FILE *inputFile, int maxGray, char *filename);
/* sanity check for memory allocation    */
int imageMallocError(FILE *inputFile,  unsigned char *imageData, char *filename);
/* sanity check	                 */
int badDataError(FILE *inputFile,  unsigned char **imageData, int height, int scanCount, int grayValue, char *filename);
/* check whether file opening worked     */
int outputFailedError(FILE *outputFile,  unsigned char **imageData, int height, char *filename);
/* check that dimensions wrote correctly */
int outputDimensionError( unsigned char **imageData, int nBytesWritten, int height, char *filename);
