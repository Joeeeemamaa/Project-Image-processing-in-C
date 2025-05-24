cmake_minimum_required(VERSION 3.10)
project(BMP_Image_Processor C)

# Set C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Add math library
find_library(MATH_LIBRARY m)

# 8-bit BMP processor
add_executable(bmp8_processor
    Img/main.c
    Img/bmp8.c
)

# 24-bit BMP processor
add_executable(bmp24_processor
    Img/main_color.c
    Img/bmp24.c
)

# Link math library for 24-bit processor
target_link_libraries(bmp24_processor ${MATH_LIBRARY})

# Set include directories
target_include_directories(bmp8_processor PRIVATE Img)
target_include_directories(bmp24_processor PRIVATE Img)
