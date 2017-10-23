#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "sizeofFile_Prototype.h"

/* 
Function to assure the correct number of files are inside of the archive, and to verify no corruption occured
@numOfArgs - number of arguments passed in from command line
@fileArgs - content of which was passed in from command line
*/

int checkCorrupt(int numOfArgs, const char * fileArgs[])
{    
    unsigned char fileNameLength;
    unsigned int fileSize = 0;
    char fileName[MAX_FILENAME];
    
    int i = 3;
    int matchCount = 0;
    
    
    // Pointer to the file
    FILE  *filePtr;
    
        
    while (i != numOfArgs) {
        
        
        /* Open the text file. */
        if ((filePtr = fopen(fileArgs[i], "rb")) == NULL) {
            printf("Could not open file: %s\n", fileArgs[i]);
            exit(1);
        }
        
        // Get filename length (l1) - 1 byte
        fileNameLength = strlen(fileArgs[i]);
        
        // Write the filename
        strcpy(fileName,fileArgs[i]);
        fileName[fileNameLength] = '\0';
        
        // Write the file size (s1) - 4 bytes
        fileSize = getFileSize(&fileArgs[i]);
        
        // Write the contents of file (c1) - filesize bytes
        char *fileContent = malloc(fileSize + 1);
        fread(fileContent, fileSize, 1, filePtr);

        
            FILE *archFilePtr;
            
            unsigned int numofFiles = 0;
            unsigned char sizeofName;
            /* Open the binary file. */
            if ((archFilePtr = fopen(fileArgs[2], "rb")) == NULL) {
                printf("Could not open file: %s\n", fileArgs[2]);
                exit(1);
            }
            
            // Read the total number of files
            fread(&numofFiles, sizeof(numofFiles), 1, archFilePtr);
            
            // Read in the size of the file name
            while(fread(&sizeofName, sizeof(sizeofName), 1, archFilePtr) == 1)
            {
                
                // Read in file name
                char fileName[sizeofName];
                fread(&fileName, sizeof(fileName)+1, 1, archFilePtr);
                
                // Read in the size of file content
                unsigned int fileContentSize = 0;
                
                fread((void *) &fileContentSize, sizeof(fileContentSize), 1, archFilePtr);
                
                // Read in the file content
                char fileContent[fileContentSize];
                fread(&fileContent, fileContentSize, 1, archFilePtr);
                fileContent[fileContentSize] = '\0';
                
                // if they match, increase the count
                if((strcmp(fileContent, fileContent)) == 0)
                {
                    matchCount++;
                }
                
            }
            
            /* Close the database file. */
            if (fclose(archFilePtr) == EOF) {
                printf("Could not close file: %s\n", fileArgs[2]);
            }
        
		
        free(fileContent);
        
        //Close the file we are reading from - text
        fclose(filePtr);
        
        i++;

    }
    
    if(matchCount != (numOfArgs-3))
    {
        printf("Archive is corrupted!\n");
        return 1;
    }
    else {
        return 0;
    }
    


}
