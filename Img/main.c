#include "bmp8.h"
#include <string.h>

/*
// Example: Box Blur 3x3
float box_blur_data[3][3] = {
    {1.0f/9, 1.0f/9, 1.0f/9},
    {1.0f/9, 1.0f/9, 1.0f/9},
    {1.0f/9, 1.0f/9, 1.0f/9}
};

// Convert to float** before passing to the function
float *box_blur[3] = { box_blur_data[0], box_blur_data[1], box_blur_data[2] };

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_image.bmp>\n", argv[0]);
        return 1;
    }

    const char *inputFile = argv[1];
    char outputFile[256];
    t_bmp8 *image;

    // Load the image
    image = bmp8_loadImage(inputFile);
    if (!image) {
        printf("Failed to load image.\n");
        return 1;
    }

    // Print image info
    printf("\nOriginal Image Info:\n");
    bmp8_printInfo(image);

    // Create negative image
    strcpy(outputFile, "negative_");
    strcat(outputFile, inputFile);
    t_bmp8 *negative = bmp8_loadImage(inputFile);
    if (negative) {
        bmp8_negative(negative);
        bmp8_saveImage(outputFile, negative);
        bmp8_free(negative);
        printf("Negative image saved as: %s\n", outputFile);
    }

    // Create brightened image
    strcpy(outputFile, "bright_");
    strcat(outputFile, inputFile);
    t_bmp8 *bright = bmp8_loadImage(inputFile);
    if (bright) {
        bmp8_brightness(bright, 50);  // Increase brightness by 50
        bmp8_saveImage(outputFile, bright);
        bmp8_free(bright);
        printf("Brightened image saved as: %s\n", outputFile);
    }

    // Create thresholded image
    strcpy(outputFile, "threshold_");
    strcat(outputFile, inputFile);
    t_bmp8 *threshold = bmp8_loadImage(inputFile);
    if (threshold) {
        bmp8_threshold(threshold, 128);  // Threshold at 128
        bmp8_saveImage(outputFile, threshold);
        bmp8_free(threshold);
        printf("Thresholded image saved as: %s\n", outputFile);
    }
    // Create blurred image using box blur filter
    strcpy(outputFile, "blurred_");
    strcat(outputFile, inputFile);
    t_bmp8 *filtered = bmp8_loadImage(inputFile);
    if (filtered) {
        bmp8_applyFilter(filtered, box_blur, 3);
        bmp8_saveImage(outputFile, filtered);
        bmp8_free(filtered);
        printf("Blurred image saved as: %s\n", outputFile);
    }

    // Free memory
    bmp8_free(image);

    return 0;
}

*/