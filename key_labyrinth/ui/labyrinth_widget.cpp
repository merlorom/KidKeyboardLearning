#include "labyrinth_widget.h"
#include "tile_item.h"

#include <core/labyrinth.h>

#include <QGridLayout>
#include <QMouseEvent>

namespace KeyLabyrinth {

/******************************************************************************/

LabyrinthWidget::LabyrinthWidget( QWidget* parent ) :
    QWidget( parent ),
    lab_( nullptr ),
    scene_( nullptr ),
    view_( nullptr )
{
    initialize();
}

LabyrinthWidget::~LabyrinthWidget() {
    delete lab_;
}

/*!
 * Takes ownership of the labyrinth \p lab.
 */
void LabyrinthWidget::set_labyrinth( Labyrinth* lab ) {
    if( lab_ == lab ) {
        return;
    }
    delete lab_;
    lab_ = lab;

    fill_scene();
}

void LabyrinthWidget::initialize() {
    scene_ = new QGraphicsScene( this );

    view_ = new QGraphicsView( scene_, this );
    view_->show();
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(view_,0,0);
    layout->setContentsMargins( 0, 0, 0, 0 );
    setLayout(layout);
}

void LabyrinthWidget::reset_scene() {
    QList<QGraphicsItem*> items = scene_->items();
    foreach( auto item, items ) {
        scene_->removeItem( item );
        delete item;
    }
}

void LabyrinthWidget::fill_scene() {
    reset_scene();
    if( lab_ == nullptr ) {
        return;
    }

    for( size_t i = 0; i < lab_->tiles().size(); ++i ) {
        for( size_t j = 0; j < lab_->tiles()[i].size(); ++j ) {
            TileItem* tile_item = create_tile( i, j );
            tile_item->setPos( i*tile_size(), j*tile_size() );
            scene_->addItem( tile_item );
        }
    }
}

/******************************************************************************/

LabyrinthEditorWidget::LabyrinthEditorWidget( QWidget* parent ) :
    LabyrinthWidget( parent ),
    cur_tile_( nullptr )
{}

LabyrinthEditorWidget::~LabyrinthEditorWidget() {
    cur_tile_ = nullptr;
}

void LabyrinthEditorWidget::reset_scene() {
    set_cur_tile( nullptr );
    LabyrinthWidget::reset_scene();
}

TileItem* LabyrinthEditorWidget::create_tile( size_t tile_row, size_t tile_col ) {
    return new TileEditorItem( *this, tile_row, tile_col );
}

void LabyrinthEditorWidget::mousePressEvent( QMouseEvent* event ) {
    QGraphicsItem* item = view_->itemAt( event->pos() );
    TileItem* tile = dynamic_cast<TileItem*>( item );
    set_cur_tile( tile );
    if( tile != nullptr ) {
        event->accept();
    }

    QWidget::mousePressEvent( event );
}

void LabyrinthEditorWidget::keyPressEvent( QKeyEvent* event ) {
    if( cur_tile_ != nullptr ) {

    }

    QWidget::keyPressEvent( event );
}

void LabyrinthEditorWidget::set_cur_tile( TileItem* tile ) {
    TileItem* old_cur_tile = cur_tile_;
    cur_tile_ = tile;

    if( old_cur_tile != nullptr ) {
        old_cur_tile->update();
    }
    if( cur_tile_ != nullptr ) {
        cur_tile_->update();
    }
}

void LabyrinthEditorWidget::set_nb_rows( int nb_rows ) {
    if( lab_ == nullptr ) {
        return;
    }

    lab_->set_nb_rows( nb_rows );
    fill_scene();
}

void LabyrinthEditorWidget::set_nb_cols( int nb_cols ) {
    if( lab_ == nullptr ) {
        return;
    }

    lab_->set_nb_cols( nb_cols );
    fill_scene();
}

void LabyrinthEditorWidget::set_wall_left( bool /*set*/ ) {
    if( lab_ == nullptr ) {
        return;
    }

    //QTableWidgetItem* item = ui_->tableLabyrinth->currentItem();
}

void LabyrinthEditorWidget::set_wall_right( bool /*set*/ ) {
    if( lab_ == nullptr ) {
        return;
    }

    //QTableWidgetItem* item = ui_->tableLabyrinth->currentItem();
}

void LabyrinthEditorWidget::set_wall_top( bool /*set*/ ) {
    if( lab_ == nullptr ) {
        return;
    }

    //QTableWidgetItem* item = ui_->tableLabyrinth->currentItem();
}

void LabyrinthEditorWidget::set_wall_bottom( bool /*set*/ ) {
    if( lab_ == nullptr ) {
        return;
    }

    //QTableWidgetItem* item = ui_->tableLabyrinth->currentItem();
}

/******************************************************************************/

}
