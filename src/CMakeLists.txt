add_executable(snake main.cpp)

include_directories(include)

add_library(game "")

target_sources(game
  PRIVATE
    Snake.cpp
  )

target_link_libraries(snake
  PRIVATE
    game
  )
