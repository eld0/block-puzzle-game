#include "block.hpp"
#include <SDL2/SDL_render.h>
#include <cstdint>

const uint8_t Block::MATRIX_SIZE = 4;

const uint16_t Block::getMatrix() { return matrix; }

uint16_t Block::getRotateMatrix() {
  int init = MATRIX_SIZE - block_size;
  uint16_t result_matrix = 0;
  for (int b = init; b < MATRIX_SIZE; b++) {
    for (int nibble = init; nibble < MATRIX_SIZE; nibble++) {
      uint8_t mask_offset = (nibble * MATRIX_SIZE + b);
      uint16_t mask = 1 << mask_offset;
      if (matrix & mask) {
        uint8_t matrix_offset = MATRIX_SIZE + init - (nibble + 1);
        matrix_offset += MATRIX_SIZE * b;

        result_matrix |= 1 << matrix_offset;
      }
    }
  }
  return result_matrix;
}
void Block::rotate() { matrix = getRotateMatrix(); }

const RGB_Color &Block::getColor() { return color; }

void Block::setPosition(char x, char y) {
  pos_x = x;
  pos_y = y;
}

char Block::getPosX() { return pos_x; }

char Block::getPosY() { return pos_y; }

byte_t Block::getBlockSize() { return block_size; }

bool Block::isCollidesWithObstacle(uint16_t obstacleMask) {
  return matrix & obstacleMask;
}
