#include "game_field.hpp"
#include "bar_block.hpp"
#include "block.hpp"
#include "constants.hpp"
#include "cube_block.hpp"
#include "game_object.hpp"
#include "stickl_block.hpp"
#include "stickr_block.hpp"
#include "trix_block.hpp"
#include "zigzag.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_rect.h>
#include <SDL2/SDL_render.h>
#include <cstdint>
#include <cstdlib>
#include <memory>

void Game_Field::init() { nextGameIteration(); }

void Game_Field::render(SDL_Renderer *renderer) {
  RGB_Color grid_color = DARK_GREY_COLOR;
  for (int row = 0; row < v_size; row++) {
    for (int cell = 0; cell < h_size; cell++) {
      Game_Cell cell_state = game_cells[cell][row];
      SDL_FRect rect;
      rect.h = cell_size;
      rect.w = cell_size;
      rect.x = 100 + (cell * cell_size);
      rect.y = 10 + (row * cell_size);
      SDL_SetRenderDrawColor(renderer, grid_color.r, grid_color.g, grid_color.b,
                             255);
      SDL_RenderDrawRectF(renderer, &rect);
      if (cell_state.occupied) {
        SDL_SetRenderDrawColor(renderer, cell_state.color.r, cell_state.color.g,
                               cell_state.color.b, 255);
        SDL_RenderFillRectF(renderer, &rect);
      }
    }
  }
}

void Game_Field::update(Game_Context &game_context) {
  moveBlockDown(game_context);
  byte_t new_rows = rows_completed - game_context.lines_completed;
  game_context.game_score += 100 * new_rows + (100 * (new_rows / 2));
  game_context.lines_completed = rows_completed;
}

void Game_Field::onKeyPress(SDL_Keycode key_code, Game_Context &game_context) {
  switch (key_code) {
  case SDLK_LEFT:
    moveBlockLeft();
    break;
  case SDLK_RIGHT:
    moveBlockRight();
    break;
  case SDLK_DOWN:
    moveBlockDown(game_context);
    break;
  case SDLK_SPACE:
    rotateBlock();
    break;
  }
}

void Game_Field::setCell(byte_t cell_x, byte_t cell_y, RGB_Color cell_color) {
  if (cell_x < h_size && cell_y < v_size) {
    game_cells[cell_x][cell_y] = Game_Cell{true, cell_color};
  }
}

void Game_Field::unsetCell(byte_t cell_x, byte_t cell_y) {
  if (cell_x < h_size && cell_y < v_size) {
    game_cells[cell_x][cell_y] = Game_Cell{false, BLACK_COLOR};
  }
}

void Game_Field::resetBlock(Block_Type block_type) {

  switch (block_type) {
  case TRIX: {
    block = std::make_shared<Trix_Block>();
  }; break;
  case BAR: {
    block = std::make_shared<Bar_Block>();
  }; break;
  case CUBE: {
    block = std::make_shared<Cube_Block>();
  }; break;
  case STICK_L: {
    block = std::make_shared<StickL_Block>();
  }; break;
  case STICK_R: {
    block = std::make_shared<StickR_Block>();
  }; break;
  case ZIGZAG: {
    block = std::make_shared<ZigZag_Block>();
  }; break;
  }
  placeBlockAtStart();
  renderBlock();
}

void Game_Field::placeBlockAtStart() {
  block->setPosition(h_size / 2 - block->getBlockSize() / 2, 0);
}

void Game_Field::renderBlock() {
  uint16_t mask = 0b1111000000000000;
  auto matrix = block->getMatrix();

  byte_t relative_x = block->getPosX();
  byte_t relative_y = block->getPosY();

  for (int y = 0; y < 4; y++) {
    uint8_t line = ((mask >> y * 4) & matrix) >> (4 - (y + 1)) * 4;
    for (int x = 0; x < 4; x++) {
      uint8_t bit_mask = 1 << x;
      if ((bit_mask & line) == bit_mask) {
        setCell(relative_x + (4 - 1 - x), relative_y + y, block->getColor());
      }
    }
  }
}

void Game_Field::clearSquare(byte_t pos_x, byte_t pos_y, byte_t cell_size) {
  for (byte_t x = 0; x < cell_size; x++) {
    for (byte_t y = 0; y < cell_size; y++) {
      unsetCell(pos_x + x, pos_y + y);
    }
  }
}

void Game_Field::clearBlockArea(Block &block_area) {
  for (byte_t y = 0; y < Block::MATRIX_SIZE; y++) {
    for (byte_t x = 0; x < Block::MATRIX_SIZE; x++) {
      uint16_t mask = 1 << (y * Block::MATRIX_SIZE + x);
      if (mask & block_area.getMatrix()) {
        unsetCell(block_area.getPosX() + (Block::MATRIX_SIZE - x - 1),
                  block_area.getPosY() + (Block::MATRIX_SIZE - y - 1));
      }
    }
  }
}

void Game_Field::clearCurrentBlockSquare() { clearBlockArea(*block); }

bool Game_Field::moveBlock(int x_offset, int y_offset) {
  int new_x = block->getPosX() + x_offset;
  int new_y = block->getPosY() + y_offset;

  clearCurrentBlockSquare();
  uint16_t obstacle_mask = getObstacleMask(new_x, new_y);

  if (block->isCollidesWithObstacle(obstacle_mask)) {
    renderBlock();
    return false;
  }
  block->setPosition(new_x, new_y);

  renderBlock();
  return true;
}

void Game_Field::rotateBlock() {
  clearCurrentBlockSquare();
  uint16_t obstacle_mask = getObstacleMask(block->getPosX(), block->getPosY());

  if (!(block->getRotateMatrix() & obstacle_mask)) {
    block->rotate();
  }
  renderBlock();
}

void Game_Field::moveBlockLeft() { moveBlock(-1, 0); }

void Game_Field::moveBlockRight() { moveBlock(1, 0); }

void Game_Field::moveBlockDown(Game_Context &game_context) {
  if (!moveBlock(0, 1)) {
    if (2 >= block->getPosY()) {
      game_context.game_over = true;
    } else {
      nextGameIteration();
    }
  }
}

uint16_t Game_Field::getObstacleMask(int pos_x, int pos_y) {
  uint16_t collision_mask = 0;
  for (int y_offset = 0; y_offset < Block::MATRIX_SIZE; y_offset++) {
    for (int x_offset = 0; x_offset < Block::MATRIX_SIZE; x_offset++) {
      uint16_t mask = 1 << (y_offset * Block::MATRIX_SIZE + x_offset);
      int nx = pos_x + (Block::MATRIX_SIZE - (x_offset + 1));
      int ny = pos_y + (Block::MATRIX_SIZE - (y_offset + 1));
      if (0 > nx || (h_size - 1) < nx || 0 > ny || (v_size - 1) < ny ||
          game_cells[nx][ny].occupied) {
        collision_mask |= mask;
      }
    }
  }
  return collision_mask;
}

void Game_Field::nextGameIteration() {

  reCalculateField();

  srand((unsigned)time(NULL));
  int block_id = 1 + (rand() % 6);
  switch (block_id) {
  case 1:
    resetBlock(Block_Type::BAR);
    break;
  case 2:
    resetBlock(Block_Type::CUBE);
    break;
  case 3:
    resetBlock(Block_Type::TRIX);
    break;
  case 4:
    resetBlock(Block_Type::STICK_L);
    break;
  case 5:
    resetBlock(Block_Type::STICK_R);
    break;
  case 6:
    resetBlock(Block_Type::ZIGZAG);
    break;
  default:
    resetBlock(Block_Type::TRIX);
    break;
  }
}

void Game_Field::reCalculateField() {
  uint64_t rows_to_skip = 0;
  for (int row = v_size - 1; row >= 0; row--) {
    bool is_full_row = true;
    int cell = 0;
    while (is_full_row && cell < h_size) {
      is_full_row = game_cells[cell][row].occupied;
      cell++;
    }
    if (is_full_row) {
      rows_to_skip |= 1 << row;
      rows_completed++;
    }
  }
  if (rows_to_skip) {
    int iterator = v_size - 1;
    for (int r = v_size - 1; r >= 0; r--) {
      if (rows_to_skip & (1 << r)) {
        continue;
      }
      for (int c = 0; c < h_size; c++) {
        game_cells[c][iterator] = game_cells[c][r];
      }
      iterator--;
    }
    while (iterator >= 0) {
      for (int c = 0; c < h_size; c++) {
        unsetCell(c, iterator);
      }

      iterator--;
    }
  }
}
