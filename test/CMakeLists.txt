include(CTest)
enable_testing()
set(TESTS_TIMEOUT 5)

set(TESTS TCP_Connect TCP_Send UDP_Send UDP_Broadcast)

set(TEST_NUMBER 0)

foreach(TEST IN LISTS TESTS)
  math(EXPR TEST_NUMBER ${TEST_NUMBER}+2)

  add_executable(${TEST} ${TEST}.cpp)
  target_compile_definitions(${TEST} PUBLIC TEST_NUMBER=${TEST_NUMBER})

  target_link_libraries(${TEST} PUBLIC ${PROJECT_NAME})

  add_test(${TEST} ${TEST})

  set_tests_properties(
    ${TEST} PROPERTIES TIMEOUT ${TESTS_TIMEOUT} PASS_REGULAR_EXPRESSION "PASS"
                       FAIL_REGULAR_EXPRESSION "FAIL")

endforeach()
