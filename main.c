#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "prototypes.h"
#include "arch_Prototypes.h"
#include "sizeofFile_Prototype.h"

int main(int argc, const char * argv[]) {

    if(argc < 3)
	{
		printf("Please pass in the correct arguments!\n");
        exit(1);
	}
	
    if((strcmp(argv[1], "-a") == 0) && argc >= 4 && (atoi(argv[3]) == 0))
    {
        Archive(argc, argv);
		printf("Archive has been created successfully!\n");
    } 
	
	
	else if((strcmp(argv[1], "-a") == 0) && argc >= 4 && (atoi(argv[3]) != 0))
    {
        multiArchive(argc, argv);
		printf("Archives have been created successfully!\n");
    } 
    
    else if((strcmp(argv[1], "-u") == 0) && argc == 3)
    {
        unArchive(argc, argv);
		printf("Archive has been unpacked successfully!\n");
    }

    else if((strcmp(argv[1], "-l") == 0) && argc == 3)
    {
        listArchive(argc, argv);
    }

    else if((strcmp(argv[1], "-v") == 0) && argc >= 4)
    {
        
        if((checkArchive(argc, argv) == 0) && (checkCorrupt(argc, argv) == 0))
        {
            printf("Archive verified!\n");
        }
    }
    
    else {
        printf("Please pass in the correct arguments!\n");
        exit(1);
    }

}
