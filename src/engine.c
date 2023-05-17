#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../include/point.h"
#include "../include/spring.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define DT 1

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius){
   const int32_t diameter = (radius * 2);
   int32_t x = (radius - 1);
   int32_t y = 0;
   int32_t tx = 1;
   int32_t ty = 1;
   int32_t error = (tx - diameter);
   while (x >= y){
      //  Each of the following renders an octant of the circle
      SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
      SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
      SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);
      if (error <= 0){
        ++y;
        error += ty;
        ty += 2;
      }
      if (error > 0){
        --x;
        tx += 2;
        error += (tx - diameter);
      }
   }
}


int start_SDL(SDL_Window** window,SDL_Renderer** renderer,int width,int height, const char* title){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
    *window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
    if (*window == NULL) return 1;
    *renderer = SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) return 1;
    return 0;
}

int main(void){
    SDL_Window* window;
    SDL_Renderer* renderer;
    int status = start_SDL(&window,&renderer,SCREEN_WIDTH,SCREEN_HEIGHT,"test");
    if (status == 1) return EXIT_FAILURE;
    point* points = create_points(SCREEN_WIDTH,SCREEN_HEIGHT);
    spring* springs = create_springs(points);
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    int count = 0;
    vect2 force = {.x = 3.0 , .y = 9.81};
    while (count < 100) {
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        for (int i = 0;i < NB_POINTS;i++){
            update_point(&points[i],DT,0.01,force);
            int x = points[i].pos.x;
            int y = points[i].pos.y;
            DrawCircle(renderer,x,y,10);
            //print_point(points[i]);
        }
        for (int i = 0; i < NB_SPRINGS;i++){
          int p1_x = springs[i].p1->pos.x;
          int p1_y = springs[i].p1->pos.y;
          int p2_x = springs[i].p2->pos.x;
          int p2_y = springs[i].p2->pos.y;
          SDL_RenderDrawLine(renderer,p1_x,p1_y,p2_x,p2_y);
        }
        count++;
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }

    free(points);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}

//gcc particle.c -o particle -Wall -Wvla -Wextra -fsanitize=address $(sdl2-config --cflags) -lSDL2 -lm