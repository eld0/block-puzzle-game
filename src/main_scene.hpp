#include "game_object.hpp"
#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H 1

#include "game_field.hpp"
#include "scene.hpp"
#include "score_header.hpp"

class Main_Scene : public Scene {
public:
  Main_Scene(TTF_Font *&font)
      : Scene(Scene_Type::MAIN, font), score_header(game_font, {530, 30}) {}
  void init() override;
  void render(SDL_Renderer *render) override;
  void update(Game_Context &game_context) override;
  void onKeyPress(SDL_Keycode key_code, Game_Context &game_context) override;

private:
  Game_Field game_field;
  Score_Header score_header;
};

#endif // !MAIN_SCENE_H
