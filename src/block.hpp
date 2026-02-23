#ifndef BLOCK_H
#define BLOCK_H

#include "constants.hpp"
#include <SDL2/SDL.h>
#include <cstdint>

struct RGB_Color {
  byte_t r;
  byte_t g;
  byte_t b;
};

inline const RGB_Color PURPLE_COLOR{100, 20, 200};
inline const RGB_Color RED_COLOR{200, 20, 20};
inline const RGB_Color DARK_GREY_COLOR{30, 30, 30};
inline const RGB_Color BLACK_COLOR{0, 0, 0};
inline const RGB_Color BLUE_COLOR{20, 80, 200};
inline const RGB_Color GREEN_COLOR{50, 180, 60};
inline const RGB_Color YELLOW_COLOR{255, 243, 128};
inline const RGB_Color WHITE_COLOR{255, 255, 255};
inline const RGB_Color DARK_BLUE_COLOR{0, 51, 102};
inline const RGB_Color ORANGE_COLOR{255, 128, 0};

class Block {
public:
  Block(const uint16_t matrix, const RGB_Color &color)
      : matrix(matrix), color(color), block_size(4) {}
  Block(const uint16_t matrix, const RGB_Color &color, int block_s)
      : matrix(matrix), color(color), block_size(block_s) {}

  static const uint8_t MATRIX_SIZE;

  const uint16_t getMatrix();
  void rotate();
  uint16_t getRotateMatrix();
  const RGB_Color &getColor();
  void setPosition(char x, char y);
  char getPosX();
  char getPosY();
  byte_t getBlockSize();
  bool isCollidesWithObstacle(uint16_t obstacleMask);

private:
  uint16_t matrix;
  const RGB_Color color;
  const int block_size;
  char pos_x = 0;
  char pos_y = 0;
};
#endif // !BLOCK_H
