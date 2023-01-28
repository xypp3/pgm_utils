#include <stdio.h>

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

typedef struct pgm{
	unsigned short magic_number; // 0x3250 or 0x3550 (2P or 5P because little endian)
    int isBinary;
	int width;
	int height;
	int maxGray;
	unsigned char **imageData; // data array
}pgm;

int initPgm(pgm *image, int width, int height, int maxGray);
int readFile(char *filename, pgm *image);
int readMagicNum(FILE *inputFile, pgm *image, char *filename);
int checkComment(FILE *input);
int readHeaderData(FILE *inputFile, pgm *image);
int readImageData(FILE *inputFile,  pgm *image, char *filename);
int readNumbers(FILE *inputFile, unsigned char *output, int numOfData, int isInt, int maxVal, char *filename);
int writeFile(char *filename, pgm *image);
int writeBinary(pgm *image, FILE *output);
int writeAscii(pgm *image, FILE *output);
int readBinary(pgm *image, FILE *input);
int readAscii(pgm *image, FILE *input, char *filename);
