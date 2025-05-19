cmake_minimum_required(VERSION 3.30)
project(Project_Image_processing_in_C C)

set(CMAKE_C_STANDARD 11)

include_directories(Img)

add_executable(Project_Image_processing_in_C
    Img/bmp8.c
    Img/bmp8.h
    Img/main.c
    Img/main_color.c
    Img/bmp24.c
    Img/bmp24.h)
