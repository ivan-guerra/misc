cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(dice_invaders VERSION 0.1 LANGUAGES CXX)

set(ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(BIN_INSTALL_DIR ${ROOT_DIR}/bin)

add_subdirectory(app)
