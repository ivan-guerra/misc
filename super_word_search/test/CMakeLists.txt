project(wsearch_test)

file(GLOB WSEARCH_TEST_SRC
    "*.cc")

add_executable(${PROJECT_NAME}
    ${WSEARCH_TEST_SRC})

add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PUBLIC
    gtest
    wsearch_lib)

install (TARGETS ${PROJECT_NAME}
    DESTINATION ${BIN_INSTALL_DIR})
