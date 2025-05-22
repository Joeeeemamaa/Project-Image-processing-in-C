
# 📷 BMP Image Processor (8-bit & 24-bit)

A C-based image processing toolkit for BMP files. This project supports **8-bit grayscale** and **24-bit true color** BMP images with operations like **negative conversion**, **brightness adjustment**, **grayscale transformation**, **thresholding**, **histogram equalization**, and **convolution filters**.

---

## 📁 Project Structure

```
.
├── bmp8.c / bmp8.h         → 8-bit grayscale BMP support
├── bmp24.c / bmp24.h       → 24-bit color BMP support
├── main.c                  → Demo for 8-bit BMP operations
├── main_color.c            → Demo for 24-bit BMP operations
```

---

## 🖼 Features

### ✅ Supported Formats
- 8-bit grayscale BMP (with color table)
- 24-bit true color BMP

### 🧰 Operations Overview

| Operation           | 8-bit | 24-bit |
|--------------------|:-----:|:------:|
| Load/Save          |   ✅   |   ✅    |
| Negative           |   ✅   |   ✅    |
| Brightness +/-     |   ✅   |   ✅    |
| Thresholding       |   ✅   |   ❌    |
| Grayscale          |   ❌   |   ✅    |
| Histogram Equalize |   ✅   |   ❌    |
| Convolution Filter |   ✅   |   ✅    |

---

## ⚙️ Build Instructions

Compile using GCC or any C99-compliant compiler:

```bash
gcc main.c bmp8.c -o bmp8_processor
gcc main_color.c bmp24.c -lm -o bmp24_processor
```

---

## 🚀 Usage

### 🎛 8-bit Grayscale Processor

```bash
./bmp8_processor <image.bmp>
```
If no file is provided, defaults to `input_image.bmp`.

**Outputs generated:**
- `negative_<image>.bmp`
- `bright_<image>.bmp`
- `threshold_<image>.bmp`
- `equalized_<image>.bmp`

### 🎨 24-bit Color Processor

```bash
./bmp24_processor <image.bmp>
```
If no file is provided, defaults to `flowers_color.bmp`.

**Outputs generated:**
- `color_negative_<image>.bmp`
- `color_grayscale_<image>.bmp`
- `color_bright_<image>.bmp`
- `color_blur_<image>.bmp`

---

## 🔍 API Overview

### From `bmp8.h`
- `bmp8_loadImage`, `bmp8_saveImage`, `bmp8_free`
- `bmp8_negative`, `bmp8_brightness`, `bmp8_threshold`
- `bmp8_applyFilter`, `bmp8_equalize`

### From `bmp24.h`
- `bmp24_loadImage`, `bmp24_saveImage`, `bmp24_free`
- `bmp24_negative`, `bmp24_brightness`, `bmp24_grayscale`
- `bmp24_applyFilter` (with convolution)

---

## 🧪 Notes

- Convolution uses a 3×3 box blur kernel by default.
- Histogram equalization and thresholding are implemented from scratch for grayscale images.
- Works only with uncompressed BMP format.

---

## 👤 Author

- **[Jehchi Aaron](https://github.com/Joeeeemamaa)**
- **[Bencoil Jérémie](https://github.com/jeremiel1110)**
