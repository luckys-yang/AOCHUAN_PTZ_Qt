#pragma once
#ifndef BSP_COMBOBOX_H
#define BSP_COMBOBOX_H
#include <QWidget>
#include <QComboBox>

// 调试打印
//#define QT_Bsp_ComBoBox_DEBUG

class Bsp_ComBoBox  : public QComboBox
{
	Q_OBJECT
		Q_PROPERTY(int itemWidth READ getItemWidth WRITE setItemWidth)
		Q_PROPERTY(int itemHeight READ getItemHeight WRITE setItemHeight)
		Q_PROPERTY(bool autoWidth READ getAutoWidth WRITE setAutoWidth)

public:
	Bsp_ComBoBox(QWidget *parent = 0);
	~Bsp_ComBoBox();

protected:
	void showEvent(QShowEvent*);

private:
    int itemWidth;                  //元素宽度
    int itemHeight;                 //元素高度
    bool autoWidth;                 //是否自动调整元素宽度
    int maxItemWidth;               //最大元素宽度
    QFont font; // 字体
public:
    int getItemWidth()              const;
    int getItemHeight()             const;
    bool getAutoWidth()             const;

public Q_SLOTS:
    void setItemWidth(int itemWidth);
    void setItemHeight(int itemHeight);
    void setAutoWidth(bool autoWidth);
    void setTextFont(QFont font);
};


#endif