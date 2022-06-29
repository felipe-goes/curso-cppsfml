cmake_minimum_required(VERSION 3.23.1 FATAL_ERROR)
project(cpp-sfml VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include SFML
include_directories(include/SFML/include)

add_subdirectory(src)

# SFML libs
find_library(AUDIO sfml-audio libs)
find_library(GRAPHICS sfml-graphics libs)
find_library(NETWORK sfml-network libs)
find_library(SFMLSYSTEM sfml-system libs)
find_library(WINDOW sfml-window libs)

target_link_libraries(cpp-sfml
  PRIVATE
    ${AUDIO}
    ${GRAPHICS}
    ${NETWORK}
    ${SFMLSYSTEM}
    ${WINDOW}
  )

enable_testing()
add_subdirectory(tests)

