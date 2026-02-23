#ifndef TEXT_FIELD_H
#define TEXT_FIELD_H 1

#include "game_object.hpp"
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class Text_Field : public Game_Object {
public:
  Text_Field(TTF_Font *&font, SDL_Color color, SDL_Point position)
      : game_font(font), text_color(color), position(position), text("_") {}
  void init() override;
  void render(SDL_Renderer *renderer) override;
  void update(Game_Context &game_context) override;
  void onKeyPress(SDL_Keycode keyCode, Game_Context &game_context) override;
  void setText(const std::string caption);

private:
  TTF_Font *&game_font;
  SDL_Color text_color;
  SDL_Point position;
  std::string text;
};

#endif // !TEXT_FIELD_H
