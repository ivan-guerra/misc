/*!
 * \file median_filter.h
 *
 * \brief Define the API for a barebones median filter lib.
 */

#ifndef _MEDIAN_FILTER_H_
#define _MEDIAN_FILTER_H_

#include <stdint.h>
#include "jpeg_helpers.h"

/*!
 * \brief Execute a NxN median filter on the \p src image and store the result in the \p dst image.
 * \details compute_median_filter() implements a bruteforce NxN median filter. This filter does not
 *          address the boundaries of the \p src image.
 * \param dst A grayscale JPG image.
 * \param src A grayscale JPG image passed through an NxN median filter.
 * \param dim The dimension of NxN median grid.
 * \return 0 if the median filter was computed and the result stored in \p dst, 1 otherwise.
 */
int compute_median_filter(struct grayscale_image_t* dst, const struct grayscale_image_t* src, uint32_t dim);

#endif
