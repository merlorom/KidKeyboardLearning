#ifndef KeyLabyrinth_ui_labyrinth_widget_h
#define KeyLabyrinth_ui_labyrinth_widget_h

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace KeyLabyrinth {
    class Labyrinth;
    class TileItem;
    class TileEditorItem;
}

namespace KeyLabyrinth {

/******************************************************************************/

class LabyrinthWidget : public QWidget {
    Q_OBJECT

public:
    LabyrinthWidget( QWidget* parent = nullptr );
    virtual ~LabyrinthWidget();
    void initialize();

    Labyrinth* labyrinth() const;

    qreal tile_size() const;

    TileItem* tile_at( size_t tile_row, size_t tile_col ) const;

public slots:
    void set_labyrinth( Labyrinth* lab );

    virtual void move_at( TileItem* from_tile, size_t row, size_t col ) = 0;
    virtual void move_left() = 0;
    virtual void move_right() = 0;
    virtual void move_up() = 0;
    virtual void move_down() = 0;

protected:
    void reset_scene();
    void fill_scene();
    virtual TileItem* create_tile( size_t tile_row, size_t tile_col ) const = 0;
    virtual QGraphicsScene* create_scene() = 0;

protected:
    Labyrinth* lab_;

    QGraphicsScene* scene_;
    QGraphicsView* view_;
};

inline Labyrinth* LabyrinthWidget::labyrinth() const {
    return lab_;
}

inline qreal LabyrinthWidget::tile_size() const {
    return 20;
}

/******************************************************************************/

class LabyrinthEditorWidget : public LabyrinthWidget {
    Q_OBJECT

public:
    LabyrinthEditorWidget( QWidget* parent = nullptr );
    virtual ~LabyrinthEditorWidget();

public slots:
    void set_nb_rows( int nb_rows );
    void set_nb_cols( int nb_cols );

    void set_wall_left( bool set );
    void set_wall_right( bool set );
    void set_wall_top( bool set );
    void set_wall_bottom( bool set );

    void set_character( QChar c );

    virtual void move_at( TileItem* from_tile, size_t row, size_t col ) final;
    virtual void move_left() final;
    virtual void move_right() final;
    virtual void move_up() final;
    virtual void move_down() final;

private:
    virtual QGraphicsScene* create_scene() final;
    virtual TileItem* create_tile( size_t tile_row, size_t tile_col ) const final;

    QList<TileEditorItem*> selected_tiles() const;
    TileEditorItem* first_selected_tile() const;
};

/******************************************************************************/

class LabyrinthEditorWidgetScene : public QGraphicsScene {
    Q_OBJECT

public:
    LabyrinthEditorWidgetScene( QWidget* parent );

    virtual void mousePressEvent( QGraphicsSceneMouseEvent* event ) final;
    virtual void keyPressEvent( QKeyEvent* event ) final;

    QList<TileEditorItem*> selected_tiles() const;

signals:
    void move_left_pressed();
    void move_right_pressed();
    void move_up_pressed();
    void move_down_pressed();
};

}

/******************************************************************************/

#endif
