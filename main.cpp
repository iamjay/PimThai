#include <QApplication>

#include "PimThaiWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PimThaiWindow window;
    window.showMaximized();

    return a.exec();
}
