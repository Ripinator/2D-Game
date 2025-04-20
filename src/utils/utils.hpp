#ifndef UTILS_HPP
#define UTILS_HPP

#include <SDL2/SDL.h>

void renderScaleTexture(SDL_Renderer* renderer, SDL_Texture* texture, int screen_width, int screen_height);
void renderScaleScrollingTexture(SDL_Renderer* renderer, SDL_Texture* texture, int screen_width, 
                            int screen_height, int scroll_speed);



#endif