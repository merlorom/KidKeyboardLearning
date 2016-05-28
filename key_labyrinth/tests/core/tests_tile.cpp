#include "core/tests_tile.h"
#include "tests_utils.h"

#include <core/tile.h>

#include <sstream>

namespace KeyLabyrinth {

void TileTests::execute() {
    basic_tests();
    test_write_read();
}

void TileTests::basic_tests() {
    std::cout << "TileTests::basic_tests" << std::endl;
    Tile tile;

    // key
    tile.set_key( 'e' );
    CPPUNIT_ASSERT( tile.key() == 'e' );

    // walls
    for( int id = 0; id < 2; ++id ) {
        tile.set_wall( Tile::WallDir::Bottom, id != 0 );
        CPPUNIT_ASSERT( ( tile.has_wall( Tile::WallDir::Bottom ) ) == ( id != 0 ) );

        for( int il = 0; il < 2; ++il ) {
            tile.set_wall( Tile::WallDir::Left, il != 0 );
            CPPUNIT_ASSERT( ( tile.has_wall( Tile::WallDir::Left ) ) == ( il != 0 ) );

            for( int iu = 0; iu < 2; ++iu ) {
                tile.set_wall( Tile::WallDir::Top, iu != 0 );
                CPPUNIT_ASSERT( ( tile.has_wall( Tile::WallDir::Top ) ) == ( iu != 0 ) );

                for( int ir = 0; ir < 2; ++ir ) {
                    tile.set_wall( Tile::WallDir::Right, ir != 0 );
                    CPPUNIT_ASSERT( ( tile.has_wall( Tile::WallDir::Right ) ) == ( ir != 0 ) );

                    int expected = 0;
                    if( id == 1 ) expected += 1;
                    if( il == 1 ) expected += 2;
                    if( iu == 1 ) expected += 4;
                    if( ir == 1 ) expected += 8;
                    CPPUNIT_ASSERT( tile.walls() == expected );
                }
            }
        }
    }
}

void TileTests::test_write_read() {
    std::cout << "TileTests::test_write_read" << std::endl;
    // first check
    Tile tile;
    tile.set_key( 'e' );
    tile.set_walls( int(Tile::WallDir::Bottom) | int(Tile::WallDir::Right) );

    std::ostringstream out;
    out << tile;
    std::string str = out.str();

    std::istringstream in( str );
    Tile tile_check;
    in >> tile_check;

    CPPUNIT_ASSERT( tile == tile_check );

    // second check
    Tile tile2;
    tile2.set_key( ' ' );
    tile2.set_walls( int(Tile::WallDir::Top) | int(Tile::WallDir::Left) );

    std::ostringstream out2;
    out2 << tile2;
    std::string str2 = out2.str();

    std::istringstream in2( str2 );
    Tile tile_check2;
    in2 >> tile_check2;

    CPPUNIT_ASSERT( tile2 == tile_check2 );
}

}
