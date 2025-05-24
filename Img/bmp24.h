/**
 * @file bmp24.h
 * @brief Header file for 24-bit BMP image processing library
 * 
 * This library provides functions for loading, manipulating, and saving 24-bit true color BMP images.
 * It includes basic image processing operations such as negative, brightness adjustment,
 * grayscale conversion, and convolution filters.
 */

#ifndef BMP24_H
#define BMP24_H

#include <stdint.h>
#include <stdio.h>  // For FILE*

/**
 * @brief Structure representing a single RGB pixel
 */
typedef struct {
    uint8_t red;    ///< Red value
    uint8_t green;  ///< Green value
    uint8_t blue;   ///< Blue value
} t_pixel;

/**
 * @brief Structure containing BMP file header information
 */
typedef struct {
    uint16_t type;      ///< File type
    uint32_t size;      ///< File size
    uint16_t reserved1; ///< Reserved
    uint16_t reserved2; ///< Reserved
    uint32_t offset;    ///< Data offset
} t_bmp_header;

/**
 * @brief Structure containing BMP image information
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
 * @brief Structure representing a 24-bit BMP image
 */
typedef struct {
    t_bmp_header header;     ///< File header
    t_bmp_info header_info;  ///< Info header
    int width;               ///< Width
    int height;              ///< Height
    int colorDepth;          ///< Color depth
    t_pixel **data;          ///< Pixel data
} t_bmp24;

/**
 * @brief Allocates memory for pixel data
 * @param width Image width
 * @param height Image height
 * @return 2D array of pixels
 */
t_pixel **bmp24_allocateDataPixels(int width, int height);

/**
 * @brief Frees memory allocated for pixel data
 * @param pixels 2D array of pixels
 * @param height Image height
 */
void bmp24_freeDataPixels(t_pixel **pixels, int height);

/**
 * @brief Allocates memory for a new BMP image
 * @param width Image width
 * @param height Image height
 * @param colorDepth Color depth in bits
 * @return Pointer to new image structure
 */
t_bmp24 *bmp24_allocate(int width, int height, int colorDepth);

/**
 * @brief Frees memory allocated for an image
 * @param img Pointer to image structure
 */
void bmp24_free(t_bmp24 *img);

/**
 * @brief Loads a 24-bit BMP image from file
 * @param filename Path to the BMP file
 * @return Pointer to loaded image structure, NULL if loading fails
 */
t_bmp24 *bmp24_loadImage(const char *filename);

/**
 * @brief Saves a 24-bit BMP image to file
 * @param img Pointer to image structure
 * @param filename Output file path
 */
void bmp24_saveImage(t_bmp24 *img, const char *filename);

/**
 * @brief Prints basic information about the image
 * @param img Pointer to image structure
 */
void bmp24_printInfo(t_bmp24 *img);

/**
 * @brief Creates a negative version of the image
 * @param img Pointer to image structure
 */
void bmp24_negative(t_bmp24 *img);

/**
 * @brief Converts the image to grayscale
 * @param img Pointer to image structure
 */
void bmp24_grayscale(t_bmp24 *img);

/**
 * @brief Adjusts image brightness
 * @param img Pointer to image structure
 * @param value Brightness adjustment value (-255 to 255)
 */
void bmp24_brightness(t_bmp24 *img, int value);

/**
 * @brief Applies convolution to a single pixel
 * @param img Pointer to image structure
 * @param x X coordinate
 * @param y Y coordinate
 * @param kernel 2D filter kernel
 * @param kernelSize Size of the kernel
 * @return Resulting pixel value
 */
t_pixel bmp24_convolution(t_bmp24 *img, int x, int y, float **kernel, int kernelSize);

/**
 * @brief Applies a convolution filter to the entire image
 * @param img Pointer to image structure
 * @param kernel 2D filter kernel
 * @param kernelSize Size of the kernel (must be odd)
 */
void bmp24_applyFilter(t_bmp24 *img, float **kernel, int kernelSize);

#endif // BMP24_H
