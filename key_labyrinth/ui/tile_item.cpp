#include "tile_item.h"
#include "labyrinth_widget.h"

#include <core/labyrinth.h>
#include <core/tile.h>

namespace KeyLabyrinth {

/******************************************************************************/

TileItem::TileItem(
    LabyrinthWidget& lab_widget,
    size_t tile_row,
    size_t tile_col
) :
    QGraphicsItem(),
    lab_widget_( lab_widget ),
    tile_row_( tile_row ),
    tile_col_( tile_col )
{}

QRectF TileItem::boundingRect() const
{
    qreal pen_width = 1;
    qreal size = lab_widget_.tile_size() + pen_width;
    return QRectF( -size/2, -size/2, size, size );
}

void TileItem::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* /*option*/,
    QWidget* /*widget*/
) {
    painter->drawRoundedRect(-10, -10, 20, 20, 5, 5);
}

const Labyrinth* TileItem::labyrinth() const {
    return lab_widget_.labyrinth();
}

const Tile* TileItem::tile() const {
    if( labyrinth() == nullptr ) {
        return nullptr;
    }
    const auto& tiles = labyrinth()->tiles();
    if( tiles.size() <= tile_row_ ) {
        return nullptr;
    }
    if( tiles[tile_row_].size() <= tile_col_ ) {
        return nullptr;
    }
    return &tiles[tile_row_][tile_col_];
}

/******************************************************************************/

}
