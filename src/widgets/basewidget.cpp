/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     kirigaya <kirigaya@mkacg.com>
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

#include "basewidget.h"
#include <DHiDPIHelper>
#include <QDebug>

DWIDGET_USE_NAMESPACE

BaseWidget::BaseWidget(QWidget *parent)
    : DFrame(parent)
    , m_layout(new QVBoxLayout(this))
    , m_title(new DLabel(this))
    , m_borderWidget(new BorderWidget(this))
{
    m_layout->setMargin(0);
    m_layout->setSpacing(16);

    m_layout->addStretch();
    m_layout->addWidget(m_borderWidget, 0, Qt::AlignCenter);
    m_layout->addWidget(m_title, 0, Qt::AlignCenter);
    m_layout->addStretch();
    setLineWidth(0);

    setLayout(m_layout);
}

void BaseWidget::setLayoutSpacing(int i)
{
    m_layout->setSpacing(i);
}

void BaseWidget::setBigPixmap(const QString &url)
{
    setBigPixmap(QPixmap(DHiDPIHelper::loadNxPixmap(url)));
}

void BaseWidget::setSmallPixmap(const QString &url)
{
    setSmallPixmap(QPixmap(DHiDPIHelper::loadNxPixmap(url)));
}

void BaseWidget::setPixmap(const QPixmap &pixmap)
{
    m_borderWidget->setFixedSize(pixmap.size() / devicePixelRatioF() + QSize(15, 20));
    m_borderWidget->setPixmap(pixmap);

    setFixedWidth(m_borderWidget->width());
}

void BaseWidget::setBigPixmap(const QPixmap &pixmap)
{
    QSize scaleSize = QSize(320, 200) * devicePixelRatioF();
    QPixmap scaledPixmap = pixmap.scaled(scaleSize, Qt::KeepAspectRatio);
    m_borderWidget->setFixedSize(QSize(320, 200) + QSize(10, 11));
    m_borderWidget->setPixmap(scaledPixmap);

    setFixedWidth(m_borderWidget->width());
}

void BaseWidget::setSmallPixmap(const QPixmap &pixmap)
{
    QSize scaleSize = QSize(240, 150) * devicePixelRatioF();
    QPixmap scaledPixmap = pixmap.scaled(scaleSize, Qt::KeepAspectRatio);
    m_borderWidget->setFixedSize(QSize(240, 150) + QSize(10, 10));
    m_borderWidget->setPixmap(scaledPixmap);

    setFixedWidth(m_borderWidget->width());
}

void BaseWidget::setTitle(const QString &title)
{
    m_title->setText(title);
}

void BaseWidget::setChecked(bool checked)
{
    m_borderWidget->setChecked(checked);
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QFrame::mouseReleaseEvent(event);

    emit clicked();
}

void BaseWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    return;
}

void BaseWidget::resizeEvent(QResizeEvent *event)
{
    DFrame::resizeEvent(event);

    emit sizeChanged();
}
