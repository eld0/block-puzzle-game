#include "block.hpp"

class Cube_Block : public Block {
public:
  Cube_Block() : Block(0b1100110000000000, YELLOW_COLOR, 2){};
};
