cmake_minimum_required(VERSION 3.20)
project(${SKBUILD_PROJECT_NAME} LANGUAGES C)

find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)

python_add_library(calculator MODULE src/calculator.c)

install(TARGETS calculator DESTINATION .)
