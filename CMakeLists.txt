cmake_minimum_required(VERSION 3.16)

project(Kepler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(${PROJECT_NAME} Kepler.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE Eigen3::Eigen)

