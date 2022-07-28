#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bmp.h"

char default_filename[] = "upscaled.bmp";

void usage()
{
    printf("Usage: ./upscale_example <filename> <ouput_width> <output_height> [<output_filename>]\n");
}

static inline uint8_t *ptr_at(void *data, uint32_t width, uint32_t height, uint32_t x, uint32_t y)
{
    if (x >= width || y >= height) { return 0; }
    return ((uint8_t *)data) + (x + y * width) * 3;
}

int upscale_example(void *data_in, uint32_t width_in, uint32_t height_in, void *data_out, uint32_t width_out, uint32_t height_out, uint32_t num_instance)
{
    uint32_t x, y, ch;
    int8_t err;
    uint8_t mix_lv = 1;
    uint8_t err_lv = 30;

    for (y = 0; y < height_out; y++) {
        for (x = 0; x < width_out; x++) {
            uint8_t *pix = ptr_at(data_out, width_out, height_out, x , y);
            uint8_t *pix_s = ptr_at(data_in, width_in, height_in, x * width_in / width_out + rand()%(mix_lv*2)-mix_lv, y * height_in / height_out+ rand()%(mix_lv*2)-mix_lv);
            if (!pix_s) { ptr_at(data_in, width_in, height_in, x * width_in / width_out, y * height_in / height_out); }
            if (!pix_s) { continue; }
            err = rand() % (err_lv * 2) - err_lv;
            for (ch = 0; ch < 3; ch++) {
                pix[ch] = pix_s[ch] >= err_lv && pix_s[ch] <= 254 - err_lv ? pix_s[ch] + err : pix_s[ch];
            }
        }
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    if (argc < 4) {
        usage();
        exit(1);
    }

    
    BMPImage *img = bmp_read(argv[1]);
    BMPImage *res = bmp_create(atoi(argv[2]), atoi(argv[3]));
    upscale_example(img->data, img->header.width_px, img->header.height_px, res->data, res->header.width_px, res->header.height_px, 1);

    return bmp_write(res, argc > 4 ? argv[4] : default_filename);
}
