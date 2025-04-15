#include "scene.hpp"

class StartMenu : public Scene {
private:
    SDL_Renderer* renderer_;
    SDL_Rect menu_rect_;
public:
    StartMenu(SDL_Renderer* renderer);
    void handleEvent(const SDL_Event& event) override;
    void update() override;
    void render() override;
};
