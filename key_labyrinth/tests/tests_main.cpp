#include "core/tests_tile.h"

#include <iostream>

int main( int /*argc*/, char** /*argv*/ ) {
    KeyLabyrinth::TileTests tile_tests;
    tile_tests.execute();

    std::cout << "All tests ran." << std::endl;
    return 1;
}
