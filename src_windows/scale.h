#ifndef __SCALE_H__
#define __SCALE_H__

#include "bmp.h"

BMPImage *bmp_downscale(BMPImage *img, uint32_t width_out, uint32_t height_out);

#endif /* __SCALE_H__ */