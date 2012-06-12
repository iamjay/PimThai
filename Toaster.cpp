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

#include <QtGui>

#include "Toaster.h"

Toaster::Toaster(QWidget *parent)
    : QWidget(parent, Qt::ToolTip | Qt::FramelessWindowHint)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setStyleSheet("QLabel { font-size: 12pt; border-radius: 8px; border: 2px solid white; color: white; background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #559BBF, stop: 0.6 #3895D2, stop:1 #3381C3); padding: 4px; }");

    QHBoxLayout *hbox = new QHBoxLayout();
    setLayout(hbox);

    label = new QLabel();
    hbox->addWidget(label);
}

void Toaster::showToast(QPoint &p, const QString &text)
{
    label->setText(text);
    show();

    QSize s = size();
    p.rx() -= s.width() / 2;
    p.ry() -= s.height() / 2;
    move(p);

    QTimer::singleShot(800, this, SLOT(toastTimeout()));
}

void Toaster::toastTimeout()
{
    hide();
    static_cast<QWidget *>(parent())->activateWindow();
}
