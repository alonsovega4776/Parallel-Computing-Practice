//
// Created by Alonso Vega  on 12/31/20.
//
#include "ImageProcessing.h"


void flip_imageH(unsigned char** image)
{
    struct Pixel pix_temp;
    int r = 0, c = 0;

    LOOP(r, 0, image_property.Vpixels)
    {
        c = 0;
        while (c < ((image_property.Hpixels*3)/2))
        {
            pix_temp.B = image[r][c];
            pix_temp.G = image[r][c + 1];
            pix_temp.R = image[r][c + 2];

            image[r][c]   = image[r][image_property.Hpixels * 3 - (c + 3)];
            image[r][c+1] = image[r][image_property.Hpixels * 3 - (c + 2)];
            image[r][c+2] = image[r][image_property.Hpixels * 3 - (c + 1)];

            image[r][image_property.Hpixels * 3 - (c + 3)] = pix_temp.B;
            image[r][image_property.Hpixels * 3 - (c + 2)] = pix_temp.G;
            image[r][image_property.Hpixels * 3 - (c + 1)] = pix_temp.R;

            c += 3;
        }
    }
}


void flip_imageV(unsigned char** image)
{
    struct Pixel pix_temp;
    int r = 0, c = 0;

    LOOP(c, 0, image_property.Hbytes)
    {
        r = 0;
        while(r < (image_property.Vpixels/2))
        {
            pix_temp.B = image[r][c];
            pix_temp.R = image[r][c + 2];
            pix_temp.G = image[r][c + 1];

            image[r][c]     = image[image_property.Vpixels - (r + 1)][c];
            image[r][c + 1] = image[image_property.Vpixels - (r + 1)][c + 1];
            image[r][c + 2] = image[image_property.Vpixels - (r + 1)][c + 2];

            image[image_property.Vpixels - (r + 1)][c]     = pix_temp.B;
            image[image_property.Vpixels - (r + 1)][c + 1] = pix_temp.G;
            image[image_property.Vpixels - (r + 1)][c + 2] = pix_temp.R;

            r++;
        }
        c += 2;
    }
}


void *MT_flip_imageH(void *treadID)
{
    struct Pixel pix_temp;
    int r = 0, c = 0;

    long threadID_start =  *((int*)treadID);
    threadID_start      *= image_property.Vpixels / ThNumber;
    long threadID_end   =  threadID_start + (image_property.Vpixels/ThNumber) - 1;

    LOOP(r, threadID_start, threadID_end + 1)
    {
        c = 0;
        while (c < ((image_property.Hpixels*3)/2))
        {
            pix_temp.B = image[r][c];
            pix_temp.G = image[r][c + 1];
            pix_temp.R = image[r][c + 2];

            image[r][c]   = image[r][image_property.Hpixels * 3 - (c + 3)];
            image[r][c+1] = image[r][image_property.Hpixels * 3 - (c + 2)];
            image[r][c+2] = image[r][image_property.Hpixels * 3 - (c + 1)];

            image[r][image_property.Hpixels * 3 - (c + 3)] = pix_temp.B;
            image[r][image_property.Hpixels * 3 - (c + 2)] = pix_temp.G;
            image[r][image_property.Hpixels * 3 - (c + 1)] = pix_temp.R;

            c += 3;
        }
    }
    pthread_exit(NULL);
}

void *MT_flip_imageV(void *treadID)
{
    struct Pixel pix_temp;
    int r = 0, c = 0;

    long threadID_start =  *((int*)treadID);
    threadID_start      *= image_property.Hbytes / ThNumber;
    long threadID_end   = threadID_start + (image_property.Hbytes / ThNumber) - 1;

    LOOP(c, threadID_start, threadID_end + 1)
    {
        r = 0;
        while (r < (image_property.Vpixels/2))
        {
            pix_temp.B = image[r][c];
            pix_temp.G = image[r][c + 1];
            pix_temp.R = image[r][c + 2];

            image[r][c]   = image[image_property.Vpixels - (r+1)][c];
            image[r][c+1] = image[image_property.Vpixels - (r+1)][c + 1];
            image[r][c+2] = image[image_property.Vpixels - (r+1)][c + 2];

            image[image_property.Vpixels - (r+1)][c]     = pix_temp.B;
            image[image_property.Vpixels - (r+1)][c + 1] = pix_temp.G;
            image[image_property.Vpixels - (r+1)][c + 2] = pix_temp.R;

            r++;
        }
        c += 2;
    }

    pthread_exit(NULL);
}



