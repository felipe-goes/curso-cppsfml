add_executable(cpp-sfml main.cpp)

include_directories(include)

add_library(minecrap "")

target_sources(minecrap
  PRIVATE
    minecrap.cpp
  )

target_link_libraries(cpp-sfml
  PRIVATE
    minecrap
  )
