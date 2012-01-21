
#include "const_block.hpp"
#include <cassert>

int main(void) {
    //[example_const_block
    int x = 1, y = 2;
    CONST_BLOCK(x, y) { // Constant block.
        assert(x = y); // Compiler error.
    } CONST_BLOCK_END
    //]
    return 0;
}

