//
// Created by Alonso Vega  on 12/31/20.
//
#include "ImageIO.h"

//-------------------------------------------Blank BMP File---------------------------------------------------
unsigned char** CreateBlankBMP(unsigned char FILL)
{
    int i=0;

    unsigned char** image = (unsigned char** )malloc(image_property.Vpixels * sizeof(unsigned char*));
    LOOP(i, 0, image_property.Vpixels)
    {
        image[i] = (unsigned char*)malloc(image_property.Hbytes * sizeof(unsigned char ));
        memset((void*)image[i], FILL, (size_t)image_property.Hbytes);
    }
    return image;
}
//-------------------------------------------Blank BMP File---------------------------------------------------


//-------------------------------------------Read BMP File---------------------------------------------------
unsigned char** ReadBMP(char* fileName)
{
    int i   = 0;
    FILE* f = fdopen(fileName, "rb");

    if (f == NULL)
    {
        printf("\nERROR: %s NOT FOUND\n\n",fileName);
        exit(1);
    }

    int num_items = 54;
    unsigned char HeaderInfo[num_items];
    fread(HeaderInfo, sizeof(unsigned char), num_items, f);

    int w         = *(int*)&HeaderInfo[18];     //width
    int h         = *(int*)&HeaderInfo[22];     //height
    int row_bytes = (w*3 + 3) & (~3);           //row of bytes

    LOOP(i,0, num_items) image_property.HeaderInfo[i] = HeaderInfo[i];
    image_property.Vpixels = h;
    image_property.Hpixels = w;
    image_property.Hbytes  = row_bytes;

    printf("\nInput BMP File name: %20s  (%u x %u)", fileName, image_property.Hpixels, image_property.Vpixels);

    unsigned char **image = (unsigned char**)malloc(h*sizeof(unsigned char*));
    LOOP(i,0,h) image[i] = (unsigned char*)malloc(row_bytes * sizeof(unsigned char));
    LOOP(i,0,h) fread(image[i], sizeof(unsigned char), row_bytes, f);
    fclose(f);

    return image;
}
//-------------------------------------------Read BMP File---------------------------------------------------


//-------------------------------------------Write BMP File---------------------------------------------------
void WriteBMP(unsigned char** image, char* fileName)
{
    FILE *f = fopen(fileName, "wb");
    if(f == NULL)
    {
        printf("\nERROR: FILE CREATION ERROR: %s\n\n", fileName);
        exit(1);
    }

    unsigned long int x_1 = 0, x_2 = 0;
    LOOP(x_1,0,54) fputc(image_property.HeaderInfo[x_1], f);    //write header
    LOOP(x_1, 0, image_property.Vpixels)
        LOOP(x_2, 0, image_property.Hpixels)
            fputc(image[x_1][x_2], f);

    printf("\nOutput BMP File name: %20s  (%u x %u)", fileName, image_property.Hpixels, image_property.Vpixels);
    fclose(f);
}
//-------------------------------------------Write BMP File---------------------------------------------------