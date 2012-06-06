#include "WorkaroundCodec.h"

#include <qdebug.h>

static WorkaroundCodec myCodec;

static const struct {
    const char *mime;
    const char *aliases[7];
    int mib;
    quint16 values[128];
} unicodevalues[1] = {
    { "TIS-620A", { "tis620a", 0 }, 22259,
      { 0x20AC, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD, 0x2026, 0xFFFD, 0xFFFD,
        0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD,
        0xFFFD, 0x2018, 0x2019, 0x201C, 0x201D, 0x2022, 0x2013, 0x2014,
        0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD,
        0xFFFD, 0x0E01, 0x0E02, 0x0E03, 0x0E04, 0x0E05, 0x0E06, 0x0E07,
        0x0E08, 0x0E09, 0x0E0A, 0x0E0B, 0x0E0C, 0xFFFD, 0x0E0E, 0x0E0F,
        0x0E10, 0x0E11, 0x0E12, 0x0E13, 0x0E14, 0x0E15, 0x0E16, 0x0E17,
        0x0E18, 0x0E19, 0x0E1A, 0x0E1B, 0x0E1C, 0x0E1D, 0x0E1E, 0x0E1F,
        0x0E20, 0x0E21, 0x0E22, 0x0E23, 0x0E24, 0x0E25, 0x0E26, 0x0E27,
        0x0E28, 0x0E29, 0x0E2A, 0x0E2B, 0x0E2C, 0x0E2D, 0x0E2E, 0x0E2F,
        0x0E30, 0x0E31, 0x0E32, 0x0E33, 0x0E34, 0x0E35, 0x0E36, 0x0E37,
        0x0E38, 0x0E39, 0x0E3A, 0xFFFD, 0xFFFD, 0xFFFD, 0xFFFD, 0x0E3F,
        0x0E40, 0x0E41, 0x0E42, 0x0E43, 0x0E44, 0x0E45, 0x0E46, 0x0E47,
        0x0E48, 0x0E49, 0x0E4A, 0x0E4B, 0x0E4C, 0x0E4D, 0x0E4E, 0x0E4F,
        0x0E50, 0x0E51, 0x0E52, 0x0E53, 0x0E54, 0x0E55, 0x0E56, 0x0E57,
        0x0E58, 0x0E59, 0x0E5A, 0x0E5B, 0x0E0D, 0xFFFD, 0xFFFD, 0xFFFD }
    }
};

static QByteArray *buildReverseMap(int forwardIndex)
{
    QByteArray *map = new QByteArray();
    int m = 0;
    int i = 0;
    while(i < 128) {
        if (unicodevalues[forwardIndex].values[i] > m &&
             unicodevalues[forwardIndex].values[i] < 0xfffd)
            m = unicodevalues[forwardIndex].values[i];
        i++;
    }
    m++;
    map->resize(m);
    for(i = 0; i < 128 && i < m; i++)
        (*map)[i] = (char)i;
    for(;i < m; i++)
        (*map)[i] = 0;
    for(i=128; i<256; i++) {
        int u = unicodevalues[forwardIndex].values[i-128];
        if (u < m)
            (*map)[u] = (char)(unsigned char)(i);
    }
    return map;
}

WorkaroundCodec::WorkaroundCodec()
    : forwardIndex(0)
{
}

QByteArray WorkaroundCodec::name() const
{
    return unicodevalues[forwardIndex].mime;
}

QList<QByteArray> WorkaroundCodec::aliases() const
{
    QList<QByteArray> list;
    const char * const*a = unicodevalues[forwardIndex].aliases;
    while (*a) {
        list << *a;
        ++a;
    }
    return list;
}

int WorkaroundCodec::mibEnum() const
{
    return unicodevalues[forwardIndex].mib;
}

QString WorkaroundCodec::convertToUnicode(const char *chars, int len, ConverterState *) const
{
    qDebug() << "here1";
    if (len <= 0 || chars == 0)
        return QString();

    const unsigned char * c = (const unsigned char *)chars;

    QString r(len, Qt::Uninitialized);
    QChar* uc = r.data();

    for (int i = 0; i < len; i++) {
        if (c[i] > 127)
            uc[i] = unicodevalues[forwardIndex].values[c[i]-128];
        else
            uc[i] = QLatin1Char(c[i]);
    }
    return r;
}

QByteArray WorkaroundCodec::convertFromUnicode(const QChar *in, int length, ConverterState *state) const
{
    qDebug() << "here2";
    const char replacement = (state && state->flags & ConvertInvalidToNull) ? 0 : '?';
    int invalid = 0;

    if (!reverseMap){
        QByteArray *tmp = buildReverseMap(this->forwardIndex);
        if (!reverseMap.testAndSetOrdered(0, tmp))
            delete tmp;
    }

    QByteArray r(length, Qt::Uninitialized);
    int i = length;
    int u;
    const QChar* ucp = in;
    unsigned char* rp = (unsigned char *)r.data();
    const unsigned char* rmp = (const unsigned char *)reverseMap->constData();
    int rmsize = (int) reverseMap->size();
    while(i--)
    {
        u = ucp->unicode();
        if (u < 128) {
            *rp = (char)u;
        } else {
            *rp = ((u < rmsize) ? (*(rmp+u)) : 0);
            if (*rp == 0) {
                *rp = replacement;
                ++invalid;
            }
        }
        rp++;
        ucp++;
    }

    if (state) {
        state->invalidChars += invalid;
    }
    return r;
}
