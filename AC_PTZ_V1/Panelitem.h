#pragma once
#ifndef PANELITEM_H
#define PANELITEM_H

/**
 * 面板区域控件
 * 1:可设置标题栏文字/高度/字体/对齐方式/颜色
 * 2:可设置边框宽度/边框圆角角度/边框颜色
 * 3:可设置报警颜色切换间隔/报警加深颜色/报警普通颜色
 * 4:可设置启用状态和禁用状态时文字和边框颜色
 */

#include <QWidget>
#include <QPainterPath>
#include <QTimer>

 // 调试打印
//#define QT_PanelItem_DEBUG


class PanelItem : public QWidget
{
    Q_OBJECT
        Q_ENUMS(Alignment)

        Q_PROPERTY(int titleHeight READ getTitleHeight WRITE setTitleHeight)
        Q_PROPERTY(QString titleText READ getTitleText WRITE setTitleText)
        Q_PROPERTY(QFont titleFont READ getTitleFont WRITE setTitleFont)
        Q_PROPERTY(Alignment titleAlignment READ getTitleAlignment WRITE setTitleAlignment)
        Q_PROPERTY(QColor titleColor READ getTitleColor WRITE setTitleColor)
        Q_PROPERTY(QColor titleDisableColor READ getTitleDisableColor WRITE setTitleDisableColor)

        Q_PROPERTY(int borderWidth READ getBorderWidth WRITE setBorderWidth)
        Q_PROPERTY(int borderRadius READ getBorderRadius WRITE setBorderRadius)
        Q_PROPERTY(QColor borderColor READ getBorderColor WRITE setBorderColor)
        Q_PROPERTY(QColor borderDisableColor READ getBorderDisableColor WRITE setBorderDisableColor)

        Q_PROPERTY(int alarmInterval READ getAlarmInterval WRITE setAlarmInterval)
        Q_PROPERTY(QColor alarmTextColor READ getAlarmTextColor WRITE setAlarmTextColor)
        Q_PROPERTY(QColor alarmDarkColor READ getAlarmDarkColor WRITE setAlarmDarkColor)
        Q_PROPERTY(QColor alarmNormalColor READ getAlarmNormalColor WRITE setAlarmNormalColor)

        Q_PROPERTY(bool isAlarm READ getIsAlarm WRITE setAlarm)
        Q_PROPERTY(bool isEnable READ getIsEnable WRITE setEnable)

public:
    enum Alignment
    {
        Alignment_Left = 0,     //左对齐
        Alignment_Center = 1,   //居中对齐
        Alignment_Right = 2     //右对齐
    };

    explicit PanelItem(QWidget* parent = 0);
    ~PanelItem();

protected:
    void paintEvent(QPaintEvent*);
    void drawBorder(QPainter* painter);
    void drawTitle(QPainter* painter);

private:
    int titleHeight;                //标题高度
    QString titleText;              //标题文字
    QFont titleFont;                //标题字体
    Alignment titleAlignment;       //标题对齐方式
    QColor titleColor;              //标题颜色
    QColor titleDisableColor;       //禁用状态下文字颜色

    int borderWidth;                //边框宽度
    int borderRadius;               //边框圆角角度
    QColor borderColor;             //边框颜色
    QColor borderDisableColor;      //禁用状态下边框颜色

    int alarmInterval;              //报警切换间隔
    QColor alarmTextColor;          //报警文字颜色
    QColor alarmDarkColor;          //报警加深颜色
    QColor alarmNormalColor;        //报警普通颜色

    bool isAlarm;                   //是否报警
    bool isEnable;                  //是否启用

    bool isDark;                    //是否加深
    QColor tempColor;               //临时颜色
    QTimer* timer;                  //报警切换定时器

public:
    // 获取标题的高度。
    int getTitleHeight() const;
    // 获取标题的文本。
    QString getTitleText() const;
    // 获取标题的字体。
    QFont getTitleFont() const;
    // 获取标题的对齐方式。
    Alignment getTitleAlignment() const;
    // 获取标题的颜色。
    QColor getTitleColor() const;
    // 获取标题禁用状态下的颜色。
    QColor getTitleDisableColor() const;
    // 获取边框的宽度。
    int getBorderWidth() const;
    // 获取边框的圆角半径。
    int getBorderRadius() const;
    // 获取边框的颜色。
    QColor getBorderColor() const;
    // 获取边框禁用状态下的颜色。
    QColor getBorderDisableColor() const;
    // 获取警报间隔。
    int getAlarmInterval() const;
    // 获取警报文本的颜色。
    QColor getAlarmTextColor() const;
    // 获取警报的深色颜色。
    QColor getAlarmDarkColor() const;
    // 获取警报的正常颜色。
    QColor getAlarmNormalColor() const;
    // 检查是否存在活动的警报。
    bool getIsAlarm() const;
    // 检查组件是否启用。
    bool getIsEnable() const;
    // 获取组件的推荐大小。
    QSize sizeHint() const;
    // 获取组件允许的最小大小。
    QSize minimumSizeHint() const;


private slots:
    void checkAlarm();

public Q_SLOTS:
    //设置报警状态
    void setAlarm(bool alarm);
    //设置启用状态
    void setEnable(bool enable);

    //设置标题栏高度
    void setTitleHeight(int titleHeight);
    //设置标题文字
    void setTitleText(const QString& titleText);
    //设置标题字体
    void setTitleFont(const QFont& titleFont);
    //设置标题文字对齐方式
    void setTitleAlignment(const Alignment& titleAlignment);
    //设置标题文字颜色
    void setTitleColor(const QColor& titleColor);
    //设置禁用状态下标题文字颜色
    void setTitleDisableColor(const QColor& titleDisableColor);

    //设置边框宽度
    void setBorderWidth(int borderWidth);
    //设置边框圆角角度
    void setBorderRadius(int borderRadius);
    //设置边框颜色
    void setBorderColor(const QColor& borderColor);
    //设置禁用状态下边框颜色
    void setBorderDisableColor(const QColor& borderDisableColor);

    //设置报警切换间隔
    void setAlarmInterval(int alarmInterval);
    //设置报警文字颜色
    void setAlarmTextColor(const QColor& alarmTextColor);
    //设置报警加深颜色
    void setAlarmDarkColor(const QColor& alarmDarkColor);
    //设置报警普通颜色
    void setAlarmNormalColor(const QColor& alarmNormalColor);
};


#endif