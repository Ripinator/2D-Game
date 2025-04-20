#include "utils.hpp"

void renderScaleTexture(SDL_Renderer* renderer, SDL_Texture* texture, int screen_width, int screen_height)
{
  int texture_width = 0, texture_height = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);

  if (texture_width <= 0 || texture_height <= 0) return;

  float scale_x = static_cast<float>(screen_width) / texture_width;
  float scale_y = static_cast<float>(screen_height) / texture_height;

  SDL_Rect src = { 0, 0, texture_width, texture_height };
  SDL_Rect dst = 
  {
    0, 0,
    static_cast<int>(texture_width * scale_x),
    static_cast<int>(texture_height * scale_y)
  };

  SDL_RenderCopy(renderer, texture, &src, &dst);
}

void renderScaleScrollingTexture(SDL_Renderer* renderer, SDL_Texture* texture, int screen_width, 
                                 int screen_height, int scroll_speed)
{
  int texture_width = 0, texture_height = 0;
  SDL_QueryTexture(texture, nullptr, nullptr, &texture_width, &texture_height);

  if (texture_width <= 0 || texture_height <= 0) return;

  float scale_x = static_cast<float>(screen_width) / texture_width;
  float scale_y = static_cast<float>(screen_height) / texture_height;

  int offset = (SDL_GetTicks() / scroll_speed) % texture_width;
  int num_tiles = (screen_width / texture_width) + 2;

  for (int i = 0; i < num_tiles; ++i)
  {
    int draw_x = (i * texture_width - offset);
    SDL_Rect src = { 0, 0, texture_width, texture_height };
    SDL_Rect dst = 
    {
      static_cast<int>(draw_x * scale_x), 0,
      static_cast<int>(texture_width * scale_x),
      static_cast<int>(texture_height * scale_y)
    };
    SDL_RenderCopy(renderer, texture, &src, &dst);
  }
}