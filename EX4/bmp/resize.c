/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy intRatio infile outfile\n");
        return 1;
    }
    
    if (argv[1] == NULL)
    {
        printf("imput a positive number as an argument.\n");
        return 1;
    }

    // remember filenames
    int ratio = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    //check the 1st argument is the int required
    if (ratio < 1 || ratio > 100 )
    {
        printf("first argument must be an int.\n");
        return 2;
    }
    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
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
    
    // create outfile BITMAPINFOHEADER and BITMAPFILEHEADER
    BITMAPFILEHEADER bfOut = bf;
    BITMAPINFOHEADER biOut = bi;
    
    // change headers the outfile's BITMAPINFOHEADER
    biOut.biWidth = bi.biWidth * ratio;
    biOut.biHeight = bi.biHeight * ratio;
    
    // determine padding for scanlines    
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    int paddingOut = (4 - (biOut.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    biOut.biSizeImage = (biOut.biWidth * abs(biOut.biHeight) * 
    sizeof(RGBTRIPLE)) + (paddingOut * biOut.biWidth);
    
    // change headers for the outfile's BITMAPFILEHEADER
    bfOut.bfSize = biOut.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bfOut, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&biOut, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // how much back for each scanline repeat
    int trackBack = padding + (bi.biWidth * sizeof(RGBTRIPLE));
    // set it so the last line won't be repeated on the last iteration
    // of rescan
    int trackBackEx = ratio - 1;
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        for (int hRep = 0; hRep < ratio; hRep++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
               
                for (int wRep = 0; wRep < ratio; wRep++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
    
            // skip over padding, if any
            fseek(inptr, padding, SEEK_CUR);
            
            // then add it back (to demonstrate how)
            for (int k = 0; k < paddingOut; k++)
            {
                fputc(0x00, outptr);
            }
            if (hRep < trackBackEx)
            {
                fseek(inptr, -trackBack, SEEK_CUR);
            }
        }
    }
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
