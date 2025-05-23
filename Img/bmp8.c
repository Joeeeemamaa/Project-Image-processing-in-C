/**
 * Implementation of 8-bit BMP image processing functions
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bmp8.h"

/* File I/O Operations */
t_bmp8* bmp8_loadImage(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error: Unable to open file %s\n", filename);
        return NULL;
    }

    // Read BMP header (54 bytes)
    unsigned char header[54];
    if (fread(header, sizeof(unsigned char), 54, file) != 54) {
        printf("Error: Failed to read BMP header.\n");
        fclose(file);
        return NULL;
    }

    // Extract image metadata from the header
    unsigned int width = *(unsigned int *)&header[18];
    unsigned int height = *(unsigned int *)&header[22];
    unsigned short colorDepth = *(unsigned short *)&header[28];

    // Verify that the image is 8-bit grayscale
    if (colorDepth != 8) {
        printf("Error: Image is not 8-bit grayscale (found %d-bit color depth).\n", colorDepth);
        fclose(file);
        return NULL;
    }

    // Calculate data size (each row is padded to 4-byte boundary)
    unsigned int rowSize = (width + 3) & ~3;
    unsigned int dataSize = rowSize * height;

    // Allocate memory for the image structure
    t_bmp8 *image = (t_bmp8*)malloc(sizeof(t_bmp8));
    if (!image) {
        printf("Error: Memory allocation failed.\n");
        fclose(file);
        return NULL;
    }

    // Initialize structure fields
    image->width = width;
    image->height = height;
    image->colorDepth = colorDepth;
    image->dataSize = dataSize;
    
    // Copy header
    memcpy(image->header, header, 54);
    
    // Read color table
    if (fread(image->colorTable, sizeof(unsigned char), 1024, file) != 1024) {
        printf("Error: Failed to read color table.\n");
        free(image->data);
        free(image);
        fclose(file);
        return NULL;
    }
    
    image->data = (unsigned char*)malloc(dataSize);
    if (!image->data) {
        printf("Error: Memory allocation for image data failed.\n");
        free(image);
        fclose(file);
        return NULL;
    }

    // Move file pointer to the pixel data
    unsigned int dataOffset = *(unsigned int*)&header[10];
    fseek(file, dataOffset, SEEK_SET);

    // Read pixel data
    if (fread(image->data, sizeof(unsigned char), dataSize, file) != dataSize) {
        printf("Error: Failed to read image data.\n");
        free(image->data);
        free(image);
        fclose(file);
        return NULL;
    }

    fclose(file);
    return image;
}

void bmp8_free(t_bmp8 *img) {
    if (img) {
        if (img->data) {
            free(img->data);
        }
        free(img);
        printf("Image memory successfully freed.\n");
    }
}

void bmp8_printInfo(t_bmp8 *img) {
    if (!img) {
        printf("Error: Invalid image pointer.\n");
        return;
    }

    printf("Image Info:\n");
    printf("Width: %d\n", img->width);
    printf("Height: %d\n", img->height);
    printf("Color Depth: %d-bit\n", img->colorDepth);
    printf("Data Size: %d bytes\n", img->dataSize);
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

/* Basic Image Transformations */
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

/* Advanced Image Processing */
void bmp8_applyFilter(t_bmp8 *img, float **kernel, int kernelSize) {
    if (!img || !img->data) return;

    int n = kernelSize / 2;
    unsigned int width = img->width;
    unsigned int height = img->height;
    unsigned int rowSize = (width + 3) & ~3;

    // Allocate memory for a copy of the original data
    unsigned char *copy = (unsigned char *)malloc(img->dataSize);
    if (!copy) {
        printf("Error: Memory allocation for filter copy failed.\n");
        return;
    }
    memcpy(copy, img->data, img->dataSize);

    for (int y = n; y < (int)height - n; y++) {
        for (int x = n; x < (int)width - n; x++) {
            float sum = 0.0f;

            for (int ky = -n; ky <= n; ky++) {
                for (int kx = -n; kx <= n; kx++) {
                    int ix = x + kx;
                    int iy = y + ky;
                    unsigned char pixel = copy[iy * rowSize + ix];
                    sum += pixel * kernel[ky + n][kx + n];
                }
            }

            int result = (int)(sum + 0.5f);
            if (result < 0) result = 0;
            if (result > 255) result = 255;

            img->data[y * rowSize + x] = (unsigned char)result;
        }
    }
    free(copy);
}

/* Histogram Operations */
unsigned int *bmp8_computeHistogram(t_bmp8 *img) {
    unsigned int *hist = calloc(256, sizeof(unsigned int));
    if (!hist) {
        fprintf(stderr, "Error: Failed to allocate memory for histogram.\n");
        return NULL;
    }

    for (unsigned int i = 0; i < img->dataSize; i++) {
        hist[img->data[i]]++;
    }

    return hist;
}

unsigned int *bmp8_computeCDF(unsigned int *hist, unsigned int total_pixels) {
    unsigned int *cdf = calloc(256, sizeof(unsigned int));
    if (!cdf) {
        fprintf(stderr, "Error: Failed to allocate memory for CDF.\n");
        return NULL;
    }

    // Compute raw CDF
    cdf[0] = hist[0];
    for (int i = 1; i < 256; i++) {
        cdf[i] = cdf[i - 1] + hist[i];
    }

    // Find cdfmin (first non-zero)
    unsigned int cdfmin = 0;
    for (int i = 0; i < 256; i++) {
        if (cdf[i] != 0) {
            cdfmin = cdf[i];
            break;
        }
    }

    // Normalize to get equalized histogram
    for (int i = 0; i < 256; i++) {
        cdf[i] = round((double)(cdf[i] - cdfmin) / (total_pixels - cdfmin) * 255.0);
    }

    return cdf;
}

void bmp8_equalize(t_bmp8 *img, unsigned int *hist_eq) {
    for (unsigned int i = 0; i < img->dataSize; i++) {
        img->data[i] = (unsigned char)hist_eq[img->data[i]];
    }
}