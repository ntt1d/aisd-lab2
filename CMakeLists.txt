cmake_minimum_required(VERSION 4.1)

set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")

project("AiSD_Lab2" CXX)

add_executable("lab" "main.cpp")

target_compile_features("lab" PUBLIC cxx_std_23)