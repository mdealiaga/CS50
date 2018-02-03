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
    
    
char outfile[8];
FILE *IMGOutput = fopen(outfile, "w");
//int open = 1;
 if (IMGOutput == NULL)
    {
        fprintf(stderr, "Could not create IMGOutput\n");
        return 3;
    }
  
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

//repeat until end of card
while (fread(buffer, 512, 1, MemCard) == 1)
    {
    //read 512 bytes into a buffer
    if (IMGCount == 0)
    {
    fread(buffer, 512, 1, MemCard);
    }
    
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
                        
                     //  if (IMGCount > 0)
                                
                                fclose(IMGOutput);
                                fopen(outfile, "w");
                    

                if(IMGOutput == NULL)
                    {
                        fprintf(stderr, "Could not open outfile.\n");
                        return 4;
                    }
                // write into the output JPEG files
                fwrite(buffer, 512, 1, IMGOutput);
                
                int boing = 0;
                
                //locates end of jpeg
                while (boing == 0)
                    {
                        fread(buffer, 512, 1, MemCard);
                            if (buffer[0] == 0xff && 
                                buffer[1] == 0xd8 &&
                                buffer[2] == 0xff &&
                               (buffer[3] & 0xf0) == 0xe0)
                                    { 
                                        boing = 1;
                                    }
                        //Locates end of file
                        /*
                        if (fread(buffer, 512, 1, MemCard) != 1)
                            {
                                fclose(MemCard);
                                fclose(IMGOutput);
                                free(buffer);
                                return 0; 
                            }
                            */
                            if (boing == 0)
                                {
                                fwrite(buffer, 512, 1, IMGOutput);
                                }
                    }
                    
            IMGCount += 1;
            }
    }
    fclose(MemCard);
    fclose(IMGOutput);
    free(buffer);
    return 0; 
}