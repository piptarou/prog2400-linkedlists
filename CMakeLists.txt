cmake_minimum_required(VERSION 3.29)
project(prog2400_linkedlists C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(prog2400_linkedlists
    linked_list.c
    main.c
    singly_linked_list.h)
