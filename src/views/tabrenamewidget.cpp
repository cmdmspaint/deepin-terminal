/*
 *  Copyright (C) 2019 ~ 2020 Uniontech Software Technology Co.,Ltd
 *
 * Author:     zhaogongqiang <zhaogongqiang@uniontech.com>
 *
 * Maintainer: zhaogongqiang <zhaogongqiang@uniontech.com>
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

#include "tabrenamewidget.h"
#include <QDebug>
#include <QKeyEvent>

#include <DFontSizeManager>

TabRenameWidget::TabRenameWidget(bool isRemote, bool isSetting, QWidget *parent)
    : QWidget(parent)
    , m_isRemote(isRemote)
    , m_isSetting(isSetting)
{
    initChoseMenu();
    initUi();
    initConnections();
}

void TabRenameWidget::initUi()
{
    m_layout = new QHBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    // 设置布局之间的宽度,之前的间距比较宽
    m_layout->setSpacing(10);
    // widet 自己设置0 0 0 0
    this->setContentsMargins(0, 0, 0, 0);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    // 内容输入框
    m_inputedit = new DLineEdit(this);
    m_inputedit->setText("%n:%d");
    m_inputedit->setMaximumSize(172, 36);
    m_inputedit->setMinimumSize(135, 36);
    DFontSizeManager::instance()->bind(m_inputedit, DFontSizeManager::T6);

    // 插入按钮
    m_choseButton = new DPushButton(tr("Insert"), this);
    m_choseButton->setMaximumHeight(36);
    // 添加下拉菜单
    m_choseButton->setMenu(m_choseMenu);
    DFontSizeManager::instance()->bind(m_choseButton, DFontSizeManager::T6);
    m_choseButton->setAutoDefault(false);
    m_choseButton->setDefault(false);

    //  设置界面隐藏clearbutton并且不需要初始化标题 重命名窗口不用隐藏clearbutton需要初始化标题
    if (!m_isSetting) {
        initLabel();
    } else {
        m_inputedit->lineEdit()->setClearButtonEnabled(false);
    }

    m_layout->addWidget(m_inputedit);
    m_layout->addWidget(m_choseButton);
}

void TabRenameWidget::initChoseMenu()
{
    m_choseMenu = new DMenu(this);
    DFontSizeManager::instance()->bind(m_choseMenu, DFontSizeManager::T6);
    if (m_isRemote) {
        // 初始化远程菜单
        initRemoteChoseMenu();
    } else {
        // 初始化正常菜单
        initNormalChoseMenu();
    }
}

void TabRenameWidget::initRemoteChoseMenu()
{
    QStringList list;
    list << tr("username: %u") << tr("username@: %U") << tr("remote host: %h")
         << tr("session number: %#") << tr("title set by shell: %w");

    foreach (auto it, list) {
        QAction *ac = new QAction(it, m_choseMenu);
        m_choseMenu->addAction(ac);
    }
}

void TabRenameWidget::initNormalChoseMenu()
{
    QStringList list;
    list << tr("program name: %n") << tr("current directory (short): %d")
         << tr("current directory (long): %D") << tr("session number: %#")
         << tr("username: %u") << tr("local host: %h")
         << tr("title set by shell: %w");

    foreach (auto it, list) {
        QAction *ac = new QAction(it, m_choseMenu);
        m_choseMenu->addAction(ac);
    }
}

void TabRenameWidget::initConnections()
{
    connect(m_choseMenu, &DMenu::triggered, this, [ = ](QAction * ac) {
        QStringList spiltlist = ac->text().split("%");
        m_inputedit->lineEdit()->insert("%" + spiltlist.at(1));
        //向输入条中输入内容后，焦点应该同步设置过去
        m_inputedit->lineEdit()->setFocus(Qt::MouseFocusReason);
    });
}

void TabRenameWidget::initLabel()
{
    m_Label = new QLabel;
    if (!m_isRemote) {
        m_Label->setText(QObject::tr("Tab title format"));
    } else {
        m_Label->setText(QObject::tr("Remote tab title format"));
    }

    DFontSizeManager::instance()->bind(m_Label, DFontSizeManager::T6);

    // label要跟随字体扩展 => 所有控件都扩展效果不好
    m_Label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_layout->addWidget(m_Label);
}

DLineEdit *TabRenameWidget::getInputedit() const
{
    return m_inputedit;
}


