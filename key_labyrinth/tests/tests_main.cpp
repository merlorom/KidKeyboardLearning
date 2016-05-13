#include "core/tests_tile.h"
#include "core/tests_labyrinth.h"

#include <iostream>

int main( int /*argc*/, char** /*argv*/ ) {
    KeyLabyrinth::TileTests tile_tests;
    tile_tests.execute();

    KeyLabyrinth::LabyrinthTests lab_tests;
    lab_tests.execute();

    std::cout << "All tests ran." << std::endl;
    return 0;
}
