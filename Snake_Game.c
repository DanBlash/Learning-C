#include <stdlib.h>
#include <ncurses.h>
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
      //system("clear");
   printf("        GAME OVER.\n      Your score is %d.", score);
   printf("\nPress ENTER to quit the game.");
   }

 void input() {
   initscr();
   if (getch()) {
      switch (getch()) {
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
    }
  }

int main() {

setup();
draw();
//input();

}