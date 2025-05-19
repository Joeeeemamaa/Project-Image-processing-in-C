#include "bmp8.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *inputFile;

    if (argc == 2) {
        inputFile = argv[1];
    } else {
        inputFile = "input_image.bmp";  // <-- change this if needed
        printf("No input provided, using default: %s\n", inputFile);
    }

    char outputFile[256];
    t_bmp8 *image;

    image = bmp8_loadImage(inputFile);
    if (!image) {
        printf("Failed to load image.\n");
        return 1;
    }

    // Show info
    bmp8_printInfo(image);

    // Create negative image
    strcpy(outputFile, "negative_");
    strcat(outputFile, inputFile);
    t_bmp8 *negative = bmp8_loadImage(inputFile);
    if (negative) {
        bmp8_negative(negative);
        bmp8_saveImage(outputFile, negative);
        bmp8_free(negative);
    }

    // Brightness +50
    strcpy(outputFile, "bright_");
    strcat(outputFile, inputFile);
    t_bmp8 *bright = bmp8_loadImage(inputFile);
    if (bright) {
        bmp8_brightness(bright, 50);
        bmp8_saveImage(outputFile, bright);
        bmp8_free(bright);
    }

    // Threshold at 128
    strcpy(outputFile, "threshold_");
    strcat(outputFile, inputFile);
    t_bmp8 *threshold = bmp8_loadImage(inputFile);
    if (threshold) {
        bmp8_threshold(threshold, 128);
        bmp8_saveImage(outputFile, threshold);
        bmp8_free(threshold);
    }

    bmp8_free(image);
    return 0;
}
