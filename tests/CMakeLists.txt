add_executable(dummy main-test.cpp)

# target_link_libraries(dummy include)

add_test(
  NAME
    dummy
  COMMAND
    $<TARGET_FILE:dummy>
  )
