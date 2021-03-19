#include <stdio.h>
#include <stdio.h>
#include <sys/time.h>
#include <ctype.h>

#include "ImageProcessing.h"

#define MAXTHREADS 12
#define REPS       1


int main(int argc, char** argv)
{
    char             Flip;
    int              a,i,ThErr;
    struct timeval   t_struct;
    double           t_1, t_2, dura;

    int            ThParameters[MAXTHREADS];
    pthread_t      ThHandle[MAXTHREADS];
    pthread_attr_t ThAttribute;


    switch (argc)
    {
        case 3: ThNumber=1;             Flip='V';                     break;
        case 4: ThNumber=1;             Flip=toupper(argv[3][0]); break;
        case 5: ThNumber=atoi(argv[4]); Flip=toupper(argv[3][0]); break;
        default: printf("Usage: main input_File output_File [V/H] [number_of_threads] \n");
                 printf("Example: main infile.bmp out.bmp H 8\n\n");
                 return 0;
    }
    if ((Flip != 'V') && (Flip != 'H'))
    {
        printf("Invalid option ’%c’ ... Exiting...\n", Flip);
        exit(EXIT_FAILURE);
    }
    if ((ThNumber < 1) || (ThNumber > MAXTHREADS))
    {
        printf("Threads must be in [1..%u]... Exiting...\n", MAXTHREADS);
        exit(EXIT_FAILURE);
    }
    else
    {
        if(ThNumber != 1)
        {
            printf("\nExecuting %ld threads...\n", ThNumber);
            MT_flip_function = (Flip=='V') ? MT_flip_imageV:MT_flip_imageH;
        }
        else
        {
            printf("\nExecuting the serial version ...\n");
            flip_function = (Flip=='V') ? flip_imageV:flip_imageH;
        }
    }
    image = ReadBMP(argv[1]);

    gettimeofday(&t_struct, NULL);
    t_1 = (double)t_struct.tv_sec*1000000.0 + ((double)t_struct.tv_usec);


    if (ThNumber > 1)
    {
        pthread_attr_init(&ThAttribute);
        pthread_attr_setdetachstate(&ThAttribute, PTHREAD_CREATE_JOINABLE);

        LOOP(a,0,REPS)
        {
            LOOP(i, 0, ThNumber)
            {
                ThParameters[i] = i;
                ThErr = pthread_create(&ThHandle[i],
                                       &ThAttribute, MT_flip_function,
                                       (void *)&ThParameters[i]);
                if (ThErr != 0)
                {
                    printf("ERROR: Creating Threads Error %d. Exiting abruptly...\n", ThErr);
                    exit(EXIT_FAILURE);
                }
            }
            pthread_attr_destroy(&ThAttribute);
            LOOP(i, 0, ThNumber) pthread_join(ThHandle[i], NULL);
        }
    }
    else
    {
        LOOP(a,0,REPS) (*flip_function)(image);
    }


    gettimeofday(&t_struct, NULL);
    t_2  = (double)t_struct.tv_sec*1000000.0 + ((double)t_struct.tv_usec);
    dura = (t_2 - t_1)/1000.00;
    dura /= (double)REPS;

    WriteBMP(image, argv[2]);

    LOOP(i,0,image_property.Vpixels) free(image[i]);
    free(image);

    printf("\nTotal execution time: %9.4f ms (%s flip)", dura,
           Flip=='V'?"Vertical":"Horizontal");
    printf(" (%6.3f ns/pixel)\n", 1000000*dura/(double)(image_property.Hpixels*image_property.Vpixels));

    return (EXIT_SUCCESS);
}
