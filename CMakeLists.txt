cmake_minimum_required(VERSION 3.10)
project(PP_projekt C)

set(CMAKE_C_STANDARD 11)

add_executable(PP_projekt
        main.c
        structs.h
        list.c
        list.h
        file_io.c
        file_io.h
        ui.c
        ui.h
)
