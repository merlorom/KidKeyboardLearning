#ifndef KeyLabyrinth_ui_labyrinth_widget_h
#define KeyLabyrinth_ui_labyrinth_widget_h

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace KeyLabyrinth {
    class Labyrinth;
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

    void set_nb_rows( int nb_rows );
    void set_nb_cols( int nb_cols );
    void set_wall_left( bool set );
    void set_wall_right( bool set );
    void set_wall_top( bool set );
    void set_wall_bottom( bool set );

private:
    void initialize();
    void reset_scene();
    void fill_scene();

private:
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

}

#endif
