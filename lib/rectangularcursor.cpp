/*
    Copyright 2020, Mitch Curtis

    This file is part of Slate.

    Slate is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Slate is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Slate. If not, see <http://www.gnu.org/licenses/>.
*/

#include "rectangularcursor.h"

#include <QPainter>

#include "imageutils.h"

RectangularCursor::RectangularCursor()
{
}

void RectangularCursor::paint(QPainter *painter)
{
    ImageUtils::strokeRectWithDashes(painter, QRect(0, 0, width(), height()));
}
