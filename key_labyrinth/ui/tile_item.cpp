#include "tile_item.h"
#include "labyrinth_widget.h"

#include <core/labyrinth.h>
#include <core/tile.h>

namespace KeyLabyrinth {

/******************************************************************************/

TileItem::TileItem(
    size_t tile_row,
    size_t tile_col
) :
    QGraphicsItem(),
    tile_row_( tile_row ),
    tile_col_( tile_col )
{}

QRectF TileItem::boundingRect() const
{
    qreal size = lab_widget().tile_size();
    return QRectF( 0, 0, size, size );
}

void TileItem::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* /*option*/,
    QWidget* /*widget*/
) {
    const Tile* t = tile();
    if( t == nullptr ) {
        return;
    }

    const QRectF rect = boundingRect();
    const qreal wall_width = lab_widget().tile_size() / 20.;

    // start finish
    Labyrinth::TilePos start_pos = labyrinth()->start_tile();
    Labyrinth::TilePos finish_pos = labyrinth()->finish_tile();
    if( start_pos.row == tile_row_ && start_pos.col == tile_col_ ) {
        painter->setBrush( QColor( 0, 255, 0, 255 ) );
        painter->drawRect( rect );
    } else if( finish_pos.row == tile_row_ && finish_pos.col == tile_col_ ) {
        painter->setBrush( QColor( 255, 0, 0, 255 ) );
        painter->drawRect( rect );
    }

    // text
    painter->drawText( boundingRect(), Qt::AlignCenter, QString( t->key() ) );

    // walls
    painter->setPen( Qt::black );
    painter->setBrush( Qt::black );
    if( t->has_wall( Tile::WallDir::Left ) ) {
        painter->drawRect( rect.left(), rect.top(), wall_width, rect.height() );
    }
    if( t->has_wall( Tile::WallDir::Right ) ) {
        painter->drawRect( rect.right() - wall_width, rect.top(), wall_width, rect.height() );
    }
    if( t->has_wall( Tile::WallDir::Top ) ) {
        painter->drawRect( rect.left(), rect.top(), rect.width(), wall_width );
    }
    if( t->has_wall( Tile::WallDir::Bottom ) ) {
        painter->drawRect( rect.left(), rect.bottom() - wall_width, rect.width(), wall_width );
    }
}

Labyrinth* TileItem::labyrinth() const {
    return lab_widget().labyrinth();
}

Tile* TileItem::tile() const {
    if( labyrinth() == nullptr ) {
        return nullptr;
    }
    auto& tiles = labyrinth()->tiles();
    if( tiles.size() <= tile_row_ ) {
        return nullptr;
    }
    if( tiles[tile_row_].size() <= tile_col_ ) {
        return nullptr;
    }
    return &tiles[tile_row_][tile_col_];
}

/******************************************************************************/

TileEditorItem::TileEditorItem(
    const LabyrinthEditorWidget& lab_widget,
    size_t tile_row,
    size_t tile_col
) :
    TileItem( tile_row, tile_col ),
    lab_widget_( lab_widget )
{
    setFlag( QGraphicsItem::ItemIsSelectable, true );
}

void TileEditorItem::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget
) {
    QRectF rect = boundingRect();

    TileItem::paint( painter, option, widget );

    // selection
    if( isSelected() ) {
        painter->setBrush( QColor( 255, 100, 100, 127 ) );
        painter->drawRect( rect );
    }

    // tile limit
    const qreal tile_width = lab_widget().tile_size();
    painter->setPen( Qt::lightGray );
    painter->setBrush( QBrush() );
    painter->drawRoundedRect( rect, tile_width / 4., tile_width / 4. );
}

/******************************************************************************/

}
