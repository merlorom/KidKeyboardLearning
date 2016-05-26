#ifndef KeyLabyrinth_ui_labyrinth_widget_h
#define KeyLabyrinth_ui_labyrinth_widget_h

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace KeyLabyrinth {
    class Labyrinth;
    class TileItem;
}

namespace KeyLabyrinth {

/******************************************************************************/

class LabyrinthWidget : public QWidget {
    Q_OBJECT

public:
    LabyrinthWidget( QWidget* parent = nullptr );
    virtual ~LabyrinthWidget();

    Labyrinth* labyrinth() const;

    qreal tile_size() const;

public slots:
    void set_labyrinth( Labyrinth* lab );

protected:
    void initialize();
    virtual void reset_scene();
    virtual void fill_scene();
    virtual TileItem* create_tile( size_t tile_row, size_t tile_col ) = 0;

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

    TileItem* cur_tile() const;
    void set_cur_tile( TileItem* tile );

public slots:
    void set_nb_rows( int nb_rows );
    void set_nb_cols( int nb_cols );

    void set_wall_left( bool set );
    void set_wall_right( bool set );
    void set_wall_top( bool set );
    void set_wall_bottom( bool set );

private:
    virtual void reset_scene();
    virtual TileItem* create_tile( size_t tile_row, size_t tile_col );

    // events
    virtual void mousePressEvent( QMouseEvent* event );
    virtual void keyPressEvent( QKeyEvent* event );

private:
    TileItem* cur_tile_;
};

inline TileItem* LabyrinthEditorWidget::cur_tile() const {
    return cur_tile_;
}

/******************************************************************************/

}

#endif
