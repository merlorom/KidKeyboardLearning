#include "editor.h"
#include "ui_editor.h"

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
    // table size
    connect( ui_->spinNbRows, SIGNAL(valueChanged(int)), this, SLOT(set_nb_rows(int)) );
    connect( ui_->spinNbCols, SIGNAL(valueChanged(int)), this, SLOT(set_nb_cols(int)) );

    // wall style
    connect( ui_->pushWallLeft, SIGNAL(toggled(bool)), this, SLOT(set_wall_left(bool)) );
    connect( ui_->pushWallRight, SIGNAL(toggled(bool)), this, SLOT(set_wall_right(bool)) );
    connect( ui_->pushWallTop, SIGNAL(toggled(bool)), this, SLOT(set_wall_top(bool)) );
    connect( ui_->pushWallBottom, SIGNAL(toggled(bool)), this, SLOT(set_wall_bottom(bool)) );
}

void LabyrinthEditor::set_nb_rows( int nb_rows ) {
    ui_->tableLabyrinth->setRowCount( nb_rows );
}

void LabyrinthEditor::set_nb_cols( int nb_cols ) {
    ui_->tableLabyrinth->setColumnCount( nb_cols );
}

void LabyrinthEditor::set_wall_left( bool /*set*/ ) {
    //QTableWidgetItem* item = ui_->tableLabyrinth->currentItem();
}

void LabyrinthEditor::set_wall_right( bool /*set*/ ) {
    //QTableWidgetItem* item = ui_->tableLabyrinth->currentItem();
}

void LabyrinthEditor::set_wall_top( bool /*set*/ ) {
    //QTableWidgetItem* item = ui_->tableLabyrinth->currentItem();
}

void LabyrinthEditor::set_wall_bottom( bool /*set*/ ) {
    //QTableWidgetItem* item = ui_->tableLabyrinth->currentItem();
}

}
