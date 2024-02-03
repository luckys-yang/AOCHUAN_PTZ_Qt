#include "Panelitem.h"
#include <QPainter>
#include <QPainterPath>
#include <QTimer>

#ifdef QT_PanelItem_DEBUG
#include <QDebug>
#endif

PanelItem::PanelItem(QWidget* parent) : QWidget(parent)
{
    titleHeight = 30;
    titleText = "";
    titleFont = QFont(font().family(), 15);
    titleAlignment = Alignment_Center;
    titleColor = QColor(0, 0, 0);
    titleDisableColor = QColor(230, 230, 230);

    borderWidth = 3;
    borderRadius = 5;
    borderColor = QColor(21, 156, 119);
    borderDisableColor = QColor(180, 180, 180);

    alarmTextColor = QColor(250, 250, 250);
    alarmDarkColor = QColor(205, 0, 0);
    alarmNormalColor = QColor(80, 80, 80);
    alarmInterval = 500;

    isAlarm = false;
    isEnable = true;

    isDark = false;
    tempColor = borderColor;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(checkAlarm()));
    timer->setInterval(alarmInterval);
}

PanelItem::~PanelItem()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void PanelItem::paintEvent(QPaintEvent*)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制边框
    drawBorder(&painter);
    //绘制标题
    drawTitle(&painter);
}

void PanelItem::drawBorder(QPainter* painter)
{
    // 如果边框宽度小于等于0，直接返回。
    if (borderWidth <= 0) {
        return;
    }

    // 保存当前绘图状态。
    painter->save();

    // 设置画笔属性。
    QPen pen;
    pen.setWidth(borderWidth);
    pen.setColor(tempColor);

    // 应用画笔和无刷。
    painter->setPen(pen);
    painter->setBrush(Qt::NoBrush);

    // 创建圆角矩形的区域。
    QRect rect(borderWidth / 2, borderWidth / 2, width() - borderWidth, height() - borderWidth);

    // 绘制圆角矩形边框。
    painter->drawRoundedRect(rect, borderRadius, borderRadius);

    // 恢复绘图状态。
    painter->restore();
}

void PanelItem::drawTitle(QPainter* painter)
{
    // 保存当前绘图状态。
    painter->save();

    // 设置画笔和刷子。
    painter->setPen(Qt::NoPen);
    painter->setBrush(tempColor);

    // 创建标题区域的矩形。
    int offset = borderWidth - borderWidth / 3;
    QRect rect(offset, offset, width() - offset * 2, titleHeight);

    // 绘制标题区域。
    painter->drawRect(rect);

    // 绘制标题文字。
    if (isEnable) {
        // 如果启用，根据是否有警报设置画笔颜色。
        painter->setPen(isAlarm ? alarmTextColor : titleColor);
    }
    else {
        // 如果禁用，使用禁用状态的标题颜色。
        painter->setPen(titleDisableColor);
    }

    // 设置标题文字的字体。
    painter->setFont(titleFont);

    // 重新计算文字区域。
    offset = borderWidth * 3;
    QRect textRect(offset, 0, width() - offset * 2, titleHeight);

    // 根据标题对齐方式设置对齐属性。
    Qt::Alignment align;
    if (titleAlignment == Alignment_Left) {
        align = Qt::AlignLeft | Qt::AlignVCenter;
    }
    else if (titleAlignment == Alignment_Center) {
        align = Qt::AlignHCenter | Qt::AlignVCenter;
    }
    else if (titleAlignment == Alignment_Right) {
        align = Qt::AlignRight | Qt::AlignVCenter;
    }

    // 绘制标题文字。
    painter->drawText(textRect, align, titleText);

    // 恢复绘图状态。
    painter->restore();
}

int PanelItem::getTitleHeight() const
{
    return this->titleHeight;
}

QString PanelItem::getTitleText() const
{
    return this->titleText;
}

QFont PanelItem::getTitleFont() const
{
    return this->titleFont;
}

PanelItem::Alignment PanelItem::getTitleAlignment() const
{
    return this->titleAlignment;
}

QColor PanelItem::getTitleColor() const
{
    return this->titleColor;
}

QColor PanelItem::getTitleDisableColor() const
{
    return this->titleDisableColor;
}

int PanelItem::getBorderWidth() const
{
    return this->borderWidth;
}

int PanelItem::getBorderRadius() const
{
    return this->borderRadius;
}

QColor PanelItem::getBorderColor() const
{
    return this->borderColor;
}

QColor PanelItem::getBorderDisableColor() const
{
    return this->borderDisableColor;
}

int PanelItem::getAlarmInterval() const
{
    return this->alarmInterval;
}

QColor PanelItem::getAlarmTextColor() const
{
    return this->alarmTextColor;
}

QColor PanelItem::getAlarmDarkColor() const
{
    return this->alarmDarkColor;
}

QColor PanelItem::getAlarmNormalColor() const
{
    return this->alarmNormalColor;
}

bool PanelItem::getIsAlarm() const
{
    return this->isAlarm;
}

bool PanelItem::getIsEnable() const
{
    return this->isEnable;
}

QSize PanelItem::sizeHint() const
{
    return QSize(250, 200);
}

QSize PanelItem::minimumSizeHint() const
{
    return QSize(30, 20);
}

void PanelItem::checkAlarm()
{
    // 根据当前是否为暗模式切换临时颜色。
    if (isDark) {
        tempColor = alarmNormalColor;
    }
    else {
        tempColor = alarmDarkColor;
    }

    // 切换暗模式标志。
    isDark = !isDark;

    // 更新绘图。
    this->update();
}

void PanelItem::setAlarm(bool alarm)
{
    // 如果组件未启用，直接返回。
    if (!isEnable) {
        return;
    }

    // 设置警报状态。
    isAlarm = alarm;

    // 处理警报启用和禁用逻辑。
    if (alarm) {
        // 如果警报启用，且定时器未启动，则启动定时器。
        if (!timer->isActive()) {
            timer->start();
        }

        // 初始化暗模式和临时颜色。
        isDark = true;
        tempColor = alarmDarkColor;
    }
    else {
        // 如果警报禁用，且定时器正在运行，则停止定时器。
        if (timer->isActive()) {
            timer->stop();
        }

        // 初始化暗模式和临时颜色。
        isDark = false;
        tempColor = borderColor;
    }

    // 更新绘图。
    this->update();
}

void PanelItem::setEnable(bool enable)
{
    // 设置组件的启用禁用状态。
    isEnable = enable;

    // 如果定时器正在运行，停止定时器。
    if (timer->isActive()) {
        timer->stop();
    }

    // 根据启用禁用状态设置临时颜色。
    if (enable) {
        tempColor = borderColor;
    }
    else {
        tempColor = borderDisableColor;
    }

    // 更新绘图。
    this->update();

    // 将子元素的启用禁用状态同步设置。
    QList<QWidget*> widgets = this->findChildren<QWidget*>();
    foreach(QWidget * w, widgets) {
        w->setEnabled(enable);
    }
}


void PanelItem::setTitleHeight(int titleHeight)
{
    if (this->titleHeight != titleHeight) {
        this->titleHeight = titleHeight;
        this->update();
    }
}

void PanelItem::setTitleText(const QString& titleText)
{
    if (this->titleText != titleText) {
        this->titleText = titleText;
        this->update();
    }
}

void PanelItem::setTitleFont(const QFont& titleFont)
{
    if (this->titleFont != titleFont) {
        this->titleFont = titleFont;
        this->update();
    }
}

void PanelItem::setTitleAlignment(const Alignment& titleAlignment)
{
    if (this->titleAlignment != titleAlignment) {
        this->titleAlignment = titleAlignment;
        this->update();
    }
}

void PanelItem::setTitleColor(const QColor& titleColor)
{
    if (this->titleColor != titleColor) {
        this->titleColor = titleColor;
        this->update();
    }
}

void PanelItem::setTitleDisableColor(const QColor& titleDisableColor)
{
    if (this->titleDisableColor != titleDisableColor) {
        this->titleDisableColor = titleDisableColor;
        this->update();
    }
}

void PanelItem::setBorderWidth(int borderWidth)
{
    if (this->borderWidth != borderWidth) {
        this->borderWidth = borderWidth;
        this->update();
    }
}

void PanelItem::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        this->update();
    }
}

void PanelItem::setBorderColor(const QColor& borderColor)
{
    if (this->borderColor != borderColor) {
        this->borderColor = borderColor;
        setEnable(isEnable);
        this->update();
    }
}

void PanelItem::setBorderDisableColor(const QColor& borderDisableColor)
{
    if (this->borderDisableColor != borderDisableColor) {
        this->borderDisableColor = borderDisableColor;
        setEnable(isEnable);
        this->update();
    }
}

void PanelItem::setAlarmInterval(int alarmInterval)
{
    if (this->alarmInterval != alarmInterval && alarmInterval >= 100) {
        this->alarmInterval = alarmInterval;
        timer->setInterval(alarmInterval);
    }
}

void PanelItem::setAlarmTextColor(const QColor& alarmTextColor)
{
    if (this->alarmTextColor != alarmTextColor) {
        this->alarmTextColor = alarmTextColor;
        this->update();
    }
}

void PanelItem::setAlarmDarkColor(const QColor& alarmDarkColor)
{
    if (this->alarmDarkColor != alarmDarkColor) {
        this->alarmDarkColor = alarmDarkColor;
        setAlarm(isAlarm);
        this->update();
    }
}

void PanelItem::setAlarmNormalColor(const QColor& alarmNormalColor)
{
    if (this->alarmNormalColor != alarmNormalColor) {
        this->alarmNormalColor = alarmNormalColor;
        setAlarm(isAlarm);
        this->update();
    }
}