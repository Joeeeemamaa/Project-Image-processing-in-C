# 📷 BMP Image Processor (8-bit & 24-bit)

A C-based image processing toolkit for BMP files. This project provides a comprehensive set of image processing operations for both 8-bit grayscale and 24-bit true color BMP images. It's designed to be educational and practical, demonstrating fundamental image processing techniques.

## 📁 Project Structure

```
.
├── bmp8.c / bmp8.h         → 8-bit grayscale BMP support
├── bmp24.c / bmp24.h       → 24-bit color BMP support
├── main.c                  → Demo for 8-bit BMP operations
├── main_color.c            → Demo for 24-bit BMP operations
├── main_menu.c             → Interactive menu-driven interface
```

## 🖼 Features

### ✅ Supported Formats
- 8-bit grayscale BMP (with color table)
- 24-bit true color BMP

### 🧰 Operations Overview

| Operation           | 8-bit | 24-bit | Description |
|--------------------|:-----:|:------:|-------------|
| Load/Save          |   ✅   |   ✅    | Basic I/O operations |
| Negative           |   ✅   |   ✅    | Inverts image colors |
| Brightness +/-     |   ✅   |   ✅    | Adjusts image brightness |
| Thresholding       |   ✅   |   ❌    | Converts to binary image |
| Grayscale          |   ❌   |   ✅    | Converts color to grayscale |
| Histogram Equalize |   ✅   |   ❌    | Improves image contrast |
| Convolution Filter |   ✅   |   ✅    | Applies various filters |

## ⚙️ Build Instructions

### Prerequisites
- GCC or any C99-compliant compiler
- Make (optional, for using Makefile)

### Compilation
```bash
# Compile 8-bit processor
gcc main.c bmp8.c -o bmp8_processor

# Compile 24-bit processor
gcc main_color.c bmp24.c -lm -o bmp24_processor

# Compile menu-driven processor
gcc main_menu.c bmp8.c bmp24.c -lm -o bmp_menu_processor
```

## 🚀 Usage

### Menu-Driven Interface
```bash
./bmp_menu_processor
```
This interactive interface allows you to:
1. Choose between 8-bit and 24-bit image processing
2. Select your input BMP file
3. Choose multiple operations to apply sequentially
4. Get separate output files for each operation

Available operations for 8-bit images:
1. Negative
2. Brightness +
3. Brightness -
4. Thresholding
5. Histogram Equalization
6. Convolution Filter

Available operations for 24-bit images:
1. Negative
2. Brightness +
3. Brightness -
4. Grayscale
5. Convolution Filter

Each operation creates a new output file with a descriptive name indicating the operation performed and its sequence number.

### 8-bit Grayscale Processor
```bash
./bmp8_processor <image.bmp>
```
If no file is provided, defaults to `input_image.bmp`.

**Outputs generated:**
- `negative_<image>.bmp` - Inverted version
- `bright_<image>.bmp` - Brightness adjusted (+50)
- `threshold_<image>.bmp` - Binary threshold at 128
- `equalized_<image>.bmp` - Contrast enhanced version

### 24-bit Color Processor
```bash
./bmp24_processor <image.bmp>
```
If no file is provided, defaults to `flowers_color.bmp`.

**Outputs generated:**
- `color_negative_<image>.bmp` - Inverted colors
- `color_grayscale_<image>.bmp` - Grayscale conversion
- `color_bright_<image>.bmp` - Brightness adjusted (+50)
- `color_blur_<image>.bmp` - 3x3 box blur applied

## 🔍 API Overview

### From `bmp8.h`
- `bmp8_loadImage` - Loads 8-bit BMP image
- `bmp8_saveImage` - Saves image to file
- `bmp8_free` - Frees image memory
- `bmp8_negative` - Creates negative version
- `bmp8_brightness` - Adjusts brightness
- `bmp8_threshold` - Applies binary threshold
- `bmp8_applyFilter` - Applies convolution filter
- `bmp8_equalize` - Performs histogram equalization

### From `bmp24.h`
- `bmp24_loadImage` - Loads 24-bit BMP image
- `bmp24_saveImage` - Saves image to file
- `bmp24_free` - Frees image memory
- `bmp24_negative` - Creates negative version
- `bmp24_brightness` - Adjusts brightness
- `bmp24_grayscale` - Converts to grayscale
- `bmp24_applyFilter` - Applies convolution filter

## 🐛 Known Issues

1. **Memory Management**
   - No memory leak detection
   - Large images might cause memory issues

2. **File Format Limitations**
   - Only supports uncompressed BMP format
   - No support for RLE compression
   - Limited to 8-bit and 24-bit color depths

3. **Performance**
   - Convolution operations are not optimized
   - Large images may process slowly

4. **Feature Limitations**
   - No support for 16-bit or 32-bit images
   - Limited filter kernel sizes
   - No support for custom color tables

## 🧪 Technical Notes

- Convolution uses a 3×3 box blur kernel by default
- Histogram equalization and thresholding are implemented from scratch
- Works only with uncompressed BMP format
- All operations are performed in-place to save memory

## 👤 Authors

- **[Jehchi Aaron](https://github.com/Joeeeemamaa)**
- **[Bencoil Jérémie](https://github.com/jeremiel1110)**
