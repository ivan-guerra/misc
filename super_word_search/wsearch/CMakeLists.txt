project(wsearch VERSION 0.1 LANGUAGES CXX)

file(GLOB WSEARCH_SRC
    "src/*.cc")

add_executable(${PROJECT_NAME}
    ${WSEARCH_SRC})

# We are building this static lib so that we can link the code
# in to our tests during unit testing. In a larger project,
# WordSearchSolver would exist in it's own shared lib and be
# linked into both the application and test binary.
add_library(${PROJECT_NAME}_lib STATIC
    ${WSEARCH_SRC})

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_include_directories(${PROJECT_NAME}_lib PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)

target_compile_options(${PROJECT_NAME}
    PUBLIC -std=c++14
    PRIVATE -Wall -Werror)

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${BIN_INSTALL_DIR})

install(TARGETS ${PROJECT_NAME}_lib
    DESTINATION ${LIB_INSTALL_DIR})
