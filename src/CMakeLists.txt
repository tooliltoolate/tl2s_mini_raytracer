cmake_minimum_required(VERSION 3.28)
project(tl2_raytracer CXX)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/305e5a238b3c8d11266fbafd85520fb6b3184851.zip
)
FetchContent_MakeAvailable(googletest)

add_library(Image)

target_sources(Image PUBLIC
	FILE_SET CXX_MODULES
	BASE_DIRS ${CMAKE_SOURCE_DIR}/modules
	FILES modules/image.cxx
)

add_library(Geometry)

target_sources(Geometry PUBLIC
	FILE_SET CXX_MODULES
	BASE_DIRS ${CMAKE_SOURCE_DIR}/modules
	FILES modules/geometry.cxx
)

add_executable(tl2_raytracer main.cxx modules/lodepng.cpp)
target_link_libraries(tl2_raytracer Image Geometry)

enable_testing()

add_executable(image_test image_test.cxx modules/lodepng.cpp)
target_link_libraries(image_test GTest::gtest_main Image)

include(GoogleTest)
gtest_discover_tests(image_test)
