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

#ifndef JKEYBOARD_H
#define JKEYBOARD_H

#include <QtGui>
#include <QtSql>

#include "KeyLayout.h"

class JKeyboard;

class JKey : public QPushButton
{
    Q_OBJECT

public:
    JKey(const KeyData *key, QWidget *parent = 0);

    int getKeyCode(bool alt) const;
    const QString &getText(bool alt) const;

protected:
    static QFont *font;

    const KeyData *keyData;
    QString text;
    QString altText;
    QString altPaintText;

    void paintEvent(QPaintEvent *);
};

class JKeyboardLayout : public QWidget
{
    Q_OBJECT

public:
    JKeyboardLayout(JKeyboard *receiver, const KeyLayout *layout,
                    QWidget *parent = 0);
};

class PredictionContainer : public QScrollArea
{
    Q_OBJECT

public:
    PredictionContainer(QWidget * parent = 0);
    QSize minimumSizeHint() const;
};

class JKeyboard : public QWidget
{
    Q_OBJECT

public:
    JKeyboard(QWidget *receiver, QWidget *parent = 0);
    void clearCompose();
    QWidget *getPredictionWidget() { return predictionWidget; }

    static QTextCodec *codec;

private:
    enum {
        MAX_PREDICTION = 16
    };

    enum {
        ENGLISH,
        THAI
    } currentLang;

    QWidget *receiver;
    bool shifted;
    bool shiftLocked;
    bool symbolActive;
    bool held;
    QSqlDatabase dictDb;
    QSqlDatabase engDictDb;

    PredictionContainer *predictionWidget;
    QList<QPushButton *> predictButton;
    QStackedLayout *stacked;
    JKeyboardLayout *qwerty;
    JKeyboardLayout *qwertyShifted;
    JKeyboardLayout *thai;
    JKeyboardLayout *thaiShifted;
    JKeyboardLayout *symbol;
    JKeyboardLayout *symbolShifted;

    JKey *holdKey;
    QTimer holdTimer;

    bool predictionEnabled;
    QString composeStr;
    QString predictWord;

    void setShift(bool b);
    void processKeyInput(JKey *key, bool held);
    void updatePrediction();

public slots:
    void keyPressed();
    void keyReleased();
    void holdTimeout();
    void predictWordClicked();
    void predictToggleClicked(bool enabled);
};

#endif
