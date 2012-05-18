#include <QtCore>
#include <QtSql>

#if __QNX__
#include <stdbool.h>
#include <sys/platform.h>
#include "bps/navigator.h"
#endif

#include "JDummyInputContext.h"
#include "PimThaiWindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if __QNX__
    navigator_set_orientation(0, 0);
    navigator_rotation_lock(true);
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
