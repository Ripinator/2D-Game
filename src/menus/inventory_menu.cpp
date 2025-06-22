#include "inventory_menu.hpp"
#include "utils/utils.hpp"

InventoryMenu::InventoryMenu(Window &window, TTF_Font *font, OverlayState &overlay_state, GameState &game_state)
: renderer_(window.getRenderer()), font_(font), overlay_state_(overlay_state), game_state_(game_state), inventory_(OccupantType::Player, 32, {})
{
  screen_width_ = window.getScreenWidth();
  screen_height_ = window.getScreenHeight();

  float scale_x = static_cast<float>(screen_width_) / BASE_WIDTH;
  float scale_y = static_cast<float>(screen_height_) / BASE_HEIGHT;
  float ui_scale = std::min(scale_x, scale_y);

  rows_ = 4;
  columns_ = 8;

  src_inventory_menu_rect_.x = 576;
  src_inventory_menu_rect_.y = 160;
  src_inventory_menu_rect_.w = 142;
  src_inventory_menu_rect_.h = 76;

  dest_inventory_menu_rect_.w = (src_inventory_menu_rect_.w * ui_scale) * 1.5;
  dest_inventory_menu_rect_.h = (src_inventory_menu_rect_.h * ui_scale) * 1.5;
  dest_inventory_menu_rect_.x = (screen_width_ - dest_inventory_menu_rect_.w) / 2;
  dest_inventory_menu_rect_.y = (screen_height_ - dest_inventory_menu_rect_.h) / 2;

  player_inventory_surface_ = IMG_Load("assets/inventory-system/1-50InventorySlots-10Colors.png");
  player_inventory_texture_ = SDL_CreateTextureFromSurface(renderer_, player_inventory_surface_);
  SDL_FreeSurface(player_inventory_surface_);

  int scaled_slot_width = dest_inventory_menu_rect_.w / columns_;
  int scaled_slot_height = dest_inventory_menu_rect_.h / rows_;

  int grid_start_x = dest_inventory_menu_rect_.x;
  int grid_start_y = dest_inventory_menu_rect_.y;

  for (int i = 0; i < rows_; i++)
  {
    for (int j = 0; j < columns_; j++)
    {
      inventory_slot_rects_[i][j].x = grid_start_x + j * (scaled_slot_width - 2) + 10;
      inventory_slot_rects_[i][j].y = grid_start_y + i * (scaled_slot_height - 4) + 7;
      inventory_slot_rects_[i][j].w = scaled_slot_width - 2;
      inventory_slot_rects_[i][j].h = scaled_slot_height - 4;
    }
  }
}

SDL_Texture *InventoryMenu::createText(const std::string& text, TTF_Font* font, SDL_Color color, SDL_Rect& outRect)
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

void InventoryMenu::handleEvent(const SDL_Event &event)
{
  if (event.type == SDL_KEYDOWN)
  {
    if (event.key.keysym.sym == SDLK_i)
    {
      overlay_state_ = OverlayState::None;
    }
  }
}

void InventoryMenu::update(float delta_time) 
{

}

void InventoryMenu::render()
{
  SDL_RenderCopy(renderer_, player_inventory_texture_, &src_inventory_menu_rect_, &dest_inventory_menu_rect_);
  SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);

  // DEBUGGING RECTS
  // for (int i = 0; i < rows_; i++)
  // {
  //   for (int j = 0; j < columns_; j++)
  //   {
  //     SDL_RenderDrawRect(renderer_, &inventory_slot_rects_[i][j]);
  //   }
  // }


  for (int i = 0; i < rows_; i++)
  {
    for (int j = 0; j < columns_; j++)
    {
      
    }
  }

}
