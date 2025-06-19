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

  int scaled_slot_width = SLOT_WIDTH * ui_scale;
  int scaled_slot_height = SLOT_HEIGHT * ui_scale;
  int scaled_spacing = SLOT_SPACING * ui_scale;

  int rows = 4;
  int columns = 8;
  int grid_width = columns * scaled_slot_width + (columns - 1) * scaled_spacing;
  int grid_height = rows * scaled_slot_height + (rows - 1) * scaled_spacing;

  // inventory_menu_rect_.w = grid_width + 40;
  // inventory_menu_rect_.h = grid_height + 40;
  // inventory_menu_rect_.x = (screen_width_ - inventory_menu_rect_.w) / 2;
  // inventory_menu_rect_.y = (screen_height_ - inventory_menu_rect_.h) / 2;

  // border_rect_.x = inventory_menu_rect_.x - 4;
  // border_rect_.y = inventory_menu_rect_.y - 4;
  // border_rect_.w = inventory_menu_rect_.w + 8;
  // border_rect_.h = inventory_menu_rect_.h + 8;

  // int start_x = inventory_menu_rect_.x + 20;
  // int start_y = inventory_menu_rect_.y + 20;

  // for (int i = 0; i < rows; i++)
  // {
  //   for (int j = 0; j < columns; j++)
  //   {
  //     inventory_slot_rects_[i][j].x = start_x + j * (scaled_slot_width + scaled_spacing);
  //     inventory_slot_rects_[i][j].y = start_y + i * (scaled_slot_height + scaled_spacing);
  //     inventory_slot_rects_[i][j].w = scaled_slot_width;
  //     inventory_slot_rects_[i][j].h = scaled_slot_height;
  //   }
  // }

  src_inventory_menu_rect_.x = 8.5 * 64;
  src_inventory_menu_rect_.y = 155;
  src_inventory_menu_rect_.w = 64 * 3;
  src_inventory_menu_rect_.h = 80;

  dest_inventory_menu_rect_.x = screen_width_ / 2;
  dest_inventory_menu_rect_.y = screen_height_ / 2;
  dest_inventory_menu_rect_.w = 64 * 3;
  dest_inventory_menu_rect_.h = 80;

  player_inventory_surface_ = IMG_Load("assets/inventory-system/1-50InventorySlots-10Colors.png");
  player_inventory_texture_ = SDL_CreateTextureFromSurface(renderer_, player_inventory_surface_);
  SDL_FreeSurface(player_inventory_surface_);
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
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderFillRect(renderer_, &border_rect_);
  SDL_RenderDrawRect(renderer_, &border_rect_);

  //  SDL_SetRenderDrawColor(renderer_, 128, 128, 128, 255);
  //  SDL_RenderFillRect(renderer_, &inventory_menu_rect_);
  //  SDL_RenderDrawRect(renderer_, &inventory_menu_rect_);

  

  SDL_RenderCopy(renderer_, player_inventory_texture_, &src_inventory_menu_rect_, &dest_inventory_menu_rect_);
}
