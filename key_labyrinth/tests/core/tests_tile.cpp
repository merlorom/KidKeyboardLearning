#include "core/tests_tile.h"
#include "tests_utils.h"

#include <core/tile.h>

namespace KeyLabyrinth {

void TileTests::execute() {
    basic_tests();
}

void TileTests::basic_tests() {
    Tile tile;

    // key
    tile.set_key( 'e' );
    CPPUNIT_ASSERT( tile.key() == 'e' );

    // walls
    for( int id = 0; id < 2; ++id ) {
        tile.set_wall( Tile::Down, id != 0 );
        CPPUNIT_ASSERT( ( tile.has_wall( Tile::Down ) ) == ( id != 0 ) );

        for( int il = 0; il < 2; ++il ) {
            tile.set_wall( Tile::Left, il != 0 );
            CPPUNIT_ASSERT( ( tile.has_wall( Tile::Left ) ) == ( il != 0 ) );

            for( int iu = 0; iu < 2; ++iu ) {
                tile.set_wall( Tile::Up, iu != 0 );
                CPPUNIT_ASSERT( ( tile.has_wall( Tile::Up ) ) == ( iu != 0 ) );

                for( int ir = 0; ir < 2; ++ir ) {
                    tile.set_wall( Tile::Right, ir != 0 );
                    CPPUNIT_ASSERT( ( tile.has_wall( Tile::Right ) ) == ( ir != 0 ) );

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

}
