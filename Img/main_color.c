/**
 * Main program for 24-bit BMP image processing demonstration
 * 
 * This file contains the main program that demonstrates various image processing
 * operations on 24-bit BMP images. It processes a single input image and generates
 * multiple output images with different effects applied.
 */

#include "bmp24.h"
#include <string.h>
#include <stdio.h>

/* 3x3 box blur kernel for image filtering */
float box_blur_data[3][3] = {
    {1.0f/9, 1.0f/9, 1.0f/9},
    {1.0f/9, 1.0f/9, 1.0f/9},
    {1.0f/9, 1.0f/9, 1.0f/9}
};
float *box_blur[3] = { box_blur_data[0], box_blur_data[1], box_blur_data[2] };

/* Main function for 24-bit BMP image processing */
int main(int argc, char *argv[]) {
    const char *inputFile;

    if (argc == 2) {
        inputFile = argv[1];
    } else {
        inputFile = "flowers_color.bmp";
        printf("No input provided, using default: %s\n", inputFile);
    }

    char outputFile[256];
    t_bmp24 *image = bmp24_loadImage(inputFile);

    if (!image) {
        printf("Failed to load image.\n");
        return 1;
    }

    printf("\nOriginal Color Image Info:\n");
    bmp24_printInfo(image);
    bmp24_free(image); // Free initial info image early

    // Negative
    strcpy(outputFile, "color_negative_");
    strcat(outputFile, inputFile);
    t_bmp24 *neg = bmp24_loadImage(inputFile);
    if (neg) {
        bmp24_negative(neg);
        bmp24_saveImage(neg, outputFile);
        bmp24_free(neg);
    }

    // Grayscale
    strcpy(outputFile, "color_grayscale_");
    strcat(outputFile, inputFile);
    t_bmp24 *gray = bmp24_loadImage(inputFile);
    if (gray) {
        bmp24_grayscale(gray);
        bmp24_saveImage(gray, outputFile);
        bmp24_free(gray);
    }

    // Brightness +50
    strcpy(outputFile, "color_bright_");
    strcat(outputFile, inputFile);
    t_bmp24 *bright = bmp24_loadImage(inputFile);
    if (bright) {
        bmp24_brightness(bright, 50);
        bmp24_saveImage(bright, outputFile);
        bmp24_free(bright);
    }

    // Box blur
    strcpy(outputFile, "color_blur_");
    strcat(outputFile, inputFile);
    t_bmp24 *blur = bmp24_loadImage(inputFile);
    if (blur) {
        bmp24_applyFilter(blur, box_blur, 3);
        bmp24_saveImage(blur, outputFile);
        bmp24_free(blur);
    }

    return 0;
}
