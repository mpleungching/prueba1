#include <QApplication>
#include "MazeWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    MazeWidget w;
    w.show();

    return a.exec();
}
