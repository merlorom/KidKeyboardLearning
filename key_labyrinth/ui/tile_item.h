#ifndef KeyLabyrinth_ui_tile_item_h
#define KeyLabyrinth_ui_tile_item_h

#include <QGraphicsItem>

namespace KeyLabyrinth {
    class LabyrinthWidget;
    class LabyrinthEditorWidget;
    class Labyrinth;
    class Tile;
}

namespace KeyLabyrinth {

/******************************************************************************/

class TileItem : public QGraphicsItem {

public:
    TileItem( size_t tile_row, size_t tile_col );

    virtual QRectF boundingRect() const;
    virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );

    Tile* tile() const;
    size_t tile_row() const;
    size_t tile_col() const;

protected:
    virtual const LabyrinthWidget& lab_widget() const = 0;
    Labyrinth* labyrinth() const;

protected:
    size_t tile_row_;
    size_t tile_col_;
};

inline size_t TileItem::tile_row() const {
    return tile_row_;
}

inline size_t TileItem::tile_col() const {
    return tile_col_;
}

/******************************************************************************/

class TileEditorItem : public TileItem {

public:
    TileEditorItem( const LabyrinthEditorWidget& lab_widget, size_t tile_row, size_t tile_col );

    virtual void paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget );

protected:
    virtual const LabyrinthWidget& lab_widget() const;

private:
    const LabyrinthEditorWidget& lab_widget_;
};

inline const LabyrinthWidget& TileEditorItem::lab_widget() const {
    return (const LabyrinthWidget&)lab_widget_;
}
/******************************************************************************/

}

#endif
