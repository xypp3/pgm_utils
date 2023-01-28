# PGM Utilities
### programming project coursework 1
 
## How to Run
### Compiling code
    To compile all of the executable files run the `make all` command.
Individual executables can be compiled using the `make <name>` command,
where <name> is the name of the main module to be compiled.

#### Cleaning compiled code
    To remove executables and temporary executable files run the
    `make clean` command.

### Running executables
    Once compiled run the executables according to specifications, so:
Usage: ./pgmEcho inputImage.pgm outputImage.pgm
Usage: ./pgmComp inputImage.pgm inputImage.pgm
Usage: ./pgma2b inputImage.pgm outputImage.pgm
Usage: ./pgmb2a inputImage.pgm outputImage.pgm
Usage: ./pgmReduce inputImage.pgm reduction_factor outputImage.pgm

### Running tests
Usage: ./testscript.sh name_of_executable

- valid name_of_executable options:
    `echo`, `comp`, `bin`, `ascii`, `reduce`, `tile`, `assemble`


## Points of interest in project
1. plans for what the modules should contain in modules.txt
2. plans for how to test code in testplan.txt
3. test file testscript.sh
4. .pgm files found in imagesPGM/
