#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "QDialog"

#include "ui_About.h"

class QWidget;

class AboutDialog : public QDialog,
        private Ui::About
{
    Q_OBJECT

public:
    AboutDialog(QWidget *parent = 0);

private:
    static const char *aboutText;
};

#endif
