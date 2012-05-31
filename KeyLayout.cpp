#include <QtGui>

#include "KeyLayout.h"

static KeyData qwerty1[] = {
    { 2, Qt::Key_Q, Qt::Key_1, "q", "1", 0, 0 },
    { 2, Qt::Key_W, Qt::Key_2, "w", "2", 0, 0 },
    { 2, Qt::Key_E, Qt::Key_3, "e", "3", 0, 0 },
    { 2, Qt::Key_R, Qt::Key_4, "r", "4", 0, 0 },
    { 2, Qt::Key_T, Qt::Key_5, "t", "5", 0, 0 },
    { 2, Qt::Key_Y, Qt::Key_6, "y", "6", 0, 0 },
    { 2, Qt::Key_U, Qt::Key_7, "u", "7", 0, 0 },
    { 2, Qt::Key_I, Qt::Key_8, "i", "8", 0, 0 },
    { 2, Qt::Key_O, Qt::Key_9, "o", "9", 0, 0 },
    { 2, Qt::Key_P, Qt::Key_0, "p", "0", 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData qwerty2[] = {
    { 1, -1, 0, 0, 0, 0, 0 },
    { 2, Qt::Key_A, Qt::Key_At, "a", "@", 0, 0 },
    { 2, Qt::Key_S, Qt::Key_Dollar, "s", "$", 0, 0 },
    { 2, Qt::Key_D, Qt::Key_Ampersand, "d", "&", 0, 0 },
    { 2, Qt::Key_F, Qt::Key_Underscore, "f", "_", 0, 0 },
    { 2, Qt::Key_G, Qt::Key_ParenLeft, "g", "(", 0, 0 },
    { 2, Qt::Key_H, Qt::Key_ParenRight, "h", ")", 0, 0 },
    { 2, Qt::Key_J, Qt::Key_Colon, "j", ":", 0, 0 },
    { 2, Qt::Key_K, Qt::Key_Semicolon, "k", ";", 0, 0 },
    { 2, Qt::Key_L, Qt::Key_Backslash, "l", "\"", 0, 0 },
    { 1, -1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData qwerty3[] = {
    { 2, Qt::Key_Shift, Qt::Key_Shift, "Shift", 0, 0, 0 },
    { 2, Qt::Key_Z, 0, "z", 0, 0, 0 },
    { 2, Qt::Key_X, Qt::Key_Exclam, "x", "!", 0, 0 },
    { 2, Qt::Key_C, Qt::Key_NumberSign, "c", "#", 0, 0 },
    { 2, Qt::Key_V, Qt::Key_Equal, "v", "=", 0, 0 },
    { 2, Qt::Key_B, Qt::Key_Slash, "b", "/", 0, 0 },
    { 2, Qt::Key_N, Qt::Key_Plus, "n", "+", 0, 0 },
    { 2, Qt::Key_M, Qt::Key_Question, "m", "?", 0, 0 },
    { 4, Qt::Key_Shift, Qt::Key_Shift, "Shift", 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData qwerty4[] = {
    { 2, Qt::Key_Mode_switch, Qt::Key_Mode_switch, "TH", 0, 0, 0 },
    { 2, Qt::Key_Comma, Qt::Key_Minus, ",", "-", 0, 0 },
    { 8, Qt::Key_Space, 0, " ", 0, 0, 0 },
    { 2, Qt::Key_Period, Qt::Key_Apostrophe, ".", "'", 0, 0 },
    { 3, Qt::Key_Return, Qt::Key_Return, "Enter", 0, 0, 0 },
    { 3, Qt::Key_Backspace, Qt::Key_Backspace, "<-", 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData qwertyShifted1[] = {
    { 2, Qt::Key_Q, 0, "Q", 0, 0, 0 },
    { 2, Qt::Key_W, 0, "W", 0, 0, 0 },
    { 2, Qt::Key_E, 0, "E", 0, 0, 0 },
    { 2, Qt::Key_R, 0, "R", "`", 0, 0 },
    { 2, Qt::Key_T, 0, "T", "^", 0, 0 },
    { 2, Qt::Key_Y, 0, "Y", 0, 0, 0 },
    { 2, Qt::Key_U, 0, "U", 0, 0, 0 },
    { 2, Qt::Key_I, 0, "I", 0, 0, 0 },
    { 2, Qt::Key_O, 0, "O", "{", 0, 0 },
    { 2, Qt::Key_P, 0, "P", "}", 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData qwertyShifted2[] = {
    { 1, -1, 0, 0, 0, 0, 0 },
    { 2, Qt::Key_A, 0, "A", 0, 0, 0 },
    { 2, Qt::Key_S, 0, "S", 0, 0, 0 },
    { 2, Qt::Key_D, 0, "D", "|", 0, 0 },
    { 2, Qt::Key_F, 0, "F", 0, 0, 0 },
    { 2, Qt::Key_G, 0, "G", "[", 0, 0 },
    { 2, Qt::Key_H, 0, "H", "]", 0, 0 },
    { 2, Qt::Key_J, 0, "J", "<", 0, 0 },
    { 2, Qt::Key_K, 0, "K", ">", 0, 0 },
    { 2, Qt::Key_L, 0, "L", 0, 0, 0 },
    { 1, -1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData qwertyShifted3[] = {
    { 2, Qt::Key_Meta, Qt::Key_Meta, "Shift", 0, 0, 0 },
    { 2, Qt::Key_Z, 0, "Z", 0, 0, 0 },
    { 2, Qt::Key_X, 0, "X", 0, 0, 0 },
    { 2, Qt::Key_C, 0, "C", "%", 0, 0 },
    { 2, Qt::Key_V, 0, "V", "*", 0, 0 },
    { 2, Qt::Key_B, 0, "B", "\\", 0, 0 },
    { 2, Qt::Key_N, 0, "N", "~", 0, 0 },
    { 2, Qt::Key_M, 0, "M", 0, 0, 0 },
    { 4, Qt::Key_Meta, Qt::Key_Meta, "Shift", 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData qwertyShifted4[] = {
    { 2, Qt::Key_Mode_switch, Qt::Key_Mode_switch, "TH", 0, 0, 0 },
    { 2, Qt::Key_Minus, 0, "-", 0, 0, 0 },
    { 8, Qt::Key_Space, 0, " ", 0, 0, 0 },
    { 2, Qt::Key_Apostrophe, 0, "'", 0, 0, 0 },
    { 3, Qt::Key_Return, Qt::Key_Return, "Enter", 0, 0, 0 },
    { 3, Qt::Key_Backspace, Qt::Key_Backspace, "<-", 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData *qwertyKeyData[] = { qwerty1, qwerty2, qwerty3, qwerty4 };
static KeyData *qwertyShiftedKeyData[] = { qwertyShifted1, qwertyShifted2,
                                            qwertyShifted3, qwertyShifted4 };

static KeyData thai1[] = {
    { 2, Qt::Key_Comma, 0, "ๆ", 0, 0, 0 },
    { 2, 0, 0, "ภ", "๑", 0, 0 },
    { 2, 0, 0, "ถ", "๒", 0, 0 },
    { 2, 0, 0, "ุ", "๓", 0, 0 },
    { 2, 0, 0, "ึ", "๔", -1, 0 },
    { 2, 0, 0, "ค", "๕", 0, 0 },
    { 2, 0, 0, "ต", "๖", 0, 0 },
    { 2, 0, 0, "จ", "๗", 0, 0 },
    { 2, 0, 0, "ข", "๘", 0, 0 },
    { 2, 0, 0, "ช", "๙", 0, 0 },
    { 2, 0, 0, "ล", "๐", 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData thai2[] = {
    { 1, -1, 0, 0, 0, 0, 0 },
    { 2, 0, 0, "ไ", 0, 0, 0 },
    { 2, 0, 0, "ำ", "ฎ", 0, 0 },
    { 2, 0, 0, "พ", "ฑ", 0, 0 },
    { 2, 0, 0, "ะ", "ธ", 0, 0 },
    { 2, 0, 0, "ั", "ู", 1, -1 },
    { 2, 0, 0, "ี", "๊", 1, 2 },
    { 2, 0, 0, "ร", "ณ", 0, 0 },
    { 2, 0, 0, "น", "ฯ", 0, 0 },
    { 2, 0, 0, "ย", "ญ", 0, 0 },
    { 2, 0, 0, "บ", "ฐ", 0, 0 },
    { 1, -1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData thai3[] = {
    { 2, 0, 0, "ฟ", "ฤ", 0, 0 },
    { 2, 0, 0, "ห", "ฆ", 0, 0 },
    { 2, 0, 0, "ก", "ฏ", 0, 0 },
    { 2, 0, 0, "ด", "โ", 0, 1 },
    { 2, 0, 0, "เ", "ฌ", 0, 0 },
    { 2, 0, 0, "้", "็", 1, 1},
    { 2, 0, 0, "่", "๋", 1, 2},
    { 2, 0, 0, "า", "ษ", 0, 0 },
    { 2, 0, 0, "ส", "ศ", 0, 0 },
    { 2, 0, 0, "ว", "ซ", 0, 0 },
    { 2, 0, 0, "ง", "\"", 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData thai4[] = {
    { 3, Qt::Key_Shift, Qt::Key_Shift, "Shift", 0, 0, 0 },
    { 2, 0, 0, "ป", "ผ", 0, 0 },
    { 2, 0, 0, "แ", "ฉ", 0, 0 },
    { 2, 0, 0, "อ", "ฮ", 0, 0 },
    { 2, 0, 0, "ิ", "ฺ", 1, -1},
    { 2, 0, 0, "ื", "์", 1, 2},
    { 2, 0, 0, "ท", "ๅ", 0, 0 },
    { 2, 0, 0, "ม", "ฒ", 0, 0 },
    { 2, 0, 0, "ใ", "ฬ", 0, 0 },
    { 3, Qt::Key_Shift, Qt::Key_Shift, "Shift", 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData thai5[] = {
    { 2, Qt::Key_Mode_switch, Qt::Key_Mode_switch, "EN", 0, 0, 0 },
    { 2, Qt::Key_Comma, Qt::Key_Minus, ",", "-", 0, 0 },
    { 6, Qt::Key_Space, 0, " ", 0, 0, 0 },
    { 2, 0, 0, "ฝ", "ฦ", 0, 0 },
    { 2, Qt::Key_Apostrophe, 0, ".", "'", 0, 0 },
    { 3, Qt::Key_Return, Qt::Key_Return, "Enter", 0, 0, 0 },
    { 3, Qt::Key_Backspace, Qt::Key_Backspace, "<-", 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData thaiShifted1[] = {
    { 2, 0, 0, "ๆ", 0, 0, 0 },
    { 2, 0, Qt::Key_1, "๑", "1", 0, 0 },
    { 2, 0, Qt::Key_2, "๒", "2", 0, 0 },
    { 2, 0, Qt::Key_3, "๓", "3", 0, 0 },
    { 2, 0, Qt::Key_4, "๔", "4", 0, 0 },
    { 2, 0, Qt::Key_5, "๕", "5", 0, 0 },
    { 2, 0, Qt::Key_6, "๖", "6", 0, 0 },
    { 2, 0, Qt::Key_7, "๗", "7", 0, 0 },
    { 2, 0, Qt::Key_8, "๘", "8", 0, 0 },
    { 2, 0, Qt::Key_9, "๙", "9", 0, 0 },
    { 2, 0, Qt::Key_0, "๐", "0", 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData thaiShifted2[] = {
    { 1, -1, 0, 0, 0, 0, 0 },
    { 2, 0, 0, "ไ", 0, 0, 0 },
    { 2, 0, Qt::Key_At, "ฎ", "@", 0, 0 },
    { 2, 0, Qt::Key_NumberSign, "ฑ", "#", 0, 0 },
    { 2, 0, Qt::Key_Percent, "ธ", "%", 0, 0 },
    { 2, 0, 0, "ู", "ํ", -1, 1},
    { 2, 0, Qt::Key_Equal, "๊", "=", 0, 0 },
    { 2, 0, Qt::Key_Minus, "ณ", "-", 0, 0 },
    { 2, 0, 0, "ฯ", "™", 0, 0 },
    { 2, 0, Qt::Key_ParenLeft, "ญ", "(", 0, 0 },
    { 2, 0, Qt::Key_ParenRight, "ฐ", ")", 0, 0 },
    { 1, -1, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData thaiShifted3[] = {
    { 2, 0, Qt::Key_Ampersand, "ฤ", "&", 0, 0 },
    { 2, 0, Qt::Key_Dollar, "ฆ", "$", 0, 0 },
    { 2, 0, 0, "ฏ", 0, 0, 0 },
    { 2, 0, 0, "โ", 0, 0, 0 },
    { 2, 0, Qt::Key_Asterisk, "ฌ", "*", 0, 0 },
    { 2, 0, Qt::Key_AsciiCircum, "็", "^", 1, 0 },
    { 2, 0, Qt::Key_Plus, "๋", "+", 1, 0 },
    { 2, 0, Qt::Key_Slash, "ษ", "/", 0, 0 },
    { 2, 0, Qt::Key_Backslash, "ศ", "\\", 0, 0 },
    { 2, 0, Qt::Key_Colon, "ซ", ":", 0, 0 },
    { 2, 0, Qt::Key_Semicolon, "'", ";", 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData thaiShifted4[] = {
    { 3, Qt::Key_Meta, Qt::Key_Meta, "Shift", 0, 0, 0 },
    { 2, 0, Qt::Key_Exclam, "ผ", "!", 0, 0 },
    { 2, 0, 0, "ฉ", 0, 0, 0 },
    { 2, 0, 0, "ฮ", 0, 0, 0 },
    { 2, 0, 0, "ฺ", 0, 1, 0 },
    { 2, 0, 0, "์", 0, 1, 0 },
    { 2, 0, Qt::Key_BraceLeft, "ๅ", "[", 0, 0 },
    { 2, 0, Qt::Key_BraceRight, "ฒ", "]", 0, 0 },
    { 2, 0, Qt::Key_QuoteLeft, "ฬ", "`", 0, 0 },
    { 3, Qt::Key_Meta, Qt::Key_Meta, "Shift", 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData thaiShifted5[] = {
    { 2, Qt::Key_Mode_switch, Qt::Key_Mode_switch, "EN", 0, 0, 0 },
    { 2, Qt::Key_Minus, 0, "-", 0, 0, 0 },
    { 6, Qt::Key_Space, 0, " ", 0, 0, 0 },
    { 2, 0, 0, "ฦ", 0, 0, 0 },
    { 2, 0, 0, "'", 0, 0, 0 },
    { 3, Qt::Key_Return, Qt::Key_Return, "Enter", 0, 0, 0 },
    { 3, Qt::Key_Backspace, Qt::Key_Backspace, "<-", 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0 },
};

static KeyData *thaiKeyData[] = { thai1, thai2, thai3, thai4, thai5 };
static KeyData *thaiShiftedKeyData[] = { thaiShifted1, thaiShifted2,
                                         thaiShifted3, thaiShifted4,
                                         thaiShifted5 };

KeyLayout qwertyKeys = KeyLayout(4, qwertyKeyData);
KeyLayout qwertyShiftedKeys = KeyLayout(4, qwertyShiftedKeyData);
KeyLayout thaiKeys = KeyLayout(5, thaiKeyData);
KeyLayout thaiShiftedKeys = KeyLayout(5, thaiShiftedKeyData);
