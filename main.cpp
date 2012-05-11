#include <QtCore>
#include <QtSql>

#include "PimThaiWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PimThaiWindow window;
#if __QNX__
    window.showMaximized();
#else
    window.show();
#endif

    return a.exec();
}
