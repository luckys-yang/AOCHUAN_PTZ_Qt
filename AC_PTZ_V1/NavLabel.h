#pragma once
#ifndef NAVLABEL_H
#define NAVLABEL_H

/**
 * 导航标签控件
 * 1:可设置前景色和背景色
 * 2:可设置箭头位置方向 左右上下
 * 3:可设置箭头大小
 * 4:可设置显示倒三角
 * 5:可设置倒三角长度/位置/颜色
 */

#include <QLabel>

class NavLabel : public QLabel
{
    Q_OBJECT
public:
    enum ArrowPosition
    {
        ArrowPosition_Left = 0,     //向左箭头
        ArrowPosition_Right = 1,    //向右箭头
        ArrowPosition_Top = 2,      //向上箭头
        ArrowPosition_Bottom = 3    //向下箭头
    };

    enum TrianglePosition
    {
        TrianglePosition_Left = 0,  //左侧
        TrianglePosition_Right = 1, //右侧
        TrianglePosition_Top = 2,   //顶部
        TrianglePosition_Bottom = 3 //底部
    };

    explicit NavLabel(QWidget* parent = 0);

protected:
    void mousePressEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);
    void drawBg(QPainter* painter);
    void drawText(QPainter* painter);
    void drawTriangle(QPainter* painter);

private:
    int borderRadius;                   //边框圆角角度
    QColor foreground;                  //前景色
    QColor start_background;    // 背景颜色开始颜色
    QColor end_background;    // 背景颜色结束颜色

    bool showArrow;                     //显示箭头
    int arrowSize;                      //箭头大小
    ArrowPosition arrowPosition;        //箭头位置

    bool showTriangle;                  //显示倒三角
    int triangleLen;                    //倒三角边长
    TrianglePosition trianglePosition;  //倒三角位置
    QColor triangleColor;               //倒三角颜色

    QRect bgRect;                       //绘制区域
    QFont font; // 字体
public:
    int getBorderRadius()               const;
    QColor getStartBackground()              const;
    QColor getEndBackground()              const;
    QColor getForeground()              const;

    bool getShowArrow()                 const;
    int getArrowSize()                  const;
    ArrowPosition getArrowPosition()    const;

    bool getShowTriangle()              const;
    int getTriangleLen()                const;
    TrianglePosition getTrianglePosition()const;
    QColor getTriangleColor()           const;

    QSize sizeHint()                    const;
    QSize minimumSizeHint()             const;

public Q_SLOTS:
    //设置边框圆角角度
    void setBorderRadius(int borderRadius);
    //设置背景色
    void setBackground(const QColor& start_color, const QColor& end_color);
    //设置前景色
    void setForeground(const QColor& foreground);

    //设置显示箭头
    void setShowArrow(bool showArrow);
    //设置箭头大小
    void setArrowSize(int arrowSize);
    //设置箭头位置
    void setArrowPosition(const ArrowPosition& arrowPosition);

    //设置显示倒三角
    void setShowTriangle(bool showTriangle);
    //设置倒三角边长
    void setTriangleLen(int triangleLen);
    //设置倒三角位置
    void setTrianglePosition(const TrianglePosition& trianglePosition);
    //设置倒三角颜色
    void setTriangleColor(const QColor& triangleColor);
    // 设置字体
    void setTextFont(QFont font);
Q_SIGNALS:
    void clicked();
};

#endif