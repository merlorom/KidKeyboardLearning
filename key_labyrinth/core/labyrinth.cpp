#include "labyrinth.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace KeyLabyrinth {

/******************************************************************************/

Labyrinth::Labyrinth() {}

void Labyrinth::reset() {
    tiles_.clear();
}

void Labyrinth::resize( int nb_rows, int nb_cols ) {
    tiles_.resize( nb_rows );
    for( auto& tile_row : tiles_ ) {
        tile_row.resize( nb_cols );
    }
}

bool Labyrinth::operator==( const Labyrinth& rhs ) const {
    return tiles() == rhs.tiles();
}

Labyrinth& Labyrinth::operator<<( const Modifier& mod ) {
    switch( mod ) {
        case NewRow:
            tiles_.push_back( std::vector<Tile>() );
    }
    return *this;
}

Labyrinth& Labyrinth::operator<<( const Tile& tile ) {
    if( !tiles_.empty() ) {
        tiles_.back().push_back( tile );
    }
    return *this;
}

Labyrinth& Labyrinth::operator<<( Tile&& tile ) {
    if( !tiles_.empty() ) {
        tiles_.back().push_back( tile );
    }
    return *this;
}

/******************************************************************************/

LabyrinthWriter::LabyrinthWriter( const Labyrinth& lab ) :
    lab_( lab )
{}

bool LabyrinthWriter::write( const std::string& /*path*/ ) const {
    //std::ofstream out( path );
    //if( !out.good() ) {
        //return false;
    //}
    //bool ok = write( out );
    //out.close();
    return true;
}

bool LabyrinthWriter::write( std::ostream& out ) const {
    // writing header
    out << "Key Labyrinth file - version 1.0" << std::endl;

    // writing tiles
    out << "TILES" << std::endl;
    out << lab_.tiles().size() << std::endl;; // nb_row
    for( const auto& tile_row : lab_.tiles() ) {
        out << tile_row.size() << std::endl; // nb_tiles_in_row
        for( const Tile& tile : tile_row ) {
            out << tile << std::endl;
        }
    }

    out << "END" << std::endl;
    return true;

}

/******************************************************************************/

LabyrinthReader::LabyrinthReader( Labyrinth& lab ) :
    lab_( lab )
{}

bool LabyrinthReader::read( const std::string& /*path*/ ) {
    //std::ifstream in( path );
    //if( !in.good() ) {
        //return false;
    //}

    return true;
}

bool LabyrinthReader::read( std::istream& in ) {
    lab_.reset();

    char linebuf[1080];
    do {
        in.getline( linebuf, sizeof( linebuf ) );
        std::istringstream line( linebuf );

        // reading header
        std::string header;
        line >> header;

        if( header == "END" ) {
            break;
        }

        if( header == "TILES" ) {
            read_tiles( in );
            continue;
        }

    } while( !in.eof() );

    return true;
}

bool LabyrinthReader::read_tiles( std::istream& in ) {
    char linebuf[1080];
    in.getline( linebuf, sizeof( linebuf ) );
    std::istringstream nb_rows_line( linebuf );
    int nb_rows;
    nb_rows_line >> nb_rows;

    for( int row = 0; row < nb_rows && !in.eof(); ++row ) {
        lab_ << Labyrinth::NewRow;
        in.getline( linebuf, sizeof( linebuf ) );
        std::istringstream nb_tiles_line( linebuf );
        int nb_tiles;
        nb_tiles_line >> nb_tiles;

        for( int t = 0; t < nb_tiles && !in.eof(); ++t ) {
            in.getline( linebuf, sizeof( linebuf ) );
            std::istringstream tile_line( linebuf );
            Tile tile;
            tile_line >> tile;
            lab_ << std::move( tile );
        }
    }

    return true;
}

/******************************************************************************/

}
