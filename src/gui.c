#include "../include/gui.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>

SDL_Renderer*
gui_init(const char* app_name)
{
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not be initialized! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  SDL_Window* window = NULL;
  SDL_Renderer* renderer = NULL;

  window = SDL_CreateWindow(app_name,
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            1000,
                            700,
                            SDL_WINDOW_SHOWN);
  if (window == NULL) {
    printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (renderer == NULL) {
    fprintf(
      stderr, "Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
    exit(1);
  }

  return renderer;
}

void
gui_loop()
{
  // TODO: add quit key shortcut as it hangs now while quiting
  SDL_Event e;
  int quit = 0;
  while (!quit) {
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT)
        quit = 1;
    }
    SDL_Delay(10);
  }
}
