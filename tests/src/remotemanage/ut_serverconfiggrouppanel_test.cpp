/*
 *  Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd
 *
 * Author:     daizhengwen <daizhengwen@uniontech.com>
 *
 * Maintainer: daizhengwen <daizhengwen@uniontech.com>
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

#include "ut_serverconfiggrouppanel_test.h"

#include "serverconfiggrouppanel.h"
#include "service.h"
#include "mainwindow.h"

//Google GTest 相关头文件
#include <gtest/gtest.h>

//Qt单元测试相关头文件
#include <QTest>
#include <QtGui>

UT_ServerConfigGroupPanel_Test::UT_ServerConfigGroupPanel_Test()
{
}

void UT_ServerConfigGroupPanel_Test::SetUp()
{
    if (!Service::instance()->property("isServiceInit").toBool()) {
        Service::instance()->init();
        Service::instance()->setProperty("isServiceInit", true);
    }

    m_normalTermProperty[QuakeMode] = false;
    m_normalTermProperty[SingleFlag] = true;
    m_normalWindow = new NormalWindow(m_normalTermProperty, nullptr);
    m_normalWindow->resize(800, 600);
    m_normalWindow->show();
}

void UT_ServerConfigGroupPanel_Test::TearDown()
{
    delete m_normalWindow;
}

#ifdef UT_SERVERCONFIGGROUPPANEL_TEST
TEST_F(UT_ServerConfigGroupPanel_Test, refreshData)
{
    EXPECT_EQ(m_normalWindow->isVisible(), true);

    m_normalWindow->showPlugin(MainWindow::PLUGIN_TYPE_REMOTEMANAGEMENT);

    RemoteManagementPlugin *remotePlugin = m_normalWindow->findChild<RemoteManagementPlugin *>();
    RemoteManagementTopPanel *remoteTopPanel = remotePlugin->getRemoteManagementTopPanel();
    EXPECT_NE(remoteTopPanel, nullptr);
    EXPECT_EQ(remoteTopPanel->isVisible(), true);

    ServerConfigGroupPanel *groupPanel = remoteTopPanel->findChild<ServerConfigGroupPanel *>();
    EXPECT_NE(groupPanel, nullptr);
    groupPanel->refreshData("group01");
}

TEST_F(UT_ServerConfigGroupPanel_Test, setFocusBack)
{
    EXPECT_EQ(m_normalWindow->isVisible(), true);

    m_normalWindow->showPlugin(MainWindow::PLUGIN_TYPE_REMOTEMANAGEMENT);

    RemoteManagementPlugin *remotePlugin = m_normalWindow->findChild<RemoteManagementPlugin *>();
    RemoteManagementTopPanel *remoteTopPanel = remotePlugin->getRemoteManagementTopPanel();
    EXPECT_NE(remoteTopPanel, nullptr);
    EXPECT_EQ(remoteTopPanel->isVisible(), true);

    ServerConfigGroupPanel *groupPanel = remoteTopPanel->findChild<ServerConfigGroupPanel *>();
    EXPECT_NE(groupPanel, nullptr);
    groupPanel->setFocusBack();
}

TEST_F(UT_ServerConfigGroupPanel_Test, clearAllFocus)
{
    EXPECT_EQ(m_normalWindow->isVisible(), true);

    m_normalWindow->showPlugin(MainWindow::PLUGIN_TYPE_REMOTEMANAGEMENT);

    RemoteManagementPlugin *remotePlugin = m_normalWindow->findChild<RemoteManagementPlugin *>();
    RemoteManagementTopPanel *remoteTopPanel = remotePlugin->getRemoteManagementTopPanel();
    EXPECT_NE(remoteTopPanel, nullptr);
    EXPECT_EQ(remoteTopPanel->isVisible(), true);

    ServerConfigGroupPanel *groupPanel = remoteTopPanel->findChild<ServerConfigGroupPanel *>();
    EXPECT_NE(groupPanel, nullptr);
    groupPanel->clearAllFocus();

    EXPECT_EQ(groupPanel->m_rebackButton->hasFocus(), false);
    EXPECT_EQ(groupPanel->m_searchEdit->hasFocus(), false);
    EXPECT_EQ(groupPanel->m_listWidget->hasFocus(), false);
}

/*******************************************************************************
 1. @函数:    refreshDataTest
 2. @作者:    ut000610 戴正文
 3. @日期:    2020-12-24
 4. @说明:    刷新列表 => 组内数据
*******************************************************************************/
TEST_F(UT_ServerConfigGroupPanel_Test, refreshDataTest)
{
    // 创建分组
    ServerConfig groupConfig;
    groupConfig.m_serverName = "group_item";
    groupConfig.m_address = "127.0.0.1";
    groupConfig.m_group = "group2020";
    groupConfig.m_userName = "dzw";
    groupConfig.m_port = "22";
    // 分组数据存储结构
    QList<ServerConfig *> list;
    list.append(&groupConfig);
    // 数据存储结构
    // 清空数据
    ServerConfigManager::instance()->m_serverConfigs.clear();
    // 装填数据
    ServerConfigManager::instance()->m_serverConfigs.insert("group2020", list);

    // 新建界面
    ServerConfigGroupPanel groupPanel;
    // 刷新界面
    groupPanel.refreshData("group2020");
    // 界面下只有一个数据
    int count = groupPanel.m_listWidget->count();
    EXPECT_EQ(count, 1);

    // 不存在的组
    groupPanel.refreshData("group1988");
    count = groupPanel.m_listWidget->count();
    EXPECT_EQ(count, 0);

    // 清空数据
    ServerConfigManager::instance()->m_serverConfigs.clear();
}

/*******************************************************************************
 1. @函数:    setFocusBackTest
 2. @作者:    ut000610 戴正文
 3. @日期:    2020-12-24
 4. @说明:    测试界面返回
*******************************************************************************/
TEST_F(UT_ServerConfigGroupPanel_Test, setFocusBackTest)
{
    // 创建分组
    ServerConfig groupConfig;
    groupConfig.m_serverName = "group_item";
    groupConfig.m_address = "127.0.0.1";
    groupConfig.m_group = "group2020";
    groupConfig.m_userName = "dzw";
    groupConfig.m_port = "22";
    ServerConfig groupConfig2;
    groupConfig2.m_serverName = "group_item2";
    groupConfig2.m_address = "127.0.0.1";
    groupConfig2.m_group = "group2020";
    groupConfig2.m_userName = "dzw";
    groupConfig2.m_port = "22";
    // 分组数据存储结构
    QList<ServerConfig *> list;
    list.append(&groupConfig);
    list.append(&groupConfig);
    // 数据存储结构
    // 清空数据
    ServerConfigManager::instance()->m_serverConfigs.clear();
    // 装填数据
    ServerConfigManager::instance()->m_serverConfigs.insert("group2020", list);

    // 新建界面
    ServerConfigGroupPanel groupPanel;
    // 刷新界面
    groupPanel.refreshData("group2020");
    // 刷新搜索框状态
    groupPanel.refreshSearchState();

    // 两个数据 => 有搜索框
    groupPanel.setFocusBack();

    // 影藏搜索框
    groupPanel.m_searchEdit->hide();
    groupPanel.setFocusBack();

    // 清空数据
    ServerConfigManager::instance()->m_serverConfigs.clear();
    // 刷新界面
    groupPanel.refreshData("group2020");
    groupPanel.setFocusBack();
}

/*******************************************************************************
 1. @函数:    clearAllFocusTest
 2. @作者:    ut000610 戴正文
 3. @日期:    2020-12-24
 4. @说明:    测试清除焦点是否成功
*******************************************************************************/
TEST_F(UT_ServerConfigGroupPanel_Test, clearAllFocusTest)
{
    ServerConfigGroupPanel groupPanel;
    groupPanel.show();
    groupPanel.refreshData("group2020");
    groupPanel.clearAllFocus();
    EXPECT_EQ(groupPanel.m_rebackButton->hasFocus(), false);
    EXPECT_EQ(groupPanel.m_listWidget->hasFocus(), false);
    EXPECT_EQ(groupPanel.m_searchEdit->hasFocus(), false);
}

/*******************************************************************************
 1. @函数:    lambda
 2. @作者:    ut000610 戴正文
 3. @日期:    2020-12-24
 4. @说明:    测试lambda表达式,是否会影响进程
*******************************************************************************/
TEST_F(UT_ServerConfigGroupPanel_Test, lambda)
{
    // 初始化界面
    ServerConfigGroupPanel groupPanel;
    groupPanel.show();
    groupPanel.refreshData("group2020");
    groupPanel.m_isShow = true;

    // 焦点信号
    emit groupPanel.m_listWidget->focusOut(Qt::BacktabFocusReason);
    emit groupPanel.m_listWidget->focusOut(Qt::OtherFocusReason);
    emit groupPanel.m_listWidget->focusOut(Qt::NoFocusReason);


    emit ServerConfigManager::instance()->refreshList();


}
#endif
