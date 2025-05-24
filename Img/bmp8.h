/**
 * @file bmp8.h
 * @brief Header file for 8-bit BMP image processing library
 * 
 * This library provides functions for loading, manipulating, and saving 8-bit grayscale BMP images.
 * It includes basic image processing operations such as negative, brightness adjustment,
 * thresholding, and histogram equalization.
 */

#ifndef BMP8_H
#define BMP8_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Structure representing an 8-bit BMP image
 */
typedef struct {
    unsigned char header[54];      ///< File header
    unsigned char colorTable[1024]; ///< Color table
    unsigned char * data;          ///< Pixel data
    unsigned int width;            ///< Width
    unsigned int height;           ///< Height
    unsigned int colorDepth;       ///< Color depth
    unsigned int dataSize;         ///< Data size
} t_bmp8;

/* Basic file operations */
t_bmp8 * bmp8_loadImage(const char * filename);
void bmp8_saveImage(const char * filename, t_bmp8 * img);
void bmp8_free(t_bmp8 * img);
void bmp8_printInfo(t_bmp8 * img);

/* Basic image transformations */
void bmp8_negative(t_bmp8 * img);
void bmp8_brightness(t_bmp8 * img, int value);
void bmp8_threshold(t_bmp8 * img, int threshold);

/* Advanced image processing */
void bmp8_applyFilter(t_bmp8 *img, float **kernel, int kernelSize);

/* Histogram operations for contrast enhancement */
unsigned int *bmp8_computeHistogram(t_bmp8 *img);
unsigned int *bmp8_computeCDF(unsigned int *hist, unsigned int total_pixels);
void bmp8_equalize(t_bmp8 *img, unsigned int *hist_eq);

#endif //BMP8_H
