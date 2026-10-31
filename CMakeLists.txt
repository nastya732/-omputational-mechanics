cmake_minimum_required(VERSION 3.16)
project(Kepler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

# 1. Подключаем папку src, чтобы CMake узнал о библиотеке
add_subdirectory(src)

# 2. Создаем исполняемый файл из main.cpp
add_executable(kepler_test tests/main.cpp)

# 3. Связываем main.cpp с нашей библиотекой и Eigen
# (Имя KeplerConversions должно совпадать с тем, что в src/CMakeLists.txt)
target_compile_features(kepler_test PRIVATE cxx_std_20)
target_link_libraries(kepler_test PRIVATE KeplerConversions Eigen3::Eigen)

# 4. ВАЖНО: Указываем, где искать заголовки "library/..."
target_include_directories(kepler_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)
