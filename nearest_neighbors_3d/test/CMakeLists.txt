project(nearest_neighbors_test)

file(GLOB NN_TEST_SRC
    "*.cc")

add_executable(${PROJECT_NAME}
    ${NN_TEST_SRC})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
    gtest
    nearest_neighbors_lib)

install (TARGETS ${PROJECT_NAME}
    DESTINATION ${BIN_INSTALL_DIR})
