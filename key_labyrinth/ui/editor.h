#ifndef KeyLabyrinth_ui_editor_h
#define KeyLabyrinth_ui_editor_h

#include <QDialog>

namespace Ui {
    class LabyrinthEditor;
}

namespace KeyLabyrinth {
    class Labyrinth;
}

namespace KeyLabyrinth {

class LabyrinthEditor : public QDialog {
    Q_OBJECT

public:
    LabyrinthEditor( QWidget* parent = 0 );
    ~LabyrinthEditor();

private:
    void initialize();

private slots:
    void set_nb_rows( int nb_rows );
    void set_nb_cols( int nb_cols );
    void set_wall_left( bool set );
    void set_wall_right( bool set );
    void set_wall_top( bool set );
    void set_wall_bottom( bool set );

private:
    Ui::LabyrinthEditor* ui_;
    Labyrinth* lab_;
};

}

#endif
