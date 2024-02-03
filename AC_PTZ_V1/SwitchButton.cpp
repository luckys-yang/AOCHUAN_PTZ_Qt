#pragma execution_character_set("utf-8")  // 防止MSVC编译器乱码的，如果不使用MSVC编译器则可以移除

#include "SwitchButton.h"
#include <QPainterPath>
#include <QEvent>
#include <QTimer>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

SwitchButton::SwitchButton(QWidget* parent) : QWidget(parent)
{
    space = 2; // 设置默认间距为2
    rectRadius = 5; // 设置默认圆角半径为5
    checked = false; // 初始状态为未选中
    showText = true; // 默认显示文本
    showCircle = false; // 默认不显示圆形
    animation = false; // 默认无动画

    buttonStyle = ButtonStyle_CircleIn; // 默认按钮样式为圆形内部

    // 整体背景颜色
    bgColorOff = QColor(111, 122, 126); // 关闭状态背景颜色
    bgColorOn = QColor(21, 156, 119); // 打开状态背景颜色

    // 那个圆圈的颜色
    sliderColorOff = QColor(255, 255, 255); // 关闭状态滑块颜色
    sliderColorOn = QColor(255, 255, 255); // 打开状态滑块颜色

    textColorOff = QColor(0, 0, 0); // 关闭状态文本颜色
    textColorOn = QColor(0, 0, 0); // 打开状态文本颜色

    textOff = "关闭"; // 关闭状态文本
    textOn = "开启"; // 打开状态文本

    step = 0;
    startX = 0;
    endX = 0;

    timer = new QTimer(this);
    timer->setInterval(5); // 设置定时器间隔为30毫秒
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue())); // 连接定时器的超时信号到更新数值的槽函数
}

SwitchButton::~SwitchButton()
{
    if (timer->isActive())
    {
        timer->stop(); // 如果定时器在活动状态，则停止定时器
    }
}

void SwitchButton::mouseReleaseEvent(QMouseEvent* event)
{
    if (event->button() != Qt::LeftButton)  // 不是左键按下则退出
    {
        return;
    }

    // 获取了全局鼠标位置
    QPoint mousePos = QCursor::pos();
    QPoint localPos = this->mapFromGlobal(mousePos);

    if (this->rect().contains(localPos))    // 检查局部坐标是否在窗口的矩形区域内
    {
        //checked = !checked; // 切换选择状态
        emit checkedChanged(checked);  // 触发信号
    }
    QWidget::mouseReleaseEvent(event);
}

void SwitchButton::resizeEvent(QResizeEvent*)
{
    //每次移动的步长为宽度的 50分之一
    step = width() / 50; // 根据宽度计算移动步长

    //尺寸大小改变后自动设置起点坐标为终点
    if (checked)
    {
        if (buttonStyle == ButtonStyle_Rect)
        {
            startX = width() - width() / 2;
        }
        else if (buttonStyle == ButtonStyle_CircleIn)
        {
            startX = width() - height();
        }
        else if (buttonStyle == ButtonStyle_CircleOut)
        {
            startX = width() - height();
        }
    }
    else
    {
        startX = 0;
    }

    this->update(); // 更新界面
}

void SwitchButton::paintEvent(QPaintEvent*)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制滑块
    drawSlider(&painter);
}

void SwitchButton::drawBg(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    QColor bgColor = checked ? bgColorOn : bgColorOff; // 根据选择状态确定背景颜色
    if (!isEnabled())
    {
        bgColor.setAlpha(60); // 如果控件不可用，降低背景颜色的透明度
    }

    painter->setBrush(bgColor);

    if (buttonStyle == ButtonStyle_Rect)
    {
        painter->drawRoundedRect(rect(), rectRadius, rectRadius); // 绘制圆角矩形
    }
    else if (buttonStyle == ButtonStyle_CircleIn)
    {
        // 绘制内部圆形开关
        QRect rect(0, 0, width(), height());
        int side = qMin(rect.width(), rect.height());

        //左侧圆
        QPainterPath path1;
        path1.addEllipse(rect.x(), rect.y(), side, side);
        //右侧圆
        QPainterPath path2;
        path2.addEllipse(rect.width() - side, rect.y(), side, side);
        //中间矩形
        QPainterPath path3;
        path3.addRect(rect.x() + side / 2, rect.y(), rect.width() - side, rect.height());

        QPainterPath path;
        path = path3 + path1 + path2; // 合并路径
        painter->drawPath(path);
    }
    else if (buttonStyle == ButtonStyle_CircleOut)
    {
        // 绘制外部圆形开关
        QRect rect(height() / 2, space, width() - height(), height() - space * 2);
        painter->drawRoundedRect(rect, rectRadius, rectRadius); // 绘制圆角矩形
    }

    //绘制文本和小圆,互斥
    if (buttonStyle == ButtonStyle_Rect || buttonStyle == ButtonStyle_CircleIn)
    {
        // 绘制文本和小圆
        if (showText)
        {
            int sliderWidth = qMin(width(), height()) - space * 2;
            if (buttonStyle == ButtonStyle_Rect)
            {
                sliderWidth = width() / 2 - 5;
            }
            else if (buttonStyle == ButtonStyle_CircleIn)
            {
                sliderWidth -= 5;
            }

            painter->setFont(font); // 设置字体

            if (checked)
            {
                QRect textRect(0, 0, width() - sliderWidth, height());
                painter->setPen(textColorOn);
                painter->drawText(textRect, Qt::AlignCenter, textOn);
            }
            else
            {
                QRect textRect(sliderWidth, 0, width() - sliderWidth, height());
                painter->setPen(textColorOff);
                painter->drawText(textRect, Qt::AlignCenter, textOff);
            }
        }
        else if (showCircle)
        {
            int side = qMin(width(), height()) / 2;
            int y = (height() - side) / 2;

            if (checked)
            {
                QRect circleRect(side / 2, y, side, side);
                QPen pen(textColorOn, 2);
                painter->setPen(pen);
                painter->setBrush(Qt::NoBrush);
                painter->drawEllipse(circleRect);
            }
            else
            {
                QRect circleRect(width() - (side * 1.5), y, side, side);
                QPen pen(textColorOff, 2);
                painter->setPen(pen);
                painter->setBrush(Qt::NoBrush);
                painter->drawEllipse(circleRect);
            }
        }
    }

    painter->restore();
}

void SwitchButton::drawSlider(QPainter* painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    if (!checked)
    {
        painter->setBrush(sliderColorOff);
    }
    else
    {
        painter->setBrush(sliderColorOn);
    }

    if (buttonStyle == ButtonStyle_Rect)
    {
        int sliderWidth = width() / 2 - space * 2;
        int sliderHeight = height() - space * 2;
        QRect sliderRect(startX + space, space, sliderWidth, sliderHeight);
        painter->drawRoundedRect(sliderRect, rectRadius, rectRadius);
    }
    else if (buttonStyle == ButtonStyle_CircleIn)
    {
        QRect rect(0, 0, width(), height());
        int sliderWidth = qMin(rect.width(), rect.height()) - space * 2;
        QRect sliderRect(startX + space, space, sliderWidth, sliderWidth);
        painter->drawEllipse(sliderRect);
    }
    else if (buttonStyle == ButtonStyle_CircleOut)
    {
        int sliderWidth = this->height();
        QRect sliderRect(startX, 0, sliderWidth, sliderWidth);

        QColor color1 = (checked ? Qt::white : bgColorOff);
        QColor color2 = (checked ? sliderColorOn : sliderColorOff);

        QRadialGradient radialGradient(sliderRect.center(), sliderWidth / 2);
        radialGradient.setColorAt(0, checked ? color1 : color2);
        radialGradient.setColorAt(0.5, checked ? color1 : color2);
        radialGradient.setColorAt(0.6, checked ? color2 : color1);
        radialGradient.setColorAt(1.0, checked ? color2 : color1);
        painter->setBrush(radialGradient);

        painter->drawEllipse(sliderRect);
    }

    painter->restore();
}

void SwitchButton::change()
{
    mouseReleaseEvent(NULL); // 调用鼠标点击事件实现状态切换
}

void SwitchButton::updateValue()
{
    if (checked)
    {
        if (startX < endX)
        {
            startX = startX + step; // 移动滑块
        }
        else
        {
            startX = endX;
            timer->stop(); // 达到终点后停止定时器
        }
    }
    else
    {
        if (startX > endX)
        {
            startX = startX - step; // 移动滑块
        }
        else
        {
            startX = endX;
            timer->stop(); // 达到终点后停止定时器
        }
    }

    this->update(); // 更新界面
}


int SwitchButton::getSpace() const
{
    return this->space;
}

int SwitchButton::getRectRadius() const
{
    return this->rectRadius;
}

bool SwitchButton::getChecked() const
{
    return this->checked;
}

bool SwitchButton::getShowText() const
{
    return this->showText;
}

bool SwitchButton::getShowCircle() const
{
    return this->showCircle;
}

bool SwitchButton::getAnimation() const
{
    return this->animation;
}

SwitchButton::ButtonStyle SwitchButton::getButtonStyle() const
{
    return this->buttonStyle;
}

QColor SwitchButton::getBgColorOff() const
{
    return bgColorOff;
}

QColor SwitchButton::getBgColorOn() const
{
    return this->bgColorOn;
}

QColor SwitchButton::getSliderColorOff() const
{
    return this->sliderColorOff;
}

QColor SwitchButton::getSliderColorOn() const
{
    return this->sliderColorOn;
}

QColor SwitchButton::getTextColorOff() const
{
    return this->textColorOff;
}

QColor SwitchButton::getTextColorOn() const
{
    return this->textColorOn;
}

QString SwitchButton::getTextOff() const
{
    return this->textOff;
}

QString SwitchButton::getTextOn() const
{
    return this->textOn;
}

QSize SwitchButton::sizeHint() const
{
    return QSize(70, 30);
}

QSize SwitchButton::minimumSizeHint() const
{
    return QSize(10, 5);
}

void SwitchButton::setSpace(int space)
{
    if (this->space != space)
    {
        this->space = space;
        this->update();
    }
}

void SwitchButton::setRectRadius(int rectRadius)
{
    if (this->rectRadius != rectRadius)
    {
        this->rectRadius = rectRadius;
        this->update();
    }
}

void SwitchButton::setChecked(bool checked)
{
    //如果刚刚初始化完成的属性改变则延时处理
    if (this->checked != checked)
    {
        if (step == 0)
        {
            QTimer::singleShot(10, this, SLOT(setButtonOnOff(checked)));
        }
        else
        {
            setButtonOnOff(checked);
            //mouseReleaseEvent(NULL);
        }
    }
}

void SwitchButton::setShowText(bool showText)
{
    if (this->showText != showText)
    {
        this->showText = showText;
        this->update();
    }
}

void SwitchButton::setShowCircle(bool showCircle)
{
    if (this->showCircle != showCircle)
    {
        this->showCircle = showCircle;
        this->update();
    }
}

void SwitchButton::setAnimation(bool animation)
{
    if (this->animation != animation)
    {
        this->animation = animation;
        this->update();
    }
}

void SwitchButton::setButtonStyle(const SwitchButton::ButtonStyle& buttonStyle)
{
    if (this->buttonStyle != buttonStyle)
    {
        this->buttonStyle = buttonStyle;
        this->update();
    }
}

void SwitchButton::setBgColorOff(const QColor& bgColorOff)
{
    if (this->bgColorOff != bgColorOff)
    {
        this->bgColorOff = bgColorOff;
        this->update();
    }
}

void SwitchButton::setBgColorOn(const QColor& bgColorOn)
{
    if (this->bgColorOn != bgColorOn)
    {
        this->bgColorOn = bgColorOn;
        this->update();
    }
}

void SwitchButton::setSliderColorOff(const QColor& sliderColorOff)
{
    if (this->sliderColorOff != sliderColorOff)
    {
        this->sliderColorOff = sliderColorOff;
        this->update();
    }
}

void SwitchButton::setSliderColorOn(const QColor& sliderColorOn)
{
    if (this->sliderColorOn != sliderColorOn)
    {
        this->sliderColorOn = sliderColorOn;
        this->update();
    }
}

void SwitchButton::setTextColorOff(const QColor& textColorOff)
{
    if (this->textColorOff != textColorOff)
    {
        this->textColorOff = textColorOff;
        this->update();
    }
}

void SwitchButton::setTextColorOn(const QColor& textColorOn)
{
    if (this->textColorOn != textColorOn)
    {
        this->textColorOn = textColorOn;
        this->update();
    }
}

void SwitchButton::setTextOff(const QString& textOff)
{
    if (this->textOff != textOff)
    {
        this->textOff = textOff;
        this->update();
    }
}

void SwitchButton::setTextOn(const QString& textOn)
{
    if (this->textOn != textOn)
    {
        this->textOn = textOn;
        this->update();
    }
}

void SwitchButton::setTextFont(QFont font)
{
    this->font = font;
    this->update();
}

void SwitchButton::setButtonOnOff(bool status)
{
    if (this->checked != status)
    {
        this->checked = status;

        //每次移动的步长
        step = width() / 7; // 计算移动步长

        if (true == status)    // 关闭
        {
            if (buttonStyle == ButtonStyle_Rect)
            {
                endX = width() - width() / 2;
            }
            else if (buttonStyle == ButtonStyle_CircleIn)
            {
                endX = width() - height();
            }
            else if (buttonStyle == ButtonStyle_CircleOut)
            {
                endX = width() - height();
            }
        }
        else
        {
            endX = 0;
        }

        if (animation)
        {
            timer->start(); // 如果需要动画效果，则启动定时器
        }
        else
        {
            startX = endX;
            this->update(); // 否则立即更新界面
        }
    }
}
