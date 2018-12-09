cmake_minimum_required(VERSION 3.13)
project(ProgTest06_wordWrap C)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -pedantic")

add_executable(ProgTest06_wordWrap main.c)