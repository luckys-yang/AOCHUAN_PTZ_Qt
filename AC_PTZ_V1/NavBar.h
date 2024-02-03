#pragma once
#ifndef NAVBAR_H
#define NAVBAR_H

/**
 * 滑动导航条控件
 * 1:可键盘按键上下移动元素功能
 * 2:支持窗体大小改变控件自动拉伸
 * 3:支持移动到第一个/末一个/上移/下移/移动到指定索引/移动到指定元素
 * 4:支持扁平处理
 * 5:支持纵向风格
 * 6:可设置圆角角度,包括主背景和选中元素背景
 * 7:可设置间距
 * 8:可设置导航条主背景渐变色
 * 9:可设置当前条目选中背景渐变色
 * 10:可设置条目未选中和选中的文字颜色
 * 11:可设置五种选中风格样式
 * 12:可设置线条颜色和宽度
 * 13:选中条目的宽度为条目文字集合中最长的一个
 */

#include <QWidget>
#include <QPainterPath>
#include <QMutexLocker>

class NavBar : public QWidget
{
    Q_OBJECT
        Q_ENUMS(BarStyle)

        Q_PROPERTY(QColor bgColorStart READ getBgColorStart WRITE setBgColorStart)
        Q_PROPERTY(QColor bgColorEnd READ getBgColorEnd WRITE setBgColorEnd)

        Q_PROPERTY(QColor barColorStart READ getBarColorStart WRITE setBarColorStart)
        Q_PROPERTY(QColor barColorEnd READ getBarColorEnd WRITE setBarColorEnd)

        Q_PROPERTY(QColor textNormalColor READ getTextNormalColor WRITE setTextNormalColor)
        Q_PROPERTY(QColor textSelectColor READ getTextSelectColor WRITE setTextSelectColor)

        Q_PROPERTY(QString items READ getItems WRITE setItems)
        Q_PROPERTY(int currentIndex READ getCurrentIndex WRITE setCurrentIndex)
        Q_PROPERTY(QString currentItem READ getCurrentItem WRITE setCurrentItem)

        Q_PROPERTY(int bgRadius READ getBgRadius WRITE setBgRadius)
        Q_PROPERTY(int barRadius READ getBarRadius WRITE setBarRadius)
        Q_PROPERTY(int space READ getSpace WRITE setSpace)

        Q_PROPERTY(int lineWidth READ getLineWidth WRITE setLineWidth)
        Q_PROPERTY(QColor lineColor READ getLineColor WRITE setLineColor)

        Q_PROPERTY(BarStyle barStyle READ getBarStyle WRITE setBarStyle)

        Q_PROPERTY(bool keyMove READ getKeyMove WRITE setKeyMove)
        Q_PROPERTY(bool horizontal READ getHorizontal WRITE setHorizontal)
        Q_PROPERTY(bool flat READ getFlat WRITE setFlat)

public:
    enum BarStyle
    {
        // 圆角矩形
        BarStyle_Rect = 0,      
        // 上边线条
        BarStyle_Line_Top = 1,
        // 右边线条
        BarStyle_Line_Right = 2,  
        // 下边线条
        BarStyle_Line_Bottom = 3, 
        // 左边线条
        BarStyle_Line_Left = 4    
    };

    explicit NavBar(QWidget* parent = 0);
    ~NavBar();

protected:
protected:
    // 重写 resizeEvent 事件，用于处理窗口大小变化
    void resizeEvent(QResizeEvent*) override;
    // 重写 mousePressEvent 事件，处理鼠标按下事件
    void mousePressEvent(QMouseEvent*) override;
    // 重写 keyPressEvent 事件，处理键盘按下事件
    void keyPressEvent(QKeyEvent*) override;
    // 重写 paintEvent 事件，进行绘制操作
    void paintEvent(QPaintEvent*) override;
    // 绘制背景
    void drawBg(QPainter* painter);
    // 绘制进度条
    void drawBar(QPainter* painter);
    // 绘制文本信息
    void drawText(QPainter* painter);
    
private:
    int step;                   // 每次移动的步长
    bool horizontal; // 是否横向显示
    QRectF barRect, targetRect; // 选中区域和目标区域的矩形
    double barLen, targetLen;   // 选中区域和目标区域的长度
    bool isForward; // 是否往前移动

    QColor bgColorStart; // 导航条主背景渐变开始颜色
    QColor bgColorEnd;   // 导航条主背景渐变结束颜色

    QColor barColorStart; // 导航条当前条目渐变开始颜色
    QColor barColorEnd;   // 导航条当前条目渐变结束颜色

    QColor textNormalColor; // 文字正常颜色
    QColor textSelectColor; // 文字选中颜色

    QColor old_bgColorEnd;  // 用于扁平化切换
    QColor old_barColorEnd; // 用于扁平化切换

    QString items;       // 所有条目文字信息
    int currentIndex;    // 当前选中条目索引
    QString currentItem; // 当前选中条目文字

    int bgRadius;  // 背景圆角半径
    int barRadius; // 选中条目背景圆角半径
    int space;     // 条目元素之间的间距

    int lineWidth;    // 线条宽度
    QColor lineColor; // 线条颜色

    BarStyle barStyle; // 选中元素样式

    bool keyMove;    // 是否支持按键移动
    
    bool flat;       // 是否扁平化
    QFont textFont;                //文本字体
    // 元素集合,成对出现,元素的名字,矩形区域范围(其中每个元素都是一个 QPair，QPair 由一个 QString 和一个 QRectF 组成)
    QVector<QPair<QString, QRectF>> listItem;
    double initLen;             // 导航条的长度
    
    int initStep(int distance); // 计算步长
    bool isVirgin;  // 是否首次处理
    QTimer* timer;  // 滑动绘制定时器
private slots:
    void slide();   // 控制导航条滑动槽函数

public:
    // 获取背景渐变的起始颜色
    QColor getBgColorStart() const;
    // 获取背景渐变的结束颜色
    QColor getBgColorEnd() const;

    // 获取滑块渐变的起始颜色
    QColor getBarColorStart() const;
    // 获取滑块渐变的结束颜色
    QColor getBarColorEnd() const;

    // 获取文本正常状态颜色
    QColor getTextNormalColor() const;
    // 获取文本选中状态颜色
    QColor getTextSelectColor() const;

    // 获取导航项列表
    QString getItems() const;
    // 获取当前选中项的索引
    int getCurrentIndex() const;
    // 获取当前选中项的文本
    QString getCurrentItem() const;

    // 获取背景圆角半径
    int getBgRadius() const;
    // 获取滑块圆角半径
    int getBarRadius() const;
    // 获取导航项之间的间隔
    int getSpace() const;

    // 获取分隔线的宽度
    int getLineWidth() const;
    // 获取分隔线的颜色
    QColor getLineColor() const;

    // 获取滑块的样式
    BarStyle getBarStyle() const;

    // 获取是否允许通过键盘移动导航条
    bool getKeyMove() const;
    // 获取导航条的方向，是水平的还是垂直的
    bool getHorizontal() const;
    // 获取是否为扁平风格
    bool getFlat() const;

    // 获取建议的控件大小
    QSize sizeHint() const;
    // 获取最小的控件大小
    QSize minimumSizeHint() const;


public Q_SLOTS:
    // 删除所有条目
    void clearItem();

    // 设置导航条主背景渐变色
    void setBgColorStart(const QColor& bgColorStart);
    void setBgColorEnd(const QColor& bgColorEnd);

    // 设置当前条目选中背景渐变色
    void setBarColorStart(const QColor& barColorStart);
    void setBarColorEnd(const QColor& barColorEnd);

    // 设置文字颜色
    void setTextNormalColor(const QColor& textNormalColor);
    void setTextSelectColor(const QColor& textSelectColor);

    // 设置导航项列表
    void setItems(const QString& items);
    // 设置当前选中项的索引
    void setCurrentIndex(int index);
    // 设置当前选中项的文本
    void setCurrentItem(const QString& item);

    // 设置边框圆角
    void setBgRadius(int bgRadius);
    void setBarRadius(int barRadius);
    // 设置条目间距
    void setSpace(int space);

    // 设置线条宽度
    void setLineWidth(int lineWidth);
    // 设置线条颜色
    void setLineColor(const QColor& lineColor);

    // 设置选中元素样式
    void setBarStyle(const BarStyle& barStyle);

    // 设置键盘按键是否能够移动条目(true--运行 false--不允许)
    void setKeyMove(bool keyMove);
    // true--设置横向显示 false--纵向显示
    void setHorizontal(bool horizontal);
    // 设置扁平,默认不扁平(true--扁平化 false--不扁平化)
    void setFlat(bool flat);
    // 设置文本字体
    void setTextFont(QFont font);

    // 移动到第一个条目
    void moveFirst();
    // 移动到最后一个条目
    void moveLast();
    // 往前移动条目
    void movePrevious();
    // 往后移动条目
    void moveNext();
    // 移动到指定索引条目
    void moveTo(int index);
    // 移动到指定文字条目
    void moveTo(const QString& item);
    // 移动到指定坐标位置条目
    void moveTo(const QPointF& point);

signals:
    // 当前条目改变信号,index为当前条目索引索引 item为当前条目文字
    void NavBar_Signals_CurrentItemChanged(int index, const QString& item);
};

#endif