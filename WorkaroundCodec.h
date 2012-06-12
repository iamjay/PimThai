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
