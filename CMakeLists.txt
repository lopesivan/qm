cmake_minimum_required(VERSION 3.5)
project(qm)

set(CMAKE_C_STANDARD 99)
SET(CMAKE_VERBOSE_MAKEFILE ON)
SET(CMAKE_C_FLAGS "-Wall -Werror")

set(SOURCE_FILES main.c quine_mc_cluskey.c qmc.h)
add_executable(qm ${SOURCE_FILES})