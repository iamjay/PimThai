#ifndef MAINMENUBAR_H
#define MAINMENUBAR_H

#include "ui_MenuBar.h"

class MenuBar : public QWidget, public Ui::MenuBar
{
    Q_OBJECT
    
public:
    explicit MenuBar(QWidget *parent = 0);

protected:
#if __QNX__
    bool event(QEvent *event);
#endif
};

#endif
