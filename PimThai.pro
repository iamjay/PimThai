##
## Copyright (c) 2012 Pathompong Puengrostham <pathompong@gmail.com>
##
## This file is part of PimThai.
##
## PimThai is free software: you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation version 3 of the License.
##
## PimThai is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with PimThai.  If not, see <http://www.gnu.org/licenses/>.
##

QT += sql

TEMPLATE = app
DEPENDPATH += .
INCLUDEPATH += .

SOURCES += \
    main.cpp \
    JKeyboard.cpp \
    PimThaiWindow.cpp \
    JDummyInputContext.cpp \
    KeyLayout.cpp \
    AboutDialog.cpp \
    Toaster.cpp \
    MenuBar.cpp \
    WorkaroundCodec.cpp

HEADERS += \
    JKeyboard.h \
    PimThaiWindow.h \
    JDummyInputContext.h \
    KeyLayout.h \
    AboutDialog.h \
    Toaster.h \
    MenuBar.h \
    WorkaroundCodec.h

FORMS += \
    PimThaiWindow.ui \
    About.ui \
    MenuBar.ui

OTHER_FILES += \
    bar-descriptor.xml \
    icon.png \
    dict.db \
    Garuda.ttf \
    splash.png

blackberry-armv7le-qcc {
    LIBS += -lclipboard
}

PACKAGE_OPT = \
    -arg -platform -arg blackberry \
    $${PWD}/bar-descriptor.xml PimThai \
    -e $${PWD}/icon.png icon.png \
    -e $${PWD}/splash.png splash.png \
    -e $${PWD}/dict.db dict.db \
    -e $${PWD}/Garuda.ttf fonts/Garuda.ttf \
    -e ${QTDIR}/lib/libQtCore.so.4 lib/libQtCore.so.4 \
    -e ${QTDIR}/lib/libQtGui.so.4 lib/libQtGui.so.4 \
    -e ${QTDIR}/lib/libQtOpenGL.so.4 lib/libQtOpenGL.so.4 \
    -e ${QTDIR}/lib/libQtNetwork.so.4 lib/libQtNetwork.so.4 \
    -e ${QTDIR}/lib/libQtSql.so.4 lib/libQtSql.so.4 \
    -e ${QTDIR}/plugins/platforms/libblackberry.so plugins/platforms/libblackberry.so \
    -e ${QTDIR}/plugins/sqldrivers/libqsqlite.so plugins/sqldrivers/libqsqlite.so

PACKAGE_DEPEND = \
    $${TARGET} $${PWD}/bar-descriptor.xml \
    $${TARGET} $${PWD}/icon.png \
    $${TARGET} $${PWD}/dict.db \
    $${TARGET} $${PWD}/Garuda.ttf \
    $${TARGET} $${PWD}/splash.png

package.target = $${TARGET}.bar
package.depends = $${PACKAGE_DEPEND}
package.commands = blackberry-nativepackager \
    -devMode -debugToken $${PWD}/debugtoken1.bar \
    -package $${TARGET}.bar \
    $${PACKAGE_OPT}

package-release.target = $${TARGET}-release.bar
package-release.depends = $${PACKAGE_DEPEND}
package-release.commands = blackberry-nativepackager \
    -package $${TARGET}-release.bar \
    $${PACKAGE_OPT}

QMAKE_EXTRA_TARGETS += package package-release

QMAKE_CLEAN += $${TARGET} $${TARGET}.bar

RESOURCES += \
    PimThai.qrc
