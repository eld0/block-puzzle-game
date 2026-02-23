#include "block.hpp"
//
// 1100
// 0110
// 0000
// 0000

class ZigZag_Block : public Block {
public:
  ZigZag_Block() : Block(0b1100011000000000, ORANGE_COLOR, 3) {}
};
