#ifndef KeyLabyrinth_core_labyrinth_h
#define KeyLabyrinth_core_labyrinth_h

#include "tile.h"

#include <vector>

namespace KeyLabyrinth {

/******************************************************************************/

class Labyrinth {
public:
    Labyrinth();

    void reset();
    void resize( int nb_rows, int nb_cols );

    std::vector<std::vector<Tile>>& tiles();
    const std::vector<std::vector<Tile>>& tiles() const;

    bool operator==( const Labyrinth& rhs ) const;

    // fast manual building
    enum Modifier { NewRow };
    Labyrinth& operator<<( const Modifier& mod );
    Labyrinth& operator<<( const Tile& tile );
    Labyrinth& operator<<( Tile&& tile );

private:
    std::vector<std::vector<Tile>> tiles_;
};

inline std::vector<std::vector<Tile>>& Labyrinth::tiles() {
    return tiles_;
}

inline const std::vector<std::vector<Tile>>& Labyrinth::tiles() const {
    return tiles_;
}

/******************************************************************************/

class LabyrinthWriter {
public:
    LabyrinthWriter( const Labyrinth& lab );
    bool write( const std::string& path ) const;
    bool write( std::ostream& out ) const;

private:
    const Labyrinth& lab_;
};

/******************************************************************************/

class LabyrinthReader {
public:
    LabyrinthReader( Labyrinth& lab );
    bool read( const std::string& path );
    bool read( std::istream& in );

private:
    bool read_tiles( std::istream& in );

private:
    Labyrinth& lab_;
};

/******************************************************************************/
}

#endif
