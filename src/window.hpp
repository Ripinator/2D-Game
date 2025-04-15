#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <cstdio> 
#include <string>

class Window
{
  private:
    int screen_width_;
    int screen_height_;
    SDL_Window *window_;
    SDL_Renderer *renderer_;

  public:
    Window();
    Window(const Window&) = delete;
    ~Window();

    bool init(const std::string &title, int screen_width, int screen_height);
    void close();
    SDL_Window *getWindow() const;
    SDL_Renderer *getRenderer() const;
    int getScreenWidth() const;
    int getScreenHeight() const;
};

#endif
