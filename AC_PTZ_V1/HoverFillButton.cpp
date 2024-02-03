#include "HoverFillButton.h"
#include <QLinearGradient>
#include <QStyleOption>               // QStyleOption 类用于描述 Qt 绘图元素的各种选项
#ifdef QT_HoverFillButton_DEBUG
#include <QDebug>
#endif


HoverFillButton::HoverFillButton(QWidget* parent)
    : QPushButton(parent)
{
    /*默认值*/
    this->addShadow(0, 0, 15, QColor(111, 74, 206));//添加阴影 54, 226, 145
}

HoverFillButton::~HoverFillButton()
{
#ifdef QT_Mainwindow_DEBUG
    qDebug() << "delete Mainwindow";
#endif 
}

void HoverFillButton::addShadow(int right, int down, qreal blurRadius, const QColor& shadowColor)
{
    QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    shadow->setOffset(right, down); //阴影的偏移量（右，下）
    shadow->setColor(shadowColor);  //阴影的颜色
    shadow->setBlurRadius(blurRadius); //控制阴影的模糊程度（光源距离）
    this->setGraphicsEffect(shadow);
}

void HoverFillButton::paintEvent(QPaintEvent* event)
{
    // 创建 QStyleOption 对象并初始化
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    p.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);     // 设置抗锯齿
    // 使用当前样式绘制基本控件
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    // 调用基类的 paintEvent 函数
    QPushButton::paintEvent(event);
}

void HoverFillButton::setButtonStyle(QFont font,
    int radius,
    const QString& normalColor,
    const QString& normalTextColor,
    const QString& hoverColor,
    const QString& hoverTextColor,
    const QString& pressedColor,
    const QString& pressedTextColor)
{
    QStringList list;   // 创建字符串列表，存放不同状态下的样式
    // 正常状态样式
    list.append(QString("QPushButton{border-radius:%2px;color:%3;background:%4;}")
        .arg(radius).arg(normalTextColor).arg(normalColor));
    // 悬停状态样式
    list.append(QString("QPushButton:hover{color:%1;background:%2;}")
        .arg(hoverTextColor).arg(hoverColor));
    // 按下状态样式
    list.append(QString("QPushButton:pressed{color:%1;background:%2;}")
        .arg(pressedTextColor).arg(pressedColor));

    QString qss = list.join("");    // 将样式表字符串拼接成一个字符串

    this->setStyleSheet(qss);    // 设置按钮的样式表
    this->setFont(font);
}

void HoverFillButton::mouseReleaseEvent(QMouseEvent* event)
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
        emit HoverFillButton_Signals_mose_isRelease();  // 发送信号
    }

    // 调用基类的 mouseReleaseEvent 以确保正常的事件处理(没有则不会恢复原来颜色)
    QPushButton::mouseReleaseEvent(event);
}
