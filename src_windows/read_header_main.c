#include <stdio.h>
#include "bmp.h"

void usage()
{
    printf("Usage: ./read_header <filename>\n");
}

int main(int argc, char const *argv[])
{
    if (argc < 2) {
        usage();
        return 1;
    }

    BMPImage *img = bmp_read(argv[1]);
    if (!img) { return 1; }

    bmp_print_header(img);

    return 0;
}