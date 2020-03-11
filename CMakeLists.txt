# Project's name
PROJECT ( kmeans C )

# Specify the minimum version for CMake

cmake_minimum_required(VERSION 3.1)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

find_package(Png REQUIRED)
include_directories(${PNG_INCLUDE_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}/include")
#include_directories("/usr/local/include")

add_library(${PROJECT_NAME} SHARED 
	${PROJECT_SOURCE_DIR}/src/image.c
	${PROJECT_SOURCE_DIR}/src/center.c
	${PROJECT_SOURCE_DIR}/src/kmeans.c
	${PROJECT_SOURCE_DIR}/src/utils.c
)

target_link_libraries(${PROJECT_NAME} PNG::PNG)
target_link_libraries(${PROJECT_NAME} m)

add_executable(main ${PROJECT_SOURCE_DIR}/main.c)

target_link_libraries(main PNG::PNG)
target_link_libraries(main ${PROJECT_NAME})
