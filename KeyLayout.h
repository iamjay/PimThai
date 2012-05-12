#ifndef KEYLAYOUT_H
#define KEYLAYOUT_H

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

extern KeyLayout qwertyKeys;
extern KeyLayout qwertyShiftedKeys;
extern KeyLayout thaiKeys;
extern KeyLayout thaiShiftedKeys;

#endif
