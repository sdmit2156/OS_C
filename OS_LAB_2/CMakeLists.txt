cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем исполняемый файл
add_executable(MyApp src/main.cpp "src/logic.cpp" "src/logic.h")

# Подключаем GoogleTest
enable_testing()
add_subdirectory(tests)
