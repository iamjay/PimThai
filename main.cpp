#include <QtCore>
#include <QtSql>

#include "JDummyInputContext.h"
#include "PimThaiWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if __QNX__
    QFontDatabase::addApplicationFont("app/native/fonts/Garuda.ttf");
#else
    QFontDatabase::addApplicationFont("Garuda.ttf");
#endif

    a.setOrganizationName("kanokgems");
    a.setApplicationName("PimThai");
    a.setInputContext(new JDummyInputContext());

    PimThaiWindow window;
#if __QNX__
    window.showMaximized();
#else
    window.show();
#endif

    return a.exec();
}
