#pragma once
#ifndef NAVPROGRESS_H
#define NAVPROGRESS_H

#include <QWidget>
#include <QPainterPath>

#if 0

class NavProgress : public QWidget
{
    Q_OBJECT
        //Q_ENUMS(NavStyle)

        //Q_PROPERTY(int maxStep READ getMaxStep WRITE setMaxStep)
        //Q_PROPERTY(int currentStep READ getCurrentStep WRITE setCurrentStep)
        //Q_PROPERTY(NavStyle navStyle READ getNavStyle WRITE setNavStyle)

        //Q_PROPERTY(QColor background READ getBackground WRITE setBackground)
        //Q_PROPERTY(QColor foreground READ getForeground WRITE setForeground)
        //Q_PROPERTY(QColor currentBackground READ getCurrentBackground WRITE setCurrentBackground)
        //Q_PROPERTY(QColor currentForeground READ getCurrentForeground WRITE setCurrentForeground)

public:
    enum NavStyle {
        NavStyle_JD = 0,    //京东订单流程样式
        NavStyle_TB = 1,    //淘宝订单流程样式
    };

    explicit NavProgress(QWidget* parent = 0);

protected:
    void paintEvent(QPaintEvent*);
    void drawBg_JD(QPainter* painter);
    void drawText_JD(QPainter* painter);
    void drawCurrentBg_JD(QPainter* painter);
    void drawCurrentText_JD(QPainter* painter);
    void drawBg_TB(QPainter* painter);
    void drawText_TB(QPainter* painter);
    void drawCurrentBg_TB(QPainter* painter);

private:
    QStringList topInfo;            //导航顶部标签数据
    QStringList bottomInfo;         //导航底部标签数据

    int maxStep;                    //最大步数
    int currentStep;                //当前第几步
    NavStyle navStyle;              //导航样式

    QColor background;              //背景色
    QColor foreground;              //前景色
    QColor currentBackground;       //当前背景色
    QColor currentForeground;       //当前前景色

    QFont iconFont;                 //图形字体

public:
    QStringList getTopInfo()        const;
    QStringList getBottomInfo()     const;

    int getMaxStep()                const;
    int getCurrentStep()            const;
    NavStyle getNavStyle()          const;

    QColor getBackground()          const;
    QColor getForeground()          const;
    QColor getCurrentBackground()   const;
    QColor getCurrentForeground()   const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置导航顶部标签数据
    void setTopInfo(const QStringList& topInfo);
    //设置导航底部标签数据
    void setBottomInfo(const QStringList& bottomInfo);

    //设置最大步数
    void setMaxStep(int maxStep);
    //设置当前第几步
    void setCurrentStep(int currentStep);
    //设置导航样式
    void setNavStyle(const NavStyle& navStyle);

    //设置前景色
    void setBackground(const QColor& background);
    //设置前景色
    void setForeground(const QColor& foreground);
    //设置当前前景色
    void setCurrentBackground(const QColor& currentBackground);
    //设置当前前景色
    void setCurrentForeground(const QColor& currentForeground);
};

#endif

#endif
