#include <QtGui>

#include <stdlib.h>

#include "PacmanWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    PacmanWindow window;
    window.show();
    return app.exec();
}
