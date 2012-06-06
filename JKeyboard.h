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
    JKeyboard(QPlainTextEdit *receiver, QWidget *parent = 0);
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

    QPlainTextEdit *receiver;
    bool shifted;
    bool shiftLocked;
    bool held;
    QSqlDatabase dictDb;

    PredictionContainer *predictionWidget;
    QList<QPushButton *> predictButton;
    QStackedLayout *stacked;
    JKeyboardLayout *qwerty;
    JKeyboardLayout *qwertyShifted;
    JKeyboardLayout *thai;
    JKeyboardLayout *thaiShifted;

    JKey *holdKey;
    QTimer holdTimer;

    bool predictionEnabled;
    QString composeStr;

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
