#include <stdio.h>
#include "bmp8.h"

int main() {
    const char *inputFile = "image.bmp";
    const char *outputFile = "output.bmp";

    // Load the image
    t_bmp8 *image = bmp8_loadImage(inputFile);
    if (!image) {
        printf("Failed to load image.\n");
        return 1;
    }

    // Print image info
    bmp8_printInfo(image);

    // Save the image
    bmp8_saveImage(outputFile, image);

    // Free memory
    bmp8_free(image);

    return 0;
}