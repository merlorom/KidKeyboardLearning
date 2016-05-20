#include "ui/main_window.h"
#include "ui/editor.h"

#include <QApplication>

#include <iostream>
#include <memory>

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    std::unique_ptr<KeyLabyrinth::MainWindow> mw;
    std::unique_ptr<KeyLabyrinth::LabyrinthEditor> editor;
    if( argc > 1 ) {
        if( std::string( argv[1] ) == "-editor" ) {
            editor.reset( new KeyLabyrinth::LabyrinthEditor() );
            editor->show();
        } else {
            std::cout << "KeyLabyrinth program -- Usage" << std::endl;
            std::cout << "  [empty]      Opens the main window" << std::endl;
            std::cout << "  -editor      Opens a labyrinth editor" << std::endl;
            return 0;
        }
    } else {
        mw.reset( new KeyLabyrinth::MainWindow() );
        mw->show();
    }

    return app.exec();
}
