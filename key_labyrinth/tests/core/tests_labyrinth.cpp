#include "core/tests_labyrinth.h"
#include "tests_utils.h"

#include <core/labyrinth.h>

#include <sstream>

namespace KeyLabyrinth {

void LabyrinthTests::execute() {
    basic_tests();
    test_write_read();
}

void LabyrinthTests::basic_tests() {
    Labyrinth lab;

}

void LabyrinthTests::test_write_read() {
    Labyrinth lab = make_labyrinth();

    LabyrinthWriter lab_writer( lab );
    std::ostringstream out;
    lab_writer.write( out );

    Labyrinth lab2;
    LabyrinthReader lab_reader( lab2 );
    std::istringstream in( out.str() );
    lab_reader.read( in );

    CPPUNIT_ASSERT( lab == lab2 );
}

Labyrinth LabyrinthTests::make_labyrinth() const {
    Labyrinth lab;
    lab << Labyrinth::NewRow << Tile( 'e', 2 ) << Tile( 'i', 3 ) << Tile( 'o', 4 );
    lab << Labyrinth::NewRow << Tile( '~', 0 ) << Tile( 'r', 1 ) << Tile( 'h', 7 ) << Tile( 't', 3 );
    return std::move( lab );
}

}
