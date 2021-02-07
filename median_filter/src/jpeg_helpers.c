/*!
 * \file jpeg_helpers.c
 *
 * \brief jpeg_helpers.h implementation file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <jpeglib.h>
#include "jpeg_helpers.h"

static void free_decompress_resources(struct jpeg_decompress_struct* cinfo, FILE* infile)
{
    jpeg_finish_decompress(cinfo);
    jpeg_destroy_decompress(cinfo); // Release the JPEG decompression object.
    fclose(infile);
}

int alloc_image(struct grayscale_image_t* img, uint32_t w, uint32_t h)
{
    img->width = w;
    img->height = h;

    img->pixelmat = (JSAMPROW*)malloc(sizeof(JSAMPROW) * img->height);
    if (!img->pixelmat) {
        fprintf(stderr, "Insufficient memory available for JPEG conversion.\n");
        free_image(img);
        return 1;
    }

    for (int i = 0; i < img->height; ++i) {
        img->pixelmat[i] = (JSAMPROW)malloc(sizeof(JSAMPLE) * img->width);
        if (!img->pixelmat[i]) {
            fprintf(stderr, "Insufficient memory available for JPEG conversion.\n");
            free_image(img);
            return 1;
        }
        memset(img->pixelmat[i], 0, sizeof(JSAMPLE) * img->width);
    }
    return 0;
}

void free_image(struct grayscale_image_t* img)
{
    if (!img)
        return;

    for (int i = 0; i < img->height; ++i) {
        free(img->pixelmat[i]);
    }
    free(img->pixelmat);

    img->width = 0;
    img->height = 0;
    img->pixelmat = NULL;
}

int read_jpeg(const char* filename, struct grayscale_image_t* img)
{
    struct jpeg_error_mgr jerr;
    struct jpeg_decompress_struct cinfo;
    FILE* infile = NULL; // Image source file.
    JSAMPARRAY buffer = NULL; // Output row buffer.
    uint32_t row_stride = 0; // Physical row width in output buffer.
    unsigned char grayscale = 0;

    if (NULL == (infile = fopen(filename, "rb"))) {
        fprintf(stderr, "cannot open file %s\n", filename);
        return 1;
    }

    cinfo.err = jpeg_std_error(&jerr); // Setup the JPEG lib's error handler.
    jpeg_create_decompress(&cinfo); // Initialize the JPEG decompression object.
    jpeg_stdio_src(&cinfo, infile); // Specify the data source.
    jpeg_read_header(&cinfo, TRUE); // Read the file parameters.
    jpeg_start_decompress(&cinfo); // Start the decompressor.

    // Allocate space to buffer the image pixels.
    if (alloc_image(img, cinfo.output_width, cinfo.output_height)) {
        fprintf(stderr, "Insufficient memory available for JPEG conversion.\n");
        free_decompress_resources(&cinfo, infile);
        return 1;
    }

    row_stride = img->width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);
    while (cinfo.output_scanline < cinfo.output_height) {
        jpeg_read_scanlines(&cinfo, buffer, 1);
        for (int i = 0; i < img->width; ++i) {
            grayscale = buffer[0][cinfo.output_components * i];
            img->pixelmat[cinfo.output_scanline-1][i] = grayscale;
        }
    }
    free_decompress_resources(&cinfo, infile);

    return 0;
}

int write_jpeg(const char* filename, const struct grayscale_image_t* img, uint32_t quality)
{
    struct jpeg_error_mgr jerr;
    struct jpeg_compress_struct cinfo;
    FILE * outfile; // Target file.
    JSAMPROW row_pointer[1];

    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo); // Initialize the compression object.

    if (NULL == (outfile = fopen(filename, "wb"))) {
        fprintf(stderr, "can't open %s\n", filename);
        return 1;
    }
    jpeg_stdio_dest(&cinfo, outfile);

    cinfo.image_width = img->width;
    cinfo.image_height = img->height;
    cinfo.input_components = 1; // Number of color components per pixel.
    cinfo.in_color_space = JCS_GRAYSCALE;  // Colorspace of input image.
    jpeg_set_defaults(&cinfo); // Set default parameters.
    jpeg_set_quality(&cinfo, quality, TRUE); // Explicitly set image quality.
    jpeg_start_compress(&cinfo, TRUE); // Start the compressor.

    while (cinfo.next_scanline < cinfo.image_height) {
        row_pointer[0] = img->pixelmat[cinfo.next_scanline];
        jpeg_write_scanlines(&cinfo, row_pointer, 1);
    }

    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);

    return 0;
}
