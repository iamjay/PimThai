/*
 * Copyright (c) 2012 Pathompong Puengrostham <pathompong@gmail.com>
 *
 * This file is part of PimThai.
 *
 * PimThai is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation version 3 of the License.
 *
 * PimThai is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PimThai.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <QtGui>

#include <QDebug>

#if Q_OS_BLACKBERRY
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

    QVBoxLayout *l = static_cast<QVBoxLayout *>(mainContainer->layout());

    textEditView = new QDeclarativeView;
    textEditView->setResizeMode(QDeclarativeView::SizeRootObjectToView);
    textEditView->setSource(QUrl("qrc:/qml/textedit.qml"));
    textEditView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    textEdit = textEditView->rootObject();
    l->addWidget(textEditView, 1);

    keyboard = new JKeyboard(textEditView);
    l->addWidget(keyboard->getPredictionWidget());

    verticalLayout->addWidget(keyboard, 3);

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
        QClipboard *cb = QApplication::clipboard();

        if (autoCopyEnabled && !isActiveWindow()) {
            QString s = textEdit->property("selectedText").toString();
            if (s.length() == 0)
                s = textEdit->property("text").toString();
            cb->setText(s);
        }

        if (isActiveWindow()) {
            cb->setText(JKeyboard::codec->fromUnicode(cb->text()));
        } else {
            QString s = JKeyboard::codec->toUnicode(cb->text().toLatin1());
#if Q_OS_BLACKBERRY
            const QByteArray buf = s.toUtf8();
            set_clipboard_data("text/plain", buf.size(), buf.constData());
            set_clipboard_data("text/html", buf.size(), buf.constData());
#else
            cb->setText(s);
#endif
        }
    }
}

void PimThaiWindow::saveSettings()
{
    buffers[activeBuffer] = textEdit->property("text").toString();

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
#if Q_OS_BLACKBERRY
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
    textEdit->setProperty("text", "");
    keyboard->clearCompose();
}

void PimThaiWindow::copyToClipboard()
{
    QString s = textEdit->property("selectedText").toString();
    if (s.length() == 0)
        s = textEdit->property("text").toString();

    QClipboard *cb = QApplication::clipboard();
    cb->setText(s);

    QSize ts = textEditView->size();
    QPoint p = textEditView->pos();
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
            textEdit->setProperty("text", buffers[i]);
            bufferButtons[i]->setChecked(true);
        } else {
            bufferButtons[i]->setChecked(false);
        }
    }
    keyboard->clearCompose();
}

void PimThaiWindow::bufferButtonClicked()
{
    buffers[activeBuffer] = textEdit->property("text").toString();
    updateBuffer(static_cast<QToolButton *>(QObject::sender()));
}

void PimThaiWindow::predictToggleClicked(bool enabled)
{
    menuBar->hide();

    predictionEnabled = enabled;
    keyboard->predictToggleClicked(enabled);
}
