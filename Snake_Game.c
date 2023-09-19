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
 int snake_start_position_x;
 int snake_start_position_y;
 int fruitx;
 int fruity;
 int direction;
 // For window generation with ncurses **
 int start_y = 0; 
 int start_x = 0;
 WINDOW *win;
 // ** 

 typedef struct Snake {
   unsigned int snake_y;
   unsigned int snake_x;
   unsigned int prev_snake_y;
   unsigned int prev_snake_x;   
   struct Snake* next;
   struct Snake* prev;
 } Snake;

 Snake* head = NULL;
 Snake* body = NULL;
 Snake* tail = NULL;

void createSnake() {
   head = malloc(sizeof(*head));
   head->snake_y = snake_start_position_y;
   head->snake_x = snake_start_position_x;
   head->prev_snake_y = snake_start_position_y;
   head->prev_snake_x = snake_start_position_x;
      
   tail = malloc(sizeof(*tail));
   tail->snake_y = head->prev_snake_y;
   tail->snake_x = head->prev_snake_x;
   tail->prev_snake_y = 0;
   tail->prev_snake_x = 0;

   head->next = tail;
   head->prev = NULL;
   tail->next = NULL;
   tail->prev = head;
}

void growSnake() {
   struct Snake* newNode = (struct Snake*)malloc(sizeof(struct Snake));
   tail->next = newNode;
   newNode->prev = tail;
   newNode->prev_snake_y = tail->snake_y;
   newNode->prev_snake_x = tail->snake_x;
   tail = newNode;
   tail->snake_x = tail->prev_snake_x;
   tail->snake_y = tail->prev_snake_y;
   }

void setup() {
   gameover = 0;
   snake_start_position_x = width / 2;
   snake_start_position_y = height / 2;
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
   wrefresh(win);

   for (struct Snake* i = head; i != NULL; i = i->next) {
       mvwprintw(win, i->snake_y, i->snake_x, "o");
       wrefresh(win);
   }
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
         break;
      }
   
}

void logic() {
   sleep(0.01);
   switch (direction) {
   case 1:
      for (struct Snake* i = tail; i != NULL; i = i->prev) {
         if (i == head) {
            head->snake_x--;
         }
         
         i->prev_snake_x = i->snake_x;
         i->prev_snake_y = i->snake_y;
         
         if (i->prev != NULL) {
         i->snake_x = (i->prev)->prev_snake_x;
         i->snake_y = (i->prev)->prev_snake_y;
         }
      }
      break;
   case 2:
      for (struct Snake* i = tail; i != NULL; i = i->prev) {
         if (i == head) {
           head->snake_y++; 
         }
         
         i->prev_snake_x = i->snake_x;
         i->prev_snake_y = i->snake_y;
         
         if (i->prev != NULL) {
         i->snake_x = (i->prev)->prev_snake_x;
         i->snake_y = (i->prev)->prev_snake_y;
         }
      }
      break;
   case 3:
      for (struct Snake* i = tail; i != NULL; i = i->prev) {
         if (i == head) {
            head->snake_x++;
         }
         
         i->prev_snake_x = i->snake_x;
         i->prev_snake_y = i->snake_y;
         
         if (i->prev != NULL) {
         i->snake_x = (i->prev)->prev_snake_x;
         i->snake_y = (i->prev)->prev_snake_y;
         }
      }
      break;
   case 4:
      for (struct Snake* i = tail; i != NULL; i = i->prev) {
         if (i == head) {
            head->snake_y--;
         }
         
         i->prev_snake_x = i->snake_x;
         i->prev_snake_y = i->snake_y;
         
         if (i->prev != NULL) {
         i->snake_x = (i->prev)->prev_snake_x;
         i->snake_y = (i->prev)->prev_snake_y;
         }
      }
      break;
   default:
      break;
   }

   if (head->snake_x < 0 || head->snake_x > width - 1 || head->snake_y < 0 || head->snake_y > height - 1) {
      gameover = 1;
   }

   if (head->snake_x == fruitx && head->snake_y == fruity) {
      growSnake();
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
   curs_set(0);
   mvaddstr(10, 30, "Press ENTER to start");
   noecho();
   cbreak();
   getch();
   refresh();
   createSnake(); 
   
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