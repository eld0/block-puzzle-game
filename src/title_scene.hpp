#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H 1
#include "game_object.hpp"
#include <SDL2/SDL_render.h>

#include "constants.hpp"
#include "scene.hpp"
#include "text_field.hpp"

class Title_Scene : public Scene {
public:
  Title_Scene(TTF_Font *&font, SDL_Texture *&logo_texture)
      : Scene(Scene_Type::TITLE, font), logo_texture(logo_texture),
        game_start_text(game_font, SDL_FC_WHITE, {260, 600}) {}
  void init() override;
  void render(SDL_Renderer *render) override;
  void update(Game_Context &game_context) override;
  void onKeyPress(SDL_Keycode key_code, Game_Context &game_context) override;

private:
  SDL_Texture *&logo_texture;
  Text_Field game_start_text;
};

#endif // !TITLE_SCENE_H
