#include "menus/console.hpp"

Console::Console(Window &window, TTF_Font *font, GameState &game_state)
  : renderer_(window.getRenderer()), font_(font), window_(window), game_state_(game_state)
{
  width_ = (window.getScreenWidth() / 3) * 2;
  height_ = (window.getScreenHeight() / 3) * 2;

  console_rect_.w = width_;
  console_rect_.h = height_;
  console_rect_.x = 0;
  console_rect_.y = 0;

  console_top_bar_rect_.w = width_;
  console_top_bar_rect_.h = height_ / 30;
  console_top_bar_rect_.x = 0;
  console_top_bar_rect_.y = 0;

  command_line_rect_.w = width_;
  command_line_rect_.h = height_ / 30;
  command_line_rect_.x = 0;
  command_line_rect_.y = height_;

  command_line_border_rect_.w = width_ - 8;
  command_line_border_rect_.h = height_ / 30 - 8;
  command_line_border_rect_.x = 4;
  command_line_border_rect_.y = height_ + 4;

  input_text_rect_.h = command_line_border_rect_.h;
  input_text_rect_.w = command_line_border_rect_.w;
  input_text_rect_.x = command_line_border_rect_.x;
  input_text_rect_.y = command_line_border_rect_.y;

  console_top_bar_text_rect_.x = 0;
  console_top_bar_text_rect_.y = -2;

  block_cursor_.w = 10;
  block_cursor_.h = 20;
  block_cursor_.x = 5;
  block_cursor_.y = height_ + 6;

  input_text_texture_ = nullptr;

  SDL_Color black = {0, 0, 0, 255};

  texture_console_top_bar_text_ = createText("Console", font, black, console_top_bar_text_rect_);
}

Console::~Console()
{
  if (texture_console_top_bar_text_) 
  {
    SDL_DestroyTexture(texture_console_top_bar_text_);
  }
  if (input_text_texture_)
  {
    SDL_DestroyTexture(input_text_texture_);
  }
  // if (text_texture_command_line_) 
  // {
  //   SDL_DestroyTexture(text_texture_command_line_);
  // }
  //SDL_StopTextInput();
}

SDL_Texture *Console::createText(const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect& outRect)
{
  SDL_Surface* surface = TTF_RenderText_Blended(font, text.c_str(), color);
  if (!surface)
  {
    std::cerr << "Failed to render text surface: " << TTF_GetError() << std::endl;
    outRect.w = outRect.h = 0;
    return nullptr;
  }
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
  outRect.w = surface->w;
  outRect.h = surface->h;
  SDL_FreeSurface(surface);
  return texture;
}

void Console::handleEvent(const SDL_Event &event)
{
  //SDL_StartTextInput();
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_F3)
    {
      SDL_StopTextInput();
      game_state_ = GameState::QuitConsole;
    }
    else if (event.key.keysym.sym == SDLK_BACKSPACE && !input_text_.empty())
    {
      input_text_.pop_back(); 
    }
    else if (event.key.keysym.sym == SDLK_RETURN)
    {
      // do something here handle commands
      //input_text_.clear();
    }
  }
  else if (event.type == SDL_TEXTINPUT)
  {
    input_text_ += event.text.text;
  }

  if (input_text_texture_)
  {
    SDL_DestroyTexture(input_text_texture_);
  }

  SDL_Color white = {255, 255, 255, 255};
  if (input_text_.length() != 0)
  {
    input_text_texture_ = createText(input_text_, font_, white, input_text_rect_);
  }
  
  input_text_rect_.x = command_line_border_rect_.x + 4;
  input_text_rect_.y = command_line_border_rect_.y + 2;
}

void Console::update(float delta_time)
{

}

void Console::render()
{
  // SDL_ShowCursor(SDL_ENABLE);
  // SDL_Color black = {0, 0, 0, 255};

  // int mouse_x, mouse_y;
  // SDL_GetMouseState(&mouse_x, &mouse_y);
  // SDL_Point mouse_point = {mouse_x, mouse_y};

  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer_, &console_rect_);
  SDL_RenderDrawRect(renderer_, &console_rect_);

  SDL_SetRenderDrawColor(renderer_, 128, 128, 128, 255);
  SDL_RenderFillRect(renderer_, &console_top_bar_rect_);
  SDL_RenderDrawRect(renderer_, &console_top_bar_rect_);

  SDL_RenderFillRect(renderer_, &command_line_rect_);
  SDL_RenderDrawRect(renderer_, &command_line_rect_);

  SDL_SetRenderDrawColor(renderer_, 44, 44, 44, 255);
  SDL_RenderFillRect(renderer_, &command_line_border_rect_);
  SDL_RenderDrawRect(renderer_, &command_line_border_rect_);  

  SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
  SDL_RenderFillRect(renderer_, &block_cursor_);
  SDL_RenderDrawRect(renderer_, &block_cursor_);  

  SDL_RenderCopy(renderer_, texture_console_top_bar_text_, nullptr, &console_top_bar_text_rect_);

  if (input_text_texture_)
  {
    SDL_RenderCopy(renderer_, input_text_texture_, nullptr, &input_text_rect_);
  }
}
