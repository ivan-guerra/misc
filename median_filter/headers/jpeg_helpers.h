/*!
 * \file jpeg_helpers.h
 *
 * \brief Define a barebones grayscale JPG image API.
 *
 * \details The goal behind the jpeg_helpers API is to provide a simple wrapper around libjpeg via which
 *          the user can read and write grayscale JPG images.
 */

#ifndef _JPEG_HELPERS_H_
#define _JPEG_HELPERS_H_

#include <stdint.h>
#include <jpeglib.h>

/*!
 * \brief Representation of a grayscale JPG image.
 */
struct grayscale_image_t
{
    uint32_t width; /*!< Width of the image. */
    uint32_t height; /*!< Height of the image. */
    JSAMPROW* pixelmat; /*!< grayscale value matrix with dimension \p width by \p height.*/
};

/*!
 * \brief Allocate a grayscale image on the heap with dimensions \w by \p h.
 * \param img Grayscale image structure whose members are to be populated/allocated memory.
 * \param w Width of the image.
 * \param h Height of the image.
 * \return 0 if a grayscale image \w by \p height is allocated, 1 otherwise.
 */
int alloc_image(struct grayscale_image_t* img, uint32_t w, uint32_t h);

/*!
 * \brief Free memory previously allocated to \p img.
 * \param img A grayscale_image_t image previously allocated via a call to alloc_image().
 */
void free_image(struct grayscale_image_t* img);

/*!
 * \brief Load the image data stored in \p filename to \p img.
 * \details read_jpeg() uses the libjpeg API to read image data from the file pointed to by \p filename.
 *          Worth noting, read_jpeg() can potentially use a significant amount of memory since
 *          it allocates space during execution to load the image into memory AND allocates space in
 *          \p img to store the loade data. Note, memory acquired to initially load the image is freed
 *          on return (whether return is successful or not).
 * \param filename Path to a grayscale JPG file.
 * \param img grayscale_image_t structure used to store the image data extracted from \p filename.
 * \return 0 if image data from \p filename is read into \p img, 1 otherwise.
 */
int read_jpeg(const char* filename, struct grayscale_image_t* img);

/*!
 * \brief Write image data in \p img to \p filename with caller specified quality.
 * \param filename Name of the file to which image data will be written.
 * \param img Grayscale JPG image data.
 * \param quality Integer value in the range [0,100] indicating output image quality.
 * \return 0 if \p img is written to\p filename successfully, 1 otherwise.
 */
int write_jpeg(const char* filename, const struct grayscale_image_t* img, uint32_t quality);

#endif
