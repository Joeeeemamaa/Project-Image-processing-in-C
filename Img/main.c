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

void bmp8_saveImage(const char *filename, t_bmp8 *img) {
    if (!img || !img->data) {
        printf("Error: Invalid image data.\n");
        return;
    }

    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error: Unable to open file %s for writing.\n", filename);
        return;
    }

    // Write header
    fwrite(img->header, sizeof(unsigned char), 54, file);

    // Write color table
    fwrite(img->colorTable, sizeof(unsigned char), 1024, file);

    // Write pixel data
    fwrite(img->data, sizeof(unsigned char), img->dataSize, file);

    fclose(file);
    printf("Image saved to %s\n", filename);
}

void bmp8_negative(t_bmp8 *img) {
    if (!img || !img->data) return;

    for (unsigned int i = 0; i < img->dataSize; ++i) {
        img->data[i] = 255 - img->data[i];
    }
}

void bmp8_brightness(t_bmp8 *img, int value) {
    if (!img || !img->data) return;

    for (unsigned int i = 0; i < img->dataSize; ++i) {
        int temp = img->data[i] + value;
        if (temp > 255) temp = 255;
        if (temp < 0) temp = 0;
        img->data[i] = (unsigned char)temp;
    }
}

void bmp8_threshold(t_bmp8 *img, int threshold) {
    if (!img || !img->data) return;

    for (unsigned int i = 0; i < img->dataSize; ++i) {
        img->data[i] = (img->data[i] > threshold) ? 255 : 0;
    }
}
