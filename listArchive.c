#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prototypes.h"
#include "sizeofFile_Prototype.h"

/* 
Function to give a description of the archive file to be called when -l flag is specified
@numOfArgs - number of arguments passed through command line
@fileNames - files to be evaluated by list function
*/
void listArchive(int numOfArgs, const char * fileNames[])
{
    FILE *filePtr;
    
    unsigned int numofFiles = 0;
    unsigned char sizeofName;
    
    unsigned int totalSize = 0;
    
    /* Open the archive file. */
    if ((filePtr = fopen(fileNames[2], "rb")) == NULL) {
        printf("Could not open file: %s\n", fileNames[2]);
        exit(1);
    }
    
    // Get num of files from archive
    fread(&numofFiles, sizeof(numofFiles), 1, filePtr);
    printf("Number of files: %u\n\n", numofFiles);
    
    // Get the size of file names
    while(fread(&sizeofName, sizeof(sizeofName), 1, filePtr) == 1)
    {
        // Get the file name
        char fileName[sizeofName];
        fread(&fileName, sizeof(fileName)+1, 1, filePtr);
        printf("File Name: %s\n", fileName);
        
        //Get the size of file content
        unsigned int fileContentSize = 0;
        
        fread((void *) &fileContentSize, sizeof(fileContentSize), 1, filePtr);
        printf("Size: %u\n\n", fileContentSize);
        
        
        // Get the file content
        char fileContent[fileContentSize];
        fread(&fileContent, fileContentSize, 1, filePtr);
        fileContent[fileContentSize] = '\0';
        
        // Adding two because 1 byte is taken by the file name length and 1 byte is taken by the null terminating character
        totalSize += sizeofName + 2;
		
        // Adding 4 bytes because the length of file content takes up 4 bytes
        totalSize += fileContentSize + 4;

    }
    // 4 bytes are taken by the "Number of files"
    printf("Size of Archive: %u bytes\n", totalSize + 4);
    
    /* Close the archive file. */
    if (fclose(filePtr) == EOF) {
        printf("Could not close file: %s\n", fileNames[2]);
    }
}
