#include "editor.h"
#include "ui_editor.h"
#include "labyrinth_widget.h"

#include <core/labyrinth.h>

namespace KeyLabyrinth {

LabyrinthEditor::LabyrinthEditor( QWidget* parent ) :
    QDialog( parent ),
    ui_( new Ui::LabyrinthEditor )
{
    ui_->setupUi( this );
    initialize();
}

LabyrinthEditor::~LabyrinthEditor() {
    delete ui_;
}

void LabyrinthEditor::initialize() {
    // labyrinth widget
    lab_widget_ = new LabyrinthWidget();
    ui_->mainLayout->insertWidget( 1, lab_widget_ );
    Labyrinth* lab = new Labyrinth();
    lab->resize( 5, 5 );
    lab_widget_->set_labyrinth( lab );

    // table size
    connect( ui_->spinNbRows, SIGNAL(valueChanged(int)), lab_widget_, SLOT(set_nb_rows(int)) );
    connect( ui_->spinNbCols, SIGNAL(valueChanged(int)), lab_widget_, SLOT(set_nb_cols(int)) );

    // wall style
    connect( ui_->pushWallLeft, SIGNAL(toggled(bool)), lab_widget_, SLOT(set_wall_left(bool)) );
    connect( ui_->pushWallRight, SIGNAL(toggled(bool)), lab_widget_, SLOT(set_wall_right(bool)) );
    connect( ui_->pushWallTop, SIGNAL(toggled(bool)), lab_widget_, SLOT(set_wall_top(bool)) );
    connect( ui_->pushWallBottom, SIGNAL(toggled(bool)), lab_widget_, SLOT(set_wall_bottom(bool)) );
}

}
