#ifndef KeyLabyrinth_ui_editor_h
#define KeyLabyrinth_ui_editor_h

#include <QDialog>

namespace Ui {
    class LabyrinthEditor;
}

namespace KeyLabyrinth {
    class LabyrinthEditorWidget;
}

namespace KeyLabyrinth {

class LabyrinthEditor : public QDialog {
    Q_OBJECT

public:
    LabyrinthEditor( QWidget* parent = 0 );
    ~LabyrinthEditor();

public slots:
    void load();
    void save();

signals:
    void wall_left_pressed();
    void wall_right_pressed();
    void wall_top_pressed();
    void wall_bottom_pressed();

private:
    void initialize();
    virtual void keyPressEvent( QKeyEvent* event ) final;

private:
    Ui::LabyrinthEditor* ui_;
    LabyrinthEditorWidget* lab_widget_;

    bool insert_mode_;
};

}

#endif
