/*
 *  Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd
 *
 * Author:     wangliang <wangliang@uniontech.com>
 *
 * Maintainer: wangliang <wangliang@uniontech.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ut_pagesearchbar_test.h"

#include "pagesearchbar.h"
#include "termwidgetpage.h"
#include "service.h"
#include "utils.h"

//Qt单元测试相关头文件
#include <QTest>
#include <QtGui>
#include <QSignalSpy>
#include <QDebug>
#include <QMainWindow>

UT_PageSearchBar_Test::UT_PageSearchBar_Test()
{
}

void UT_PageSearchBar_Test::SetUp()
{
    if (!Service::instance()->property("isServiceInit").toBool()) {
        Service::instance()->init();
        Service::instance()->setProperty("isServiceInit", true);
    }

    m_normalTermProperty[QuakeMode] = false;
    m_normalTermProperty[SingleFlag] = true;
    m_normalWindow = new NormalWindow(m_normalTermProperty, nullptr);
}

void UT_PageSearchBar_Test::TearDown()
{
    delete  m_normalWindow;
}

#ifdef UT_PAGESEARCHBAR_TEST
TEST_F(UT_PageSearchBar_Test, PageSearchBarTest)
{
    m_normalWindow->resize(800, 600);
    m_normalWindow->show();
    EXPECT_EQ(m_normalWindow->isVisible(), true);

    TermWidgetPage *termPage = m_normalWindow->currentPage();
    EXPECT_EQ(termPage->isVisible(), true);

    termPage->sendTextToCurrentTerm("ls -al\n");

    PageSearchBar *searchBar = termPage->m_findBar;
    termPage->showSearchBar(SearchBar_State::SearchBar_Show);
    EXPECT_EQ(searchBar->isVisible(), true);

    QString placeHolder = searchBar->m_originalPlaceHolder;
    searchBar->saveOldHoldContent();
    EXPECT_EQ(searchBar->m_searchEdit->placeHolder(), searchBar->m_originalPlaceHolder);
    searchBar->clearHoldContent();
    EXPECT_EQ(searchBar->m_searchEdit->placeHolder().length(), 0);
    searchBar->recoveryHoldContent();
    EXPECT_EQ(searchBar->m_searchEdit->placeHolder(), searchBar->m_originalPlaceHolder);

    QString searchTxt = searchBar->searchKeytxt();
    EXPECT_EQ(searchTxt.length(), 0);

    QString searchCmd = QString("rw");
    searchBar->m_searchEdit->setText(searchCmd);
    EXPECT_EQ(searchBar->m_searchEdit->text().length(), searchCmd.length());

    const int findNextCount = 2;
    //查找下一个'rw'字符串
    DIconButton *findNextButton = searchBar->m_findNextButton;
    QPoint clickPoint(3, 3);
    for (int i = 0; i < findNextCount; i++) {
        QSignalSpy spyNext(findNextButton, SIGNAL(clicked()));
        EXPECT_EQ(spyNext.count(), 0);
        QTest::mouseClick(findNextButton, Qt::LeftButton, Qt::NoModifier, clickPoint);
        EXPECT_EQ(spyNext.count(), 1);
    }

    const int findPrevCount = 2;
    //查找前一个rw
    for (int i = 0; i < findPrevCount; i++) {
        DIconButton *findPrevButton = searchBar->m_findPrevButton;
        QSignalSpy spyPrev(findPrevButton, SIGNAL(clicked()));
        EXPECT_EQ(spyPrev.count(), 0);
        QTest::mouseClick(findPrevButton, Qt::LeftButton, Qt::NoModifier, clickPoint);
        EXPECT_EQ(spyPrev.count(), 1);
    }
}
#endif
