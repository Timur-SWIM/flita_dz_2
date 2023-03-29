cmake_minimum_required(VERSION 3.24)
project(dz_2 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(dz_2
        main.c
        main.h deblank.c)
