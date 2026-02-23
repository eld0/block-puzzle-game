#include "block.hpp"
//
// 0100
// 1110
// 0000
// 0000

class Trix_Block : public Block {
public:
  Trix_Block() : Block(0b0100111000000000, RED_COLOR, 3) {}
};
