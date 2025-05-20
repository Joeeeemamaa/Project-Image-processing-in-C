#include "bmp8.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *inputFile;

    if (argc == 2) {
        inputFile = argv[1];
    } else {
        inputFile = "input_image.bmp";  // <-- default fallback
        printf("No input provided, using default: %s\n", inputFile);
    }

    char outputFile[256];
    t_bmp8 *image = bmp8_loadImage(inputFile);

    if (!image) {
        printf("Failed to load image.\n");
        return 1;
    }

    // Show image info
    bmp8_printInfo(image);

    // Create negative version of the image
    strcpy(outputFile, "negative_");
    strcat(outputFile, inputFile);
    t_bmp8 *negative = bmp8_loadImage(inputFile);
    if (negative) {
        bmp8_negative(negative);
        bmp8_saveImage(outputFile, negative);
        bmp8_free(negative);
        printf("Negative image saved as %s\n", outputFile);
    }

    // Increase image brightness by 50 units
    strcpy(outputFile, "bright_");
    strcat(outputFile, inputFile);
    t_bmp8 *bright = bmp8_loadImage(inputFile);
    if (bright) {
        bmp8_brightness(bright, 50);
        bmp8_saveImage(outputFile, bright);
        bmp8_free(bright);
        printf("Brightened image saved as %s\n", outputFile);
    }

    // Apply binary threshold at value 128
    strcpy(outputFile, "threshold_");
    strcat(outputFile, inputFile);
    t_bmp8 *threshold = bmp8_loadImage(inputFile);
    if (threshold) {
        bmp8_threshold(threshold, 128);
        bmp8_saveImage(outputFile, threshold);
        bmp8_free(threshold);
        printf("Threshold image saved as %s\n", outputFile);
    }

    // Apply histogram equalization to enhance contrast
    strcpy(outputFile, "equalized_");
    strcat(outputFile, inputFile);
    t_bmp8 *equalized = bmp8_loadImage(inputFile);
    if (equalized) {
        unsigned int *hist = bmp8_computeHistogram(equalized);
        unsigned int *cdf = bmp8_computeCDF(hist, equalized->width * equalized->height);
        bmp8_equalize(equalized, cdf);

        bmp8_saveImage(outputFile, equalized);
        bmp8_free(equalized);
        free(hist);
        free(cdf);
        printf("Equalized image saved as %s\n", outputFile);
    }

    bmp8_free(image);
    return 0;
}
