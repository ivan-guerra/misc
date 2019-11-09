project(wsearch VERSION 0.1 LANGUAGES CXX)

file(GLOB WSEARCH_SRC
    "src/*.cc")

add_executable(${PROJECT_NAME}
    ${WSEARCH_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_options(${PROJECT_NAME}
    PUBLIC -std=c++14
    PRIVATE -Wall -Werror)

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${BIN_INSTALL_DIR})
