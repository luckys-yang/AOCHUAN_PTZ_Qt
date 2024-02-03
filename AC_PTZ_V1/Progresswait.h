#pragma once
#ifndef PROGRESSWAIT_H
#define PROGRESSWAIT_H

/**
 * 等待进度条控件
 * 1:支持多种等待样式风格 圆弧状风格 旋转圆风格 三角圆弧 线条风格 圆环风格
 * 2:可设置范围值和当前值
 * 3:可设置前景色背景色
 * 4:可设置顺时针逆时针旋转
 * 5:支持任意大小缩放
 * 6:支持设置旋转速度间隔
 */
#include <QWidget>
#include <QPainterPath>

 // 调试打印
//#define QT_ProgressWait_DEBUG

class ProgressWait : public QWidget
{
    Q_OBJECT

        Q_ENUMS(BarStyle)

        Q_PROPERTY(bool clockWise READ getClockWise WRITE setClockWise)
        Q_PROPERTY(bool showPercent READ getShowPercent WRITE setShowPercent)

        Q_PROPERTY(int currentValue READ getCurrentValue WRITE setCurrentValue)
        Q_PROPERTY(int maxValue READ getMaxValue WRITE setMaxValue)
        Q_PROPERTY(int interval READ getInterval WRITE setInterval)

        Q_PROPERTY(BarStyle barStyle READ getBarStyle WRITE setBarStyle)
        Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
        Q_PROPERTY(QColor foreground READ getForeground WRITE setForeground)
        Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor)
        Q_ENUMS(BarStyle)

public:
    enum BarStyle
    {
        BarStyle_Arc = 0,          // 圆弧状风格
        BarStyle_RoundCircle = 1,  // 旋转圆风格
        BarStyle_Pie = 2,          // 三角圆弧风格
        BarStyle_Line = 3,         // 线条风格
        BarStyle_Ring = 4,         // 圆环风格
        BarStyle_SingleCircle = 5, // 一个圆闪烁
        BarStyle_DoubleCircle = 6  // 两个圆闪烁
    };

    ProgressWait(QWidget* parent = nullptr);
    ~ProgressWait();

protected:
    // 重写大小调整事件，响应窗口大小变化(override)
    void resizeEvent(QResizeEvent*) override;
    // 重写绘制事件，进行自定义绘制(override)
    void paintEvent(QPaintEvent*) override;
    // 绘制弧形
    void drawArc(QPainter* painter);
    // 绘制圆角矩形
    void drawRoundCircle(QPainter* painter);
    // 绘制饼图
    void drawPie(QPainter* painter);
    // 绘制直线
    void drawLine(QPainter* painter);
    // 绘制圆环
    void drawRing(QPainter* painter);
    // 绘制单个圆
    void drawSingleCircle(QPainter* painter);
    // 绘制双圆
    void drawDoubleCircle(QPainter* painter);
    // 绘制数值显示
    void drawValue(QPainter* painter);

private:
    bool clockWise;   // 顺时针逆时针
    bool showPercent; // 显示当前百分比
    int currentValue; // 当前值
    int maxValue;     // 最大值
    int interval;     // 旋转间隔

    int minRadius;      // 最小半径
    int maxRadius;      // 最大半径
    int offsetRadius;   // 半径偏移量
    int leftRadius;     // 左边圆半径
    int rightRadius;    // 右边圆半径
    bool leftIncrease;  // 左边递增
    bool rightIncrease; // 右边递增

    BarStyle barStyle; // 样式
    QColor background; // 背景色
    QColor foreground; // 前景色
    QColor textColor;  // 文字颜色

    QTimer* timer; // 定时器绘制

private:
    // 将角度转换为弧度
    double degreesToRadians(double value);

private slots:
    // 更新数值(槽函数)
    void updateValue();

public:
    bool getClockWise() const;  // 获取进度条方向是否为顺时针
    bool getShowPercent() const;    // 获取是否显示百分比
    int getCurrentValue() const;    // 获取当前数值
    int getMaxValue() const;    // 获取最大数值
    int getInterval() const;    // 获取间隔值

    BarStyle getBarStyle() const;   // 获取进度条样式
    QColor getBackground() const;   // 获取背景颜色
    QColor getForeground() const;   // 获取前景颜色
    QColor getTextColor() const;    // 获取文本颜色

    QSize sizeHint() const; // 获取推荐的大小
    QSize minimumSizeHint() const;  // 获取最小大小

public Q_SLOTS: // 公共的槽函数
    // 设置顺时针逆时针旋转
    void setClockWise(bool clockWise);
    // 设置是否显示百分比
    void setShowPercent(bool showPercent);
    // 设置当前值
    void setCurrentValue(int currentValue);
    // 设置最大值
    void setMaxValue(int maxValue);
    // 设置旋转速度间隔
    void setInterval(int interval);

    // 设置样式
    void setBarStyle(const BarStyle& barStyle);
    // 设置前景色(QColor(225, 102, 255)格式)
    void setBackground(const QColor& background);
    // 设置前景色
    void setForeground(const QColor& foreground);
    // 设置文字颜色
    void setTextColor(const QColor& textColor);
    // 启动定时器
    void Progresswait_Start_Timer();
    // 停止定时器
    void Progresswait_Stop_Timer();
signals:
    // 数值到达最大值则触发(信号)
    void Signals_progressFinished();
};

#endif
