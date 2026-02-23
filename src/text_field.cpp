#include "text_field.hpp"
#include "game_object.hpp"
#include <SDL2/SDL_error.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <cstdio>
#include <iostream>
#include <string>

void Text_Field::init() {}
void Text_Field::render(SDL_Renderer *renderer) {
  // Create surface with rendered text
  SDL_Surface *textSurface =
      TTF_RenderText_Solid(game_font, text.c_str(), text_color);

  if (!textSurface) {
    std::cout << "Failed to create text surface: " << TTF_GetError()
              << std::endl;
    throw "Surface initialization error";
  }

  // Create texture from surface
  SDL_Texture *textTexture =
      SDL_CreateTextureFromSurface(renderer, textSurface);

  if (!textTexture) {
    std::cout << "Failed to create texture: " << SDL_GetError() << std::endl;
    throw "Surface initialization error";
  }

  // Render text
  SDL_Rect textRect = {position.x, position.y, textSurface->w, textSurface->h};
  SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
}
void Text_Field::update(Game_Context &game_context) {}
void Text_Field::onKeyPress(SDL_Keycode key_code, Game_Context &game_context) {}

void Text_Field::setText(std::string text) { this->text = text; }
