#include "game_over_scene.hpp"
#include "game_object.hpp"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>

void Game_Over_Scene::init() { game_over_message.setText("Game Over"); }

void Game_Over_Scene::render(SDL_Renderer *renderer) {
  game_over_message.render(renderer);
}
void Game_Over_Scene::update(Game_Context &game_context) {}
void Game_Over_Scene::onKeyPress(SDL_Keycode key_code,
                                 Game_Context &game_context) {}
