#include "tile.h"

namespace KeyLabyrinth {

Tile::Tile() :
    key_( 'a' ),
    walls_( 0 )
{}

Tile::~Tile() {}

void Tile::set_wall( WallDir dir, bool set ) {
    if( set ) {
        walls_ |= dir;
    } else {
        walls_ = ~( ~walls_ | dir );
    }
}

}
