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
    painter->drawText( boundingRect(), Qt::AlignCenter, QString( t->key() ) );

    qreal size = lab_widget().tile_size();
    painter->drawRoundedRect( boundingRect(), size / 4., size / 4. );
}

const Labyrinth* TileItem::labyrinth() const {
    return lab_widget().labyrinth();
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

TileEditorItem::TileEditorItem(
    LabyrinthEditorWidget& lab_widget,
    size_t tile_row,
    size_t tile_col
) :
    TileItem( tile_row, tile_col ),
    lab_widget_( lab_widget )
{}

void TileEditorItem::paint(
    QPainter* painter,
    const QStyleOptionGraphicsItem* option,
    QWidget* widget
) {
    if( lab_widget_.cur_tile() == this ) {
        painter->setBrush( QColor( 255, 100, 100, 127 ) );
        painter->drawRect( boundingRect() );
    }

    TileItem::paint( painter, option, widget );
}

/******************************************************************************/

}
