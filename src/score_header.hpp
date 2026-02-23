#ifndef SCORE_HEADER_H
#define SCORE_HEADER_H 1

#include "constants.hpp"
#include "game_object.hpp"
#include "text_field.hpp"
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>

class Score_Header : public Game_Object {
public:
  Score_Header(TTF_Font *&font, SDL_Point position)
      : game_font(font), position(position),
        lines_completed_tf(font, SDL_FC_WHITE, {position.x, position.y}),
        score_tf(font, SDL_FC_GRAY, {position.x + 130, position.y}),
        level_tf(font, SDL_FC_LYELLOW, {position.x + 280, position.y}) {}
  void init() override;
  void render(SDL_Renderer *renderer) override;
  void onKeyPress(SDL_Keycode key_code, Game_Context &game_context) override;
  void update(Game_Context &game_context) override;

private:
  TTF_Font *&game_font;
  SDL_Point position;

  Text_Field lines_completed_tf;
  Text_Field score_tf;
  Text_Field level_tf;
};

#endif // !SCORE_HEADER_H
