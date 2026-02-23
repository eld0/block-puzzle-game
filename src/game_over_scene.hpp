#include "game_object.hpp"
#ifndef GAME_OVER_SCENE_H
#define GAME_OVER_SCENE_H 1

#include "constants.hpp"
#include "scene.hpp"
#include "text_field.hpp"

class Game_Over_Scene : public Scene {
public:
  Game_Over_Scene(TTF_Font *&font)
      : Scene(Scene_Type::GAME_OVER, font),
        game_over_message(game_font, SDL_FC_WHITE, {400, 300}) {}
  void init() override;
  void render(SDL_Renderer *render) override;
  void update(Game_Context &game_context) override;
  void onKeyPress(SDL_Keycode key_code, Game_Context &game_context) override;

private:
  Text_Field game_over_message;
};

#endif // !GAME_OVER_SCENE_H
