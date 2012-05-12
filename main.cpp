#include <QtCore>
#include <QtSql>

#include "PimThaiWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if __QNX__
    QFontDatabase::addApplicationFont("app/native/fonts/Garuda.ttf");
#else
    QFontDatabase::addApplicationFont("/home/jay/Jay/Programming/BlackBerry/PimThai/Garuda.ttf");
#endif

    QFontDatabase fdb;
    a.setFont(fdb.font("Garudax", "normal", 14));

    PimThaiWindow window;
#if __QNX__
    window.showMaximized();
#else
    window.show();
#endif

    return a.exec();
}
