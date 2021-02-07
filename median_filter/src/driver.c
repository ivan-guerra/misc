/*!
 * \file driver.c
 *
 * \brief Execute a brute force grayscale JPEG NxN median filter.
 *
 * \details medfilter implements a brute force median filter for grayscale JPEG images. Our brute force
 *          approach implements a NxN filter that ignores image boundaries.
 */

#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "jpeg_helpers.h"
#include "median_filter.h"

#define DEFAULT_DIM 5
#define DEFAULT_IMAGE_QUALITY 95

static void print_usage()
{
    printf("Usage: medfilter [OPTIONS] in_image out_image\n");
    printf("Run an NxN median filter on a grayscale JPG.\n");
    printf("\t-d\tDimension of the filter (i.e., the N in NxN).\n");
    printf("\t-s\tPrint timing statistics.\n");
    printf("\t-h\tPrint this help page.\n");
}

int main(int argc, char** argv)
{
    int c = 0;
    int dim = DEFAULT_DIM;
    int print_stats = FALSE;
    clock_t start, end;
    double read_time, write_time, filter_time = 0.0;

    opterr = 0;
    while (-1 != (c = getopt(argc, argv, "hsd:t:"))) {
        switch (c) {
            case 'h':
                print_usage();
                exit(EXIT_SUCCESS);
                break;
            case 'd':
                dim = atoi(optarg);
                if (dim <= 1) {
                    fprintf(stderr, "illegal dimension value: %d\n", dim);
                    exit(EXIT_FAILURE);
                }
                break;
            case 's':
                print_stats = TRUE;
                break;
            case '?':
                if ('c' == optopt)
                    fprintf(stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint(optopt))
                    fprintf(stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
                exit(EXIT_FAILURE);
            default:
                abort();
        }
    }

    if ((NULL == argv[optind]) || (NULL == argv[optind+1])) {
        fprintf(stderr, "missing input image and/or output image file name(s)\n");
        fprintf(stderr, "see program usage using the -h options for help\n");
        exit(EXIT_FAILURE);
    }

    // Read in the input image.
    struct grayscale_image_t src_img = {0, 0, NULL};
    start = clock();
    if (read_jpeg(argv[optind], &src_img)) {
        fprintf(stderr, "unable to load JPG file contents: %s\n", argv[optind]);
        exit(EXIT_FAILURE);
    }
    end = clock();
    printf("Image file %s (%dx%d) loaded successfully.\n", argv[optind], src_img.width, src_img.height);
    read_time = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000.0;

    // Compute the NxN median filter of the input image.
    struct grayscale_image_t dst_img = {0, 0, NULL};
    start = clock();
    if (compute_median_filter(&dst_img, &src_img, dim)) {
        fprintf(stderr, "unable to compute filter\n");
        free_image(&src_img);
        free_image(&dst_img);
    }
    end = clock();
    printf("%dx%d median filter applied to %s. Result image will be written to %s.\n",
            dim, dim, argv[optind], argv[optind+1]);
    filter_time = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000.0;

    // Write the filtered image to disk.
    start = clock();
    if (write_jpeg(argv[optind+1], &dst_img, DEFAULT_IMAGE_QUALITY)) {
        fprintf(stderr, "unable to write jpeg to %s\n", argv[optind+1]);
        exit(EXIT_FAILURE);
    }
    end = clock();
    printf("Image file %s (%dx%d) written successfully.\n", argv[optind+1], dst_img.width, dst_img.height);
    write_time = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000.0;

    free_image(&src_img);
    free_image(&dst_img);

    if (print_stats) {
        printf("-----------%dx%d Filter Statistics (START)-----------\n", dim, dim);
        printf("Read Time = %.2lf ms.\n", read_time);
        printf("Write Time = %.2lf ms.\n", write_time);
        printf("Filter Time = %.2lf ms.\n", filter_time);
        printf("-----------%dx%d Filter Statistics (END)-------------\n", dim, dim);
    }

    return 0;
}
