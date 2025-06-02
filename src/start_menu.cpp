#include "start_menu.hpp"
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "window.hpp"
#include "utils/utils.hpp"
// iam so sorry this file is filled with horrible code

StartMenu::StartMenu(Window &window, TTF_Font *header_font, TTF_Font *font, GameState &game_state) 
: renderer_(window.getRenderer()), header_font_(header_font), font_(font), game_state_(game_state)
{
  screen_width_ = window.getScreenWidth();
  screen_height_ = window.getScreenHeight();
  SDL_Surface *blue_background_surface_ = IMG_Load("assets/starting_menu_background/1.png");
  SDL_Surface *white_clouds_surface_ = IMG_Load("assets/starting_menu_background/2.png");
  SDL_Surface *blue_clouds_surface_ = IMG_Load("assets/starting_menu_background/3.png");
  SDL_Surface *water_surface_ = IMG_Load("assets/starting_menu_background/4.png");
  SDL_Surface *grass_1_surface_ = IMG_Load("assets/starting_menu_background/5.png");
  SDL_Surface *grass_2_surface_ = IMG_Load("assets/starting_menu_background/6.png");
  SDL_Surface *grass_3_surface_ = IMG_Load("assets/starting_menu_background/7.png");

  blue_background_texture_ = SDL_CreateTextureFromSurface(renderer_, blue_background_surface_);
  white_clouds_texture_ = SDL_CreateTextureFromSurface(renderer_, white_clouds_surface_);
  blue_clouds_texture_ = SDL_CreateTextureFromSurface(renderer_, blue_clouds_surface_);
  water_texture_ = SDL_CreateTextureFromSurface(renderer_, water_surface_);
  grass_1_texture_ = SDL_CreateTextureFromSurface(renderer_, grass_1_surface_);
  grass_2_texture_ = SDL_CreateTextureFromSurface(renderer_, grass_2_surface_);
  grass_3_texture_ = SDL_CreateTextureFromSurface(renderer_, grass_3_surface_);

  SDL_FreeSurface(blue_background_surface_);
  SDL_FreeSurface(white_clouds_surface_);
  SDL_FreeSurface(blue_clouds_surface_);
  SDL_FreeSurface(water_surface_);
  SDL_FreeSurface(grass_1_surface_);
  SDL_FreeSurface(grass_2_surface_);
  SDL_FreeSurface(grass_3_surface_);

  SDL_Color white = {255, 255, 255, 255};
  SDL_Color black = {0, 0, 0, 255};

  int rect_width = 800;
  int rect_height = 500;

  menu_rect_.x = (screen_width_ - rect_width) / 2;
  menu_rect_.y = (screen_height_ - rect_height) / 2;
  menu_rect_.w = rect_width;
  menu_rect_.h = rect_height;

  border_rect_.x = menu_rect_.x - 4;
  border_rect_.y = menu_rect_.y - 4;
  border_rect_.w = rect_width + 8;
  border_rect_.h = rect_height + 8;

  start_rect_.w = rect_width / 5;
  start_rect_.h = rect_height / 12;
  start_rect_.x = menu_rect_.x + (menu_rect_.w - start_rect_.w) / 2;
  start_rect_.y = menu_rect_.y + (menu_rect_.h - start_rect_.h) / 2 - 50;
  
  quit_rect_.w = rect_width / 5;
  quit_rect_.h = rect_height / 12;
  quit_rect_.x = menu_rect_.x + (menu_rect_.w - quit_rect_.w) / 2;
  quit_rect_.y = menu_rect_.y + (menu_rect_.h - quit_rect_.h) / 2 + 50;

  settings_menu_rect_.w = rect_width / 5;
  settings_menu_rect_.h = rect_height / 12;
  settings_menu_rect_.x = menu_rect_.x + (menu_rect_.w - quit_rect_.w) / 2;
  settings_menu_rect_.y = menu_rect_.y + (menu_rect_.h - quit_rect_.h) / 2;

  text_texture_header_ = createText("Sworld Lord", header_font_, white, text_header_rect_);
  text_texture_start_ = createText("Start", font_, black, text_start_rect_);
  text_texture_quit_ = createText("Quit", font_, black, text_quit_rect_);
  text_texture_settings_ = createText("Settings", font_, black, text_settings_rect_);
}

StartMenu::~StartMenu()
{
  SDL_DestroyTexture(blue_background_texture_);
  SDL_DestroyTexture(white_clouds_texture_);
  SDL_DestroyTexture(blue_clouds_texture_);
  SDL_DestroyTexture(water_texture_);
  SDL_DestroyTexture(grass_1_texture_);
  SDL_DestroyTexture(grass_2_texture_);
  SDL_DestroyTexture(grass_3_texture_);

  SDL_DestroyTexture(text_texture_header_);
  SDL_DestroyTexture(text_texture_start_);
  SDL_DestroyTexture(text_texture_quit_);
  SDL_DestroyTexture(text_texture_settings_);
}

void StartMenu::setType(GameState game_state)
{
  game_state_ = game_state;
}

void StartMenu::handleEvent(const SDL_Event &event) 
{
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  SDL_Point mouse_point = {mouse_x, mouse_y};

  bool hovered_start = SDL_PointInRect(&mouse_point, &start_rect_);
  bool hovered_quit = SDL_PointInRect(&mouse_point, &quit_rect_);
  bool hovered_settings = SDL_PointInRect(&mouse_point, &settings_menu_rect_);

  if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
  {
    if (hovered_start)
    {
      setType(GameState::Play);
    }
    else if (hovered_quit)
    {
      setType(GameState::Quit);
    }
    else if (hovered_settings)
    {
      setType(GameState::Settings);
    }
  }
  else if (event.key.keysym.sym == SDLK_F2)
  {
    setType(GameState::Console);
  }
}

void StartMenu::update(float delta_time) 
{
  
}

void StartMenu::drawButton(SDL_Rect &rect, SDL_Texture *texture, SDL_Rect &textRect, bool hovered, SDL_Event &event)
{
  if (hovered)
  {
    SDL_SetRenderDrawColor(renderer_, 200, 200, 200, 255);
  }
  else
  {
    SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  }

  SDL_RenderFillRect(renderer_, &rect);
  SDL_RenderDrawRect(renderer_, &rect);
  SDL_RenderCopy(renderer_, texture, nullptr, &textRect);
}

SDL_Texture *StartMenu::createText(const std::string &text, TTF_Font *font, SDL_Color color, SDL_Rect &outRect)
{
  SDL_Surface *surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer_, surface);
  outRect.w = surface->w;
  outRect.h = surface->h;
  SDL_FreeSurface(surface);
  return texture;
}

void StartMenu::render() 
{
  SDL_ShowCursor(SDL_ENABLE); 
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  SDL_Point mouse_point = {mouse_x, mouse_y};

  bool hovered_quit = SDL_PointInRect(&mouse_point, &quit_rect_);
  bool hovered_start = SDL_PointInRect(&mouse_point, &start_rect_);
  bool hovered_settings = SDL_PointInRect(&mouse_point, &settings_menu_rect_);

  renderScaleTexture(renderer_, blue_background_texture_, screen_width_, screen_height_);
  renderScaleTexture(renderer_, white_clouds_texture_, screen_width_, screen_height_);
  renderScaleTexture(renderer_, water_texture_, screen_width_, screen_height_);
  renderScaleScrollingTexture(renderer_, blue_clouds_texture_, screen_width_, screen_height_, 50);
  renderScaleScrollingTexture(renderer_, grass_1_texture_, screen_width_, screen_height_, 15);
  renderScaleScrollingTexture(renderer_, grass_2_texture_, screen_width_, screen_height_, 12);
  renderScaleScrollingTexture(renderer_, grass_3_texture_, screen_width_, screen_height_, 10);

  SDL_SetRenderDrawColor(renderer_, 255, 165, 0, 255);
  SDL_RenderFillRect(renderer_, &border_rect_);
  SDL_RenderDrawRect(renderer_, &border_rect_);

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer_, &menu_rect_);
  SDL_RenderDrawRect(renderer_, &menu_rect_);

  text_header_rect_.x = menu_rect_.x + (menu_rect_.w - text_header_rect_.w) / 2;
  text_header_rect_.y = menu_rect_.y + 40;
  SDL_RenderCopy(renderer_, text_texture_header_, nullptr, &text_header_rect_);

  text_start_rect_.x = start_rect_.x + (start_rect_.w - text_start_rect_.w) / 2;
  text_start_rect_.y = start_rect_.y + (start_rect_.h - text_start_rect_.h) / 2;
  drawButton(start_rect_, text_texture_start_, text_start_rect_, hovered_start, event);

  text_quit_rect_.x = quit_rect_.x + (quit_rect_.w - text_quit_rect_.w) / 2;
  text_quit_rect_.y = quit_rect_.y + (quit_rect_.h - text_quit_rect_.h) / 2;
  drawButton(quit_rect_, text_texture_quit_, text_quit_rect_, hovered_quit, event);

  text_settings_rect_.x = settings_menu_rect_.x + (settings_menu_rect_.w - text_settings_rect_.w) / 2;
  text_settings_rect_.y = settings_menu_rect_.y + (settings_menu_rect_.h - text_settings_rect_.h) / 2;
  drawButton(settings_menu_rect_, text_texture_settings_, text_settings_rect_, hovered_settings, event);
}
