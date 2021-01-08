//
// Created by Alonso Vega  on 12/31/20.
//

#ifndef PARELLEL_PROGRAM_CPU_IMAGEIO_H
#define PARELLEL_PROGRAM_CPU_IMAGEIO_H

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#define LOOP(i, start, end) for(i = start;i < end;i++)

struct ImgProperties
{
    int Hpixels;
    int Vpixels;
    unsigned char HeaderInfo[54];
    unsigned long int Hbytes;
};

struct Pixel
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
};

struct SwapSpace
{
    unsigned long s_1;
    unsigned long s_2;
    unsigned long s_3;
};

unsigned char** CreateBlankBMP(unsigned char FILL);
unsigned char** ReadBMP(char* fileName);
void WriteBMP(unsigned char**, char*);

long                 ThNumber;
unsigned char**      image;
struct ImgProperties image_property;

#endif //PARELLEL_PROGRAM_CPU_IMAGEIO_H
