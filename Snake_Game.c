#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
//#include <graphics.h>

// *Followed tutorial from : https://www.geeksforgeeks.org/snake-game-in-c/

 int height = 24;
 int width = 78;
 int gameover;
 int score;
 int snake_x;
 int snake_y;
 int fruitx;
 int fruity;
 int direction;
 int start_y = 0;
 int start_x = 0;
 int startgame;
 WINDOW *win;  

void setup() {
   gameover = 0;
   snake_x = width / 2;
   snake_y = height / 2;
   if (fruitx == 0) {
      fruitx=rand() % 78;
   }
   if (fruity==0) {
      fruity=rand() % 24;
   }

   score = 0;      
}

void draw() {
   
   clear();
   
   win = newwin(height, width, start_y, start_x);
   refresh();

   box(win, 0, 0);
   mvwprintw(win, 23, 29, "Press X to Quit Game");
   refresh();
   mvwprintw(win, fruity, fruitx, "*");
   refresh();
   mvwprintw(win, snake_y, snake_x, "o");
   wrefresh(win);
   

    }

int input_delay() {
   int kbhit;

   kbhit = getch();
   timeout(500);

   return kbhit;
}

void input(int kbhit) {
   
      switch (kbhit) {
      case 'a': 
         direction = 1;
         break;
      case 's':
         direction = 2;
         break;
     case 'd':
         direction = 3;
         break;
      case 'w':
         direction = 4;
         break;
      case 'x':
         gameover = 1;
         break;
      default:
         startgame = 1;
         break;
      }
   
}

void logic() {
   sleep(0.01);
   switch (direction) {
   case 1:
      snake_x--;
      break;
   case 2:
      snake_y++;
      break;
   case 3:
      snake_x++;
      break;
   case 4:
      snake_y--;
      break;
   default:
      break;
   }

   if (snake_x < 0 || snake_x > width || snake_y < 0 || snake_y > height) {
      gameover = 1;
   }

   if (snake_x == fruitx && snake_y == fruity) {
      label1:
         fruitx = rand() % 78;
         if (fruitx == 0)
            goto label1;

      label2:
         fruity = rand() % 24;
         if(fruity == 0)
            goto label2;
         score += 10;
   }
 }

 void end_game_msg() {
   clear();
   move(10, 30);
   printw("   GAME OVER.\n");
   move(11, 30);
   printw("Your score is %d.\n\n", score);
   refresh();
   sleep(30);

 }

int main() {
  
   setup();
   initscr();
   mvaddstr(10, 30, "Press ENTER to start");
   noecho();
   cbreak();
   getch();
   refresh(); 
   
   while (!gameover) {
      draw();
      input(input_delay());
      logic();
      
      
      
      if (gameover != 0) {
         refresh();
         end_game_msg();
         delwin(win);
         endwin();
          
      
      }
   }
}