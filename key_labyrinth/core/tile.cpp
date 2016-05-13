#include "tile.h"

namespace KeyLabyrinth {

Tile::Tile() :
    key_( 'a' ),
    walls_( 0 )
{}

Tile::Tile( char key, int walls ) :
    key_( key ),
    walls_( walls )
{}

Tile::~Tile() {}

void Tile::set_wall( WallDir dir, bool set ) {
    if( set ) {
        walls_ |= dir;
    } else {
        walls_ = ~( ~walls_ | dir );
    }
}

bool Tile::operator==( const Tile& rhs ) const {
    return key_ == rhs.key_ && walls_ == rhs.walls_;
}

std::ostream& operator<<( std::ostream& out, const Tile& tile ) {
    out << tile.key() << " " << tile.walls();
    return out;
}

std::istream& operator>>( std::istream& in, Tile& tile ) {
    char key;
    in >> key;
    tile.set_key( key );

    int walls;
    in >> walls;
    tile.set_walls( walls );

    return in;
}

}
