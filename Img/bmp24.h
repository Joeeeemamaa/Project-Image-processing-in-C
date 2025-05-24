/**
 * bmp24.h
 * Header file for 24-bit BMP image processing library
 * 
 * This library provides functions for loading, manipulating, and saving 24-bit true color BMP images.
 * It includes basic image processing operations such as negative, brightness adjustment,
 * grayscale conversion, and convolution filters.
 */

#ifndef BMP24_H
#define BMP24_H

#include <stdint.h>
#include <stdio.h>  // For FILE*

#pragma pack(1) // Disable padding

/**
 * Structure representing a single RGB pixel
 */
typedef struct {
    uint8_t red;    ///< Red value
    uint8_t green;  ///< Green value
    uint8_t blue;   ///< Blue value
} t_pixel;

/**
 * Structure containing BMP file header information
 */
typedef struct {
    uint16_t type;      ///< File type
    uint32_t size;      ///< File size
    uint16_t reserved1; ///< Reserved
    uint16_t reserved2; ///< Reserved
    uint32_t offset;    ///< Data offset
} t_bmp_header;

/**
 * Structure containing BMP image information
 */
typedef struct {
    uint32_t size;            ///< Header size
    int32_t width;           ///< Width
    int32_t height;          ///< Height
    uint16_t planes;         ///< Color planes
    uint16_t bits;           ///< Bits per pixel
    uint32_t compression;    ///< Compression
    uint32_t imagesize;      ///< Image size
    int32_t xresolution;     ///< X resolution
    int32_t yresolution;     ///< Y resolution
    uint32_t ncolors;        ///< Colors in palette
    uint32_t importantcolors;///< Important colors
} t_bmp_info;

/**
 * Structure representing a 24-bit BMP image
 */
typedef struct {
    t_bmp_header header;     ///< File header
    t_bmp_info header_info;  ///< Info header
    int width;               ///< Width
    int height;              ///< Height
    int colorDepth;          ///< Color depth
    t_pixel **data;          ///< Pixel data
} t_bmp24;

#pragma pack() // Re-enable padding

/**
 * Allocates memory for pixel data
 * Image width
 * Image height
 * 2D array of pixels
 */
t_pixel **bmp24_allocateDataPixels(int width, int height);

/**
 * Frees memory allocated for pixel data
 * 2D array of pixels
 * Image height
 */
void bmp24_freeDataPixels(t_pixel **pixels, int height);

/**
 * Allocates memory for a new BMP image
 * Image width
 * Image height
 * Color depth in bits
 * Pointer to new image structure
 */
t_bmp24 *bmp24_allocate(int width, int height, int colorDepth);

/**
 * Frees memory allocated for an image
 * Pointer to image structure
 */
void bmp24_free(t_bmp24 *img);

/**
 * Loads a 24-bit BMP image from file
 * Path to the BMP file
 * Pointer to loaded image structure, NULL if loading fails
 */
t_bmp24 *bmp24_loadImage(const char *filename);

/**
 * Saves a 24-bit BMP image to file
 * Pointer to image structure
 * Output file path
 */
void bmp24_saveImage(t_bmp24 *img, const char *filename);

/**
 * Prints basic information about the image
 * Pointer to image structure
 */
void bmp24_printInfo(t_bmp24 *img);

/**
 * Creates a negative version of the image
 * Pointer to image structure
 */
void bmp24_negative(t_bmp24 *img);

/**
 * Converts the image to grayscale
 * Pointer to image structure
 */
void bmp24_grayscale(t_bmp24 *img);

/**
 * Adjusts image brightness
 * Pointer to image structure
 * Brightness adjustment value (-255 to 255)
 */
void bmp24_brightness(t_bmp24 *img, int value);

/**
 * Applies convolution to a single pixel
 * Pointer to image structure
 * X coordinate
 * Y coordinate
 * 2D filter kernel
 * Size of the kernel
 * Resulting pixel value
 */
t_pixel bmp24_convolution(t_bmp24 *img, int x, int y, float **kernel, int kernelSize);

/**
 * Applies a convolution filter to the entire image
 * Pointer to image structure
 * 2D filter kernel
 * Size of the kernel (must be odd)
 */
void bmp24_applyFilter(t_bmp24 *img, float **kernel, int kernelSize);

#endif // BMP24_H
