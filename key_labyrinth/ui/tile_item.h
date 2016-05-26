#ifndef KeyLabyrinth_ui_tile_item_h
#define KeyLabyrinth_ui_tile_item_h

#include <QGraphicsItem>

namespace KeyLabyrinth {
    class LabyrinthWidget;
    class Labyrinth;
    class Tile;
}

namespace KeyLabyrinth {

/******************************************************************************/

class TileItem : public QGraphicsItem {

public:
    TileItem( LabyrinthWidget& lab_widget, size_t tile_row, size_t tile_col );

    virtual QRectF boundingRect() const;
    virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );

private:
    const Labyrinth* labyrinth() const;
    const Tile* tile() const;

private:
    LabyrinthWidget& lab_widget_;
    size_t tile_row_;
    size_t tile_col_;
};

/******************************************************************************/

}

#endif
