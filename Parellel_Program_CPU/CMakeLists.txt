cmake_minimum_required(VERSION 3.17)
project(Parellel_Program_CPU C)

set(CMAKE_C_STANDARD 11)

add_executable(Parellel_Program_CPU main.c ImageProcessing.h ImageProcessing.c ImageIO.h ImageIO.c)