#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <unistd.h>
//#include <graphics.h>


 int i;
 int j;
 int height = 30;
 int width = 30;
 int gameover;
 int score;
 int x;
 int y;
 int fruitx;
 int fruity;
 int flag;


void setup() {
   gameover = 0;
   x = height/2;
   y = width/2;
   label1:
      fruitx=rand()%20;
      if (fruitx == 0)
         goto label1;
   label2:
      fruity=rand()%20;
      if(fruity==0)
         goto label2;
   score = 0;      
}

void draw() {
   
   system("clear");
    for (i = 0; i < height; i++) {
      for (j = 0; j <width; j++) {
         if (i == 0 || i == width - 1) {
            printf("-");
         } else if (j == 0 || j == height - 1) {
            printf("|");
         } else {
           if(i == x && j == y) {
            printf("o");
         } else if (i == fruitx && j == fruity) {
            printf("*");
         } else {
            printf(" ");
         } 
         } 
         }printf("\n"); 
      }
      printf("Press X to quit the game.\n");
   }

void input() {
   int move;
   
   initscr();
   clear();
   noecho();
   cbreak();
   
   move = getch();

      switch (move) {
      case 'a': 
         flag = 1;
         break;
      case 's':
         flag = 2;
         break;
     case 'd':
         flag = 3;
          break;
      case 'w':
          flag = 4;
         break;
      case 'x':
          gameover = 1;
          break;
       }

       endwin();
    }

void logic() {
   sleep(0.01);
   switch (flag) {
   case 1:
      y--;
      break;
   case 2:
      x++;
      break;
   case 3:
      y++;
      break;
   case 4:
      x--;
      break;
   default:
      break;
   }

   if (x < 0 || x > height || y < 0 || y > width) {
      gameover = 1;
   }

   if (x == fruitx && y == fruity) {
      label3:
         fruitx = rand() % 20;
         if (fruitx == 0)
            goto label3;

      label4:
         fruity = rand() % 20;
         if(fruity == 0)
            goto label4;
         score += 10;
   }
}



int main() {


setup();

while (!gameover) {
   draw();
   input();
   logic();
   
   

if (gameover != 0) {
          system("clear");
   printf("   GAME OVER.");
   printf("\nYour score is %d.", score);
      }
}

}