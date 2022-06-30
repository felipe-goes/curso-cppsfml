#include "Snake.hpp"

int main()
{
  Snake *snake = new Snake();
  snake->run_game();
  delete snake;
  snake = nullptr;

  return 0;
}
