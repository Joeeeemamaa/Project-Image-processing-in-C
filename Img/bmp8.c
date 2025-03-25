#include <stdio.h>
#include "bmp8.h"

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