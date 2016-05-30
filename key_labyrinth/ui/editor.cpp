#include "editor.h"
#include "ui_editor.h"
#include "labyrinth_widget.h"

#include <core/labyrinth.h>

#include <QKeyEvent>
#include <QFileDialog>

#include <iostream>

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
    lab_widget_ = new LabyrinthEditorWidget();
    lab_widget_->initialize();
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
    connect( this, SIGNAL(wall_left_pressed()), ui_->pushWallLeft, SLOT(toggle()) );
    connect( this, SIGNAL(wall_right_pressed()), ui_->pushWallRight, SLOT(toggle()) );
    connect( this, SIGNAL(wall_top_pressed()), ui_->pushWallTop, SLOT(toggle()) );
    connect( this, SIGNAL(wall_bottom_pressed()), ui_->pushWallBottom, SLOT(toggle()) );

    // start finish
    connect( ui_->pushStartTile, SIGNAL(clicked()), lab_widget_, SLOT(set_start_tile()) );
    connect( ui_->pushFinishTile, SIGNAL(clicked()), lab_widget_, SLOT(set_finish_tile()) );

    // load/save
    connect( ui_->pushLoad, SIGNAL(pressed()), this, SLOT(load()) );
    connect( ui_->pushSave, SIGNAL(pressed()), this, SLOT(save()) );

    // selection
    connect( lab_widget_, SIGNAL(selection_changed(Tile&)), this, SLOT(selection_changed(Tile&)) );
}

void LabyrinthEditor::load() {
    QString file_name = QFileDialog::getOpenFileName( this, tr("Open labyrinth"), "", tr( "Labyrinth Files (*.lab)") );
    if( file_name.isEmpty() ) {
        return;
    }
    Labyrinth* lab = new Labyrinth();
    LabyrinthReader reader( *lab );
    reader.read( file_name.toStdString() );
    lab_widget_->set_labyrinth( lab );
}

void LabyrinthEditor::save() {
    if( lab_widget_->labyrinth() == nullptr ) {
        return;
    }
    QString file_name = QFileDialog::getSaveFileName( this, tr("Save labyrinth"), "", tr( "Labyrinth Files (*.lab)") );
    if( file_name.isEmpty() ) {
        return;
    }
    if( !file_name.endsWith( ".lab" ) ) {
        file_name.append( ".lab" );
    }
    LabyrinthWriter writer( *lab_widget_->labyrinth() );
    writer.write( file_name.toStdString() );
}

void LabyrinthEditor::selection_changed( Tile& tile ) {
    ui_->pushWallLeft->setChecked( tile.has_wall( Tile::WallDir::Left ) );
    ui_->pushWallRight->setChecked( tile.has_wall( Tile::WallDir::Right ) );
    ui_->pushWallTop->setChecked( tile.has_wall( Tile::WallDir::Top ) );
    ui_->pushWallBottom->setChecked( tile.has_wall( Tile::WallDir::Bottom ) );
}

void LabyrinthEditor::keyPressEvent( QKeyEvent* event ) {
    if( !insert_mode_ ) {
        // entering insert mode
        if( event->key() == Qt::Key_I ) {
            insert_mode_ = true;
            event->accept();
            return;
        }

        // moves
        if( event->key() == Qt::Key_J ) {
            lab_widget_->move_down();
            event->accept();
            return;
        }
        if( event->key() == Qt::Key_K ) {
            lab_widget_->move_up();
            event->accept();
            return;
        }
        if( event->key() == Qt::Key_L ) {
            lab_widget_->move_left();
            event->accept();
            return;
        }
        if( event->key() == Qt::Key_Semicolon ) {
            lab_widget_->move_right();
            event->accept();
            return;
        }

        // walls
        if( event->key() == Qt::Key_F ) {
            emit wall_bottom_pressed();
            event->accept();
            return;
        }
        if( event->key() == Qt::Key_D ) {
            emit wall_top_pressed();
            event->accept();
            return;
        }
        if( event->key() == Qt::Key_A ) {
            emit wall_left_pressed();
            event->accept();
            return;
        }
        if( event->key() == Qt::Key_S ) {
            emit wall_right_pressed();
            event->accept();
            return;
        }
    }
    if( insert_mode_ ) {
        // leaving insert mode
        if( event->key() == Qt::Key_Escape ) {
            insert_mode_ = false;
            event->accept();
            return;
        }

        // enter a character
        QString text = event->text();
        if( !text.isEmpty() ) {
            lab_widget_->set_character( text.at(0) );
            event->accept();
            return;
        }
    }


    QWidget::keyPressEvent( event );
}

}
