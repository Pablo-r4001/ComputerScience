/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


#define FATSIZE 512
typedef uint8_t  BYTE;

int main(void)
{
    // check for card if impossible to open return 1
    FILE* inptr = fopen("card.raw", "r");
    if (inptr == NULL)
    {
        printf("Could not open card.raw.\n");
        return 1;
    }
    
    // file ended checks the file is ended so the program can stop
    // file is the identifier for the file
    int fileEnded = 0;
    int file = 0;
    
    //outptr is the file to be outputed outfile is the name of the file
    FILE* outptr;
    char* outfile = malloc(8 * sizeof(BYTE));
    
    // As long as fileEnded is not 1
    while(fileEnded != 1)
    {
        // Create FAT allocation
        BYTE fatSec[FATSIZE];

        // Check for headers to be correct
        if (fatSec[0] == 0xff && fatSec[1] == 0xd8 && 
        fatSec[2] == 0xff && fatSec[3] >= 0xe0 && fatSec[3] < 0xf0)
        {
            //if previous outfile close
            if (file != 0)
            {
                fclose(outptr);
            }
            
            // Name outfile
            sprintf(outfile, "%03d.jpg", file);
            
            // Create new file with outfile name and check correctness
            outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                fclose(inptr);
                fprintf(stderr, "Could not create %s.\n", outfile);
                return 2;
            }
            // add 1 for new file name. 
            file++;
        }
        
        // Check first file has been created, because the name must be 0
        // we added the new filename to the end
        if (file != 0)
        {
            // Write to output file
            fwrite(&fatSec,FATSIZE, 1, outptr);
        }
        
        // Read new piece of file to output, if output is 0 then close files
        // and free all memory.
        if (fread(&fatSec,FATSIZE, 1, inptr) == 0)
        {
            fclose(outptr);
            fclose(inptr);
            free(outfile);
            fileEnded = 1;
        }
    }
}

