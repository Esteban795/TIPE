#include <SDL2/SDL.h>
#include <stdbool.h>
#include "../include/point.h"
#include "../include/spring.h"
#include "../include/data.h"


#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define DT 0.006


bool MOVED = false;


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


void draw_spring(SDL_Renderer* renderer,spring* s){
      int p1_x = s->p1->pos.x;
      int p1_y = s->p1->pos.y;
      int p2_x = s->p2->pos.x;
      int p2_y = s->p2->pos.y;
      SDL_RenderDrawLine(renderer,p1_x,p1_y,p2_x,p2_y);
}


void verlet_step(SDL_Renderer* renderer,point** points,spring** springs,double dt){

    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);
    
    clear_forces(points);
    for (int i = 0; i < NB_SPRINGS;i++){
        update_spring(springs[i]);
        draw_spring(renderer,springs[i]);
    }

    update_positions(points,dt);
    update_velocities(points,dt);

    for (int i = 0; i < NB_POINTS;i++){
        int x = points[i]->pos.x;
        int y = points[i]->pos.y;
        DrawCircle(renderer,x,y,10);
    }
    SDL_RenderPresent(renderer);
}


int events_handling(point** points,int* count){
    SDL_Event e;
    while (SDL_PollEvent(&e)){
        switch (e.type) {
          case SDL_QUIT:
              return 1;
          case SDL_KEYDOWN: {
              if (e.key.keysym.sym == SDLK_ESCAPE) return 1;
              if (e.key.keysym.sym == SDLK_LEFT) {
                *count = -25;
                MOVED = true;
                if (*count > 0) break;
                for (int i = 0; i < NB_POINTS - 1;i++){
                  if (!points[i]->is_fixed) points[i]->pos.x -= 1; 
                                
                }
              }
              if (e.key.keysym.sym == SDLK_RIGHT) {
                *count = -25;
                MOVED = true;
                if (*count > 0) break;
                for (int i = 0; i < NB_POINTS - 1;i++){
                  if (!points[i]->is_fixed) points[i]->pos.x += 1;    
                }
              }
              if (e.key.keysym.sym == SDLK_r){
                MOVED = false;
                return -1;
              }
              
            }
          default:
              break;
        } 
    }
  return 0;
}


int start_SDL(SDL_Window** window,SDL_Renderer** renderer,int width,int height, const char* title){
    if (SDL_Init(SDL_INIT_VIDEO) != 0) return 1;
    *window = SDL_CreateWindow(title,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN);
    if (*window == NULL) return 1;
    *renderer = SDL_CreateRenderer(*window,-1,SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) return 1;
    return 0;
}

int main(int argc,char* argv[]){
  if (argc != 2) return EXIT_FAILURE;

    int nb_samples = atoi(argv[1]);
    int* data_sol = malloc(sizeof(float) * nb_samples);
    int* data_top = malloc(sizeof(float) * nb_samples);
    int index = 0; //index in `data` arr
    int nb_dt = 0;
    int count = 0; //used to keep track of how many impulse we already set.
    point** points = create_points(SCREEN_WIDTH,SCREEN_HEIGHT);
    spring** springs = create_springs(points);


    SDL_Window* window;
    SDL_Renderer* renderer;
    int status = start_SDL(&window,&renderer,SCREEN_WIDTH,SCREEN_HEIGHT,"Tuned Mass Damper simulation, by Esteban795.");
    if (status == 1) return EXIT_FAILURE;
    SDL_SetRenderDrawColor(renderer,255,255,255,255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer,0,0,0,255);


     
    while (true) {
        int res = events_handling(points,&count);
        if (res == 1) break; // exits program
        else if (res == -1) {
            delete_points(points);
            delete_springs(springs);
            points = create_points(SCREEN_WIDTH,SCREEN_HEIGHT);
            springs = create_springs(points);
        }    
        verlet_step(renderer,points,springs,DT);
        count++;
        if (write_to_arr(data_sol,data_top,nb_samples,MOVED,&index,nb_dt,points) == 1) break;
        SDL_Delay(6);
    }

    save_to_file("./data/data.txt",data_sol,data_top,nb_samples,SOFT_STIFFNESS,SOFT_DAMPING,BUILDING_HHEIGHT);
    
    free(data_sol);
    free(data_top);
    delete_points(points);
    delete_springs(springs);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}
