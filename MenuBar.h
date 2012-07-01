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

#ifndef MAINMENUBAR_H
#define MAINMENUBAR_H

#include "ui_MenuBar.h"

class MenuBar : public QWidget, public Ui::MenuBar
{
    Q_OBJECT
    
public:
    explicit MenuBar(QWidget *parent = 0);

protected:
#if Q_OS_BLACKBERRY
    bool event(QEvent *event);
#endif
};

#endif
