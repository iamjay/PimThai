/*
 * Copyright (c) 2012 Pathompong Puengrostham <pathompong@gmail.com>
 *
 * This file is part of PimThai.
 *
 * PimThai is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3 of the License.
 *
 * PimThai is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PimThai.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtCore>

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
