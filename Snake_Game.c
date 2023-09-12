#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
//#include <graphics.h>

// *Followed tutorial from : https://www.geeksforgeeks.org/snake-game-in-c/

 int height = 24;
 int width = 80;
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
   

void setup() {
   gameover = 0;
   snake_x = height/2;
   snake_y = width/2;
   if (fruitx == 0) {
      fruitx=rand() % 20;
   }
   if (fruity==0) {
      fruity=rand() % 20;
   }

   score = 0;      
}

void draw() {
   
   clear();
   
   WINDOW * win = newwin(height, width, start_y, start_x);
   refresh();

   box(win, 0, 0);
   mvwprintw(win, fruity, fruitx, "*");
   wrefresh(win);
   mvwprintw(win, snake_y, snake_x, "o");
   wrefresh(win);

   //Bug on printing box that caused cursor to print after line finished even with new line print***

   //system("clear");
   //  for (int i = 0; i < height; i++) {
   //    for (int j = 0; j <width; j++) {
   //       if (i == 0 || i == width - 1) {
   //          printf("-");
   //       } else if (j == 0 || j == height - 1) {
   //          printf("|");
   //       } else {
   //          if (i == x && j == y) {
   //             printf("o");
   //          } else if (i == fruitx && j == fruity) {
   //             printf("*");
   //          } else {
   //          printf(" ");
   //          } 
   //       } 
   //       }
   //       printf("\n");
   //       fflush(stdout);
   //    }
   //    printf("Press X to quit the game.\n");
    }

int input_delay() {
   int kbhit;

   kbhit = getch();
   timeout(1000);

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
      //y--;
      snake_y--;
      break;
   case 2:
      //x++;
      snake_x++;
      break;
   case 3:
      //y++;
      snake_y++;
      break;
   case 4:
      //x--;
      snake_x--;
      break;
   default:
      break;
   }

   if (snake_x < 0 || snake_x > height || snake_y < 0 || snake_y > width) {
      gameover = 1;
   }

//    if (x == fruitx && y == fruity) {
//       label3:
//          fruitx = rand() % 20;
//          if (fruitx == 0)
//             goto label3;

//       label4:
//          fruity = rand() % 20;
//          if(fruity == 0)
//             goto label4;
//          score += 10;
//    }
 }

 void end_game_msg() {
   move(10, 30);
   printw("   GAME OVER.\n");
   move(11, 30);
   printw("Your score is %d.\n\n", score);
   refresh();
   sleep(30);

 }

int main() {
  
   //printf("Press ENTER to start");
   setup();
   initscr();
   mvaddstr(10, 30, "Press ENTER to start");
   noecho();
   cbreak();
   getch();
   refresh(); 
   
   while (!gameover) {
      draw();
      //input_delay();
      input(input_delay());
      logic();
      
      
      
      if (gameover != 0) {
         refresh();
         end_game_msg();
         endwin();
         delwin(stdscr); 
         
         
         //system("clear"); 
        
         //printf("   GAME OVER.");
         //printf("\nYour score is %d.\n\n", score);
      }
   }
}