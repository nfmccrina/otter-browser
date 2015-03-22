/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2015 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#ifndef OTTER_BOOKMARKWIDGET_H
#define OTTER_BOOKMARKWIDGET_H

#include <QtCore/QModelIndex>
#include <QtWidgets/QToolButton>

namespace Otter
{

class BookmarksItem;

class BookmarkWidget : public QToolButton
{
	Q_OBJECT

public:
	explicit BookmarkWidget(BookmarksItem *bookmark, QWidget *parent = NULL);
	explicit BookmarkWidget(const QString &path, QWidget *parent = NULL);

protected:
	void mouseReleaseEvent(QMouseEvent *event);

protected slots:
	void updateBookmark();

private:
	BookmarksItem *m_bookmark;
};

}

#endif