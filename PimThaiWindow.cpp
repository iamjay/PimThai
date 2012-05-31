#include <QtGui>

#if __QNX__
#include <clipboard/clipboard.h>
#endif

#include "PimThaiWindow.h"

#include "AboutDialog.h"

const char *PimThaiWindow::activeBufferKey = "activeBuffer";
const char *PimThaiWindow::buffer0Key = "buffer0";
const char *PimThaiWindow::buffer1Key = "buffer1";
const char *PimThaiWindow::buffer2Key = "buffer2";
const char *PimThaiWindow::buffer3Key = "buffer3";
const char *PimThaiWindow::predictionEnabledKey = "predict";

PimThaiWindow::PimThaiWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    toaster = new Toaster(this);

    keyboard = new JKeyboard();
    QVBoxLayout *l = static_cast<QVBoxLayout *>(mainContainer->layout());
    l->addWidget(keyboard->getPredictionWidget());

    verticalLayout->addWidget(keyboard, 3);

    textEdit->setFocus();
    setFocusProxy(textEdit);

    bufferButtons[0] = buf0Button;
    bufferButtons[1] = buf1Button;
    bufferButtons[2] = buf2Button;
    bufferButtons[3] = buf3Button;

    connect(aboutButton, SIGNAL(clicked()), this, SLOT(aboutClicked()));
    connect(copyButton, SIGNAL(clicked()), this, SLOT(copyToClipboard()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearBuffer()));
    connect(predictButton, SIGNAL(toggled(bool)), this, SLOT(predictToggleClicked(bool)));
    connect(buf0Button, SIGNAL(clicked()), this, SLOT(bufferButtonClicked()));
    connect(buf1Button, SIGNAL(clicked()), this, SLOT(bufferButtonClicked()));
    connect(buf2Button, SIGNAL(clicked()), this, SLOT(bufferButtonClicked()));
    connect(buf3Button, SIGNAL(clicked()), this, SLOT(bufferButtonClicked()));

    activeBuffer = settingsDb.value(activeBufferKey, 0).toInt();
    buffers[0] = settingsDb.value(buffer0Key, "").toString();
    buffers[1] = settingsDb.value(buffer1Key, "").toString();
    buffers[2] = settingsDb.value(buffer2Key, "").toString();
    buffers[3] = settingsDb.value(buffer3Key, "").toString();
    predictionEnabled = settingsDb.value(predictionEnabledKey, true).toBool();

    predictButton->setChecked(predictionEnabled);
    updateBuffer(bufferButtons[activeBuffer]);
    predictToggleClicked(predictionEnabled);
}

PimThaiWindow::~PimThaiWindow()
{
    saveSettings();
}

void PimThaiWindow::saveSettings()
{
    buffers[activeBuffer] = textEdit->toPlainText();

    settingsDb.setValue(activeBufferKey, activeBuffer);
    settingsDb.setValue(buffer0Key, buffers[0]);
    settingsDb.setValue(buffer1Key, buffers[1]);
    settingsDb.setValue(buffer2Key, buffers[2]);
    settingsDb.setValue(buffer3Key, buffers[3]);
    settingsDb.setValue(predictionEnabledKey, predictionEnabled);
}

void PimThaiWindow::resizeEvent(QResizeEvent *event)
{
    if (event->size().height() >= 1024)
        verticalLayout->setStretchFactor(keyboard, 2);
    else
        verticalLayout->setStretchFactor(keyboard, 3);
}

void PimThaiWindow::aboutClicked()
{
    AboutDialog d;
    d.setModal(true);
#if __QNX__
    d.showMaximized();
#endif
    d.exec();
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

    QSize ts = textEdit->size();
    QPoint p = textEdit->pos();
    p.rx() += ts.width() / 2;
    p.ry() += ts.height() / 2;
    p = mapToGlobal(p);
    toaster->showToast(p, "Text is copied");
}

void PimThaiWindow::updateBuffer(QToolButton *button)
{
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
    buffers[activeBuffer] = textEdit->toPlainText();
    updateBuffer(static_cast<QToolButton *>(QObject::sender()));
}

void PimThaiWindow::predictToggleClicked(bool enabled)
{
    predictionEnabled = enabled;
    keyboard->predictToggleClicked(enabled);
}
