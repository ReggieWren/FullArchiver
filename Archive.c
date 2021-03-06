#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prototypes.h"
#include "constants.h"
#include "sizeofFile_Prototype.h"

/*
Function to create an archive file based on the input from the command line 
@numOfArgs - number of arguments passed through command line 
@fileArgs - Array of pointers to the content passed through command line
*/

void Archive(int numOfArgs, const char * fileArgs[])
{
    int i = 3;
    int flag = 0;
    
    unsigned int numofFiles = numOfArgs - 3;
    unsigned char fileNameLength;
    unsigned int fileSize = 0;
    
    char fileName[MAX_FILENAME];
    
    // Pointer to the file
    FILE  *filePtr;
    

    // Pointer to the archive file
    FILE *archiveFilePtr = fopen(fileArgs[2], "wb");

    
    while (i != numOfArgs) {
        
        
        /* Open the file. */
        if ((filePtr = fopen(fileArgs[i], "r")) == NULL) {
            printf("Could not open file: %s\n", fileArgs[i]);
            exit(1);
        }
        if (flag == 0)
        {
        // Write the total number of files 
        fwrite((const void *) &numofFiles, sizeof(numofFiles), 1, archiveFilePtr);
        }
        
        // Write filename length - 1 byte for null character
        fileNameLength = strlen(fileArgs[i]);
        
        fwrite(&fileNameLength, sizeof(fileNameLength), 1, archiveFilePtr);
        
        // Write the filename
        strcpy(fileName,fileArgs[i]);
        fileName[fileNameLength] = '\0';
        
        fwrite((const void *) &fileName, (fileNameLength + 1), 1, archiveFilePtr);
        
        // Write the file size
        unsigned int fsize;
        fsize = getFileSize(&fileArgs[i]);
        

        
        fwrite((const void *) &fsize, sizeof(fsize), 1, archiveFilePtr);
        
        // Write the contents of the non-archive file
        char *fileContent = malloc(fsize + 1);
        fread(fileContent, fsize, 1, filePtr);
        
        
        fwrite((const void *) fileContent, (fsize), 1, archiveFilePtr);
        
        free(fileContent);
        
        //Close the file
        fclose(filePtr);
        
        i++;
        flag = 1;
    }
    
    
    // Close the archive file
    fclose(archiveFilePtr);
    

}
