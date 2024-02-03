#include "Bsp_ComBoBox.h"
#include "qlistview.h"

#ifdef QT_Bsp_ComBoBox_DEBUG
#include <QDebug>
#endif


Bsp_ComBoBox::Bsp_ComBoBox(QWidget* parent)
    : QComboBox(parent)
{
    itemWidth = 5;
    itemHeight = 20;
    autoWidth = true;
    this->setView(new QListView());
}

Bsp_ComBoBox::~Bsp_ComBoBox()
{
#ifdef QT_Bsp_ComBoBox_DEBUG
    qDebug() << "delete Bsp_ComBoBox";
#endif

}

void Bsp_ComBoBox::showEvent(QShowEvent*)
{
    if (autoWidth)
    {
        //自动计算所有元素,找到最长的元素
        QFontMetrics fm = this->fontMetrics();
        int count = this->count();
        for (int i = 0; i < count; i++)
        {
            QRect textRect = fm.boundingRect(this->itemText(i));
            int textWidth = textRect.width();
            itemWidth = (textWidth > itemWidth ? textWidth : itemWidth);    //宽度增加像素,因为有边距
        }
       
        // 如果小于框宽度则等于框宽度---2024.1.13加
        itemWidth = (itemWidth > this->width() ? itemWidth + 20: this->width());
        this->view()->setFixedWidth(itemWidth);
    }
}

int Bsp_ComBoBox::getItemWidth() const
{
    return this->itemWidth;
}

int Bsp_ComBoBox::getItemHeight() const
{
    return this->itemHeight;
}

bool Bsp_ComBoBox::getAutoWidth() const
{
    return this->autoWidth;
}

void Bsp_ComBoBox::setItemWidth(int itemWidth)
{
    if (this->itemWidth != itemWidth)
    {
        this->itemWidth = itemWidth;
        if (!autoWidth)
        {
            this->view()->setFixedWidth(itemWidth);
        }
    }
}

void Bsp_ComBoBox::setItemHeight(int itemHeight)
{
    if (this->itemHeight != itemHeight)
    {
        this->itemHeight = itemHeight;
        this->setStyleSheet(QString("QComboBox QAbstractItemView::item{border-radius: 4px;min-height:%1px;}").arg(itemHeight));
    }
}

void Bsp_ComBoBox::setAutoWidth(bool autoWidth)
{
    if (this->autoWidth != autoWidth)
    {
        this->autoWidth = autoWidth;
    }
}

void Bsp_ComBoBox::setTextFont(QFont font)
{
    this->font = font;
}
