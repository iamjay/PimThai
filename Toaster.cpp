#include <QtGui>

#include "Toaster.h"

Toaster::Toaster(QWidget *parent)
    : QWidget(parent, Qt::ToolTip | Qt::FramelessWindowHint)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("QLabel { font-size: 12pt; border-radius: 8px; border: 2px solid white; color: white; background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #559BBF, stop: 0.6 #3895D2, stop:1 #3381C3); padding: 4px; }");

    QHBoxLayout *hbox = new QHBoxLayout();
    setLayout(hbox);

    label = new QLabel();
    hbox->addWidget(label);
}

void Toaster::showToast(QPoint &p, const QString &text)
{
    label->setText(text);
    show();

    QSize s = size();
    p.rx() -= s.width() / 2;
    p.ry() -= s.height() / 2;
    move(p);

    QTimer::singleShot(800, this, SLOT(toastTimeout()));
}

void Toaster::toastTimeout()
{
    hide();
}
