
#include "const_block.hpp"
#include <cassert>

int main(void) {
    int x = 0, y = 0;
    CONST_BLOCK(x, y) {
        assert(x == y);
    } CONST_BLOCK_END
    return 0;
}

