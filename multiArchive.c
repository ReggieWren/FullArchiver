#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "prototypes.h"
#include "constants.h"
#include "sizeofFile_Prototype.h"

/*
Function to create multiple archive files based on the input from the command line 
@numOfArgs - number of arguments passed through command line 
@fileArgs - Array of pointers to the content passed through command line
*/

void multiArchive(int numOfArgs, const char * fileArgs[])
{
    int i = 4;
	int j = 1;
	unsigned char addToArch = '1';
    int flag = 0;
    
    unsigned int numofFiles = numOfArgs - 4;
	int archSize = atoi(fileArgs[3]);
	unsigned int numofArchs = (unsigned int)ceil((double)(numofFiles/archSize));
    unsigned char fileNameLength;
    unsigned int fileSize = 0;
	unsigned int archiveFileSize = 0;
    
    char fileName[MAX_FILENAME];
    
    // Pointer to the file
    FILE  *filePtr;
    

    // Pointer to the archive file
    FILE *archiveFilePtr = fopen(fileArgs[2], "wb");

    
    while (i != numOfArgs) {
        
		archiveFileSize += getFileSize(&fileArgs[i]);
           if(archiveFileSize > archSize)
		{
			if(addToArch == '1')
			{
				size_t fileLen = strlen(fileArgs[2]);

				char* newFile = malloc(fileLen + 2);

				strcpy(newFile, fileArgs[2]);    
				newFile[fileLen] = (char)addToArch;
				newFile[fileLen+1] = '\0';
			    strcpy((char*)fileArgs[2], newFile);
			}
			
			else
			{
				size_t fileLen = strlen(fileArgs[2]);
				char* newFile = malloc(fileLen + 2);
				
				strcpy(newFile, fileArgs[2]);
				newFile[fileLen-1] = (char)addToArch;
				newFile[fileLen] = '\0';
			    strcpy((char*)fileArgs[2], newFile);
			}
			addToArch++;
			archiveFilePtr = fopen(fileArgs[2], "wb");
		} 
		
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
		j++;
        flag = 1;
		archiveFileSize += getFileSize(&fileArgs[2]);
    }
    
    
    // Close the archive file
    fclose(archiveFilePtr);
    

}
