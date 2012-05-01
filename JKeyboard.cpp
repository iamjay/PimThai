#include <QtGui>

#include "JKeyboard.h"

static KeyData qwerty1[] = {
    { 2, Qt::Key_Q, Qt::Key_1, "q", "1" },
    { 2, Qt::Key_W, Qt::Key_2, "w", "2" },
    { 2, Qt::Key_E, Qt::Key_3, "e", "3" },
    { 2, Qt::Key_R, Qt::Key_4, "r", "4" },
    { 2, Qt::Key_T, Qt::Key_5, "t", "5" },
    { 2, Qt::Key_Y, Qt::Key_6, "y", "6" },
    { 2, Qt::Key_U, Qt::Key_7, "u", "7" },
    { 2, Qt::Key_I, Qt::Key_8, "i", "8" },
    { 2, Qt::Key_O, Qt::Key_9, "o", "9" },
    { 2, Qt::Key_P, Qt::Key_0, "p", "0" },
    { 0, 0, 0, 0, 0 },
};

static KeyData qwerty2[] = {
    { 1, -1, 0, 0, 0 },
    { 2, Qt::Key_A, Qt::Key_At, "a", "@" },
    { 2, Qt::Key_S, Qt::Key_Dollar, "s", "$" },
    { 2, Qt::Key_D, Qt::Key_Ampersand, "d", "&" },
    { 2, Qt::Key_F, Qt::Key_Underscore, "f", "_" },
    { 2, Qt::Key_G, Qt::Key_ParenLeft, "g", "(" },
    { 2, Qt::Key_H, Qt::Key_ParenRight, "h", ")" },
    { 2, Qt::Key_J, Qt::Key_Colon, "j", ":" },
    { 2, Qt::Key_K, Qt::Key_Semicolon, "k", ";" },
    { 2, Qt::Key_L, Qt::Key_Backslash, "l", "\"" },
    { 1, -1, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData qwerty3[] = {
    { 2, Qt::Key_Shift, Qt::Key_Shift, "Shift", 0 },
    { 2, Qt::Key_Z, 0, "z", 0 },
    { 2, Qt::Key_X, Qt::Key_Exclam, "x", "!" },
    { 2, Qt::Key_C, Qt::Key_NumberSign, "c", "#" },
    { 2, Qt::Key_V, Qt::Key_Equal, "v", "=" },
    { 2, Qt::Key_B, Qt::Key_Slash, "b", "/" },
    { 2, Qt::Key_N, Qt::Key_Plus, "n", "+" },
    { 2, Qt::Key_M, Qt::Key_Question, "m", "?" },
    { 4, Qt::Key_Backspace, Qt::Key_Backspace, "←", 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData qwerty4[] = {
    { 2, -1, 0, "+!=", 0 },
    { 2, Qt::Key_Mode_switch, Qt::Key_Mode_switch, "EN", 0 },
    { 2, Qt::Key_Comma, Qt::Key_Minus, ",", "-" },
    { 10, Qt::Key_Space, 0, " ", 0 },
    { 2, Qt::Key_Period, Qt::Key_Apostrophe, ".", "'" },
    { 2, Qt::Key_Return, Qt::Key_Return, "Enter", 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData qwertyShifted1[] = {
    { 2, Qt::Key_Q, 0, "Q", 0 },
    { 2, Qt::Key_W, 0, "W", 0 },
    { 2, Qt::Key_E, 0, "E", 0 },
    { 2, Qt::Key_R, 0, "R", 0 },
    { 2, Qt::Key_T, 0, "T", 0 },
    { 2, Qt::Key_Y, 0, "Y", 0 },
    { 2, Qt::Key_U, 0, "U", 0 },
    { 2, Qt::Key_I, 0, "I", 0 },
    { 2, Qt::Key_O, 0, "O", 0 },
    { 2, Qt::Key_P, 0, "P", 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData qwertyShifted2[] = {
    { 1, -1, 0, 0, 0 },
    { 2, Qt::Key_A, 0, "A", 0 },
    { 2, Qt::Key_S, 0, "S", 0 },
    { 2, Qt::Key_D, 0, "D", 0 },
    { 2, Qt::Key_F, 0, "F", 0 },
    { 2, Qt::Key_G, 0, "G", 0 },
    { 2, Qt::Key_H, 0, "H", 0 },
    { 2, Qt::Key_J, 0, "J", 0 },
    { 2, Qt::Key_K, 0, "K", 0 },
    { 2, Qt::Key_L, 0, "L", 0 },
    { 1, -1, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData qwertyShifted3[] = {
    { 2, Qt::Key_Shift, Qt::Key_Shift, "Shift", 0 },
    { 2, Qt::Key_Z, 0, "Z", 0 },
    { 2, Qt::Key_X, 0, "X", 0 },
    { 2, Qt::Key_C, 0, "C", 0 },
    { 2, Qt::Key_V, 0, "V", 0 },
    { 2, Qt::Key_B, 0, "B", 0 },
    { 2, Qt::Key_N, 0, "N", 0 },
    { 2, Qt::Key_M, 0, "M", 0 },
    { 4, Qt::Key_Backspace, Qt::Key_Backspace, "←", 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData qwertyShifted4[] = {
    { 2, -1, 0, "+!=", 0 },
    { 2, Qt::Key_Mode_switch, Qt::Key_Mode_switch, "EN", 0 },
    { 2, Qt::Key_Minus, 0, "-", 0 },
    { 10, Qt::Key_Tab, 0, "→", 0 },
    { 2, Qt::Key_Apostrophe, 0, "'", 0 },
    { 2, Qt::Key_Return, Qt::Key_Return, "Enter", 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData *qwertyKeyData[] = { qwerty1, qwerty2, qwerty3, qwerty4 };
static KeyData *qwertyShiftedKeyData[] = { qwertyShifted1, qwertyShifted2,
                                            qwertyShifted3, qwertyShifted4 };

static KeyData thai1[] = {
    { 2, 0, 0, "ภ", "๑" },
    { 2, 0, 0, "ถ", "๒" },
    { 2, 0, 0, "ุ", "๓" },
    { 2, 0, 0, "ึ", "๔" },
    { 2, 0, 0, "ค", "๕" },
    { 2, 0, 0, "ต", "๖" },
    { 2, 0, 0, "จ", "๗" },
    { 2, 0, 0, "ข", "๘" },
    { 2, 0, 0, "ช", "๙" },
    { 2, 0, 0, "ล", "๐" },
    { 0, 0, 0, 0, 0 },
};

static KeyData thai2[] = {
    { 2, 0, 0, "ไ", 0 },
    { 2, 0, 0, "ำ", "ฎ" },
    { 2, 0, 0, "พ", "ฑ" },
    { 2, 0, 0, "ะ", "ธ" },
    { 2, 0, 0, "ั", "ู" },
    { 2, 0, 0, "ี", "๊" },
    { 2, 0, 0, "ร", "ณ" },
    { 2, 0, 0, "น", "ฯ" },
    { 2, 0, 0, "ย", "ญ" },
    { 2, 0, 0, "บ", "ฐ" },
    { 0, 0, 0, 0, 0 },
};

static KeyData thai3[] = {
    { 2, 0, 0, "ฟ", "ฤ" },
    { 2, 0, 0, "ห", "ฆ" },
    { 2, 0, 0, "ก", "ฏ" },
    { 2, 0, 0, "ด", "โ" },
    { 2, 0, 0, "เ", "ฌ" },
    { 2, 0, 0, "้", "็" },
    { 2, 0, 0, "่", "๋" },
    { 2, 0, 0, "า", "ษ" },
    { 2, 0, 0, "ส", "ศ" },
    { 2, 0, 0, "ว", "ซ" },
    { 2, 0, 0, "ง", "'" },
    { 0, 0, 0, 0, 0 },
};

static KeyData thai4[] = {
    { 2, Qt::Key_Shift, Qt::Key_Shift, "Shift", 0 },
    { 2, 0, 0, "ป", "ผ" },
    { 2, 0, 0, "แ", "ฉ" },
    { 2, 0, 0, "อ", "ฮ" },
    { 2, 0, 0, "ิ", "ฺ" },
    { 2, 0, 0, "ื", "์" },
    { 2, 0, 0, "ท", "ๅ" },
    { 2, 0, 0, "ม", "ฒ" },
    { 2, 0, 0, "ใ", "ฬ" },
    { 2, 0, 0, "ฝ", "ฦ" },
    { 2, Qt::Key_Backspace, Qt::Key_Backspace, "←", 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData thai5[] = {
    { 2, -1, 0, "+!=", 0 },
    { 2, Qt::Key_Mode_switch, Qt::Key_Mode_switch, "EN", 0 },
    { 2, Qt::Key_Comma, 0, ",", "ๆ" },
    { 10, Qt::Key_Space, 0, " ", 0 },
    { 2, Qt::Key_Apostrophe, Qt::Key_Minus, ".", "-" },
    { 2, Qt::Key_Return, Qt::Key_Return, "Enter", 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData thaiShifted1[] = {
    { 2, 0, Qt::Key_1, "๑", "1" },
    { 2, 0, Qt::Key_2, "๒", "2" },
    { 2, 0, Qt::Key_3, "๓", "3" },
    { 2, 0, Qt::Key_4, "๔", "4" },
    { 2, 0, Qt::Key_5, "๕", "5" },
    { 2, 0, Qt::Key_6, "๖", "6" },
    { 2, 0, Qt::Key_7, "๗", "7" },
    { 2, 0, Qt::Key_8, "๘", "8" },
    { 2, 0, Qt::Key_9, "๙", "9" },
    { 2, 0, Qt::Key_0, "๐", "0" },
    { 0, 0, 0, 0, 0 },
};

static KeyData thaiShifted2[] = {
    { 2, 0, 0, "ไ", 0 },
    { 2, 0, Qt::Key_At, "ฎ", "@" },
    { 2, 0, Qt::Key_NumberSign, "ฑ", "#" },
    { 2, 0, Qt::Key_Percent, "ธ", "%" },
    { 2, 0, 0, "ู", "ํ" },
    { 2, 0, Qt::Key_Equal, "๊", "=" },
    { 2, 0, Qt::Key_Minus, "ณ", "-" },
    { 2, 0, 0, "ฯ", "™" },
    { 2, 0, Qt::Key_ParenLeft, "ญ", "(" },
    { 2, 0, Qt::Key_ParenRight, "ฐ", ")" },
    { 0, 0, 0, 0, 0 },
};

static KeyData thaiShifted3[] = {
    { 2, 0, Qt::Key_Ampersand, "ฤ", "&" },
    { 2, 0, Qt::Key_Dollar, "ฆ", "$" },
    { 2, 0, 0, "ฏ", "€" },
    { 2, 0, 0, "โ", 0 },
    { 2, 0, Qt::Key_Asterisk, "ฌ", "*" },
    { 2, 0, Qt::Key_AsciiCircum, "็", "^" },
    { 2, 0, Qt::Key_Plus, "๋", "+" },
    { 2, 0, Qt::Key_Slash, "ษ", "/" },
    { 2, 0, Qt::Key_Backslash, "ศ", "\\" },
    { 2, 0, Qt::Key_Colon, "ซ", ":" },
    { 2, 0, Qt::Key_Semicolon, "'", ";" },
    { 0, 0, 0, 0, 0 },
};

static KeyData thaiShifted4[] = {
    { 2, Qt::Key_Shift, Qt::Key_Shift, "Shift", 0 },
    { 2, 0, Qt::Key_Exclam, "ผ", "!" },
    { 2, 0, 0, "ฉ", 0 },
    { 2, 0, 0, "ฮ", 0 },
    { 2, 0, 0, "ฺ", 0 },
    { 2, 0, 0, "์", 0 },
    { 2, 0, Qt::Key_BraceLeft, "ๅ", "[" },
    { 2, 0, Qt::Key_BraceRight, "ฒ", "]" },
    { 2, 0, Qt::Key_QuoteLeft, "ฬ", "`" },
    { 2, 0, Qt::Key_Question, "ฦ", "?" },
    { 2, Qt::Key_Backspace, Qt::Key_Backspace, "←", 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData thaiShifted5[] = {
    { 2, -1, 0, "+!=", 0 },
    { 2, Qt::Key_Mode_switch, Qt::Key_Mode_switch, "EN", 0 },
    { 2, 0, 0, "ๆ", 0 },
    { 10, Qt::Key_Space, 0, " ", 0 },
    { 2, Qt::Key_Minus, 0, "-", 0 },
    { 2, Qt::Key_Return, Qt::Key_Return, "Enter", 0 },
    { 0, 0, 0, 0, 0 },
};

static KeyData *thaiKeyData[] = { thai1, thai2, thai3, thai4, thai5 };
static KeyData *thaiShiftedKeyData[] = { thaiShifted1, thaiShifted2,
                                         thaiShifted3, thaiShifted4,
                                         thaiShifted5 };

KeyLayout JKeyboard::qwertyKeys = KeyLayout(4, qwertyKeyData);
KeyLayout JKeyboard::qwertyShiftedKeys = KeyLayout(4, qwertyShiftedKeyData);
KeyLayout JKeyboard::thaiKeys = KeyLayout(5, thaiKeyData);
KeyLayout JKeyboard::thaiShiftedKeys = KeyLayout(5, thaiShiftedKeyData);

JKey::JKey(const KeyData *key, QWidget *parent)
    : QPushButton(parent)
    , keyData(key)
{
    text = QString::fromUtf8(keyData->text);
    altText = QString::fromUtf8(keyData->altText);

    setText(text);
    setFocusPolicy(Qt::NoFocus);
}

int JKey::getKeyCode(bool alt) const
{
    return alt ? keyData->altKeyCode : keyData->keyCode;
}

const QString &JKey::getText(bool alt) const
{
    return alt ? altText : text;
}

QSize JKey::sizeHint() const
{
    QSize size = QPushButton::sizeHint();
    size.setHeight(3 * size.height() / 2);

    return size;
}

void JKey::paintEvent(QPaintEvent *pe)
{
    QPushButton::paintEvent(pe);

    QStylePainter p(this);
    QStyleOptionButton option;
    initStyleOption(&option);

    QPen pen = p.pen();
    QColor color = pen.color();
    color.setRgb(100, 100, 100);
    pen.setColor(color);
    p.setPen(pen);

    QFont font = p.font();
    font.setPointSize(font.pointSize() - 2);
    p.setFont(font);
    QSize sz = p.fontMetrics().size(Qt::TextShowMnemonic, altText);

    p.drawText(contentsRect().width() - 2 * sz.width(), sz.height(), altText);
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

    setStyleSheet("QPushButton { font-size: 14pt; }"
                  "QPushButton:pressed { border-radius: 6px; background-color: #00D5FF; }");
    setBackgroundRole(QPalette::Dark);
    setAutoFillBackground(true);
}

JKeyboard::JKeyboard(QWidget *parent)
    : QWidget(parent)
{
    QFont font = QToolTip::font();
    font.setPointSize(12);
    QToolTip::setFont(font);

    currentLang = THAI;
    shifted = false;
    shiftLocked = false;

    stacked = new QStackedLayout(this);

    thai = new JKeyboardLayout(this, &thaiKeys);
    stacked->addWidget(thai);

    thaiShifted = new JKeyboardLayout(this, &thaiShiftedKeys);
    stacked->addWidget(thaiShifted);

    qwerty = new JKeyboardLayout(this, &qwertyKeys);
    stacked->addWidget(qwerty);

    qwertyShifted = new JKeyboardLayout(this, &qwertyShiftedKeys);
    stacked->addWidget(qwertyShifted);

    connect(&holdTimer, SIGNAL(timeout()), this, SLOT(holdTimeout()));

    setShift(shifted);
}

void JKeyboard::setShift(bool b)
{
    shifted = b;
    if (shifted) {
        if (currentLang == ENGLISH)
            stacked->setCurrentWidget(qwertyShifted);
        else
            stacked->setCurrentWidget(thaiShifted);
    } else {
        if (currentLang == ENGLISH)
            stacked->setCurrentWidget(qwerty);
        else
            stacked->setCurrentWidget(thai);
    }
}

void JKeyboard::processKeyInput(const JKey *key, bool held)
{
    QObject *receiver = QApplication::focusWidget();

    switch (key->getKeyCode(held)) {
    case Qt::Key_Mode_switch:
        shiftLocked = false;
        if (currentLang == ENGLISH)
            currentLang = THAI;
        else
            currentLang = ENGLISH;
        setShift(false);
        break;

    case Qt::Key_Shift:
        if (!shifted && held)
            shiftLocked = true;
        else
            shiftLocked = false;
        setShift(!shifted);
        break;

    case Qt::Key_Return:
        if (key->getKeyCode(held) && receiver) {
            QKeyEvent event(QEvent::KeyPress, key->getKeyCode(held),
                            Qt::NoModifier, "\n");
            QApplication::sendEvent(receiver, &event);
        }
        break;

    default:
        if (held && key->getText(held).isEmpty())
            held = false;

        if ((key->getKeyCode(held) != 0 || !key->getText(held).isEmpty())
                && receiver) {
            QKeyEvent event(QEvent::KeyPress, key->getKeyCode(held),
                            Qt::NoModifier, key->getText(held));
            QApplication::sendEvent(receiver, &event);
        }
        if (!shiftLocked)
            setShift(false);
        break;
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
}
