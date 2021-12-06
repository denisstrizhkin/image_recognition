cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(image_recognition VERSION 1.0)
find_package(OpenCV REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
add_executable(image_recognition ${SRC_FILES})

target_include_directories(image_recognition PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(image_recognition ${OpenCV_LIBS})
