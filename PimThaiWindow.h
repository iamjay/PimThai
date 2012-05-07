#ifndef PIMTHAIWINDOW_H
#define PIMTHAIWINDOW_H

#include <QMainWindow>

#include "ui_PimThaiWindow.h"

class PimThaiWindow : public QMainWindow,
    private Ui::PimThaiWindow
{
    Q_OBJECT

public:
    PimThaiWindow(QWidget *parent = 0);

private slots:
    void copyToClipboard();
};

#endif
