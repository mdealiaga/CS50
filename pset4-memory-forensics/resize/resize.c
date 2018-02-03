/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include "bmp.h"


int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
               fprintf(stderr, "Usage: ./copy 'n' infile outfile\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if (n < 0 || n > 100)
    {
        return 1;
    }


    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }


//new variables


long OldWidth = bi.biWidth;
int OldPadding = (4 - (OldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
//oldSizeImage = bi.biSizeImage;
int OldHeight = bi.biHeight;


bi.biWidth *= n;
bi.biHeight *= n;

// determine padding for scanlines
int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

//changes dimensions

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);



    // For Original Height
    for (int i = 0, OldHeight2 = abs(OldHeight); i < OldHeight2; i++)
    {
        // For Resize Factor
           for (int p = 0; p<n; p++)
            {
                // For Original Width
                for (int j = 0; j < OldWidth; j++)
                {
                    // temporary storage
                    RGBTRIPLE triple;
        
                    // Read Original Triple - read RGB triple from infile
                    fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
                
                    //write n copies of triple
                    for (int z = 0; z<n; z++)
                            {
                        // write RGB triple to outfile
                        fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                            }
                    
                }
                // Skip over original padding
                fseek(inptr, OldPadding, SEEK_CUR);     
                
                // Add new padding
                for (int k = 0; k < padding; k++)
                    {
                        fputc(0x00, outptr);
                    }
                    
                // Move cursor back to beginning of scanline
                int sendback = (OldWidth*sizeof(RGBTRIPLE)+OldPadding);
                //puts cursos back to the start of the row
                if (p<n-1)
                    {
                    fseek(inptr, -sendback, SEEK_CUR);
                    }
                
            }

    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
