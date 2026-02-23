#include "constants.hpp"
#include "game_over_scene.hpp"
#include "main_scene.hpp"
#include "scene.hpp"
#include "title_scene.hpp"
#include "utils.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_ttf.h>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <memory>

SDL_Window *window;
SDL_Renderer *renderer;
TTF_Font *game_font;
TTF_Font *game_font_big;
SDL_Surface *logo_surf;
SDL_Texture *logo_txtr;

int game_is_running;
int last_frame_time = 0;

float time_buffer = 0;
float game_speed = INITIAL_SPEED;

std::unique_ptr<Scene> active_scene;

Game_Context game_context;

int initialize_window(void) {
  if (0 != SDL_Init(SDL_INIT_EVERYTHING)) {
    std::cout << "Error initializing SDL!" << std::endl;
    return FALSE;
  }

  if (0 != TTF_Init()) {
    std::cout << "Error initializing TTF module!" << std::endl;
    return FALSE;
  }

  if (0 == IMG_Init(IMG_INIT_PNG)) {
    std::cout << "Error initializing SDL Image library!" << std::endl;
    return FALSE;
  }

  window =
      SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                       WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_BORDERLESS);

  if (!window) {
    std::cout << "Error creating SDL window." << std::endl;
    return FALSE;
  }

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  if (!renderer) {
    std::cout << "Error creating Renderer." << std::endl;
    return FALSE;
  }

  game_font = TTF_OpenFont(GAME_FONT, 20);
  game_font_big = TTF_OpenFont(GAME_FONT, 36);

  if (!game_font || !game_font_big) {
    std::cout << "Error creating game font." << std::endl;
    return FALSE;
  }

  logo_surf = IMG_Load("logo.png");
  if (!logo_surf) {
    std::cout << "Error loading image." << std::endl;
    return FALSE;
  }

  logo_txtr = SDL_CreateTextureFromSurface(renderer, logo_surf);
  if (!logo_txtr) {
    std::cout << "Error creating textures." << std::endl;
    return FALSE;
  }

  SDL_FreeSurface(logo_surf);

  return TRUE;
}

void change_scene(Scene_Type scene_type) {
  switch (scene_type) {
  case TITLE:
    active_scene =
        std::make_unique<Title_Scene>(Title_Scene(game_font, logo_txtr));
    break;
  case MAIN:
    active_scene = std::make_unique<Main_Scene>(Main_Scene(game_font));
    break;
  case GAME_OVER:
    active_scene =
        std::make_unique<Game_Over_Scene>(Game_Over_Scene(game_font_big));
    break;
  }
  active_scene->init();
}

void game_over() { change_scene(GAME_OVER); }

void setup(void) { change_scene(Scene_Type::TITLE); }

void handle_input(SDL_Keycode key_code) {

  if (Scene_Type::TITLE == active_scene->getSceneType()) {
    if (SDLK_SPACE == key_code) {
      change_scene(MAIN);
    } else if (SDLK_ESCAPE == key_code) {
      game_is_running = FALSE;
    }
    return;
  } else if (Scene_Type::MAIN == active_scene->getSceneType()) {
    if (SDLK_ESCAPE == key_code) {
      game_is_running = FALSE;
    }
  } else if (Scene_Type::GAME_OVER == active_scene->getSceneType()) {
    change_scene(TITLE);
    game_context.game_over = false;
  }

  active_scene->onKeyPress(key_code, game_context);

  if (game_context.game_over) {
    game_over();
    return;
  }
}

void process_input(void) {
  SDL_Event event;
  SDL_PollEvent(&event);

  switch (event.type) {
  case SDL_QUIT:
    game_is_running = FALSE;
    break;
  case SDL_KEYDOWN:
    handle_input(event.key.keysym.sym);
    break;
  }
}
void update(void) {
  active_scene->update(game_context);

  if (game_context.game_over) {
    game_over();
    return;
  }

  game_context.level = game_context.lines_completed / LEVEL_UP_THRLD;

  if (game_speed >= 1) {
    game_speed = INITIAL_SPEED - (game_context.level * 0.5);
  }
}

void process_game_tick(void) {
  int time_to_wait = FRAME_TARGET_TIME - (SDL_GetTicks() - last_frame_time);
  if (time_to_wait > 0 && time_to_wait <= FRAME_TARGET_TIME) {
    SDL_Delay(time_to_wait);
  }

  float delta_time = (SDL_GetTicks() - last_frame_time) / 1000.0f;

  if (time_buffer > game_speed) {
    update();
    time_buffer = 0;
  } else {
    time_buffer += delta_time * 10;
  }

  last_frame_time = SDL_GetTicks();
}

void render(void) {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderClear(renderer);

  active_scene->render(renderer);

  SDL_RenderPresent(renderer);
}

void destroy_window(void) {
  SDL_DestroyTexture(logo_txtr);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

int main(int argc, char *argv[]) {
  game_is_running = initialize_window();

  setup();

  while (game_is_running) {
    process_input();
    process_game_tick();
    render();
  }

  destroy_window();

  return 0;
}
