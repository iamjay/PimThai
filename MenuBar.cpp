#include <QtGui>

#include "MenuBar.h"

MenuBar::MenuBar(QWidget *parent) :
    QWidget(parent, Qt::Popup)
{
    hide();
    setupUi(this);
}

#if __QNX__
bool MenuBar::event(QEvent *event)
{
    if (event->type() == QEvent::Hide)
        parentWidget()->activateWindow();

    return QWidget::event(event);
}
#endif
