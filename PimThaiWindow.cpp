#include <QtGui>

#ifdef __QNX__
#include <clipboard/clipboard.h>
#endif

#include "PimThaiWindow.h"
#include "JKeyboard.h"

PimThaiWindow::PimThaiWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);
    JKeyboard *keyboard = new JKeyboard();
    centralwidget->layout()->addWidget(keyboard);

    QEvent event(QEvent::CloseSoftwareInputPanel);
    QApplication::sendEvent(textEdit, &event);

    textEdit->setFocus();
    setFocusProxy(textEdit);

    connect(copyButton, SIGNAL(clicked()), this, SLOT(copyToClipboard()));
}

void PimThaiWindow::copyToClipboard()
{
    const QByteArray s = textEdit->toPlainText().toUtf8();

#if __QNX__
    set_clipboard_data("text/plain", s.size(), s.constData());
#endif
}
