#include "settings_menu.hpp"

SettingsMenu::SettingsMenu(Window &window, TTF_Font *header_font, TTF_Font *font, GameState &game_state)
: renderer_(window.getRenderer()), header_font_(header_font), font_(font), game_state_(game_state), window_(window)
{
  screen_width_ = window.getScreenWidth();
  screen_height_ = window.getScreenHeight();
  int rect_width = 800;
  int rect_height = 500;
  dropdown_open_ = false;
  selected_display_ = 0;

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

  menu_rect_.x = (screen_width_ - rect_width) / 2;
  menu_rect_.y = (screen_height_ - rect_height) / 2;
  menu_rect_.w = rect_width;
  menu_rect_.h = rect_height;

  number_of_displays_ = SDL_GetNumVideoDisplays();
  int item_height = 30;
  int dropdown_x = menu_rect_.x + 50;
  int dropdown_y = menu_rect_.y + 150;

  for (int i = 0; i < number_of_displays_; i++)
  {
    const char *display_name = SDL_GetDisplayName(i);
    DropDownMenu option;
    option.label = display_name ? display_name : "Unknown";
    option.rect = 
    {
      dropdown_x,
      dropdown_y + i * item_height,
      200,
      item_height
    };
    display_options_.push_back(option);
  }

  border_rect_.x = menu_rect_.x - 4;
  border_rect_.y = menu_rect_.y - 4;
  border_rect_.w = rect_width + 8;
  border_rect_.h = rect_height + 8;

  displays_rect_.w = rect_width / 5;
  displays_rect_.h = rect_height / 12;
  displays_rect_.x = menu_rect_.x + (menu_rect_.w - displays_rect_.w) / 2;
  displays_rect_.y = menu_rect_.y + (menu_rect_.h - displays_rect_.h) / 2;
  
  resolutions_rect_.w = rect_width / 5;
  resolutions_rect_.h = rect_height / 12;
  resolutions_rect_.x = menu_rect_.x + (menu_rect_.w - displays_rect_.w) / 2;
  resolutions_rect_.y = menu_rect_.y + (menu_rect_.h - displays_rect_.h) / 2 - 50;
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color black = {0, 0, 0, 255};

  text_texture_resolutions_ = createText("Resolution", font_, black, text_resolutions_rect_);
  text_texture_displays_ = createText("Displays", font_, black, text_displays_rect_);
}

SDL_Texture* SettingsMenu::createText(const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect& outRect)
{
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
  outRect.w = surface->w;
  outRect.h = surface->h;
  SDL_FreeSurface(surface);
  return texture;
}

void SettingsMenu::handleEvent(const SDL_Event &event)
{
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  SDL_Point mouse_point = {mouse_x, mouse_y};

  bool hovered_displays = SDL_PointInRect(&mouse_point, &displays_rect_);
  bool hovered_resolutions = SDL_PointInRect(&mouse_point, &resolutions_rect_);

  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_ESCAPE)
    {
      game_state_ = GameState::Menu;
    }
  }
  else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT)
  {
    if (hovered_displays)
    {
      dropdown_open_ = !dropdown_open_;
    }
    else if(dropdown_open_)
    {
      for (int i = 0; i < display_options_.size(); ++i) 
      {
        if (SDL_PointInRect(&mouse_point, &display_options_[i].rect)) 
        {
          selected_display_ = i;
          dropdown_open_ = false;

          SDL_SetWindowFullscreen(window_.getWindow(), 0);
          SDL_Rect display_bounds;
          if (SDL_GetDisplayBounds(selected_display_, &display_bounds) == 0)
          {
            SDL_SetWindowPosition(window_.getWindow(), display_bounds.x, display_bounds.y);
          }
          SDL_SetWindowFullscreen(window_.getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP);
          break;
        }
      }
    }
    else
    {
      dropdown_open_ = false;
    }
  }
}

void SettingsMenu::update(float delta_time)
{
  
}

void SettingsMenu::drawButton(SDL_Rect &rect, SDL_Texture *texture, SDL_Rect &textRect, bool hovered, SDL_Event &event)
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

void SettingsMenu::render()
{
  SDL_ShowCursor(SDL_ENABLE);
  SDL_Color white = {255, 255, 255, 255};
  SDL_Color black = {0, 0, 0, 255};
    
  int mouse_x, mouse_y;
  SDL_GetMouseState(&mouse_x, &mouse_y);
  SDL_Point mouse_point = {mouse_x, mouse_y};

  bool hovered_displays = SDL_PointInRect(&mouse_point, &displays_rect_);
  bool hovered_resolutions = SDL_PointInRect(&mouse_point, &resolutions_rect_);

  renderScaleTexture(renderer_, blue_background_texture_, screen_width_, screen_height_);
  renderScaleTexture(renderer_, white_clouds_texture_, screen_width_, screen_height_);
  renderScaleTexture(renderer_, water_texture_, screen_width_, screen_height_);
  renderScaleScrollingTexture(renderer_, blue_clouds_texture_, screen_width_, screen_height_, 50);
  renderScaleScrollingTexture(renderer_, grass_1_texture_, screen_width_, screen_height_, 15);
  renderScaleScrollingTexture(renderer_, grass_2_texture_, screen_width_, screen_height_, 12);
  renderScaleScrollingTexture(renderer_, grass_3_texture_, screen_width_, screen_height_, 10);

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer_, &border_rect_);
  SDL_RenderDrawRect(renderer_, &border_rect_);

  SDL_SetRenderDrawColor(renderer_, 128, 128, 128, 255);
  SDL_RenderFillRect(renderer_, &menu_rect_);
  SDL_RenderDrawRect(renderer_, &menu_rect_);

  SDL_Rect display_label_rect;

  if (dropdown_open_) 
  {
    for (int i = 0; i < display_options_.size(); ++i) 
    {
      bool hovered = SDL_PointInRect(&mouse_point, &display_options_[i].rect);
      SDL_SetRenderDrawColor(renderer_, hovered ? 150 : 100, 100, 100, 255);
      SDL_RenderFillRect(renderer_, &display_options_[i].rect);

      SDL_Texture* opt_texture = createText(display_options_[i].label, font_, white, display_label_rect);
      display_label_rect.x = display_options_[i].rect.x + 5;
      display_label_rect.y = display_options_[i].rect.y + 5;
      SDL_RenderCopy(renderer_, opt_texture, nullptr, &display_label_rect);
      SDL_DestroyTexture(opt_texture);
    }
  }

  SDL_Texture *text_texture_header = createText("Settings", header_font_, white, text_header_rect_);
  text_header_rect_.x = menu_rect_.x + (menu_rect_.w - text_header_rect_.w) / 2;
  text_header_rect_.y = menu_rect_.y + 40;
  SDL_RenderCopy(renderer_, text_texture_header, nullptr, &text_header_rect_);
  SDL_DestroyTexture(text_texture_header);

  text_displays_rect_.x = displays_rect_.x + (displays_rect_.w - text_displays_rect_.w) / 2;
  text_displays_rect_.y = displays_rect_.y + (displays_rect_.h - text_displays_rect_.h) / 2;
  drawButton(displays_rect_, text_texture_displays_, text_displays_rect_, hovered_displays, event);

  text_resolutions_rect_.x = resolutions_rect_.x + (resolutions_rect_.w - text_resolutions_rect_.w) / 2;
  text_resolutions_rect_.y = resolutions_rect_.y + (resolutions_rect_.h - text_resolutions_rect_.h) / 2;
  drawButton(resolutions_rect_, text_texture_resolutions_, text_resolutions_rect_, hovered_resolutions, event);
}
