/**************************************************************************
* Otter Browser: Web browser controlled by the user, not vice-versa.
* Copyright (C) 2013 - 2017 Michal Dutkiewicz aka Emdek <michal@emdek.pl>
* Copyright (C) 2015 Piotr Wójcik <chocimier@tlen.pl>
* Copyright (C) 2016 - 2017 Jan Bajer aka bajasoft <jbajer@gmail.com>
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*
**************************************************************************/

#ifndef OTTER_WINDOW_H
#define OTTER_WINDOW_H

#include "ContentsWidget.h"
#include "WebWidget.h"
#include "../core/SessionsManager.h"
#include "../core/WindowsManager.h"

#include <QtCore/QDateTime>
#include <QtCore/QUrl>
#include <QtGui/QIcon>
#include <QtPrintSupport/QPrinter>
#include <QtWidgets/QUndoStack>
#include <QtWidgets/QWidget>

namespace Otter
{

class AddressWidget;
class ContentsWidget;
class SearchWidget;
class ToolBarWidget;

class Window : public QWidget
{
	Q_OBJECT

public:
	explicit Window(bool isPrivate, ContentsWidget *widget = nullptr, QWidget *parent = nullptr);

	void clear();
	void attachAddressWidget(AddressWidget *widget);
	void detachAddressWidget(AddressWidget *widget);
	void attachSearchWidget(SearchWidget *widget);
	void detachSearchWidget(SearchWidget *widget);
	void setOption(int identifier, const QVariant &value);
	void setSession(const SessionWindow &session);
	Window* clone(bool cloneHistory = true, QWidget *parent = nullptr);
	ContentsWidget* getContentsWidget();
	QString getSearchEngine() const;
	QString getTitle() const;
	QLatin1String getType() const;
	QVariant getOption(int identifier) const;
	QUrl getUrl() const;
	QIcon getIcon() const;
	QPixmap getThumbnail() const;
	QDateTime getLastActivity() const;
	WindowHistoryInformation getHistory() const;
	SessionWindow getSession() const;
	QSize sizeHint() const override;
	WindowsManager::LoadingState getLoadingState() const;
	WindowsManager::ContentStates getContentState() const;
	quint64 getIdentifier() const;
	bool canClone() const;
	bool isAboutToClose() const;
	bool isPinned() const;
	bool isPrivate() const;

public slots:
	void triggerAction(int identifier, const QVariantMap &parameters = QVariantMap());
	void close();
	void search(const QString &query, const QString &searchEngine);
	void markAsActive();
	void setSearchEngine(const QString &searchEngine);
	void setUrl(const QUrl &url, bool isTyped = true);
	void setToolBarsVisible(bool areVisible);
	void setPinned(bool isPinned);

protected:
	void timerEvent(QTimerEvent *event) override;
	void hideEvent(QHideEvent *event) override;
	void focusInEvent(QFocusEvent *event) override;
	void setContentsWidget(ContentsWidget *widget);
	AddressWidget* findAddressWidget() const;

protected slots:
	void handleIconChanged(const QIcon &icon);
	void handleOpenUrlRequest(const QUrl &url, WindowsManager::OpenHints hints);
	void handleSearchRequest(const QString &query, const QString &searchEngine, WindowsManager::OpenHints hints = WindowsManager::DefaultOpen);
	void handleGeometryChangeRequest(const QRect &geometry);
	void notifyRequestedCloseWindow();
	void updateNavigationBar();

private:
	ToolBarWidget *m_navigationBar;
	ContentsWidget *m_contentsWidget;
	QString m_searchEngine;
	QDateTime m_lastActivity;
	SessionWindow m_session;
	QList<QPointer<AddressWidget> > m_addressWidgets;
	QList<QPointer<SearchWidget> > m_searchWidgets;
	quint64 m_identifier;
	int m_suspendTimer;
	bool m_areToolBarsVisible;
	bool m_isAboutToClose;
	bool m_isPinned;
	bool m_isPrivate;

	static quint64 m_identifierCounter;

signals:
	void activated();
	void aboutToClose();
	void aboutToNavigate();
	void needsAttention();
	void requestedOpenBookmark(BookmarksItem *bookmark, WindowsManager::OpenHints hints);
	void requestedOpenUrl(const QUrl &url, WindowsManager::OpenHints hints);
	void requestedSearch(const QString &query, const QString &searchEngine, WindowsManager::OpenHints hints = WindowsManager::DefaultOpen);
	void requestedAddBookmark(const QUrl &url, const QString &title, const QString &description);
	void requestedEditBookmark(const QUrl &url);
	void requestedNewWindow(ContentsWidget *widget, WindowsManager::OpenHints hints);
	void requestedCloseWindow(Window *window);
	void searchEngineChanged(const QString &searchEngine);
	void statusMessageChanged(const QString &message);
	void titleChanged(const QString &title);
	void urlChanged(const QUrl &url, bool force = false);
	void iconChanged(const QIcon &icon);
	void requestBlocked(const NetworkManager::ResourceInformation &request);
	void contentStateChanged(WindowsManager::ContentStates state);
	void loadingStateChanged(WindowsManager::LoadingState state);
	void pageInformationChanged(WebWidget::PageInformation, const QVariant &value);
	void optionChanged(int identifier, const QVariant &value);
	void zoomChanged(int zoom);
	void canZoomChanged(bool can);
	void isPinnedChanged(bool isPinned);
	void widgetChanged();
};

}

#endif
