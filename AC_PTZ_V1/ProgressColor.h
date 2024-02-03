#pragma once
#ifndef PROGRESSCOLOR_H
#define PROGRESSCOLOR_H

#include <QWidget>
#include <QPainterPath>

class ProgressColor : public QWidget
{
	Q_OBJECT
public:
	explicit ProgressColor(QWidget* parent = 0);

protected:
	void paintEvent(QPaintEvent*);
	void drawBg(QPainter* painter);
	void drawBar(QPainter* painter);

private:
	double minValue;                //最小值
	double maxValue;                //最大值
	double value;                   //目标值
	int precision;                  //精确度,小数点后几位

	int step;                       //步长
	int space;                      //间距
	int radius;                     //圆角角度

	QColor bgColorStart;            //背景渐变开始颜色
	QColor bgColorEnd;              //背景渐变结束颜色

	QColor lineColor;               //线条颜色
	QColor textColor;               //文本颜色

	QColor barBgColor;              //进度背景颜色
	QColor barColor;                //进度颜色
	QString text_font;	// 字体
public:
	double getMinValue()            const;
	double getMaxValue()            const;
	double getValue()               const;
	int getPrecision()              const;

	int getStep()                   const;
	int getSpace()                  const;
	int getRadius()                 const;

	QColor getBgColorStart()        const;
	QColor getBgColorEnd()          const;

	QColor getLineColor()           const;
	QColor getTextColor()           const;

	QColor getBarBgColor()          const;
	QColor getBarColor()            const;

	QSize sizeHint()                const;
	QSize minimumSizeHint()         const;

public Q_SLOTS:
	//设置范围值
	void setRange(double minValue, double maxValue);
	void setRange(int minValue, int maxValue);

	//设置最大最小值
	void setMinValue(double minValue);
	void setMaxValue(double maxValue);

	//设置目标值
	void setValue(double value);
	void setValue(int value);

	//设置精确度
	void setPrecision(int precision);

	//设置步长
	void setStep(int step);
	//设置间距
	void setSpace(int space);
	//设置圆角角度
	void setRadius(int radius);

	//设置背景颜色
	void setBgColorStart(const QColor& bgColorStart);
	void setBgColorEnd(const QColor& bgColorEnd);

	//设置线条颜色
	void setLineColor(QColor lineColor);
	//设置文本颜色
	void setTextColor(QColor textColor);
	//设置进度颜色
	void setBarBgColor(QColor barBgColor);
	void setBarColor(QColor barColor);

	// 设置字体
	void setTextFont(const QString& font);

Q_SIGNALS:
	void valueChanged(double value);
};

#endif
