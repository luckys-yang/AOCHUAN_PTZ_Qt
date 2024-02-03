#pragma once
#ifndef STEPPROGRESS_H
#define STEPPROGRESS_H

#include <QWidget>
#include <QPainterPath>

/*
* 方框
*/

class StepProgress  : public QWidget
{
	Q_OBJECT

public:
	enum StatusMode_et {
		ColorMode_Normal = 0,       //显示正常的颜色(绿色)
		ColorMode_Finish = 1,      //显示完成的颜色(红色)
	};
	enum TextAlign {
		TextAlign_Top_Left = 0,         // 顶部居左对齐
		TextAlign_Top_Center = 1,       // 顶部居中对齐
		TextAlign_Top_Right = 2,        // 顶部居右对齐
		TextAlign_Center_Left = 3,      // 中部居左对齐
		TextAlign_Center_Center = 4,    // 中部居中对齐
		TextAlign_Center_Right = 5,     // 中部居右对齐
		TextAlign_Bottom_Left = 6,      // 底部居左对齐
		TextAlign_Bottom_Center = 7,    // 底部居中对齐
		TextAlign_Bottom_Right = 8      // 底部居右对齐
	};

public:
	explicit StepProgress(QWidget *parent = nullptr);
	~StepProgress();
protected:
	// 重写
	void paintEvent(QPaintEvent*) override;
	// 画背景
	void StepProgress_Draw_Bg(QPainter* painter);
	// 画文本
	void StepProgress_Draw_Text(QPainter* painter);

private:
	int borderRadius;           //圆角半径
	int borderWidth;            //边框宽度
	QColor borderColor;         //边框颜色

	QString text;               //文字
	QFont textFont;             //文字字体
	TextAlign textAlign;        //文字对齐方式
	QColor textColor;           //文字颜色

	QColor normalColor;		// 正常颜色
	QColor finishColor;	// 完成颜色
	StatusMode_et statusMode;		// 当前状态模式
public:
	int getBorderRadius()       const;
	int getBorderWidth()        const;
	QColor getBorderColor()     const;

	QString getText()           const;
	QFont getTextFont()         const;
	TextAlign getTextAlign()    const;
	QColor getTextColor()       const;

	QColor getNormalColor()     const;
	QColor getFinishColor()    const;

	//设置边框圆角角度
	void setBorderRadius(int borderRadius);
	//设置边框宽度
	void setBorderWidth(int borderWidth);
	//设置边框颜色
	void setBorderColor(const QColor& borderColor);

	//设置文字
	void setText(const QString& text);
	//设置文字字体
	void setTextFont(const QFont& textFont);
	//设置文字对齐方式
	void setTextAlign(const TextAlign& textAlign);
	//设置文字颜色
	void setTextColor(const QColor& textColor);

	//设置正常颜色
	void setNormalColor(const QColor& normalColor);
	//设置完成颜色
	void setFinishColor(const QColor& finishColor);

	// 设置当前状态模式
	void setStatusMode(const StatusMode_et& status);
};

#endif