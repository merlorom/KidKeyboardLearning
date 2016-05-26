#ifndef KeyLabyrinth_ui_editor_h
#define KeyLabyrinth_ui_editor_h

#include <QDialog>

namespace Ui {
    class LabyrinthEditor;
}

namespace KeyLabyrinth {
    class LabyrinthWidget;
}

namespace KeyLabyrinth {

class LabyrinthEditor : public QDialog {
    Q_OBJECT

public:
    LabyrinthEditor( QWidget* parent = 0 );
    ~LabyrinthEditor();

private:
    void initialize();

private:
    Ui::LabyrinthEditor* ui_;
    LabyrinthWidget* lab_widget_;
};

}

#endif
