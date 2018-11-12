cmake_minimum_required(VERSION 3.12)
project(untitled C)

set(CMAKE_C_STANDARD 99)

add_executable(untitled main.c parser.c parser.h PlayGround.c calculateMatch.c calculateMatch.h )