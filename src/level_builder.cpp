#include "level_builder.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include "night_borne.hpp"

using json = nlohmann::json;

LevelBuilder::LevelBuilder(Window &window, int screen_width, int screen_height, SDL_Rect floor_rect)
: window_(window), renderer_(window.getRenderer()), screen_width_(screen_width), screen_height_(screen_height), floor_rect_(floor_rect)
{}

LevelData LevelBuilder::loadLevel(int levelId)
{
  LevelData levelData;

  std::string path = "configs/levels/level_" + std::to_string(levelId) + ".json";
  std::ifstream file(path);
  if (!file.is_open()) 
  {
    SDL_Log("Failed to load level file: %s", path.c_str());
    return levelData;
  }

  json data;
  file >> data;

  levelData.playerSpawn = {data["player_spawn"]["x"], data["player_spawn"]["y"]};

  for (const auto& bgPath : data["backgrounds"]) 
  {
    SDL_Surface* surface = IMG_Load(bgPath.get<std::string>().c_str());
    if (surface) 
    {
      levelData.backgrounds.push_back(SDL_CreateTextureFromSurface(renderer_, surface));
      SDL_FreeSurface(surface);
    }
  }

  std::unordered_map<char, std::pair<SDL_Texture*, bool>> tileset;

  for (auto& [symbol, tileData] : data["tileset"].items()) 
  {
    std::string path = tileData["path"];
    bool solid = tileData["solid"];

    SDL_Surface* surf = IMG_Load(path.c_str());
    if (!surf) 
    {
      SDL_Log("Failed to load tile image: %s", path.c_str());
      continue;
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer_, surf);
    SDL_FreeSurface(surf);

    tileset[symbol[0]] = std::make_pair(tex, solid);
  }


  const int TILE_SIZE = 32;

  int y = 0;
  for (const auto& row : data["tilemap"]) 
  {
    int x = 0;
    for (char tileChar : row.get<std::string>()) 
    {
      if (tileset.find(tileChar) != tileset.end()) 
      {
        auto [tex, solid] = tileset[tileChar];

        Tile tile;
        tile.texture = tex;
        tile.destRect = { x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE };
        tile.solid = solid;

        levelData.tiles.push_back(tile);
      }
      x++;
    }
    y++;
  }


  for (const auto& enemy : data["enemies"]) 
  {
    std::string type = enemy["type"];
    int x = enemy["x"];
    int y = enemy["y"];

    if (type == "NightBorne") 
    {
      levelData.enemies.emplace_back(std::make_unique<NightBorne>(window_, x, y, floor_rect_));
    }
  }

  return levelData;
}