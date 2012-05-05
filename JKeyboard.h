#ifndef JKEYBOARD_H
#define JKEYBOARD_H

#include <QtGui>

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

    int getKeyCode(bool shifted) const;
    const QString &getText(bool shifted) const;

protected:
    static QTextCodec *codec;

    const KeyData *keyData;
    QString text;
    QString unicodeText;
    QString altText;
    QString unicodeAltText;

    QSize sizeHint() const;
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

    static KeyLayout qwertyKeys;
    static KeyLayout qwertyShiftedKeys;
    static KeyLayout thaiKeys;
    static KeyLayout thaiShiftedKeys;

private:
    enum {
        ENGLISH,
        THAI
    } currentLang;
    bool shifted;
    bool shiftLocked;
    bool held;

    QStackedLayout *stacked;
    JKeyboardLayout *qwerty;
    JKeyboardLayout *qwertyShifted;
    JKeyboardLayout *thai;
    JKeyboardLayout *thaiShifted;

    JKey *holdKey;
    QTimer holdTimer;

    void setShift(bool b);
    void processKeyInput(const JKey *key, bool held);

public slots:
    void keyPressed();
    void keyReleased();
    void holdTimeout();
};

#endif
