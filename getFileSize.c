#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sizeofFile_Prototype.h"

/* 
Simple function to get the size of a specific file or group of files
@fileName - name of the file to be evaluated
*/

unsigned int getFileSize(const char * fileName[])
{
    FILE *filePtr;
    
    /* Open the text file. */
    if ((filePtr = fopen(fileName[0], "rb")) == NULL) {
        fprintf(stderr, "Could not open file: %s\n", fileName[0]);
        exit(1);
    }
    
    unsigned int fileSize;
    
    fseek(filePtr, 0L, SEEK_END);
    fileSize = (unsigned int)ftell(filePtr);
    rewind(filePtr);
    
    fclose(filePtr);
    
    return fileSize;
}
