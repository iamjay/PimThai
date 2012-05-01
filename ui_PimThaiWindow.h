#ifndef UI_PIMTHAIWINDOW_H
#define UI_PIMTHAIWINDOW_H

#include <QtGui>

class JKeyboard;

class ui_PimThaiWindow
{
public:
    void setupUi(QMainWindow *window);

    QPushButton *copy;
    QTextEdit *edit;
    JKeyboard *keyboard;
};

#endif
