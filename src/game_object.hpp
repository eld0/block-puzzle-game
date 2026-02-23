#ifndef GAME_CONTEXT_H
#define GAME_CONTEXT_H 1

#include "game_context.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>

class Game_Object {

public:
  virtual void init() = 0;
  virtual void render(SDL_Renderer *renderer) = 0;
  virtual void update(Game_Context &game_context) = 0;
  virtual void onKeyPress(SDL_Keycode key_code, Game_Context &game_context) = 0;
};

#endif // !GAME_CONTEXT_H
