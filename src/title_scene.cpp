#include "title_scene.hpp"
#include "game_object.hpp"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>

void Title_Scene::init() {
  game_start_text.setText("Press SPACE key to start or ESC to exit.");
}

void Title_Scene::render(SDL_Renderer *renderer) {
  game_start_text.render(renderer);

  SDL_Rect src_rect = {0, 0, 800, 400};
  SDL_Rect dst_rect = {100, 100, 800, 400};

  SDL_RenderCopy(renderer, logo_texture, &src_rect, &dst_rect);
}
void Title_Scene::update(Game_Context &game_context) {}
void Title_Scene::onKeyPress(SDL_Keycode key_code, Game_Context &game_context) {
}
