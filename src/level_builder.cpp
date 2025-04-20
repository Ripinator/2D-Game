#include "level_builder.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include "night_borne.hpp"

using json = nlohmann::json;

LevelBuilder::LevelBuilder(Window &window, int screen_width, int screen_height, SDL_Rect floor_rect)
: window_(window), renderer_(window.getRenderer()), screen_width_(screen_width), screen_height_(screen_height), floor_rect_(floor_rect)
{}

void LevelBuilder::loadLevel(int levelId)
{
  std::string path = "configs/levels/level_" + std::to_string(levelId) + ".json";
  std::ifstream file(path);
  if (!file.is_open()) 
  {
    SDL_Log("Failed to load level file: %s", path.c_str());
    return;
  }

  json data;
  file >> data;

  player_spawn_ = {data["player_spawn"]["x"], data["player_spawn"]["y"]};

  background_layers_.clear();
  for (const auto& bgPath : data["backgrounds"]) 
  {
    SDL_Surface* surface = IMG_Load(bgPath.get<std::string>().c_str());
    if (surface) 
    {
      background_layers_.push_back(SDL_CreateTextureFromSurface(renderer_, surface));
      SDL_FreeSurface(surface);
    }
  }

  for (const auto& platform : platforms_)
  {
    SDL_SetRenderDrawColor(renderer_, 80, 80, 80, 255);
    SDL_RenderFillRect(renderer_, &platform); 
  }

  enemies_.clear();
  for (const auto& enemy : data["enemies"]) 
  {
    std::string type = enemy["type"];
    int x = enemy["x"];
    int y = enemy["y"];

    if (type == "NightBorne") 
    {
      enemies_.emplace_back(std::make_unique<NightBorne>(window_, x, y, floor_rect_));
    }
  }
}