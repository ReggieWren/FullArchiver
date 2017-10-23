#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arch_Prototypes.h"
#include "sizeofFile_Prototype.h"


/*
Function to read through an archive file and create the files
@numOfArgs - number of arguments passed through command line
@fileArgs - content of command line arguments
*/
void unArchive(int numOfArgs, const char * fileArgs[])
{
    FILE *archFilePtr, *filePtr;
    
    unsigned int numofFiles = 0;
    unsigned char sizeofName;
    
    /* Open archive file (specified in 2nd argument of command line) */
    if ((archFilePtr = fopen(fileArgs[2], "rb")) == NULL) {
        printf("Could not open file: %s\n", fileArgs[2]);
        exit(1);
    }
    
    // Get the total number of files
    fread(&numofFiles, sizeof(numofFiles), 1, archFilePtr);
    
    // Get the size of the file name
    while(fread(&sizeofName, sizeof(sizeofName), 1, archFilePtr) == 1)
    {
        
        // Get file name
        char fileName[sizeofName];
        fread(&fileName, sizeof(fileName)+1, 1, archFilePtr);
        
        // Get the size of file content
        unsigned int fileContentSize = 0;
        fileContentSize = getFileSize(&fileArgs[2]);
        fread((void *) &fileContentSize, sizeof(fileContentSize), 1, archFilePtr);

        // Get the file content
        char fileContent[fileContentSize];
        fread(&fileContent, fileContentSize, 1, archFilePtr);
        fileContent[fileContentSize] = '\0';

        // Open file to be read in
        if ((filePtr = fopen(fileName, "wb")) == NULL) {
            printf("Could not open file: %s\n", fileName);
            exit(1);
        }
            
        // Write to the created file from archive
        fwrite(fileContent, fileContentSize, 1, filePtr);
            
        // Close the file created
        if (fclose(filePtr) == EOF) {
            printf("Could not close file: %s\n", fileName);
        }
        
        
    }
    
    // Close the archive file. 
    if (fclose(archFilePtr) == EOF) {
        printf("Could not close file: %s\n", fileArgs[2]);
    }
}
