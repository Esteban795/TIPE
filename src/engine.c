#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../include/point.h"
#include "../include/spring.h"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define DT 0.016



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


int events_handling(point** points){
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        switch (e.type) {
          case SDL_QUIT:
              return 1;
          
          case SDL_KEYDOWN: {
              if (e.key.keysym.sym == SDLK_ESCAPE) return 1;
              if (e.key.keysym.sym == SDLK_LEFT) {
                for (int i = 0; i < NB_POINTS;i++){
                  if (!points[i]->is_fixed) points[i]->pos.x -= 50; 
                                
                }
              }
              if (e.key.keysym.sym == SDLK_RIGHT) {
                for (int i = 0; i < NB_POINTS;i++){
                  if (!points[i]->is_fixed) points[i]->pos.x += 50;    
                  
                }
              }
              
            }
          default:
              break;
        } 
    }
  return 0;
}

int euler_step(SDL_Renderer* renderer,point** points,spring** springs,double dt){
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    clear_forces(points);
    int res = events_handling(points);
    for (int i = 0; i < NB_SPRINGS;i++){
        update_spring(springs[i]);
        int p1_x = springs[i]->p1->pos.x;
        int p1_y = springs[i]->p1->pos.y;
        int p2_x = springs[i]->p2->pos.x;
        int p2_y = springs[i]->p2->pos.y;
        SDL_RenderDrawLine(renderer,p1_x,p1_y,p2_x,p2_y);
    }
    update_positions(points,dt);
    update_velocities(points,dt);
    for (int i = 0; i < NB_POINTS;i++){
        int x = points[i]->pos.x;
        int y = points[i]->pos.y;
        DrawCircle(renderer,x,y,10);
    }
    SDL_RenderPresent(renderer);
    return res;
}

int main(void){
    SDL_Window* window;
    SDL_Renderer* renderer;
    int status = start_SDL(&window,&renderer,SCREEN_WIDTH,SCREEN_HEIGHT,"test");
    if (status == 1) return EXIT_FAILURE;
    point** points = create_points(SCREEN_WIDTH,SCREEN_HEIGHT);
    spring** springs = create_springs(points);
    
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    
    while (true) {
      int res = events_handling(points);
      if (res == 1) break;
      if (euler_step(renderer,points,springs,DT) == -1) break;
      SDL_Delay(16);
    }
    for (int i = 0; i < NB_POINTS; i++){
      free(points[i]);
    }
    free(points);

    for (int i = 0; i < NB_SPRINGS; i++){
      free(springs[i]);
    }
    free(springs);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}

//gcc particle.c -o particle -Wall -Wvla -Wextra -fsanitize=address $(sdl2-config --cflags) -lSDL2 -lm