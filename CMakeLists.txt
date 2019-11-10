cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(super_word_search VERSION 0.1 LANGUAGES CXX)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LIB_INSTALL_DIR ${ROOT_DIR}/lib)
set(BIN_INSTALL_DIR ${ROOT_DIR}/bin)

add_subdirectory(wsearch)

# TODO: Add unit tests.
#enable_testing()
#if (testing_enabled)
#    add_subdirectory(test)
#endif
