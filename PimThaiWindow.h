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

#ifndef PIMTHAIWINDOW_H
#define PIMTHAIWINDOW_H

#include <QDeclarativeView>
#include <QMainWindow>

#include "ui_PimThaiWindow.h"

#include "JKeyboard.h"
#include "MenuBar.h"
#include "Toaster.h"

class PimThaiWindow : public QMainWindow,
        private Ui::PimThaiWindow
{
    Q_OBJECT

public:
    static const char *activeBufferKey;
    static const char *buffer0Key;
    static const char *buffer1Key;
    static const char *buffer2Key;
    static const char *buffer3Key;
    static const char *predictionEnabledKey;
    static const char *autoCopyEnabledKey;

    PimThaiWindow(QWidget *parent = 0);
    ~PimThaiWindow();

    void resizeEvent(QResizeEvent *);

private:
    enum {
        MAX_BUFFER = 4
    };

    QDeclarativeView *textEditView;
    QObject *textEdit;
    MenuBar *menuBar;
    Toaster *toaster;
    QSettings settingsDb;
    JKeyboard *keyboard;
    int activeBuffer;
    QString buffers[MAX_BUFFER];
    QToolButton *bufferButtons[MAX_BUFFER];
    bool predictionEnabled;
    bool autoCopyEnabled;

    void changeEvent(QEvent *event);
    void keyPressEvent(QKeyEvent *event);

    void saveSettings();
    void updateBuffer(QToolButton *button);

private slots:
    void aboutClicked();
    void autoCopyClicked(bool enabled);
    void clearBuffer();
    void copyToClipboard();
    void bufferButtonClicked();
    void predictToggleClicked(bool enabled);
};

#endif
