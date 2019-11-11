cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(super_word_search VERSION 0.1 LANGUAGES CXX)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LIB_INSTALL_DIR ${ROOT_DIR}/lib)
set(BIN_INSTALL_DIR ${ROOT_DIR}/bin)

add_subdirectory(wsearch)

enable_testing()
add_subdirectory(test)
add_subdirectory(lib/googletest)
