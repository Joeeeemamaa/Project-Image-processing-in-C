/**
 * main_menu.c
 * Interactive menu-driven interface for BMP image processing
 * 
 * This program provides a user-friendly console interface for processing both 8-bit
 * and 24-bit BMP images. It allows users to select multiple operations to apply
 * sequentially to their images, with proper error handling and feedback.
 * 
 * The program supports the following operations:
 * For 8-bit images:
 * - Negative
 * - Brightness adjustment (+/-)
 * - Thresholding
 * - Histogram equalization
 * - Convolution filtering
 * 
 * For 24-bit images:
 * - Negative
 * - Brightness adjustment (+/-)
 * - Grayscale conversion
 * - Convolution filtering
 * 
 * Each operation creates a new output file with a descriptive name indicating
 * the operation performed and its sequence number.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <direct.h>
#include "bmp8.h"
#include "bmp24.h"

// Forward declarations of types
typedef struct BMP8 BMP8;
typedef struct BMP24 BMP24;

#define MAX_FILENAME 256    // Maximum length for filenames
#define MAX_OPERATIONS 10   // Maximum number of operations that can be performed
#define RESULT_FOLDER "result"  // Folder for output files

// Function declarations
/**
 * Checks if a file exists
 * filename: Path to the file to check
 * Returns: true if file exists, false otherwise
 */
bool fileExists(const char* filename);
/**
 * Prints the menu of available operations for 8-bit images
 */
void printMenu8Bit(void);
/**
 * Prints the menu of available operations for 24-bit images
 */
void printMenu24Bit(void);
/**
 * Processes an 8-bit image with the selected operations
 * filename: Path to the input image
 * numOperations: Number of operations to perform
 */
void process8BitImage(const char* filename, int numOperations);
/**
 * Processes a 24-bit image with the selected operations
 * filename: Path to the input image
 * numOperations: Number of operations to perform
 */
void process24BitImage(const char* filename, int numOperations);
/**
 * Creates the result folder
 */
void createResultFolder(void);

int main() {
    int imageType;
    char filename[MAX_FILENAME];
    int numOperations;
    bool validInput = false;

    printf("Welcome to BMP Image Processor!\n\n");

    // Get image type
    while (!validInput) {
        printf("Select image type:\n");
        printf("1. 8-bit BMP\n");
        printf("2. 24-bit BMP\n");
        printf("Enter your choice (1 or 2): ");
        
        if (scanf("%d", &imageType) == 1 && (imageType == 1 || imageType == 2)) {
            validInput = true;
        } else {
            printf("Invalid input! Please enter 1 or 2.\n");
            while (getchar() != '\n'); // Clear input buffer
        }
    }

    // Get filename
    validInput = false;
    while (!validInput) {
        printf("\nEnter the BMP filename (e.g., image.bmp): ");
        if (scanf("%255s", filename) == 1) {
            if (fileExists(filename)) {
                validInput = true;
            } else {
                printf("File does not exist! Please try again.\n");
            }
        } else {
            printf("Invalid input! Please try again.\n");
            while (getchar() != '\n');
        }
    }

    // Show available operations based on image type
    printf("\nAvailable operations:\n");
    if (imageType == 1) {
        printMenu8Bit();
    } else {
        printMenu24Bit();
    }

    // Get number of operations
    validInput = false;
    while (!validInput) {
        printf("\nHow many operations do you want to perform? (1-%d): ", MAX_OPERATIONS);
        if (scanf("%d", &numOperations) == 1 && numOperations > 0 && numOperations <= MAX_OPERATIONS) {
            validInput = true;
        } else {
            printf("Invalid input! Please enter a number between 1 and %d.\n", MAX_OPERATIONS);
            while (getchar() != '\n');
        }
    }

    // Process image based on type
    if (imageType == 1) {
        process8BitImage(filename, numOperations);
    } else {
        process24BitImage(filename, numOperations);
    }

    return 0;
}

bool fileExists(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        fclose(file);
        return true;
    }
    return false;
}

void printMenu8Bit(void) {
    printf("\nAvailable operations for 8-bit images:\n");
    printf("1. Negative\n");
    printf("2. Brightness +\n");
    printf("3. Brightness -\n");
    printf("4. Thresholding\n");
    printf("5. Histogram Equalization\n");
    printf("6. Convolution Filter\n");
}

void printMenu24Bit(void) {
    printf("\nAvailable operations for 24-bit images:\n");
    printf("1. Negative\n");
    printf("2. Brightness +\n");
    printf("3. Brightness -\n");
    printf("4. Grayscale\n");
    printf("5. Convolution Filter\n");
}

void createResultFolder(void) {
    #ifdef _WIN32
        mkdir(RESULT_FOLDER);
    #endif
}

void process8BitImage(const char* filename, int numOperations) {
    int operations[MAX_OPERATIONS];
    int choice;
    bool validInput;
    t_bmp8* image = NULL;

    // Create result folder
    createResultFolder();

    // Load the image once
    image = bmp8_loadImage(filename);
    if (!image) {
        printf("Error: Failed to load image %s\n", filename);
        return;
    }

    for (int i = 0; i < numOperations; i++) {
        validInput = false;
        while (!validInput) {
            printMenu8Bit();
            printf("\nEnter operation %d (1-6): ", i + 1);
            if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 6) {
                operations[i] = choice;
                validInput = true;
            } else {
                printf("Invalid input! Please enter a number between 1 and 6.\n");
                while (getchar() != '\n');
            }
        }
    }

    // Process each operation
    for (int i = 0; i < numOperations; i++) {
        char outputFilename[MAX_FILENAME];
        t_bmp8* processedImage = NULL;
        
        // Create a copy of the image for processing
        processedImage = bmp8_loadImage(filename);
        if (!processedImage) {
            printf("Error: Failed to load image for operation %d\n", i + 1);
            continue;
        }
        
        switch (operations[i]) {
            case 1: // Negative
                bmp8_negative(processedImage);
                snprintf(outputFilename, MAX_FILENAME, "%s/negative_%d_%s", RESULT_FOLDER, i + 1, filename);
                bmp8_saveImage(outputFilename, processedImage);
                printf("Saved negative image as %s\n", outputFilename);
                break;
                
            case 2: // Brightness +
                bmp8_brightness(processedImage, 50);
                snprintf(outputFilename, MAX_FILENAME, "%s/bright_%d_%s", RESULT_FOLDER, i + 1, filename);
                bmp8_saveImage(outputFilename, processedImage);
                printf("Saved brightened image as %s\n", outputFilename);
                break;
                
            case 3: // Brightness -
                bmp8_brightness(processedImage, -50);
                snprintf(outputFilename, MAX_FILENAME, "%s/dark_%d_%s", RESULT_FOLDER, i + 1, filename);
                bmp8_saveImage(outputFilename, processedImage);
                printf("Saved darkened image as %s\n", outputFilename);
                break;
                
            case 4: // Thresholding
                bmp8_threshold(processedImage, 128);
                snprintf(outputFilename, MAX_FILENAME, "%s/threshold_%d_%s", RESULT_FOLDER, i + 1, filename);
                bmp8_saveImage(outputFilename, processedImage);
                printf("Saved thresholded image as %s\n", outputFilename);
                break;
                
            case 5: // Histogram Equalization
                {
                    unsigned int* hist = bmp8_computeHistogram(processedImage);
                    unsigned int total_pixels = processedImage->width * processedImage->height;
                    unsigned int* cdf = bmp8_computeCDF(hist, total_pixels);
                    bmp8_equalize(processedImage, cdf);
                    free(hist);
                    free(cdf);
                    snprintf(outputFilename, MAX_FILENAME, "%s/equalized_%d_%s", RESULT_FOLDER, i + 1, filename);
                    bmp8_saveImage(outputFilename, processedImage);
                    printf("Saved equalized image as %s\n", outputFilename);
                }
                break;
                
            case 6: // Convolution Filter
                {
                    float** kernel = (float**)malloc(3 * sizeof(float*));
                    for (int j = 0; j < 3; j++) {
                        kernel[j] = (float*)malloc(3 * sizeof(float));
                        for (int k = 0; k < 3; k++) {
                            kernel[j][k] = 1.0f/9;
                        }
                    }
                    bmp8_applyFilter(processedImage, kernel, 3);
                    for (int j = 0; j < 3; j++) {
                        free(kernel[j]);
                    }
                    free(kernel);
                    snprintf(outputFilename, MAX_FILENAME, "%s/filtered_%d_%s", RESULT_FOLDER, i + 1, filename);
                    bmp8_saveImage(outputFilename, processedImage);
                    printf("Saved filtered image as %s\n", outputFilename);
                }
                break;
        }
        
        // Free the processed image
        bmp8_free(processedImage);
    }
    
    // Free the original image
    bmp8_free(image);
}

void process24BitImage(const char* filename, int numOperations) {
    int operations[MAX_OPERATIONS];
    int choice;
    bool validInput;
    t_bmp24* image = NULL;

    // Create result folder
    createResultFolder();

    // Load the image once
    image = bmp24_loadImage(filename);
    if (!image) {
        printf("Error: Failed to load image %s\n", filename);
        return;
    }

    for (int i = 0; i < numOperations; i++) {
        validInput = false;
        while (!validInput) {
            printMenu24Bit();
            printf("\nEnter operation %d (1-5): ", i + 1);
            if (scanf("%d", &choice) == 1 && choice >= 1 && choice <= 5) {
                operations[i] = choice;
                validInput = true;
            } else {
                printf("Invalid input! Please enter a number between 1 and 5.\n");
                while (getchar() != '\n');
            }
        }
    }

    // Process each operation
    for (int i = 0; i < numOperations; i++) {
        char outputFilename[MAX_FILENAME];
        t_bmp24* processedImage = NULL;
        
        // Create a copy of the image for processing
        processedImage = bmp24_loadImage(filename);
        if (!processedImage) {
            printf("Error: Failed to load image for operation %d\n", i + 1);
            continue;
        }
        
        switch (operations[i]) {
            case 1: // Negative
                bmp24_negative(processedImage);
                snprintf(outputFilename, MAX_FILENAME, "%s/negative_%d_%s", RESULT_FOLDER, i + 1, filename);
                bmp24_saveImage(processedImage, outputFilename);
                printf("Saved negative image as %s\n", outputFilename);
                break;
                
            case 2: // Brightness +
                bmp24_brightness(processedImage, 50);
                snprintf(outputFilename, MAX_FILENAME, "%s/bright_%d_%s", RESULT_FOLDER, i + 1, filename);
                bmp24_saveImage(processedImage, outputFilename);
                printf("Saved brightened image as %s\n", outputFilename);
                break;
                
            case 3: // Brightness -
                bmp24_brightness(processedImage, -50);
                snprintf(outputFilename, MAX_FILENAME, "%s/dark_%d_%s", RESULT_FOLDER, i + 1, filename);
                bmp24_saveImage(processedImage, outputFilename);
                printf("Saved darkened image as %s\n", outputFilename);
                break;
                
            case 4: // Grayscale
                bmp24_grayscale(processedImage);
                snprintf(outputFilename, MAX_FILENAME, "%s/grayscale_%d_%s", RESULT_FOLDER, i + 1, filename);
                bmp24_saveImage(processedImage, outputFilename);
                printf("Saved grayscale image as %s\n", outputFilename);
                break;
                
            case 5: // Convolution Filter
                {
                    float** kernel = (float**)malloc(3 * sizeof(float*));
                    for (int j = 0; j < 3; j++) {
                        kernel[j] = (float*)malloc(3 * sizeof(float));
                        for (int k = 0; k < 3; k++) {
                            kernel[j][k] = 1.0f/9;
                        }
                    }
                    bmp24_applyFilter(processedImage, kernel, 3);
                    for (int j = 0; j < 3; j++) {
                        free(kernel[j]);
                    }
                    free(kernel);
                    snprintf(outputFilename, MAX_FILENAME, "%s/filtered_%d_%s", RESULT_FOLDER, i + 1, filename);
                    bmp24_saveImage(processedImage, outputFilename);
                    printf("Saved filtered image as %s\n", outputFilename);
                }
                break;
        }
        
        // Free the processed image
        bmp24_free(processedImage);
    }
    
    // Free the original image
    bmp24_free(image);
} 