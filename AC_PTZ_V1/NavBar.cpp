#include "NavBar.h"
#include "qevent.h"
#include "qpainter.h"
#include <QPainterPath>
#include "qtimer.h"
#include "qdebug.h"
#include <QStack>


NavBar::NavBar(QWidget* parent) : QWidget(parent)
{
    // 背景颜色起始和结束值
    bgColorStart = QColor(121, 121, 121);
    bgColorEnd = QColor(121, 121, 121);
    old_bgColorEnd = bgColorEnd;

    // 进度条颜色起始和结束值
    barColorStart = QColor(24, 189, 155);
    barColorEnd = QColor(24, 189, 155);
    old_barColorEnd = barColorEnd;

    // 文本颜色（未选中和选中状态）
    textNormalColor = QColor(255,255,255);
    textSelectColor = QColor(0, 0, 0);

    // 导航项列表、当前选中索引和项文本
    items = "";
    currentIndex = 0;
    currentItem = "";

    // 背景和进度条的圆角半径、导航项之间的间距
    bgRadius = 5;
    barRadius = 5;
    space = 30;

    // 进度条的线宽和颜色
    lineWidth = 3;
    lineColor = QColor(255, 107, 107);

    // 进度条的样式
    barStyle = BarStyle_Rect;

    // 是否启用键盘导航、导航方向（水平或垂直）、是否为扁平样式
    keyMove = false;
    horizontal = false;
    flat = true;

    // 初始化长度、步进值、方向标志和状态标志
    initLen = 10;
    step = 0;
    isForward = true;
    isVirgin = true;

    // 定时器用于动画效果
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(slide()));
}


NavBar::~NavBar()
{
    if (timer->isActive())  // 停止定时器
    {
        timer->stop();
    }
}

void NavBar::resizeEvent(QResizeEvent*)
{
    int index = 0;
    int count = listItem.count();

    // 如果没有导航项，直接返回
    if (count == 0)
    {
        return;
    }

    // 如果导航项不为空，且当前选中项为空，则将第一项设为当前选中项
    if (count > 0 && currentItem.isEmpty())
    {
        currentIndex = 0;
        currentItem = listItem.at(0).first;
    }

    // 查找当前选中项在导航项列表中的索引
    for (int i = 0; i < count; i++)
    {
        if (listItem.at(i).first == currentItem)
        {
            index = i;
            break;
        }
    }

    // 移动到当前选中项的位置
    moveTo(index);
}

void NavBar::mousePressEvent(QMouseEvent* e)
{
    if (e->button() != Qt::LeftButton)  // 不是左键按下则退出
    {
        return;
    }
    // 处理鼠标点击事件，移动到点击位置
    moveTo(e->pos());
}

void NavBar::keyPressEvent(QKeyEvent* keyEvent)
{
    // 处理键盘按下事件，根据方向键移动到上一个或下一个项
    if (!keyMove)
    {
        return;
    }

    if (keyEvent->key() == Qt::Key_Left || keyEvent->key() == Qt::Key_Up)
    {
        movePrevious();
    }
    else if (keyEvent->key() == Qt::Key_Right || keyEvent->key() == Qt::Key_Down)
    {
        moveNext();
    }
}

void NavBar::paintEvent(QPaintEvent* event)
{
    // 绘制准备工作，启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    // 绘制背景色
    drawBg(&painter);
    // 绘制当前条目选中背景
    drawBar(&painter);
    // 绘制条目文字
    drawText(&painter);
}

void NavBar::drawBg(QPainter* painter)
{
    // 保存当前绘图状态
    painter->save();

    // 将画笔设置为不可见（NoPen）
    painter->setPen(Qt::NoPen);

    // 创建从上到下的背景线性渐变
    QLinearGradient bgGradient(QPoint(0, 0), QPoint(0, height()));

    // 设置渐变的起始颜色
    bgGradient.setColorAt(0.0, bgColorStart);

    // 设置渐变的结束颜色
    bgGradient.setColorAt(1.0, bgColorEnd);

    // 将画刷设置为背景渐变
    painter->setBrush(bgGradient);

    // 绘制一个圆角矩形，覆盖整个 NavBar 区域
    painter->drawRoundedRect(rect(), bgRadius, bgRadius);

    // 恢复绘图状态到之前的状态
    painter->restore();
}

void NavBar::drawBar(QPainter* painter)
{
    // 保存当前绘图状态
    painter->save();

    // 创建一个画笔对象
    QPen pen;

    // 从左上到左下创建条形的线性渐变
    QLinearGradient barGradient(barRect.topLeft(), barRect.bottomLeft());

    // 设置渐变的起始颜色
    barGradient.setColorAt(0.0, barColorStart);

    // 设置渐变的结束颜色
    barGradient.setColorAt(1.0, barColorEnd);

    // 将画刷设置为条形渐变
    painter->setBrush(barGradient);

    // 检查条形样式是否为矩形
    if (barStyle == BarStyle_Rect)
    {
        // 如果是矩形，则绘制一个圆角矩形并返回
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(barRect, barRadius, barRadius);
        painter->restore();
        return;
    }
    else
    {
        // 如果不是矩形，设置线宽和画笔的刷子
        pen.setWidthF(lineWidth);
        pen.setBrush(barGradient);
        painter->setPen(pen);

        // 绘制带有圆角的条形
        painter->drawRoundedRect(barRect, barRadius, barRadius);
    }

    // 设置绘制线条的颜色
    pen.setColor(lineColor);
    painter->setPen(pen);

    // 根据线宽计算偏移量
    double offset = (double)lineWidth / 2;

    // 检查条形样式并相应绘制线条
    if (barStyle == BarStyle_Line_Top)
    {
        painter->drawLine(barRect.left(), barRect.top() + offset, barRect.right(), barRect.top() + offset);
    }
    else if (barStyle == BarStyle_Line_Right)
    {
        painter->drawLine(barRect.right() - offset, barRect.top(), barRect.right() - offset, barRect.bottom());
    }
    else if (barStyle == BarStyle_Line_Bottom)
    {
        painter->drawLine(barRect.left(), barRect.bottom() - offset, barRect.right(), barRect.bottom() - offset);
    }
    else if (barStyle == BarStyle_Line_Left)
    {
        painter->drawLine(barRect.left() + offset, barRect.top(), barRect.left() + offset, barRect.bottom());
    }

    // 附加注释：在这里可以添加代码绘制右边的三角形

    // 恢复绘图状态到之前的状态
    painter->restore();
}

void NavBar::drawText(QPainter* painter)
{
    // 保存当前绘图状态
    painter->save();

    // 设置文本绘制字体为粗体
    //textFot.setBold(true);
    painter->setFont(textFont);

    // 获取列表中元素的数量
    int count = listItem.count();
    double textLen = 0;
    QString strText;
    initLen = 0;

    // 当水平模式时，根据最长条目的宽度确定字符区域
    QString longText = "";
    QStringList list = items.split(";");
    foreach(QString str, list)
    {
        if (str.length() > longText.length())
        {
            longText = str;
        }
    }

    // 根据方向计算文本长度
    if (horizontal)
    {
        QFontMetrics fontMetrics(painter->font());
        textLen = fontMetrics.horizontalAdvance(longText);
    }
    else
    {
        textLen = painter->fontMetrics().height();
    }

    // 遍历元素列表，并为每个元素绘制文本和文本背景
    for (int i = 0; i < count; i++)
    {
        strText = listItem.at(i).first;

        // 定义文本矩形的左上和右下点
        QPointF left(initLen, 0);
        QPointF right(initLen + textLen + space, height());

        if (!horizontal)
        {
            left = QPointF(0, initLen);
            right = QPointF(width(), initLen + textLen + space);
        }

        // 创建文本矩形
        QRectF textRect(left, right);
        listItem[i].second = textRect;

        // 如果是第一次迭代，设置barRect并标记为非virgin状态
        if (isVirgin)
        {
            barRect = textRect;
            isVirgin = false;
        }

        // 根据文本矩形是否对应当前选定的项，设置画笔颜色
        if (textRect == listItem.at(currentIndex).second)
        {
            painter->setPen(textSelectColor);
        }
        else
        {
            painter->setPen(textNormalColor);
        }

        // 在文本矩形的中心绘制文本
        painter->drawText(textRect, Qt::AlignCenter, strText);
        initLen += textLen + space;
    }

    // 恢复绘图状态到之前的状态
    painter->restore();
}


int NavBar::initStep(int distance)
{
    // 初始化变量 n 为 1
    int n = 1;

    // 在 n * n 大于给定距离之前循环
    while (1)
    {
        // 检查 n * n 是否大于距离
        if (n * n > distance)
        {
            // 如果条件满足，则退出循环
            break;
        }
        else
        {
            // 如果条件不满足，则递增 n
            n++;
        }
    }

    // 返回将 n 乘以 1.4 的结果
    return n * 1.4;
}

void NavBar::slide()
{
    // 如果步长大于 1，则递减步长
    if (step > 1)
    {
        step--;
    }

    // 根据方向确定滑动条的当前位置
    if (horizontal)
    {
        barLen = barRect.topLeft().x();
    }
    else
    {
        barLen = barRect.topLeft().y();
    }

    // 检查动画是否向前移动
    if (isForward)
    {
        // 将滑动条位置增加步长
        barLen += step;

        // 如果滑动条位置达到或超过目标位置，则停止定时器
        if (barLen >= targetLen)
        {
            barLen = targetLen;
            timer->stop();
        }
    }
    else
    {
        // 将滑动条位置减少步长
        barLen -= step;

        // 如果滑动条位置达到或低于目标位置，则停止定时器
        if (barLen <= targetLen)
        {
            barLen = targetLen;
            timer->stop();
        }
    }

    // 根据新位置更新滑动条矩形
    if (horizontal)
    {
        barRect = QRectF(QPointF(barLen, 0), QPointF(barLen + barRect.width(), height()));
    }
    else
    {
        barRect = QRectF(QPointF(0, barLen), QPointF(width(), barLen + barRect.height()));
    }

    // 触发更新以重新绘制 NavBar
    this->update();
}


QColor NavBar::getBgColorStart() const
{
    // 返回起始背景颜色
    return this->bgColorStart;
}

QColor NavBar::getBgColorEnd() const
{
    // 返回结束背景颜色
    return this->bgColorEnd;
}

QColor NavBar::getBarColorStart() const
{
    // 返回条形起始颜色
    return this->barColorStart;
}

QColor NavBar::getBarColorEnd() const
{
    // 返回条形结束颜色
    return this->barColorEnd;
}

QColor NavBar::getTextNormalColor() const
{
    // 返回正常文本颜色
    return this->textNormalColor;
}

QColor NavBar::getTextSelectColor() const
{
    // 返回选中文本颜色
    return this->textSelectColor;
}

QString NavBar::getItems() const
{
    // 返回条目作为字符串
    return this->items;
}

int NavBar::getCurrentIndex() const
{
    // 返回当前索引
    return this->currentIndex;
}

QString NavBar::getCurrentItem() const
{
    // 返回当前条目作为字符串
    return this->currentItem;
}

int NavBar::getBgRadius() const
{
    // 返回背景圆角半径
    return this->bgRadius;
}

int NavBar::getBarRadius() const
{
    // 返回条形圆角半径
    return this->barRadius;
}

int NavBar::getSpace() const
{
    // 返回条目之间的间距
    return this->space;
}

int NavBar::getLineWidth() const
{
    // 返回线条宽度
    return this->lineWidth;
}

QColor NavBar::getLineColor() const
{
    // 返回线条颜色
    return this->lineColor;
}

NavBar::BarStyle NavBar::getBarStyle() const
{
    // 返回当前的条形样式
    return this->barStyle;
}

bool NavBar::getKeyMove() const
{
    // 返回按键移动的状态
    return this->keyMove;
}

bool NavBar::getHorizontal() const
{
    // 返回水平方向的状态
    return this->horizontal;
}

bool NavBar::getFlat() const
{
    // 返回平坦状态
    return this->flat;
}

QSize NavBar::sizeHint() const
{
    // 返回首选大小提示
    return QSize(500, 30);
}

QSize NavBar::minimumSizeHint() const
{
    // 返回最小大小提示
    return QSize(30, 30);
}

void NavBar::clearItem()
{
    // 清空条目列表并触发更新
    listItem.clear();
    this->update();
}

void NavBar::setBgColorStart(const QColor& bgColorStart)
{
    // 如果起始背景颜色不同，则设置并触发更新
    if (this->bgColorStart != bgColorStart)
    {
        this->bgColorStart = bgColorStart;
        this->update();
    }
}

void NavBar::setBgColorEnd(const QColor& bgColorEnd)
{
    // 如果结束背景颜色不同，则设置并触发更新
    if (this->bgColorEnd != bgColorEnd)
    {
        this->bgColorEnd = bgColorEnd;
        this->old_bgColorEnd = bgColorEnd;
        this->update();
    }
}

void NavBar::setBarColorStart(const QColor& barColorStart)
{
    // 如果条形起始颜色不同，则设置并触发更新
    if (this->barColorStart != barColorStart)
    {
        this->barColorStart = barColorStart;
        this->update();
    }
}

void NavBar::setBarColorEnd(const QColor& barColorEnd)
{
    // 如果条形结束颜色不同，则设置并触发更新
    if (this->barColorEnd != barColorEnd)
    {
        this->barColorEnd = barColorEnd;
        this->old_barColorEnd = barColorEnd;
        this->update();
    }
}

void NavBar::setTextNormalColor(const QColor& textNormalColor)
{
    // 如果正常文本颜色不同，则设置并触发更新
    if (this->textNormalColor != textNormalColor)
    {
        this->textNormalColor = textNormalColor;
        this->update();
    }
}

void NavBar::setTextSelectColor(const QColor& textSelectColor)
{
    // 如果选中文本颜色不同，则设置并触发更新
    if (this->textSelectColor != textSelectColor)
    {
        this->textSelectColor = textSelectColor;
        this->update();
    }
}

void NavBar::setItems(const QString& items)
{
    // 设置条目并清除现有列表
    this->items = items;
    this->listItem.clear();

    // 拆分条目字符串并将每个条目添加到列表中
    QStringList list = items.split(";");    // 使用分号 ";" 将字符串 items 拆分为一个 QStringList，每个条目以分号为分隔符
    foreach(QString str, list)
    {
        // 遍历 QStringList 中的每个条目
        // 将每个条目和一个默认构造的 QRectF 对象组成一个 QPair，并添加到 listItem 列表中
        // 这里使用 qMakePair 函数，它会返回一个包含两个元素的 QPair
        this->listItem.push_back(qMakePair(str, QRectF()));
    }
    // 使用索引为 0 的条目触发信号
    if (!this->listItem.isEmpty())
    {
        emit NavBar_Signals_CurrentItemChanged(0, this->listItem[0].first);
    }
    // 触发更新
    this->update();
}

void NavBar::setCurrentIndex(int index)
{
    // 使用moveTo函数设置当前索引
    moveTo(index);
}

void NavBar::setCurrentItem(const QString& item)
{
    // 使用moveTo函数设置当前条目
    moveTo(item);
}

void NavBar::setBgRadius(int bgRadius)
{
    // 如果背景圆角半径不同，则设置并触发更新
    if (this->bgRadius != bgRadius)
    {
        this->bgRadius = bgRadius;
        this->update();
    }
}

void NavBar::setBarRadius(int barRadius)
{
    // 如果条形圆角半径不同，则设置并触发更新
    if (this->barRadius != barRadius)
    {
        this->barRadius = barRadius;
        this->update();
    }
}

void NavBar::setSpace(int space)
{
    // 如果条目之间的间距不同，则设置并触发更新
    if (this->space != space)
    {
        this->space = space;
        this->update();
    }
}

void NavBar::setLineWidth(int lineWidth)
{
    // 如果线条宽度不同，则设置并触发更新
    if (this->lineWidth != lineWidth)
    {
        this->lineWidth = lineWidth;
        this->update();
    }
}

void NavBar::setLineColor(const QColor& lineColor)
{
    // 如果线条颜色不同，则设置并触发更新
    if (this->lineColor != lineColor)
    {
        this->lineColor = lineColor;
        this->update();
    }
}

void NavBar::setBarStyle(const NavBar::BarStyle& barStyle)
{
    // 如果条形样式不同，则设置并触发更新
    if (this->barStyle != barStyle)
    {
        this->barStyle = barStyle;
        this->update();
    }
}

void NavBar::setKeyMove(bool keyMove)
{
    // 如果按键移动的状态不同，则设置并相应地调整焦点策略
    if (this->keyMove != keyMove)
    {
        this->keyMove = keyMove;

        // 如果启用按键移动，将焦点策略设置为StrongFocus；否则，设置为NoFocus
        if (keyMove)
        {
            setFocusPolicy(Qt::StrongFocus);
        }
        else
        {
            setFocusPolicy(Qt::NoFocus);
        }
    }
}

void NavBar::setHorizontal(bool horizontal)
{
    // 如果水平方向的状态不同，则设置并触发更新
    if (this->horizontal != horizontal)
    {
        this->horizontal = horizontal;
        this->update();
    }
}

void NavBar::setFlat(bool flat)
{
    // 如果扁平状态不同，则设置并相应地调整颜色
    if (this->flat != flat)
    {
        // 如果扁平，将初始颜色赋值给结束颜色以达到扁平效果；
        // 如果取消扁平，恢复原始颜色
        if (flat)
        {
            bgColorEnd = bgColorStart;
            barColorEnd = barColorStart;
        }
        else
        {
            bgColorEnd = old_bgColorEnd;
            barColorEnd = old_barColorEnd;
        }

        this->flat = flat;
        this->update();
    }
}

void NavBar::setTextFont(QFont font)
{
    textFont = font;
}

void NavBar::moveFirst()
{
    // 如果当前索引不是第一个，则移动到第一个索引
    int index = 0;
    if (currentIndex != index)
    {
        moveTo(index);
    }
}

void NavBar::moveLast()
{
    // 如果当前索引不是最后一个，则移动到最后一个索引
    int index = listItem.count() - 1;
    if (currentIndex != index)
    {
        moveTo(index);
    }
}

void NavBar::movePrevious()
{
    // 如果当前索引大于0，则移动到前一个索引
    if (currentIndex > 0)
    {
        currentIndex--;
        moveTo(currentIndex);
    }
}

void NavBar::moveNext()
{
    // 如果当前索引小于最后一个索引，则移动到下一个索引
    if (currentIndex < listItem.count() - 1)
    {
        currentIndex++;
        moveTo(currentIndex);
    }
}

void NavBar::moveTo(int index)
{
    // 如果索引有效，则移动到指定索引
    if (index >= 0 && listItem.count() > index)
    {
        QRectF rec = listItem.at(index).second;
        QPoint pos = QPoint(rec.x(), rec.y());
        moveTo(pos);
    }
}

void NavBar::moveTo(const QString& item)
{
    // 移动到与指定条目关联的索引
    int count = listItem.count();
    for (int i = 0; i < count; i++)
    {
        if (listItem.at(i).first == item)
        {
            moveTo(i);
            break;
        }
    }
}

void NavBar::moveTo(const QPointF& point)
{
    // 移动到与指定点关联的索引
    int count = listItem.count();
    for (int i = 0; i < count; i++)
    {
        if (listItem.at(i).second.contains(point))
        {
            currentIndex = i;
            currentItem = listItem.at(i).first;
            targetRect = listItem.at(i).second;

            if (horizontal)
            {
                targetLen = targetRect.topLeft().x();
                barLen = barRect.topLeft().x();
            }
            else
            {
                targetLen = targetRect.topLeft().y();
                barLen = barRect.topLeft().y();
            }

            isForward = (targetLen > barLen);
            int distance = targetLen - barLen;
            distance = qAbs(distance);

            // 重新获取每次移动的步长
            step = initStep(distance);
            timer->start();

            emit NavBar_Signals_CurrentItemChanged(currentIndex, currentItem); // 发送信号
        }
    }
}
