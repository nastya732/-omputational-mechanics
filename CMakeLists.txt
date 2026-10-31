cmake_minimum_required(VERSION 3.16)
project(Kepler LANGUAGES CXX)

# Настройки (по желанию)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 1. Подключаем вашу библиотеку из папки src
add_subdirectory(src)

# 2. Собираем исполняемый файл из main.cpp (он должен лежать в корне!)
add_executable(kepler_test main.cpp)

# 3. Задаем стандарт C++20 для main
target_compile_features(kepler_test PRIVATE cxx_std_20)

# 4. Привязываем вашу библиотеку к main
# Имя KeplerConversions должно совпадать с тем, что в src/CMakeLists.txt
target_link_libraries(kepler_test PRIVATE KeplerConversions)