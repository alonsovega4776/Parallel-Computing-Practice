//
// Created by Alonso Vega  on 12/31/20.
//

#ifndef PARELLEL_PROGRAM_CPU_IMAGEPROCESSING_H
#define PARELLEL_PROGRAM_CPU_IMAGEPROCESSING_H

#include <pthread.h>
#include "ImageIO.h"

void (*flip_function)(unsigned char **img);
void *(*MT_flip_function)(void *arg);


void flip_imageV(unsigned char** image);
void flip_imageH(unsigned char** image);

void *MT_flip_imageV(void *treadID);
void *MT_flip_imageH(void *treadID);


#endif //PARELLEL_PROGRAM_CPU_IMAGEPROCESSING_H
