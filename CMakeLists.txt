cmake_minimum_required(VERSION 3.0)
project(sampleCmake)
add_executable(main src/main.cpp lib/glad.c)

set(CMAKE_EXE_LINKER_FLAGS "-lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl")

include_directories("./dependencies/include")
