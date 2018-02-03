#include <stdio.h>
#include <stdlib.h>

#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
if (argc != 2)
    {
        fprintf(stderr, "Only input the name of a forensic image\n");
        return 1;
    }
    
//Open Memory Card File
FILE *MemCard = fopen(argv[1],"r");
    if (MemCard == NULL)
    {
        fprintf(stderr, "Could not open.\n");
        return 2;
    }
    
// create a string to store a jpg file under the format: ###.jpg
char outfile[8];

FILE *IMGOutput = fopen(outfile, "w");
/*
if (IMGOutput == NULL)
    {
        fprintf(stderr, "Could not create IMGOutput\n");
        return 3;
    }
*/

//Create a buffer to store each block of bytes
uint8_t *buffer = malloc(512);

//ensure enough space
    if(buffer == NULL)
    {
        fprintf(stderr, "pointer not created.\n");
        fclose(MemCard);
       return 4;
    }

//Create variable for keeping track of images
int IMGCount = 0;

//repeat until end of card - read 512 bytes into a buffer
while (fread(buffer, 512, 1, MemCard) == 1)
    {
    //Locates beginning of a JPEG
     if (buffer[0] == 0xff && 
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
           (buffer[3] & 0xf0) == 0xe0)
            {
                    //Prints correct filenames
                        if (IMGCount <10)
                                {
                                    
                                sprintf(outfile,"00%i.jpg", IMGCount);
                                }  
                        else if (IMGCount >= 10)
                                {
                                  sprintf(outfile,"0%i.jpg", IMGCount);  
                                }

                                fclose(IMGOutput);
                                fopen(outfile, "w");
                    

                if(IMGOutput == NULL)
                    {
                        fprintf(stderr, "Could not open outfile.\n");
                        return 4;
                    }
                
    
                //Increase counter
                IMGCount += 1;
                }  
            
            
                // write into the output JPEG files until next file is found
                fwrite(buffer, 512, 1, IMGOutput); 
    }
    
    //Closes and frees everything once done
    fclose(MemCard);
    fclose(IMGOutput);
    free(buffer);
    return 0; 
}