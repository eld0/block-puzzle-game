#include "block.hpp"

class Bar_Block : public Block {
public:
  Bar_Block() : Block(0b0100010001000100, PURPLE_COLOR, 4) {}
};
