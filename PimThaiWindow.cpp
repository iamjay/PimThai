#include <QtGui>

#ifdef __QNX__
#include <clipboard/clipboard.h>
#endif

#include "PimThaiWindow.h"

PimThaiWindow::PimThaiWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    edit->setFocus();
    setFocusProxy(edit);

    connect(copy, SIGNAL(clicked()), this, SLOT(copyToClipboard()));
}

void PimThaiWindow::copyToClipboard()
{
    const QByteArray s = edit->toPlainText().toUtf8();

#if __QNX__
    set_clipboard_data("text/plain", s.size(), s.constData());
#endif
}
