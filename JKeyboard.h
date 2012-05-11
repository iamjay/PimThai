#ifndef JKEYBOARD_H
#define JKEYBOARD_H

#include <QtGui>
#include <QtSql>

struct KeyData
{
    int width;
    int keyCode;
    int altKeyCode;
    const char *text;
    const char *altText;
    int offset;
    int altOffset;
};

struct KeyLayout
{
    int numRow;
    KeyData **rows;

    KeyLayout(int numRow, KeyData **rows)
    {
        this->numRow = numRow;
        this->rows = rows;
    }
};

class JKeyboard;

class JKey : public QPushButton
{
    Q_OBJECT

public:
    JKey(const KeyData *key, QWidget *parent = 0);

    int getKeyCode(bool alt) const;
    const QString &getText(bool alt) const;

protected:
    static QTextCodec *codec;

    const KeyData *keyData;
    QString text;
    QString unicodeText;
    QString altText;
    QString unicodeAltText;

    void paintEvent(QPaintEvent *);
};

class JKeyboardLayout : public QWidget
{
    Q_OBJECT

public:
    JKeyboardLayout(JKeyboard *receiver, const KeyLayout *layout,
                    QWidget *parent = 0);
};

class JKeyboard : public QWidget
{
    Q_OBJECT

public:
    JKeyboard(QWidget *parent = 0);
    void clearCompose();

private:
    enum {
        MAX_PREDICTION = 16
    };

    enum {
        ENGLISH,
        THAI
    } currentLang;

    bool shifted;
    bool shiftLocked;
    bool held;
    QSqlDatabase dictDb;

    QList<QPushButton *> predictButton;
    QStackedLayout *stacked;
    JKeyboardLayout *qwerty;
    JKeyboardLayout *qwertyShifted;
    JKeyboardLayout *thai;
    JKeyboardLayout *thaiShifted;

    JKey *holdKey;
    QTimer holdTimer;

    bool predictionEnabled;
    QScrollArea *predictionPanel;
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
