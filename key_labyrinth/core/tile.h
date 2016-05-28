#ifndef KeyLabyrinth_core_tile_h
#define KeyLabyrinth_core_tile_h

#include <iostream>

namespace KeyLabyrinth {

/******************************************************************************/

class Tile {
public:
    enum class WallDir : int {
      Bottom = 1,
      Left = 2,
      Top = 4,
      Right = 8
    };

public:
    Tile();
    Tile( char key, int walls );
    virtual ~Tile();

    char key() const;
    void set_key( char key );

    int walls() const;
    void set_wall( WallDir dir, bool set );
    void set_walls( int walls );
    bool has_wall( WallDir dir ) const;

    bool operator==( const Tile& rhs ) const;

private:
    char key_;
    int walls_;
};

std::ostream& operator<<( std::ostream& out, const Tile& tile );
std::istream& operator>>( std::istream& in, Tile& tile );


inline char Tile::key() const {
    return key_;
}

inline void Tile::set_key( char key ) {
    key_ = key;
}

inline int Tile::walls() const {
    return walls_;
}

inline void Tile::set_walls( int walls ) {
    walls_ = walls;
}

inline bool Tile::has_wall( WallDir dir ) const {
    return walls_ & int(dir);
}

/******************************************************************************/

}

#endif
