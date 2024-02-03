#include "StepProgress.h"
#include <QPainter>
#include <QPainterPath>
#include <QEvent>
#include <QDebug>

StepProgress::StepProgress(QWidget* parent)
	: QWidget(parent)
{
	borderRadius = 5;
	borderWidth = 0;	// 2
	borderColor = QColor(107, 145, 146);	// 边框颜色

	text = "";
	textFont = this->font();
	textAlign = TextAlign_Center_Center;
	textColor = QColor(0, 0, 0);	// 黑色

	finishColor = QColor(255, 0, 0).lighter(80);	// 绿色
	normalColor = QColor(0, 255, 0).lighter(80);	// 红色

	statusMode = StepProgress::ColorMode_Normal;
}

StepProgress::~StepProgress()
{}

void StepProgress::paintEvent(QPaintEvent*)
{
	//绘制准备工作,启用反锯齿
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	StepProgress_Draw_Bg(&painter);
	StepProgress_Draw_Text(&painter);
}

void StepProgress::StepProgress_Draw_Bg(QPainter* painter)
{
	painter->save();

	//设置边框颜色及宽度
	QPen pen;
#if 0
	pen.setColor(borderColor);
#endif

	//绘制区域要减去边框宽度
	QRect rect;
	rect.setX(borderWidth);
	rect.setY(borderWidth);
	rect.setWidth(width() - borderWidth * 2);
	rect.setHeight(height() - borderWidth * 2);

	switch (statusMode)
	{
	case ColorMode_Normal:
	{
		pen.setColor(normalColor);
		painter->setBrush(QBrush(normalColor));	// 正常颜色
		break;
	}
	case ColorMode_Finish:
	{
		pen.setColor(finishColor);
		painter->setBrush(QBrush(finishColor));	// 完成颜色
		break;
	}
	default:break;
	}
	pen.setWidthF(borderWidth);
	painter->setPen(pen);

	painter->drawRoundedRect(rect, borderRadius, borderRadius);

	painter->restore();
}

void StepProgress::StepProgress_Draw_Text(QPainter* painter)
{
	painter->save();

	int offset = 5;
	QRect rect;
	rect.setX(borderWidth * offset);
	rect.setY(borderWidth);
	rect.setWidth(width() - borderWidth * offset * 2);
	rect.setHeight(height() - borderWidth * 2);

	Qt::Alignment alignment = Qt::AlignCenter;

	switch (textAlign)
	{
	case TextAlign_Top_Left:
	{
		alignment = Qt::AlignTop | Qt::AlignLeft;
		break;
	}
	case TextAlign_Top_Center:
	{
		alignment = Qt::AlignTop | Qt::AlignHCenter;
		break;
	}
	case TextAlign_Top_Right:
	{
		alignment = Qt::AlignTop | Qt::AlignRight;
		break;
	}
	case TextAlign_Center_Left:
	{
		alignment = Qt::AlignLeft | Qt::AlignVCenter;
		break;
	}
	case TextAlign_Center_Center:
	{
		alignment = Qt::AlignHCenter | Qt::AlignVCenter;
		break;
	}
	case TextAlign_Center_Right:
	{
		alignment = Qt::AlignRight | Qt::AlignVCenter;
		break;
	}
	case TextAlign_Bottom_Left:
	{
		alignment = Qt::AlignRight | Qt::AlignVCenter;
		break;
	}
	case TextAlign_Bottom_Center:
	{
		alignment = Qt::AlignBottom | Qt::AlignHCenter;
		break;
	}
	case TextAlign_Bottom_Right:
	{
		alignment = Qt::AlignBottom | Qt::AlignRight;
		break;
	}
	default:break;
	}

	painter->setPen(textColor);

	QFont font;
	font.setLetterSpacing(QFont::AbsoluteSpacing, 1.5);	// 设置字与字之间的间距，值越大间距越大
	font.setPointSize(textFont.pointSize());
	font.setFamily(textFont.family());

	painter->setFont(font);
	painter->drawText(rect, alignment, text);

	painter->restore();
}

int StepProgress::getBorderRadius() const
{
	return this->borderRadius;
}

int StepProgress::getBorderWidth() const
{
	return this->borderWidth;
}

QColor StepProgress::getBorderColor() const
{
	return this->borderColor;
}

QString StepProgress::getText() const
{
	return this->text;
}

QFont StepProgress::getTextFont() const
{
	return this->textFont;
}

StepProgress::TextAlign StepProgress::getTextAlign() const
{
	return this->textAlign;
}

QColor StepProgress::getTextColor() const
{
	return this->textColor;
}

QColor StepProgress::getNormalColor() const
{
	return this->normalColor;
}

QColor StepProgress::getFinishColor() const
{
	return this->finishColor;
}

void StepProgress::setBorderRadius(int borderRadius)
{
	this->borderRadius = borderRadius;
}

void StepProgress::setBorderWidth(int borderWidth)
{
	this->borderWidth = borderWidth;
}

void StepProgress::setBorderColor(const QColor& borderColor)
{
	this->borderColor = borderColor;
}

void StepProgress::setText(const QString& text)
{
	if (this->text != text)
	{
		this->text = text;
		this->update();
	}
}

void StepProgress::setTextFont(const QFont& textFont)
{
	this->textFont = textFont;
}

void StepProgress::setTextAlign(const TextAlign& textAlign)
{
	this->textAlign = textAlign;
}

void StepProgress::setTextColor(const QColor& textColor)
{
	this->textColor = textColor;
}

void StepProgress::setNormalColor(const QColor& normalColor)
{
	this->normalColor = normalColor;
}

void StepProgress::setFinishColor(const QColor& finishColor)
{
	this->finishColor = finishColor;
}

void StepProgress::setStatusMode(const StatusMode_et& status)
{
	if (this->statusMode != status)
	{
		this->statusMode = status;
		this->update();
	}
}
