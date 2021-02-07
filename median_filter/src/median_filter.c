/*!
 * \file median_filter.c
 *
 * \brief median_filter.h implementation file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <jpeglib.h>
#include "jpeg_helpers.h"
#include "median_filter.h"

static int jsamplecmp(const void* a, const void* b)
{
    const JSAMPLE ai = *(const JSAMPLE*)a;
    const JSAMPLE bi = *(const JSAMPLE*)b;

    if (ai == bi)
        return 0;

    return (ai < bi) ? -1 : 1;
}

int compute_median_filter(struct grayscale_image_t* dst, const struct grayscale_image_t* src, uint32_t dim)
{
    if (alloc_image(dst, src->width, src->height)) {
        fprintf(stderr, "unable to allocate space to construct output JPG\n");
        return 1;
    }

    const uint32_t EDGE = dim / 2;
    const uint8_t WIN_SIZE = dim * dim;
    JSAMPLE window[WIN_SIZE];
    for (int x = EDGE; x < (src->height - EDGE); ++x) {
        for (int y = EDGE; y < (src->width - EDGE); ++y) {
            int i = 0;
            for (int fx = 0; fx < dim; ++fx) {
                for (int fy = 0; fy < dim; ++fy) {
                    window[i] = src->pixelmat[x + fx - EDGE][y + fy - EDGE];
                    i++;
                }
            }
            qsort(window, WIN_SIZE, sizeof(JSAMPLE), jsamplecmp);
            dst->pixelmat[x][y] = window[WIN_SIZE / 2];
        }
    }

    return 0;
}
