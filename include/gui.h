#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL_render.h>

SDL_Renderer*
gui_init(const char* app_name);

void
gui_loop();

#endif // !GUI_H
