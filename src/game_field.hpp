#ifndef GAME_FIELD_H
#define GAME_FIELD_H

#include "block.hpp"
#include "constants.hpp"
#include "game_object.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <cstdint>
#include <memory>

struct Game_Cell {
  bool occupied = false;
  RGB_Color color = BLACK_COLOR;
  Game_Cell() {}
  Game_Cell(byte_t occ, RGB_Color col) : occupied(occ), color(col) {}
};

enum Block_Type { BAR, TRIX, CUBE, STICK_L, STICK_R, ZIGZAG };

class Game_Field : public Game_Object {
public:
  static const byte_t h_size = 15;
  static const byte_t v_size = 30;
  static const byte_t cell_size = 25;

  void init() override;
  void render(SDL_Renderer *renderer) override;
  void update(Game_Context &game_context) override;
  void onKeyPress(SDL_Keycode key_code, Game_Context &game_context) override;

private:
  Game_Cell game_cells[h_size][v_size];
  std::shared_ptr<Block> block;
  unsigned int rows_completed = 0;

  void resetBlock(Block_Type block_type);
  void rotateBlock();
  void moveBlockLeft();
  void moveBlockRight();
  void moveBlockDown(Game_Context &game_context);
  void renderBlock();
  void setCell(byte_t cell_x, byte_t cell_y, RGB_Color cell_color);
  void unsetCell(byte_t cell_x, byte_t cell_y);
  void clearSquare(byte_t pos_x, byte_t pos_y, byte_t cell_size);
  void clearCurrentBlockSquare();
  bool moveBlock(int offset_x, int offset_y);
  void placeBlockAtStart();
  void clearBlockArea(Block &block_area);
  uint16_t getObstacleMask(int pos_x, int pos_y);
  void nextGameIteration();
  void reCalculateField();
};

#endif // !GAME_FIELD_H
