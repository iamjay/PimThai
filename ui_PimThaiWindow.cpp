#include <QtGui>

#include "ui_PimThaiWindow.h"

#include "JKeyboard.h"

void ui_PimThaiWindow::setupUi(QMainWindow *window)
{
    QWidget *widget = new QWidget();

    QVBoxLayout *vbox = new QVBoxLayout(widget);

    QHBoxLayout *hbox = new QHBoxLayout();
    vbox->addLayout(hbox);

    QLabel *label = new QLabel(QObject::tr("PimThai"));
    hbox->addWidget(label);
    hbox->addStretch(1);
    copy = new QPushButton(QObject::tr("Copy"));
    hbox->addWidget(copy);

    edit = new QTextEdit();
    edit->setFontPointSize(14);
    vbox->addWidget(edit, 1);

    keyboard = new JKeyboard();
    vbox->addWidget(keyboard);

    window->setCentralWidget(widget);

    QEvent event(QEvent::CloseSoftwareInputPanel);
    QApplication::sendEvent(edit, &event);
}
