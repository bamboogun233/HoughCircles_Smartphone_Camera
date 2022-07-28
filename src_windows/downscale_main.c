#include <stdio.h>
#include <stdlib.h>
#include "scale.h"

char default_filename[] = "downscaled.bmp";

void usage()
{
    printf("Usage: ./downscale <filename> <ouput_width> <output_height> [<output_filename>]\n");
}

int main(int argc, char const *argv[])
{
    if (argc < 4) {
        usage();
        exit(1);
    }

    BMPImage *img = bmp_read(argv[1]);
    BMPImage *downscaled = bmp_downscale(img, atoi(argv[2]), atoi(argv[3]));

    return bmp_write(downscaled, argc > 4 ? argv[4] : default_filename);
}