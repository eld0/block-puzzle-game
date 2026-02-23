#include "score_header.hpp"
#include "game_object.hpp"
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <string>

void Score_Header::init() {}

void Score_Header::render(SDL_Renderer *renderer) {
  lines_completed_tf.render(renderer);
  score_tf.render(renderer);
  level_tf.render(renderer);
}
void Score_Header::update(Game_Context &game_context) {
  lines_completed_tf.setText("Lines: " +
                             std::to_string(game_context.lines_completed));
  level_tf.setText("Level: " + std::to_string(game_context.level));
  score_tf.setText("Score: " + std::to_string(game_context.game_score));
}
void Score_Header::onKeyPress(SDL_Keycode key_code,
                              Game_Context &game_context) {}
