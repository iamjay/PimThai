#ifndef PIMTHAIWINDOW_H
#define PIMTHAIWINDOW_H

#include <QMainWindow>

#include "ui_PimThaiWindow.h"

#include "JKeyboard.h"

class PimThaiWindow : public QMainWindow,
    private Ui::PimThaiWindow
{
    Q_OBJECT

public:
    PimThaiWindow(QWidget *parent = 0);

protected:
    enum {
        MAX_BUFFER = 4
    };

    JKeyboard *keyboard;
    int activeBuffer;
    QString buffers[MAX_BUFFER];
    QPushButton *bufferButtons[MAX_BUFFER];

    void updateBuffer(QPushButton *button);

private slots:
    void clearBuffer();
    void copyToClipboard();
    void bufferButtonClicked();
};

#endif
