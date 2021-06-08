#include "widget.h"

#include <QApplication>
//C++ version (11/14)
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AudioPlayer w;
    w.show();
    return a.exec();
}
