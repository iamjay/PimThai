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

    keyboard = new JKeyboard();
    centralwidget->layout()->addWidget(keyboard);

    QEvent event(QEvent::CloseSoftwareInputPanel);
    QApplication::sendEvent(textEdit, &event);

    textEdit->setFocus();
    setFocusProxy(textEdit);

    activeBuffer = 0;
    bufferButtons[0] = buf0Button;
    bufferButtons[1] = buf1Button;
    bufferButtons[2] = buf2Button;
    bufferButtons[3] = buf3Button;

    connect(copyButton, SIGNAL(clicked()), this, SLOT(copyToClipboard()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearBuffer()));
    connect(predictButton, SIGNAL(toggled(bool)), keyboard, SLOT(predictToggleClicked(bool)));
    connect(buf0Button, SIGNAL(clicked()), this, SLOT(bufferButtonClicked()));
    connect(buf1Button, SIGNAL(clicked()), this, SLOT(bufferButtonClicked()));
    connect(buf2Button, SIGNAL(clicked()), this, SLOT(bufferButtonClicked()));
    connect(buf3Button, SIGNAL(clicked()), this, SLOT(bufferButtonClicked()));

    updateBuffer(bufferButtons[activeBuffer]);
}

void PimThaiWindow::clearBuffer()
{
    textEdit->clear();
    keyboard->clearCompose();
}

void PimThaiWindow::copyToClipboard()
{
    const QByteArray s = textEdit->toPlainText().toUtf8();

#if __QNX__
    set_clipboard_data("text/plain", s.size(), s.constData());
#endif
}

void PimThaiWindow::updateBuffer(QPushButton *button)
{
    buffers[activeBuffer] = textEdit->toPlainText();

    for (int i = 0; i < MAX_BUFFER; ++i) {
        if (button == bufferButtons[i]) {
            activeBuffer = i;
            textEdit->setText(buffers[i]);
            bufferButtons[i]->setChecked(true);
        } else {
            bufferButtons[i]->setChecked(false);
        }
    }
    keyboard->clearCompose();
}

void PimThaiWindow::bufferButtonClicked()
{
    updateBuffer(static_cast<QPushButton *>(QObject::sender()));
}
