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

#ifndef JDUMMYINPUTCONTEXT_H
#define JDUMMYINPUTCONTEXT_H

#include <QInputContext>

class JDummyInputContext : public QInputContext
{
    Q_OBJECT

public:
    explicit JDummyInputContext(QObject *parent = 0);

    virtual QString identifierName();
    virtual bool isComposing() const;
    virtual QString language();
    virtual void reset();
};

#endif
