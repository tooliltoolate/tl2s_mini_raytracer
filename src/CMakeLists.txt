cmake_minimum_required(VERSION 3.28)
project(tl2_raytracer CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(Image)

target_sources(Image PUBLIC
	FILE_SET CXX_MODULES
	BASE_DIRS ${CMAKE_SOURCE_DIR}/modules
	FILES modules/image.cxx
)

add_executable(tl2_raytracer main.cxx)
target_link_libraries(tl2_raytracer Image)
