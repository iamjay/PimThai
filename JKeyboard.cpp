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

#include "JKeyboard.h"

QTextCodec *JKeyboard::codec = 0;

JKey::JKey(const KeyData *key, QWidget *parent)
    : QPushButton(parent)
    , keyData(key)
{
#if 1
    QFontDatabase fdb;
    setFont(fdb.font("Garudax", "normal", 14));

    text = QString::fromLatin1(JKeyboard::codec->fromUnicode(QString::fromUtf8(keyData->text)));
    altText = QString::fromLatin1(JKeyboard::codec->fromUnicode(QString::fromUtf8(keyData->altText)));
    if (keyData->altOffset)
        altPaintText = " ";
    altPaintText += altText;
#else
    text = QString::fromUtf8(keyData->text);
    if (keyData->altOffset)
        altText = " ";
    altText += QString::fromUtf8(keyData->altText);
#endif

    setObjectName("key");
    setText(text);

    if (text == "&&")
        text = "&";

    if (keyData->icon) {
        setIcon(QIcon(keyData->icon));
        setIconSize(QSize(36, 36));
        setStyleSheet("* { background-color: #404040; }"
                      "*:pressed { background-color: #00D5FF; }");
    }
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);

    if (key->keyCode == Qt::Key_Meta)
        setDown(true);
}

int JKey::getKeyCode(bool alt) const
{
    return alt ? keyData->altKeyCode : keyData->keyCode;
}

const QString &JKey::getText(bool alt) const
{
    return alt ? altText : text;
}

void JKey::paintEvent(QPaintEvent *pe)
{
    QPushButton::paintEvent(pe);

    QPainter p(this);
    QPen pen = p.pen();
    pen.setColor(QColor::fromRgb(160, 160, 160));
    p.setPen(pen);

    p.drawStaticText(10, keyData->altOffset * 10 - 10, altPaintText);
}

JKeyboardLayout::JKeyboardLayout(JKeyboard *receiver, const KeyLayout *layout,
                                 QWidget *parent)
    : QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setContentsMargins(0, 0, 0, 0);
    vbox->setSpacing(2);

    for (int i = 0; i < layout->numRow; ++i) {
        QHBoxLayout *hbox = new QHBoxLayout();
        KeyData *row = layout->rows[i];

        hbox->setContentsMargins(0, 0, 0, 0);
        hbox->setSpacing(2);

        for (KeyData *key = row; key->width; ++key) {
            if (key->keyCode >= 0) {
                JKey *k = new JKey(key);

                hbox->addWidget(k, key->width);
                connect(k, SIGNAL(pressed()), receiver, SLOT(keyPressed()));
                connect(k, SIGNAL(released()), receiver, SLOT(keyReleased()));
            } else {
                hbox->addStretch(key->width);
            }
        }

        vbox->addLayout(hbox);
    }
}

PredictionContainer::PredictionContainer(QWidget *parent)
    : QScrollArea(parent)
{
    setFocusPolicy(Qt::NoFocus);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
    setWidgetResizable(true);
    setFrameShape(QFrame::NoFrame);
    setLineWidth(0);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setStyleSheet("background-color: black; margin: 0px; padding: 0px; padding-left: 4px;");
    setAlignment(Qt::AlignVCenter);
}

QSize PredictionContainer::minimumSizeHint() const
{
    return QSize(0, 52);
}

JKeyboard::JKeyboard(QPlainTextEdit *receiver, QWidget *parent)
    : QWidget(parent)
{
    if (codec == 0)
        codec = QTextCodec::codecForName("TIS-620A");

    this->receiver = receiver;
    holdTimer.setSingleShot(true);
    currentLang = THAI;
    shifted = false;
    shiftLocked = false;
    symbolActive = false;
    predictionEnabled = false;

    dictDb = QSqlDatabase::addDatabase("QSQLITE", "dict");
    engDictDb = QSqlDatabase::addDatabase("QSQLITE", "eng_dict");
#if __QNX__
    dictDb.setDatabaseName("app/native/dict.db");
    engDictDb.setDatabaseName("app/native/eng_dict.db");
#else
    dictDb.setDatabaseName("dict.db");
    engDictDb.setDatabaseName("eng_dict.db");
#endif
    dictDb.open();
    engDictDb.open();

    setStyleSheet("QPushButton#key { font-size: 19pt; border-radius: 6px; color: white; background-color: black; }"
                  "QPushButton#key:pressed { border-radius: 6px; background-color: #00D5FF; }");

    QHBoxLayout *hbox = new QHBoxLayout();
    hbox->setContentsMargins(0, 0, 0, 0);
    hbox->setSpacing(0);

    QWidget *w = new QWidget();
    w->setLayout(hbox);

    predictionWidget = new PredictionContainer();
    predictionWidget->setWidget(w);

    for (int i = 0; i < MAX_PREDICTION; ++i) {
        QPushButton *button = new QPushButton();

        button->hide();
        button->setFocusPolicy(Qt::NoFocus);
        button->setStyleSheet("font-family: Garudax; font-size: 13pt; border-radius: 4px; border: 1px solid orange; color: darkorange; padding: 3px 6px 0px 6px; margin: 0px 4px 0px 4px;");
        button->setContentsMargins(0, 8, 0, 8);
        hbox->addWidget(button);

        predictButton.append(button);
        connect(button, SIGNAL(clicked()), this, SLOT(predictWordClicked()));
    }
    hbox->addStretch(1);

    stacked = new QStackedLayout();
    QVBoxLayout *vbox = new QVBoxLayout(this);
    vbox->setMargin(4);
    vbox->addLayout(stacked, 1);

    thai = new JKeyboardLayout(this, &thaiKeys);
    thaiShifted = new JKeyboardLayout(this, &thaiShiftedKeys);
    qwerty = new JKeyboardLayout(this, &qwertyKeys);
    qwertyShifted = new JKeyboardLayout(this, &qwertyShiftedKeys);
    symbol = new JKeyboardLayout(this, &symbolKeys);
    symbolShifted = new JKeyboardLayout(this, &symbolShiftedKeys);

    stacked->addWidget(thai);
    stacked->addWidget(thaiShifted);
    stacked->addWidget(qwerty);
    stacked->addWidget(qwertyShifted);
    stacked->addWidget(symbol);
    stacked->addWidget(symbolShifted);

    connect(&holdTimer, SIGNAL(timeout()), this, SLOT(holdTimeout()));

    setShift(shifted);
    predictToggleClicked(predictionEnabled);
    updatePrediction();
}

void JKeyboard::clearCompose()
{
    composeStr.clear();
    updatePrediction();
}

void JKeyboard::setShift(bool b)
{
    shifted = b;
    if (shifted) {
        if (symbolActive)
            stacked->setCurrentWidget(symbolShifted);
        else if (currentLang == ENGLISH)
            stacked->setCurrentWidget(qwertyShifted);
        else
            stacked->setCurrentWidget(thaiShifted);
    } else {
        if (symbolActive)
            stacked->setCurrentWidget(symbol);
        else if (currentLang == ENGLISH)
            stacked->setCurrentWidget(qwerty);
        else
            stacked->setCurrentWidget(thai);
    }
}

void JKeyboard::updatePrediction()
{
    if (!predictionEnabled)
        return;

    if (composeStr.length() == 0) {
        predictWord.clear();
        for (int i = 0; i < MAX_PREDICTION; ++i)
            predictButton.at(i)->hide();
        return;
    } else if (composeStr.length() < predictWord.length()) {
        predictWord.clear();
    }

    QString composeStrUnicode = codec->toUnicode(composeStr.toLatin1());
    QSqlQuery q(QString("select word, freq from words where word like '%1%%' order by freq desc limit %2")
                .arg(composeStrUnicode).arg(MAX_PREDICTION),
                currentLang == THAI ? dictDb : engDictDb);

    QPushButton *button = predictButton.at(0);
    button->setText(composeStr);
    button->show();

    int i = 1;
    while (q.next() && i < MAX_PREDICTION) {
        QString s = q.value(0).toString();

        if (s == composeStrUnicode) {
            if (currentLang == THAI)
                predictWord = composeStr;
        } else {
            button = predictButton.at(i);
            button->setText(QString::fromLatin1(codec->fromUnicode(s)));
            button->show();
            ++i;
        }
    }
    q.clear();

    if (i == 1) {
        if (currentLang == THAI && predictWord.length() > 0) {
            composeStr.remove(0, predictWord.length());
            predictWord.clear();
            if (composeStr.length() > 0) {
                updatePrediction();
                return;
            }
            i = 0;
        } else if (composeStr.length() == 1) {
            composeStr.clear();
            i = 0;
        }
    }

    for ( ; i < MAX_PREDICTION; ++i)
        predictButton.at(i)->hide();
}

void JKeyboard::processKeyInput(JKey *key, bool held)
{
    int keyCode = key->getKeyCode(held);

    if (keyCode == Qt::Key_Mode_switch) {
        shiftLocked = false;
        if (currentLang == ENGLISH)
            currentLang = THAI;
        else
            currentLang = ENGLISH;
        setShift(false);
        composeStr.clear();
        updatePrediction();
    } else if (keyCode == Qt::Key_AltGr) {
        shiftLocked = false;
        symbolActive = !symbolActive;
        setShift(false);
        composeStr.clear();
        updatePrediction();
    } else if (keyCode == Qt::Key_Meta || keyCode == Qt::Key_Shift) {
        if (keyCode == Qt::Key_Meta)
            key->setDown(true);

        if (!shifted && held)
            shiftLocked = true;
        else
            shiftLocked = false;
        setShift(!shifted);
    } else if (keyCode == Qt::Key_Return) {
        QKeyEvent event(QEvent::KeyPress, Qt::Key_Return, Qt::NoModifier, "\n");
        QApplication::sendEvent(receiver, &event);
        composeStr.clear();
        updatePrediction();
    } else {
        QString keyText = key->getText(held);

        if (held && keyText.isEmpty()) {
            held = false;
            keyText = key->getText(held);
        }

        if (keyCode != 0 || !keyText.isEmpty()) {
            if (keyCode == 0) {
                receiver->insertPlainText(keyText);
            } else {
                QKeyEvent event(QEvent::KeyPress, keyCode, Qt::NoModifier, keyText);
                QApplication::sendEvent(receiver, &event);
            }

            if (predictionEnabled) {
                if (keyCode == Qt::Key_Backspace) {
                    if (composeStr.length() > 0)
                        composeStr.remove(composeStr.length() - 1, 1);
                    updatePrediction();
                } else if (keyCode == Qt::Key_Space || keyCode == Qt::Key_Period) {
                    composeStr.clear();
                    updatePrediction();
                } else {
                    composeStr.append(keyText);
                    updatePrediction();
                }
            }
        }

        if (!shiftLocked)
            setShift(false);
    }
}

void JKeyboard::keyPressed()
{
    held = false;
    holdTimer.start(500);
    holdKey = static_cast<JKey *>(QObject::sender());
}

void JKeyboard::keyReleased()
{
    holdTimer.stop();

    if (!held)
        processKeyInput(static_cast<JKey *>(QObject::sender()), false);
}

void JKeyboard::holdTimeout()
{
    held = true;
    holdTimer.stop();

    if (holdKey)
        processKeyInput(holdKey, true);

    if (holdKey->getKeyCode(held) == Qt::Key_Backspace)
        holdTimer.start(200);
}

void JKeyboard::predictWordClicked()
{
    QObject *receiver = QApplication::focusWidget();

    QPushButton *button = static_cast<QPushButton *>(QObject::sender());
    QString s = button->text();
    s.remove(0, composeStr.length());
    if (s.length() && receiver) {
        QKeyEvent event(QEvent::KeyPress, 0, Qt::NoModifier, s);
        QApplication::sendEvent(receiver, &event);
    }
    if (currentLang == ENGLISH) {
        QKeyEvent event(QEvent::KeyPress, 0, Qt::NoModifier, " ");
        QApplication::sendEvent(receiver, &event);
    }

    composeStr.clear();
    updatePrediction();

    shifted = false;
    shiftLocked = false;
    setShift(shifted);
}

void JKeyboard::predictToggleClicked(bool enabled)
{
    hide();
    predictionEnabled = enabled;
    predictionWidget->setVisible(enabled);

    if (enabled) {
        composeStr.clear();
        updatePrediction();
    }
    show();
}
