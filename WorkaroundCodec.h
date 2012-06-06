#ifndef WORKAROUNDCODEC_H
#define WORKAROUNDCODEC_H

#include <QString>
#include <QTextCodec>

class WorkaroundCodec : public QTextCodec
{
public:
    WorkaroundCodec();

    QByteArray name() const;
    QList<QByteArray> aliases() const;
    int mibEnum() const;
    QString convertToUnicode(const char *in, int length, ConverterState *state) const;
    QByteArray convertFromUnicode(const QChar *in, int length, ConverterState *state) const;

private:
    int forwardIndex;
    mutable QAtomicPointer<QByteArray> reverseMap;
};

#endif
