#include <curses.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
  int x;
  int y;
} Co_ord;

Co_ord food;
Co_ord snake;
Co_ord dir;

// Generate the Food randomly
void genFood() {
  food.x = rand() % 20;
  food.y = rand() % 20;
}

// Check if the food is eaten
void checkFood(Co_ord snake) {
  if (food.x == snake.x && food.y == snake.y) {
    genFood();
  }
}

// Check for the keypress and change the Movement
void keyPress(int pressed, Co_ord *dir) {
  if (pressed == KEY_LEFT) {
    dir->x = 0;
    dir->y = -1;
  } else if (pressed == KEY_RIGHT) {
    dir->x = 0;
    dir->y = 1;
  } else if (pressed == KEY_DOWN) {
    dir->x = 1;
    dir->y = 0;
  } else if (pressed == KEY_UP) {
    dir->x = -1;
    dir->y = 0;
  }
}

int main() {
  WINDOW *win = initscr();
  keypad(win, true);
  nodelay(win, true);
  snake.x = 0;
  snake.y = 0;
  dir.x = 1;
  dir.y = 0;
  genFood();
  while (1) {
    int pressed = wgetch(win);
    keyPress(pressed, &dir);
    
    snake.x += dir.x;
    snake.y += dir.y;
    erase();
    mvaddstr(snake.x, snake.y, "*");
    mvaddstr(food.x, food.y, "&");
    checkFood(snake);
    usleep(100000);
  }
  endwin();
  return 0;
}
