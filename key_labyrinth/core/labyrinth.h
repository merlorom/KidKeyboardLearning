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
    void resize( size_t nb_rows, size_t nb_cols );
    void set_nb_rows( size_t nb_rows );
    void set_nb_cols( size_t nb_cols );
    size_t nb_rows() const;
    size_t nb_cols() const;

    std::vector<std::vector<Tile>>& tiles();
    const std::vector<std::vector<Tile>>& tiles() const;

    bool operator==( const Labyrinth& rhs ) const;

    // fast manual building
    enum Modifier { NewRow };
    Labyrinth& operator<<( const Modifier& mod );
    Labyrinth& operator<<( const Tile& tile );
    Labyrinth& operator<<( Tile&& tile );

private:
    size_t nb_rows_;
    size_t nb_cols_;
    std::vector<std::vector<Tile>> tiles_;
};

inline size_t Labyrinth::nb_rows() const {
    return nb_rows_;
}

inline size_t Labyrinth::nb_cols() const {
    return nb_cols_;
}

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
