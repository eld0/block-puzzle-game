#include "main_scene.hpp"
#include "game_object.hpp"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>

void Main_Scene::init() {
  game_field.init();
  score_header.init();
}

void Main_Scene::update(Game_Context &game_context) {
  game_field.update(game_context);
  score_header.update(game_context);
}

void Main_Scene::render(SDL_Renderer *renderer) {
  game_field.render(renderer);
  score_header.render(renderer);
}

void Main_Scene::onKeyPress(SDL_Keycode key_code, Game_Context &game_context) {
  game_field.onKeyPress(key_code, game_context);
}
