#include <QtGui>

#if __QNX__
#include <clipboard/clipboard.h>
#endif

#include "PimThaiWindow.h"

#include "AboutDialog.h"
#include "MenuBar.h"

const char *PimThaiWindow::activeBufferKey = "activeBuffer";
const char *PimThaiWindow::buffer0Key = "buffer0";
const char *PimThaiWindow::buffer1Key = "buffer1";
const char *PimThaiWindow::buffer2Key = "buffer2";
const char *PimThaiWindow::buffer3Key = "buffer3";
const char *PimThaiWindow::predictionEnabledKey = "predict";
const char *PimThaiWindow::autoCopyEnabledKey = "autoCopy";

PimThaiWindow::PimThaiWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    menuBar = new MenuBar(this);
    toaster = new Toaster(this);

    keyboard = new JKeyboard(textEdit);
    QVBoxLayout *l = static_cast<QVBoxLayout *>(mainContainer->layout());
    l->addWidget(keyboard->getPredictionWidget());

    verticalLayout->addWidget(keyboard, 3);

    textEdit->setFocus();
    setFocusProxy(textEdit);

    bufferButtons[0] = buf0Button;
    bufferButtons[1] = buf1Button;
    bufferButtons[2] = buf2Button;
    bufferButtons[3] = buf3Button;

    connect(menuBar->aboutButton, SIGNAL(clicked()), this, SLOT(aboutClicked()));
    connect(menuBar->predictionButton, SIGNAL(clicked(bool)), this, SLOT(predictToggleClicked(bool)));
    connect(menuBar->autoCopyButton, SIGNAL(clicked(bool)), this, SLOT(autoCopyClicked(bool)));
    connect(copyButton, SIGNAL(clicked()), this, SLOT(copyToClipboard()));
    connect(clearButton, SIGNAL(clicked()), this, SLOT(clearBuffer()));
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
    autoCopyEnabled = settingsDb.value(autoCopyEnabledKey, true).toBool();

    updateBuffer(bufferButtons[activeBuffer]);
    predictToggleClicked(predictionEnabled);
}

PimThaiWindow::~PimThaiWindow()
{
    saveSettings();
}

void PimThaiWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Menu || event->key() == Qt::Key_Escape) {
        menuBar->predictionButton->setChecked(predictionEnabled);
        menuBar->autoCopyButton->setChecked(autoCopyEnabled);

        menuBar->move(mapToGlobal(QPoint(0, 0)));
        menuBar->resize(width(), -1);
        menuBar->show();
    }
}

void PimThaiWindow::changeEvent(QEvent *event)
{
    if (event->type() == QEvent::ActivationChange) {
        if (autoCopyEnabled && !isActiveWindow()) {
            const QByteArray s = textEdit->toPlainText().toUtf8();

#if __QNX__
            set_clipboard_data("text/plain", s.size(), s.constData());
#endif
        }
    }
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
    settingsDb.setValue(autoCopyEnabledKey, autoCopyEnabled);
}

void PimThaiWindow::resizeEvent(QResizeEvent *event)
{
    menuBar->hide();

    if (event->size().height() >= 1024)
        verticalLayout->setStretchFactor(keyboard, 2);
    else
        verticalLayout->setStretchFactor(keyboard, 3);
}

void PimThaiWindow::aboutClicked()
{
    menuBar->hide();

    AboutDialog d;
    d.setModal(true);
#if __QNX__
    d.showMaximized();
#endif
    d.exec();
    activateWindow();
}

void PimThaiWindow::autoCopyClicked(bool enabled)
{
    menuBar->hide();

    autoCopyEnabled = enabled;
}

void PimThaiWindow::clearBuffer()
{
    textEdit->clear();
    keyboard->clearCompose();
}

void PimThaiWindow::copyToClipboard()
{
#if __QNX__
    const QByteArray s = textEdit->toPlainText().toUtf8();

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
            textEdit->setPlainText(buffers[i]);
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
    menuBar->hide();

    predictionEnabled = enabled;
    keyboard->predictToggleClicked(enabled);
}
