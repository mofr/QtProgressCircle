#include "DemoWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DemoWindow w;
    w.show();

    return a.exec();
}
