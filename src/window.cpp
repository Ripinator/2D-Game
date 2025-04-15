#include "window.hpp"
#include <iostream>

Window::Window()
    : screen_width_(0), screen_height_(0), window_(nullptr), screen_surface_(nullptr) {}

Window::~Window() 
{
  close();
}

void Window::close()
{
  if (window_) 
  {
    SDL_DestroyWindow(window_);
    window_ = nullptr;
    screen_surface_ = nullptr;
  }
}

SDL_Window *Window::getWindow() const
{
  return window_;
}

bool Window::init(const std::string &title, int width, int height)
{
  screen_width_ = width;
  screen_height_ = height;

  window_ = SDL_CreateWindow(title.c_str(),
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              screen_width_, screen_height_,
                              SDL_WINDOW_SHOWN);

  if (!window_) 
  {
    std::cerr << "Window creation failed! SDL_Error: " << SDL_GetError() << std::endl;
    return false;
  }

  screen_surface_ = SDL_GetWindowSurface(window_);
  return true;
}
