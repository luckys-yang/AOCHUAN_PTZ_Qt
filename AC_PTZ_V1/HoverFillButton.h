#pragma once
#ifndef HOVERFILLBUTTON_H
#define HOVERFILLBUTTON_H

#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QTimer>
#include <QEnterEvent>
#include <QEvent>
#include <QCursor>
#include <QPainter>
#include <QPaintEvent>
#include <QBrush>
#include <QPen>
#include <QRgb>
#include <QPainterPath>
#include <QRegularExpression>
#include <QtMath>
#include <QPalette>
#include <QPointF>
#include <QGraphicsDropShadowEffect>

// 调试打印
//#define QT_HoverFillButton_DEBUG

class HoverFillButton : public QPushButton
{
	Q_OBJECT
public:
	HoverFillButton(QWidget* parent = nullptr);
	~HoverFillButton();

	//添加阴影效果//右偏移量//下偏移量//模糊半径//阴影颜色
	void addShadow(int right, int down, qreal blurRadius, const QColor& shadowColor = Qt::black);
	void setButtonStyle(QFont font,
		int radius = 15,
		const QString& normalColor = "#97aaa3",
		const QString& normalTextColor = "#000000",
		const QString& hoverColor = "#79737b",
		const QString& hoverTextColor = "#000000",
		const QString& pressedColor = "#624a5d",
		const QString& pressedTextColor = "#000000"
	);
protected:
	// 重写绘画函数(override)
	virtual void paintEvent(QPaintEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
signals:
	void HoverFillButton_Signals_mose_isRelease();  // 鼠标松开信号
};

#endif
