//
// Created by Alonso Vega  on 12/31/20.
//
#include "ImageProcessing.h"


unsigned char** flip_imageH(unsigned char** image)
{
    struct Pixel p;
    int r, c;

    LOOP(r, 0, image_property.Vpixels)
    {
        c = 0;
        while (c < image_property.Hpixels * 3 / 2)
        {
            p.B = image[r][c];
            p.G = image[r][c+1];
            p.R = image[r][c+2];

            image[r][c]   = image[r][image_property.Hpixels * 3 - (c + 3)];
            image[r][c+1] = image[r][image_property.Hpixels * 3 - (c + 2)];
            image[r][c+2] = image[r][image_property.Hpixels * 3 - (c + 1)];

            image[r][image_property.Hpixels * 3 - (c + 3)] = p.B;
            image[r][image_property.Hpixels * 3 - (c + 2)] = p.G;
            image[r][image_property.Hpixels * 3 - (c + 1)] = p.R;

            c += 3;
        }
    }
    return image;
}


unsigned char** flip_imageV(unsigned char** image)
{
    struct Pixel p;
    int r, c;

    LOOP(c, 0, image_property.Hbytes)
    {
        r = 0;
        while(r < image_property.Vpixels / 2)
        {
            p.B = image[r][c];
            p.R = image[r][c + 2];
            p.G = image[r][c + 1];

            image[r][c]     = image[image_property.Vpixels - (r + 1)][c];
            image[r][c + 1] = image[image_property.Vpixels - (r + 1)][c + 1];
            image[r][c + 2] = image[image_property.Vpixels - (r + 1)][c + 2];

            image[image_property.Vpixels - (r + 1)][c]     = p.B;
            image[image_property.Vpixels - (r + 1)][c + 1] = p.G;
            image[image_property.Vpixels - (r + 1)][c + 2] = p.R;

            r++;
        }
        c += 2;
    }
    return image;
}



