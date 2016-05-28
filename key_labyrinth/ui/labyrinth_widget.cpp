#include "labyrinth_widget.h"
#include "tile_item.h"

#include <core/labyrinth.h>

#include <QGridLayout>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>

namespace KeyLabyrinth {

/******************************************************************************/

LabyrinthWidget::LabyrinthWidget( QWidget* parent ) :
    QWidget( parent ),
    lab_( nullptr ),
    scene_( nullptr ),
    view_( nullptr )
{}

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
    scene_ = create_scene(); //new QGraphicsScene( this );

    view_ = new QGraphicsView( scene_, this );
    view_->show();
    QGridLayout* layout = new QGridLayout;
    layout->addWidget(view_,0,0);
    layout->setContentsMargins( 0, 0, 0, 0 );
    setLayout(layout);
}

TileItem* LabyrinthWidget::tile_at( size_t tile_row, size_t tile_col ) const {
    for( QGraphicsItem* item : scene_->items() ) {
        TileItem* tile = dynamic_cast<TileItem*>( item );
        if( tile == nullptr ) {
            continue;
        }
        if( tile->tile_row() == tile_row && tile->tile_col() == tile_col ) {
            return tile;
        }
    }
    return nullptr;
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
            tile_item->setPos( j*tile_size(), i*tile_size() );
            scene_->addItem( tile_item );
        }
    }
    scene_->setSceneRect( scene_->itemsBoundingRect() );
}

/******************************************************************************/

LabyrinthEditorWidget::LabyrinthEditorWidget( QWidget* parent ) :
    LabyrinthWidget( parent )
{
}

LabyrinthEditorWidget::~LabyrinthEditorWidget() {
}

TileItem* LabyrinthEditorWidget::create_tile( size_t tile_row, size_t tile_col ) const {
    return new TileEditorItem( *this, tile_row, tile_col );
}

QGraphicsScene* LabyrinthEditorWidget::create_scene() {
    LabyrinthEditorWidgetScene* scene = new LabyrinthEditorWidgetScene( this );
    connect( scene, SIGNAL(move_left_pressed()), this, SLOT(move_left()) );
    connect( scene, SIGNAL(move_right_pressed()), this, SLOT(move_right()) );
    connect( scene, SIGNAL(move_up_pressed()), this, SLOT(move_up()) );
    connect( scene, SIGNAL(move_down_pressed()), this, SLOT(move_down()) );
    return scene;
}

QList<TileEditorItem*> LabyrinthEditorWidget::selected_tiles() const {
    return static_cast<LabyrinthEditorWidgetScene*>( scene_ )->selected_tiles();
}

TileEditorItem* LabyrinthEditorWidget::first_selected_tile() const {
    if( lab_ == nullptr ) {
        return nullptr;
    }

    QList<TileEditorItem*> tile_items = selected_tiles();
    if( tile_items.empty() ) {
        return nullptr;
    }
    return tile_items.at( 0 );
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

void LabyrinthEditorWidget::set_wall_left( bool set ) {
    if( lab_ == nullptr ) {
        return;
    }

    QList<TileEditorItem*> tile_items = selected_tiles();
    for( TileEditorItem* tile_item : tile_items ) {
        tile_item->tile()->set_wall( Tile::Left, set );
        tile_item->update();
    }
}

void LabyrinthEditorWidget::set_wall_right( bool set ) {
    if( lab_ == nullptr ) {
        return;
    }

    QList<TileEditorItem*> tile_items = selected_tiles();
    for( TileEditorItem* tile_item : tile_items ) {
        tile_item->tile()->set_wall( Tile::Right, set );
        tile_item->update();
    }
}

void LabyrinthEditorWidget::set_wall_top( bool set ) {
    if( lab_ == nullptr ) {
        return;
    }

    QList<TileEditorItem*> tile_items = selected_tiles();
    for( TileEditorItem* tile_item : tile_items ) {
        tile_item->tile()->set_wall( Tile::Top, set );
        tile_item->update();
    }
}

void LabyrinthEditorWidget::set_wall_bottom( bool set ) {
    if( lab_ == nullptr ) {
        return;
    }

    QList<TileEditorItem*> tile_items = selected_tiles();
    for( TileEditorItem* tile_item : tile_items ) {
        tile_item->tile()->set_wall( Tile::WallDir::Bottom, set );
        tile_item->update();
    }
}

void LabyrinthEditorWidget::set_character( QChar c ) {
    if( lab_ == nullptr || !c.isPrint() ) {
        return;
    }

    QList<TileEditorItem*> tile_items = selected_tiles();
    for( TileEditorItem* tile_item : tile_items ) {
        tile_item->tile()->set_key( c.toAscii() );
        tile_item->update();
    }
}

void LabyrinthEditorWidget::move_at( TileItem* from_tile, size_t row, size_t col ) {
    scene_->clearSelection();
    TileItem* to_tile = tile_at( row, col );
    if( to_tile == nullptr ) {
        to_tile = from_tile;
    }
    if( to_tile != nullptr ) {
        to_tile->setSelected( true );
    }
}

void LabyrinthEditorWidget::move_left() {
    TileItem* tile = first_selected_tile();
    if( tile == nullptr ) {
        return;
    }
    move_at( tile, tile->tile_row(), tile->tile_col() - 1 );
}

void LabyrinthEditorWidget::move_right() {
    TileItem* tile = first_selected_tile();
    if( tile == nullptr ) {
        return;
    }
    move_at( tile, tile->tile_row(), tile->tile_col() + 1 );
}

void LabyrinthEditorWidget::move_up() {
    TileItem* tile = first_selected_tile();
    if( tile == nullptr ) {
        return;
    }
    move_at( tile, tile->tile_row() - 1, tile->tile_col() );
}

void LabyrinthEditorWidget::move_down() {
    TileItem* tile = first_selected_tile();
    if( tile == nullptr ) {
        return;
    }
    move_at( tile, tile->tile_row() + 1, tile->tile_col() );
}

/******************************************************************************/

LabyrinthEditorWidgetScene::LabyrinthEditorWidgetScene( QWidget* parent ) :
    QGraphicsScene( parent )
{}

QList<TileEditorItem*> LabyrinthEditorWidgetScene::selected_tiles() const {
    QList<TileEditorItem*> tiles;
    for( QGraphicsItem* item : selectedItems() ) {
        TileEditorItem* tile = dynamic_cast<TileEditorItem*>( item );
        if( tile == nullptr ) {
            continue;
        }
        tiles.append( tile );
    }
    return tiles;
}

void LabyrinthEditorWidgetScene::mousePressEvent( QGraphicsSceneMouseEvent* event ) {
    // multi selection
    TileEditorItem* tile1 = dynamic_cast<TileEditorItem*>( itemAt( event->scenePos() ) );
    QList<TileEditorItem*> tiles = selected_tiles();
    if( tile1 != nullptr && !tiles.empty() && event->modifiers().testFlag( Qt::ShiftModifier ) ) {
        TileEditorItem* tile0 = tiles.first();
        size_t min_row = std::min( tile0->tile_row(), tile1->tile_row() );
        size_t max_row = std::max( tile0->tile_row(), tile1->tile_row() );
        size_t min_col = std::min( tile0->tile_col(), tile1->tile_col() );
        size_t max_col = std::max( tile0->tile_col(), tile1->tile_col() );
        for( QGraphicsItem* item : items() ) {
            TileEditorItem* tile = dynamic_cast<TileEditorItem*>( item );
            if( tile == nullptr ) {
                continue;
            }
            if( tile->tile_row() < min_row || tile->tile_row() > max_row ||
                tile->tile_col() < min_col || tile->tile_col() > max_col
            ) {
                continue;
            }
            tile->setSelected( true );
        }
        event->accept();
        return;
    }

    QGraphicsScene::mousePressEvent( event );
}

void LabyrinthEditorWidgetScene::keyPressEvent( QKeyEvent* event ) {
    if( event->key() == Qt::Key_Left ) {
        emit move_left_pressed();
        event->accept();
        return;
    }
    if( event->key() == Qt::Key_Right ) {
        emit move_right_pressed();
        event->accept();
        return;
    }
    if( event->key() == Qt::Key_Up ) {
        emit move_up_pressed();
        event->accept();
        return;
    }
    if( event->key() == Qt::Key_Down ) {
        emit move_down_pressed();
        event->accept();
        return;
    }

    QGraphicsScene::keyPressEvent( event );
}

/******************************************************************************/

}
