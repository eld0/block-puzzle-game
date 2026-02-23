#ifndef SCENE_H
#define SCENE_H 1

#include "SDL2/SDL_ttf.h"
#include "game_object.hpp"

enum Scene_Type { TITLE, MAIN, GAME_OVER };

class Scene : public Game_Object {
public:
  Scene(Scene_Type scene_type, TTF_Font *&font)
      : scene_type(scene_type), game_font(font){};
  virtual ~Scene(){};
  const Scene_Type getSceneType();

protected:
  const Scene_Type scene_type;
  TTF_Font *&game_font;
};

#endif // !SCENE_H
