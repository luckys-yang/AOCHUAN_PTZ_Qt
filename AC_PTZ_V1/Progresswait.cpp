#include "Progresswait.h"
#include "qpainter.h"
#include <QPainterPath>
#include "qtimer.h"
#include "qmath.h"
#include "qdebug.h"

// 计算数值
#define DISPLAY_MAX_VALUE 10

ProgressWait::ProgressWait(QWidget* parent)
    : QWidget(parent)
{
    /*默认初始化属性值*/

    clockWise = true; // 进度条方向为顺时针
    showPercent = false; // 不显示百分比
    currentValue = 0; // 当前数值为0
    maxValue = 10; // 最大数值为10
    interval = 100; // 定时器间隔为100毫秒

    barStyle = BarStyle_Line; // 进度条样式为线形
    background = QColor(255, 255, 255); // 背景颜色为白色
    foreground = QColor(100, 184, 255); // 前景颜色为淡蓝色
    textColor = QColor(100, 184, 255); // 文本颜色为淡蓝色

    resizeEvent(NULL); // 调用重写的 resizeEvent 函数进行初始化

    // 创建定时器并连接到槽函数 updateValue
    timer = new QTimer(this);
    timer->setInterval(interval);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    //setFont(QFont("Arial", 8)); // 设置字体为 Arial，字号为 8
}

ProgressWait::~ProgressWait()
{
    if (timer->isActive())  // 如果定时器正在运行，停止它
    {
        timer->stop();
    }
#ifdef QT_ProgressWait_DEBUG
    qDebug() << "delete ProgressWait";
#endif
}

// 重写大小调整事件
void ProgressWait::resizeEvent(QResizeEvent*)
{
    // 如果进度条样式为双圆形
    if (barStyle == BarStyle_DoubleCircle)
    {
        // 初始化双圆形的半径和增量属性
        int radius = 200; // 双圆形的总半径
        minRadius = radius / 10; // 左侧圆的最小半径
        maxRadius = radius / 5; // 右侧圆的最大半径
        offsetRadius = radius / 30; // 圆之间的偏移
        leftRadius = minRadius; // 左侧圆的当前半径
        rightRadius = maxRadius; // 右侧圆的当前半径
        leftIncrease = true; // 左侧圆半径是否递增
        rightIncrease = false; // 右侧圆半径是否递增
    }
}


// 重写绘制事件
void ProgressWait::paintEvent(QPaintEvent*)
{
    // 获取控件宽度和高度，并计算较小的一边作为绘制的边长
    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    QPainter painter(this);
    // 启用反锯齿和文本反锯齿
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    // 平移坐标轴中心
    painter.translate(width / 2, height / 2);
    // 等比例缩放，以较小的一边作为绘制的边长
    painter.scale(side / 200.0, side / 200.0);

    // 根据进度条样式选择相应的绘制函数
    if (barStyle == BarStyle_Arc)
    {
        drawArc(&painter);
    }
    else if (barStyle == BarStyle_RoundCircle)
    {
        drawRoundCircle(&painter);
    }
    else if (barStyle == BarStyle_Pie)
    {
        drawPie(&painter);
    }
    else if (barStyle == BarStyle_Line)
    {
        drawLine(&painter);
    }
    else if (barStyle == BarStyle_Ring)
    {
        drawRing(&painter);
    }
    else if (barStyle == BarStyle_SingleCircle)
    {
        drawSingleCircle(&painter);
    }
    else if (barStyle == BarStyle_DoubleCircle)
    {
        drawDoubleCircle(&painter);
    }

    // 绘制数值显示
    drawValue(&painter);
}


// 绘制 Arc 样式的进度条
void ProgressWait::drawArc(QPainter* painter)
{
    painter->save(); // 保存绘制状态

    painter->setPen(Qt::NoPen); // 设置画笔为透明

    // 计算中心点坐标
    int centerX = 0;
    int centerY = 0;
    int radius = 99; // 大圆半径
    int radiusBig = radius / 2; // 八卦大圆半径
    int radiusSmall = radius / 6; // 八卦小圆半径
    double currentangle = currentValue * (360 / (maxValue + 1)); // 当前角度

    if (clockWise)
    {
        currentangle = -currentangle; // 如果是顺时针旋转，取反角度
    }

    // 绘制八卦大圆1
    painter->setBrush(foreground); // 设置画刷颜色
    QPainterPath pathBig1(QPointF(centerX + radius * qCos(degreesToRadians(currentangle)),
        centerY - radius * qSin(degreesToRadians(currentangle))));
    pathBig1.arcTo(centerX - radius, centerY - radius, radius * 2, radius * 2, currentangle, 180);
    pathBig1.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle + 180)) - radiusBig,
        centerY - radiusBig * qSin(degreesToRadians(currentangle + 180)) - radiusBig,
        radiusBig * 2, radiusBig * 2, currentangle + 180, 180);
    pathBig1.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle)) - radiusBig,
        centerY - radiusBig * qSin(degreesToRadians(currentangle)) - radiusBig,
        radiusBig * 2, radiusBig * 2, currentangle + 180, -180);
    painter->drawPath(pathBig1);

    // 绘制八卦大圆2
    painter->setBrush(background); // 设置画刷颜色
    QPainterPath pathBig2(QPointF(centerX + radius * qCos(degreesToRadians(currentangle)),
        centerY - radius * qSin(degreesToRadians(currentangle))));
    pathBig2.arcTo(centerX - radius, centerY - radius, radius * 2, radius * 2, currentangle, -180);
    pathBig2.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle + 180)) - radiusBig,
        centerY - radiusBig * qSin(degreesToRadians(currentangle + 180)) - radiusBig,
        radiusBig * 2, radiusBig * 2, currentangle + 180, 180);
    pathBig2.arcTo(centerX + radiusBig * qCos(degreesToRadians(currentangle)) - radiusBig,
        centerY - radiusBig * qSin(degreesToRadians(currentangle)) - radiusBig,
        radiusBig * 2, radiusBig * 2, currentangle + 180, -180);
    painter->drawPath(pathBig2);

    // 绘制八卦小圆1
    painter->setBrush(foreground); // 设置画刷颜色
    QPainterPath pathSmall1;
    pathSmall1.addEllipse(centerX + radiusBig * qCos(degreesToRadians(currentangle)) - radiusSmall,
        centerY - radiusBig * qSin(degreesToRadians(currentangle)) - radiusSmall,
        radiusSmall * 2, radiusSmall * 2);
    painter->drawPath(pathSmall1);

    // 绘制八卦小圆2
    painter->setBrush(background); // 设置画刷颜色
    QPainterPath pathSmall2;
    pathSmall2.addEllipse(centerX + radiusBig * qCos(degreesToRadians(180 + currentangle)) - radiusSmall,
        centerY - radiusBig * qSin(degreesToRadians(180 + currentangle)) - radiusSmall,
        radiusSmall * 2, radiusSmall * 2);
    painter->drawPath(pathSmall2);

    painter->restore(); // 恢复绘制状态
}


// 绘制 RoundCircle 样式的进度条
void ProgressWait::drawRoundCircle(QPainter* painter)
{
    painter->save(); // 保存绘制状态

    painter->setPen(Qt::NoPen); // 设置画笔为透明

    int radius = 99; // 大圆半径
    int minRadius = radius / 6; // 圆的最小半径
    double angleStep = 360.0 / maxValue; // 每个圆之间的角度步进值
    double alpha = (double)1 / maxValue; // 透明度增量

    if (!clockWise)
    {
        angleStep = -angleStep; // 如果是逆时针旋转，取反角度步进值
    }

    // 计算中心点坐标
    int centerX = 0;
    int centerY = 0;
    double centerRadius = radius / 1.2;

    for (int i = 0; i < maxValue; i++)
    {
        double angle = (currentValue + i) * angleStep;
        double initX = centerRadius * qCos(degreesToRadians(angle)) + centerX;
        double initY = centerRadius * qSin(degreesToRadians(angle)) + centerY;

        int value = i * alpha * 255;
        value = value < 30 ? 30 : value; // 限制透明度的最小值

        foreground.setAlpha(value); // 设置画刷颜色的透明度
        painter->setBrush(foreground); // 设置画刷颜色
        painter->drawEllipse(initX - minRadius, initY - minRadius, minRadius * 2, minRadius * 2); // 绘制圆形
    }

    painter->restore(); // 恢复绘制状态
}


// 绘制 Pie 样式的进度条
void ProgressWait::drawPie(QPainter* painter)
{
    int radius = 99; // 大圆半径
    painter->save(); // 保存绘制状态

    // 绘制背景圆
    painter->setPen(Qt::NoPen);
    painter->setBrush(background);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);

    // 扇形起始角度
    int startAngle = (360 / (maxValue + 1)) * currentValue * 16;
    // 扇形覆盖范围
    int spanAngle = 60 * 16;
    // 绘制扇形
    painter->setBrush(foreground);

    if (clockWise)
    {
        startAngle = -startAngle; // 如果是顺时针旋转，取反起始角度
    }

    painter->drawPie(-radius, -radius, radius * 2, radius * 2, startAngle, spanAngle);

    painter->restore(); // 恢复绘制状态
}


// 绘制 Line 样式的进度条
void ProgressWait::drawLine(QPainter* painter)
{
    int radius = 95; // 大圆半径

    // 这个 Y 轴坐标控制线条的高度，默认为半径的一半，值越大线条越短
    int initY = 50;

    painter->save(); // 保存绘制状态
    painter->setBrush(Qt::NoBrush); // 设置画刷为无刷

    QPen pen;
    pen.setWidth(10); // 设置线条宽度
    pen.setCapStyle(Qt::RoundCap); // 设置线条两端为圆形

    double angleStep = 360.0 / maxValue; // 每个线之间的角度步进值
    double alpha = (double)1 / maxValue; // 透明度增量

    if (!clockWise)
    {
        angleStep = -angleStep; // 如果是逆时针旋转，取反角度步进值
    }

    for (int i = 0; i <= maxValue; i++)
    {
        int value = (currentValue - i) * alpha * 255;
        if (value < 0)
        {
            value = value + 255; // 如果透明度小于0，加上255
        }

        value = value < 30 ? 30 : value; // 限制透明度的最小值
        foreground.setAlpha(value); // 设置画刷颜色的透明度
        pen.setColor(foreground); // 设置画笔颜色
        painter->setPen(pen); // 设置画笔

        painter->drawLine(0, initY, 0, radius); // 绘制线条
        painter->rotate(angleStep); // 旋转角度
    }

    painter->restore(); // 恢复绘制状态
}


// 绘制 Ring 样式的进度条
void ProgressWait::drawRing(QPainter* painter)
{
    int radius = 99; // 大圆半径
    painter->save(); // 保存绘制状态
    painter->setPen(Qt::NoPen); // 设置无边框

    QRectF rect(-radius, -radius, radius * 2, radius * 2);
    int arcHeight = 30; // 弧的高度
    QPainterPath subPath;
    subPath.addEllipse(rect.adjusted(arcHeight, arcHeight, -arcHeight, -arcHeight));

    // 当前扇形起始角度
    int startAngle = (360 / (maxValue + 1)) * currentValue;
    // 当前扇形覆盖范围
    int spanAngle = 90;
    QPainterPath currentPath;

    if (clockWise)
    {
        currentPath.arcTo(rect, -startAngle, spanAngle);
    }
    else
    {
        currentPath.arcTo(rect, startAngle, spanAngle);
    }

    // 其余扇形的起始角度为当前扇形的起始 + 覆盖范围
    if (clockWise)
    {
        startAngle = startAngle - spanAngle;
    }
    else
    {
        startAngle = startAngle + spanAngle;
    }

    // 其余扇形的覆盖范围为 360 - 当前扇形的覆盖范围
    spanAngle = 360 - spanAngle;
    QPainterPath otherPath;

    if (clockWise)
    {
        otherPath.arcTo(rect, -startAngle, spanAngle);
    }
    else
    {
        otherPath.arcTo(rect, startAngle, spanAngle);
    }

    painter->setBrush(foreground);
    painter->drawPath(currentPath - subPath);
    painter->setBrush(background);
    painter->drawPath(otherPath - subPath);

    painter->restore(); // 恢复绘制状态
}

// 绘制 SingleCircle 样式的进度条
void ProgressWait::drawSingleCircle(QPainter* painter)
{
    int radius = currentValue * 10; // 圆的半径，根据当前值动态计算
    painter->save(); // 保存绘制状态
    painter->setPen(Qt::NoPen); // 设置无边框
    painter->setBrush(foreground); // 设置画刷颜色
    painter->drawEllipse(QPoint(0, 0), radius, radius); // 绘制圆形
    painter->restore(); // 恢复绘制状态
}


// 绘制 DoubleCircle 样式的进度条
void ProgressWait::drawDoubleCircle(QPainter* painter)
{
    // 如果左圆半径小于最小半径则递增，大于最大半径则递减
    if (leftRadius <= minRadius)
    {
        leftIncrease = true;
    }
    else if (leftRadius >= maxRadius)
    {
        leftIncrease = false;
    }

    // 如果右圆半径小于最小半径则递增，大于最大半径则递减
    if (rightRadius <= minRadius)
    {
        rightIncrease = true;
    }
    else if (rightRadius >= maxRadius)
    {
        rightIncrease = false;
    }

    // 根据递增/递减来更新左右圆半径
    if (leftIncrease)
    {
        leftRadius += offsetRadius;
    }
    else
    {
        leftRadius -= offsetRadius;
    }

    if (rightIncrease)
    {
        rightRadius += offsetRadius;
    }
    else
    {
        rightRadius -= offsetRadius;
    }

    int radius = 50;

    painter->save(); // 保存绘制状态
    painter->setPen(Qt::NoPen); // 设置无边框

    // 绘制左边圆
    painter->setBrush(foreground);
    painter->drawEllipse(QPointF(-radius, 0), leftRadius, leftRadius);

    // 绘制右边圆
    painter->setBrush(background);
    painter->drawEllipse(QPointF(radius, 0), rightRadius, rightRadius);

    painter->restore(); // 恢复绘制状态
}

// 绘制进度百分比
void ProgressWait::drawValue(QPainter* painter)
{
    if (!showPercent)
    {
        return;
    }

    int radius = 100;
    painter->save(); // 保存绘制状态
    QFont font;
    font.setPixelSize(40); // 设置字体大小
    font.setBold(true);
    painter->setFont(font);
    painter->setPen(textColor); // 设置文本颜色
    QRect rect(-radius, -radius, radius * 2, radius * 2);
#if 1
    painter->drawText(rect, Qt::AlignCenter, QString("%1%").arg(currentValue * (100 / maxValue)));  // // 绘制进度百分比文本 --- 扩大10倍，显示10 20 30...
#elif 0
    painter->drawText(rect, Qt::AlignCenter, QString("%1%").arg(currentValue));  // // 绘制进度百分比文本 正常递增显示 1 2 3 4 ...
#endif
    painter->restore(); // 恢复绘制状态
}


double ProgressWait::degreesToRadians(double degrees)
{
    // 将角度转换为弧度
    return degrees * (M_PI / 180);
}

void ProgressWait::updateValue()
{
    // 更新数值，如果超过最大值则重置为0
    if (currentValue < maxValue)
    {
        currentValue++;
        this->update(); // 重绘事件
    }
    else
    {
        currentValue = 0;
        emit Signals_progressFinished();
    }

#if 0
    // 触发重绘事件，相当于加到100%又重新0%开始，以此循环
    this->update();
#endif
}

bool ProgressWait::getClockWise() const
{
    // 获取是否顺时针旋转
    return this->clockWise;
}

bool ProgressWait::getShowPercent() const
{
    // 获取是否显示百分比
    return this->showPercent;
}

int ProgressWait::getCurrentValue() const
{
    // 获取当前数值
    return this->currentValue;
}

int ProgressWait::getMaxValue() const
{
    // 获取最大数值
    return this->maxValue;
}

int ProgressWait::getInterval() const
{
    // 获取定时器间隔
    return this->interval;
}

ProgressWait::BarStyle ProgressWait::getBarStyle() const
{
    // 获取进度条样式
    return this->barStyle;
}

QColor ProgressWait::getBackground() const
{
    // 获取背景颜色
    return this->background;
}

QColor ProgressWait::getForeground() const
{
    // 获取前景颜色
    return this->foreground;
}

QColor ProgressWait::getTextColor() const
{
    // 获取文本颜色
    return this->textColor;
}

QSize ProgressWait::sizeHint() const
{
    // 获取推荐大小
    return QSize(100, 100);
}

QSize ProgressWait::minimumSizeHint() const
{
    // 获取最小大小
    return QSize(20, 20);
}

void ProgressWait::setClockWise(bool clockWise)
{
    // 设置是否顺时针旋转
    if (this->clockWise != clockWise)
    {
        this->clockWise = clockWise;
        this->update();
    }
}

void ProgressWait::setShowPercent(bool showPercent)
{
    // 设置是否显示百分比
    if (this->showPercent != showPercent)
    {
        this->showPercent = showPercent;
        this->update();
    }
}

void ProgressWait::setCurrentValue(int currentValue)
{
    // 设置当前数值
    if (this->currentValue != currentValue)
    {
        this->currentValue = currentValue;
        this->update();
    }
}

void ProgressWait::setMaxValue(int maxValue)
{
    // 设置最大数值，并重置当前数值为0
    if (this->maxValue != maxValue)
    {
        this->maxValue = maxValue;
        this->currentValue = 0;
        this->update();
    }
}

void ProgressWait::setInterval(int interval)
{
    // 设置定时器间隔，并更新界面
    if (this->interval != interval)
    {
        this->interval = interval;
        timer->setInterval(interval);
        this->update();
    }
}

void ProgressWait::setBarStyle(const ProgressWait::BarStyle& barStyle)
{
    // 设置进度条样式
    if (this->barStyle != barStyle)
    {
        this->barStyle = barStyle;
        this->update();
    }
}

void ProgressWait::setBackground(const QColor& background)
{
    // 设置背景颜色
    if (this->background != background)
    {
        this->background = background;
        this->update();
    }
}

void ProgressWait::setForeground(const QColor& foreground)
{
    // 设置前景颜色
    if (this->foreground != foreground)
    {
        this->foreground = foreground;
        this->update();
    }
}

void ProgressWait::setTextColor(const QColor& textColor)
{
    // 设置文本颜色
    if (this->textColor != textColor)
    {
        this->textColor = textColor;
        this->update();
    }
}

// 启动定时器
void ProgressWait::Progresswait_Start_Timer()
{
    timer->start();
}

// 停止定时器
void ProgressWait::Progresswait_Stop_Timer()
{
    timer->stop();
}

