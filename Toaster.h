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

#ifndef TOASTER_H
#define TOASTER_H

#include <QTimer>
#include <QWidget>

class QLabel;

class Toaster : public QWidget
{
    Q_OBJECT
public:
    Toaster(QWidget *parent = 0);
    void showToast(QPoint &p, const QString &text);

protected:
    QLabel *label;

private slots:
    void toastTimeout();
};

#endif
