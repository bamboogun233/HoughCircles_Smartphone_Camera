#include <stdio.h>
#include <math.h>
#include "bmp.h"

BMPImage *bmp_downscale(BMPImage *img, uint32_t width_out, uint32_t height_out)
{
    if (img->header.width_px < width_out || img->header.height_px < height_out) {
        printf("downscale should have smaller dimensions!\n");
        return 0;
    }

    if (!width_out || !height_out) {
        printf("?\n");
        return 0;
    }

    uint32_t w = img->header.width_px;
    uint32_t h = img->header.height_px;
    uint32_t w_o = width_out;
    uint32_t h_o = height_out;

    BMPImage *res = bmp_create(width_out, height_out);

    uint32_t num_sample_x = w / w_o; 
    uint32_t num_sample_y = h / h_o; 

    uint32_t x, y, _x, _y;
    for (y = 0; y < height_out; y++) {
        for (x = 0; x < width_out; x++) {
            uint32_t _x_base = x * w / w_o;
            uint32_t _y_base = y * h / h_o;
            uint32_t num_accum = 0;
            uint32_t ac_r = 0, ac_g = 0, ac_b = 0; //accumulated color channels
            for (_y = 0; _y < num_sample_y && _y + _y_base < h; _y++) {
                for (_x = 0; _x < num_sample_x && _x + _x_base < w; _x++) {
                    Pixel *p = bmp_pixel_at(img, _x + _x_base, _y + _y_base);
                    ac_r += p->r;
                    ac_g += p->g;
                    ac_b += p->b;
                    num_accum++;
                }
            }
            Pixel *t = bmp_pixel_at(res, x, y);
            t->r = (uint8_t)(ac_r / num_accum);
            t->g = (uint8_t)(ac_g / num_accum);
            t->b = (uint8_t)(ac_b / num_accum);
        }
    }
    return res;
}

static inline uint8_t *ptr_at(void *data, uint32_t width, uint32_t height, uint32_t x, uint32_t y)
{
    if (x >= width || y >= height) { return 0; }
    return ((uint8_t *)data) + (x + y * width) * 3;
}