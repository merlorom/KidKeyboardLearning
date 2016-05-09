#include "ui/main_window.h"

#include <QApplication>
#include <iostream>

int main( int argc, char** argv ) {
    QApplication app( argc, argv );

    KeyLabyrinth::MainWindow mw;
    mw.show();

    return app.exec();
}
