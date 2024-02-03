#pragma once
#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>
#include <QEvent>
#include <QPainterPath>

class SwitchButton : public QWidget
{
	Q_OBJECT
		Q_ENUMS(ButtonStyle)

		Q_PROPERTY(int space READ getSpace WRITE setSpace) // 设置间距
		Q_PROPERTY(int rectRadius READ getRectRadius WRITE setRectRadius) // 设置圆角角度
		Q_PROPERTY(bool checked READ getChecked WRITE setChecked) // 设置是否选中
		Q_PROPERTY(bool showText READ getShowText WRITE setShowText) // 设置是否显示文字
		Q_PROPERTY(bool showCircle READ getShowCircle WRITE setShowCircle) // 设置是否显示小圆
		Q_PROPERTY(bool animation READ getAnimation WRITE setAnimation) // 设置是否启用动画

		Q_PROPERTY(ButtonStyle buttonStyle READ getButtonStyle WRITE setButtonStyle) // 设置按钮样式

		Q_PROPERTY(QColor bgColorOff READ getBgColorOff WRITE setBgColorOff) // 设置关闭状态背景色
		Q_PROPERTY(QColor bgColorOn READ getBgColorOn WRITE setBgColorOn) // 设置开启状态背景色
		Q_PROPERTY(QColor sliderColorOff READ getSliderColorOff WRITE setSliderColorOff) // 设置关闭状态滑块颜色
		Q_PROPERTY(QColor sliderColorOn READ getSliderColorOn WRITE setSliderColorOn) // 设置开启状态滑块颜色
		Q_PROPERTY(QColor textColorOff READ getTextColorOff WRITE setTextColorOff) // 设置关闭状态文本颜色
		Q_PROPERTY(QColor textColorOn READ getTextColorOn WRITE setTextColorOn) // 设置开启状态文本颜色

		Q_PROPERTY(QString textOff READ getTextOff WRITE setTextOff) // 设置关闭状态文本
		Q_PROPERTY(QString textOn READ getTextOn WRITE setTextOn) // 设置开启状态文本
public:
	enum ButtonStyle
	{
		ButtonStyle_Rect = 0,       //圆角矩形
		ButtonStyle_CircleIn = 1,   //内圆形
		ButtonStyle_CircleOut = 2   //外圆形
	};

	SwitchButton(QWidget* parent = 0);	// 构造函数
	~SwitchButton();	// 析构函数
protected:
	//void mousePressEvent(QMouseEvent* event) override;	// 鼠标按下事件处理
	void mouseReleaseEvent(QMouseEvent* event) override;	// 鼠标按下松开事件处理
	void resizeEvent(QResizeEvent*) override;	// 尺寸改变事件处理
	void paintEvent(QPaintEvent*) override;	// 绘图事件处理
	void drawBg(QPainter* painter);	// 绘制背景
	void drawSlider(QPainter* painter);	// 绘制滑块

private:
	int space;                      //滑块离背景间隔
	int rectRadius;                 //圆角角度
	bool checked;                   //是否选中(即开关)
	bool showText;                  //显示文字
	bool showCircle;                //显示小圆
	bool animation;                 //动画过渡

	ButtonStyle buttonStyle;        //开关按钮样式

	QColor bgColorOff;              //关闭时背景颜色
	QColor bgColorOn;               //打开时背景颜色
	QColor sliderColorOff;          //关闭时滑块颜色
	QColor sliderColorOn;           //打开时滑块颜色
	QColor textColorOff;            //关闭时文字颜色
	QColor textColorOn;             //打开时文字颜色

	QString textOff;                //关闭时显示的文字
	QString textOn;                 //打开时显示的文字

	int step;                       //每次移动的步长
	int startX;                     //滑块开始X轴坐标
	int endX;                       //滑块结束X轴坐标
	QTimer* timer;                  //定时器绘制
	QFont font;	// 字体

private slots:	// 槽函数
	void change();	// 切换按钮状态函数 --- 切换按钮状态
	void updateValue();	// 更新数值函数 --- 更新滑块位置和状态

public:
	int getSpace()                  const;	// 获取间距
	int getRectRadius()             const;	// 获取矩形圆角
	bool getChecked()               const;		// 获取按钮状态
	bool getShowText()              const;		// 获取是否显示文本
	bool getShowCircle()            const;	// 获取是否显示圆圈
	bool getAnimation()             const;	// 获取是否启用动画

	ButtonStyle getButtonStyle()    const;	// 获取按钮样式

	QColor getBgColorOff()          const;	// 获取关闭状态背景色
	QColor getBgColorOn()           const;	// 获取开启状态背景色
	QColor getSliderColorOff()      const;	// 获取关闭状态滑块颜色
	QColor getSliderColorOn()       const;	// 获取开启状态滑块颜色
	QColor getTextColorOff()        const;	// 获取关闭状态文本颜色
	QColor getTextColorOn()         const;	// 获取开启状态文本颜色

	QString getTextOff()            const;	// 获取关闭状态文本
	QString getTextOn()             const;	// 获取开启状态文本

	QSize sizeHint()                const;	// 获取建议大小
	QSize minimumSizeHint()         const;	// 获取最小大小

public Q_SLOTS:
	//设置间隔
	void setSpace(int space);
	//设置圆角角度
	void setRectRadius(int rectRadius);
	//设置是否选中
	void setChecked(bool checked);
	//设置是否显示文字
	void setShowText(bool showText);
	//设置是否显示小圆
	void setShowCircle(bool showCircle);
	//设置是否动画过渡
	void setAnimation(bool animation);

	//设置风格样式
	void setButtonStyle(const ButtonStyle& buttonStyle);

	//设置背景颜色
	void setBgColorOff(const QColor& bgColorOff);
	void setBgColorOn(const QColor& bgColorOn);

	//设置滑块颜色
	void setSliderColorOff(const QColor& sliderColorOff);
	void setSliderColorOn(const QColor& sliderColorOn);

	//设置文字颜色
	void setTextColorOff(const QColor& textColorOff);
	void setTextColorOn(const QColor& textColorOn);

	//设置文字
	void setTextOff(const QString& textOff);
	void setTextOn(const QString& textOn);

	// 设置字体
	void setTextFont(QFont font);

	// 设置按钮开关
	void setButtonOnOff(bool status);
signals:	// 信号
	void checkedChanged(bool check);	// 鼠标按键信号
};

#endif // SWITCHBUTTON_H