#include "bmp24.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

// Allocate a 2D array of t_pixel

// Memory allocation and deallocation functions for image data
t_pixel **bmp24_allocateDataPixels(int width, int height) {
    t_pixel **pixels = (t_pixel **)malloc(height * sizeof(t_pixel *));
    if (!pixels) return NULL;

    for (int i = 0; i < height; i++) {
        pixels[i] = (t_pixel *)malloc(width * sizeof(t_pixel));
        if (!pixels[i]) {
            for (int j = 0; j < i; j++) free(pixels[j]);
            free(pixels);
            return NULL;
        }
    }
    return pixels;
}

void bmp24_freeDataPixels(t_pixel **pixels, int height) {
    if (!pixels) return;
    for (int i = 0; i < height; i++) free(pixels[i]);
    free(pixels);
}

t_bmp24 *bmp24_allocate(int width, int height, int colorDepth) {
    t_bmp24 *img = (t_bmp24 *)malloc(sizeof(t_bmp24));
    if (!img) return NULL;
    img->width = width;
    img->height = height;
    img->colorDepth = colorDepth;
    img->data = bmp24_allocateDataPixels(width, height);
    if (!img->data) {
        free(img);
        return NULL;
    }
    return img;
}

void bmp24_free(t_bmp24 *img) {
    if (!img) return;
    bmp24_freeDataPixels(img->data, img->height);
    free(img);
}

// Print image information and metadata
void bmp24_printInfo(t_bmp24 *img) {
    if (!img) return;
    printf("Image Info:\n");
    printf("Width: %d\n", img->width);
    printf("Height: %d\n", img->height);
    printf("Color Depth: %d-bit\n", img->colorDepth);
}

// File input/output operations for loading and saving images
t_bmp24 *bmp24_loadImage(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Error: cannot open file %s\n", filename);
        return NULL;
    }

    t_bmp_header header;
    fread(&header, sizeof(t_bmp_header), 1, file);

    t_bmp_info info;
    fread(&info, sizeof(t_bmp_info), 1, file);

    if (info.bits != 24) {
        printf("Error: image is not 24-bit\n");
        fclose(file);
        return NULL;
    }

    t_bmp24 *img = bmp24_allocate(info.width, info.height, info.bits);
    if (!img) {
        fclose(file);
        return NULL;
    }

    img->header = header;
    img->header_info = info;

    fseek(file, header.offset, SEEK_SET);

    for (int i = img->height - 1; i >= 0; i--) {
        for (int j = 0; j < img->width; j++) {
            uint8_t bgr[3];
            fread(bgr, sizeof(uint8_t), 3, file);
            img->data[i][j].blue  = bgr[0];
            img->data[i][j].green = bgr[1];
            img->data[i][j].red   = bgr[2];
        }
    }
    fclose(file);
    return img;
}

void bmp24_saveImage(t_bmp24 *img, const char *filename) {
    if (!img) return;
    FILE *file = fopen(filename, "wb");
    if (!file) {
        printf("Error: cannot save file %s\n", filename);
        return;
    }

    fwrite(&img->header, sizeof(t_bmp_header), 1, file);
    fwrite(&img->header_info, sizeof(t_bmp_info), 1, file);

    for (int i = img->height - 1; i >= 0; i--) {
        for (int j = 0; j < img->width; j++) {
            uint8_t bgr[3] = {
                img->data[i][j].blue,
                img->data[i][j].green,
                img->data[i][j].red
            };
            fwrite(bgr, sizeof(uint8_t), 3, file);
        }
    }
    fclose(file);
    printf("Saved image to: %s\n", filename);
}

// Image processing operations (negative, grayscale, brightness)
void bmp24_negative(t_bmp24 *img) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            img->data[i][j].red   = 255 - img->data[i][j].red;
            img->data[i][j].green = 255 - img->data[i][j].green;
            img->data[i][j].blue  = 255 - img->data[i][j].blue;
        }
    }
}

void bmp24_grayscale(t_bmp24 *img) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            uint8_t avg = (img->data[i][j].red + img->data[i][j].green + img->data[i][j].blue) / 3;
            img->data[i][j].red = img->data[i][j].green = img->data[i][j].blue = avg;
        }
    }
}

void bmp24_brightness(t_bmp24 *img, int value) {
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            int r = img->data[i][j].red + value;
            int g = img->data[i][j].green + value;
            int b = img->data[i][j].blue + value;
            img->data[i][j].red   = (r > 255) ? 255 : (r < 0 ? 0 : r);
            img->data[i][j].green = (g > 255) ? 255 : (g < 0 ? 0 : g);
            img->data[i][j].blue  = (b > 255) ? 255 : (b < 0 ? 0 : b);
        }
    }
}

// Convolution and filtering operations
t_pixel bmp24_convolution(t_bmp24 *img, int x, int y, float **kernel, int kernelSize) {
    int offset = kernelSize / 2;
    float sumR = 0, sumG = 0, sumB = 0;

    for (int i = -offset; i <= offset; i++) {
        for (int j = -offset; j <= offset; j++) {
            int xi = x + i;
            int yj = y + j;
            if (xi < 0 || xi >= img->height || yj < 0 || yj >= img->width) continue;

            t_pixel px = img->data[xi][yj];
            float coeff = kernel[i + offset][j + offset];

            sumR += coeff * px.red;
            sumG += coeff * px.green;
            sumB += coeff * px.blue;
        }
    }

    t_pixel result;
    result.red   = fminf(fmaxf(roundf(sumR), 0), 255);
    result.green = fminf(fmaxf(roundf(sumG), 0), 255);
    result.blue  = fminf(fmaxf(roundf(sumB), 0), 255);
    return result;
}

void bmp24_applyFilter(t_bmp24 *img, float **kernel, int kernelSize) {
    t_pixel **copy = bmp24_allocateDataPixels(img->width, img->height);
    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            copy[i][j] = bmp24_convolution(img, i, j, kernel, kernelSize);
        }
    }

    for (int i = 0; i < img->height; i++) {
        for (int j = 0; j < img->width; j++) {
            img->data[i][j] = copy[i][j];
        }
    }
    bmp24_freeDataPixels(copy, img->height);
}
