#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "arch_Prototypes.h"
#include "sizeofFile_Prototype.h"

/* 
Function to check if the archive contains the correct amount of files and the files were written properly 
@numOfArgs - number of command line arguments passed in from command line
@fileArgs - array of pointers containing all of the elements passed in from command line
*/
int checkArchive(int numOfArgs, const char * fileArgs[])
{
    FILE *archiveFilePtr, *filePtr;
    
    long archFileSize = 0;
    long tempFileSize = 0;
    long fileSize = 0;
    int i = 3;
    long fileNameLength = 0;
    

    /* Open the archive file. */
    if ((archiveFilePtr = fopen(fileArgs[2], "rb")) == NULL) {
        printf("Could not open file: %s\n", fileArgs[2]);
        exit(1);
    }
    
    fseek(archiveFilePtr, 0, SEEK_END);
    archFileSize= ftell(archiveFilePtr);
    rewind(archiveFilePtr);

    
    /* Close the archive file. */
    if (fclose(archiveFilePtr) == EOF) {
        printf("Could not close file: %s\n", fileArgs[2]);
    }
    
    
    while(i != numOfArgs)
    {
        /* Open the file passed in */
        if ((filePtr = fopen(fileArgs[i], "rb")) == NULL) {
            printf("Could not open file: %s\n", fileArgs[i]);
            exit(1);
        }

        
		//Perform calculations to get file size
        fileNameLength += strlen(fileArgs[i]);
        
        tempFileSize = getFileSize(&fileArgs[i]);
        
        fileSize += tempFileSize;
        
        /* Close the file. */
        if (fclose(filePtr) == EOF) {
            printf("Could not close file: %s\n", fileArgs[i]);
        }
        
        i++;
        
        // Adding 1 for the byte of the length of filename
        fileSize += 1;
    
        // Adding 1 for the null terminating character
        fileSize += 1;
        
        // Adding 4 bytes for the length of file content
        fileSize += 4;
        
    }
    
    // Adding the length for the length of filename
    fileSize += fileNameLength;
    
    // Adding 4 bytes for total number of files
    fileSize += 4;
    
    //error logging
    if((fileSize - archFileSize) > 0)
    {
        printf("The archive is missing %ld bytes.\n", (fileSize - archFileSize));
        return 1;
    }
    else {
        return 0;
    }
}
