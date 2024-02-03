#include "FlatUI.h"
#include <QMutex>
#include <QPushbutton>
#include <QLineedit>
#include <QProgressbar>
#include <QSlider>
#include <QRadiobutton>
#include <QCheckbox>
#include <QScrollbar>
#include <QLabel>
#include <QDebug>

QScopedPointer<FlatUI> FlatUI::self;    // 声明了FlatUI类中的一个静态成员变量self

FlatUI* FlatUI::Instance()
{
    // 检查 self 是否为空
    if (self.isNull())
    {
        // 使用静态局部变量来确保线程安全的初始化
        static QMutex mutex;
        QMutexLocker locker(&mutex);
        // 再次检查 self 是否为空，防止多线程竞争条件
        if (self.isNull())
        {
            self.reset(new FlatUI); // 创建并初始化 FlatUI 实例
        }
    }

    return self.data(); // 返回 FlatUI 实例的指针
}

FlatUI::FlatUI(QObject* parent) : QObject(parent)
{

}

QString FlatUI::setPushButtonQss(QPushButton* btn,
    QFont font,
    int radius, 
    int padding,
    const QString& normalColor,
    const QString& normalTextColor,
    const QString& hoverColor,
    const QString& hoverTextColor,
    const QString& pressedColor,
    const QString& pressedTextColor)
{
    QStringList list;   // 创建字符串列表，存放不同状态下的样式
    // 正常状态样式
    list.append(QString("QPushButton{border-style:none;padding:%1px;border-radius:%2px;color:%3;background:%4;}")
        .arg(padding).arg(radius).arg(normalTextColor).arg(normalColor));
    // 悬停状态样式
    list.append(QString("QPushButton:hover{color:%1;background:%2;}")
        .arg(hoverTextColor).arg(hoverColor));
    // 按下状态样式
    list.append(QString("QPushButton:pressed{color:%1;background:%2;}")
        .arg(pressedTextColor).arg(pressedColor));

    QString qss = list.join("");    // 将样式表字符串拼接成一个字符串
    btn->setStyleSheet(qss);    // 设置按钮的样式表
    btn->setFont(font);

    return qss; // 返回生成的样式表字符串
}

QString FlatUI::setLineEditQss(QLineEdit* txt, const QFont& font, 
    int radius, 
    int borderWidth,
    const QString& normalColor,
    const QString& focusColor)
{
    QStringList list;
    // 正常状态样式
    list.append(QString("QLineEdit{border-style:none;padding:3px;border-radius:%1px;border:%2px solid %3;}")
        .arg(radius).arg(borderWidth).arg(normalColor));
    // 聚焦状态样式
    list.append(QString("QLineEdit:focus{border:%1px solid %2;}")
        .arg(borderWidth).arg(focusColor));

    QString qss = list.join("");    // 将样式表字符串拼接成一个字符串
    txt->setStyleSheet(qss);
    txt->setFont(font);

    return qss;
}

QString FlatUI::setProgressQss(QProgressBar* bar, int barHeight,
    int barRadius, int fontSize,
    const QString& normalColor,
    const QString& chunkColor)
{

    QStringList list;
    // 正常状态样式
    list.append(QString("QProgressBar{font:%1pt;background:%2;max-height:%3px;border-radius:%4px;text-align:center;border:1px solid %2;}")
        .arg(fontSize).arg(normalColor).arg(barHeight).arg(barRadius));
    // 进度状态样式
    list.append(QString("QProgressBar:chunk{border-radius:%2px;background-color:%1;}")
        .arg(chunkColor).arg(barRadius));

    QString qss = list.join("");    // 将样式表字符串拼接成一个字符串
    bar->setStyleSheet(qss);
    return qss;
}

QString FlatUI::setSliderQss(QSlider* slider, int sliderHeight,
    const QString& normalColor,
    const QString& grooveColor,
    const QString& handleBorderColor,
    const QString& handleColor)
{
    // 计算滑块的相关参数
    int sliderRadius = sliderHeight / 2;
    int handleWidth = (sliderHeight * 3) / 2 + (sliderHeight / 5);
    int handleRadius = handleWidth / 2;
    int handleOffset = handleRadius / 2;
        
    QStringList list;   // 创建字符串列表，存放不同状态下的样式
    // 水平方向滑块样式
    list.append(QString("QSlider::horizontal{min-height:%1px;}").arg(sliderHeight * 2));
    list.append(QString("QSlider::groove:horizontal{background:%1;height:%2px;border-radius:%3px;}")
        .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::add-page:horizontal{background:%1;height:%2px;border-radius:%3px;}")
        .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::sub-page:horizontal{background:%1;height:%2px;border-radius:%3px;}")
        .arg(grooveColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::handle:horizontal{width:%3px;margin-top:-%4px;margin-bottom:-%4px;border-radius:%5px;"
        "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 %1,stop:0.8 %2);}")
        .arg(handleColor).arg(handleBorderColor).arg(handleWidth).arg(handleOffset).arg(handleRadius));

    // 垂直方向滑块样式
    //偏移一个像素
    handleWidth = handleWidth + 1;
    list.append(QString("QSlider::vertical{min-width:%1px;}").arg(sliderHeight * 2));
    list.append(QString("QSlider::groove:vertical{background:%1;width:%2px;border-radius:%3px;}")
        .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::add-page:vertical{background:%1;width:%2px;border-radius:%3px;}")
        .arg(grooveColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::sub-page:vertical{background:%1;width:%2px;border-radius:%3px;}")
        .arg(normalColor).arg(sliderHeight).arg(sliderRadius));
    list.append(QString("QSlider::handle:vertical{height:%3px;margin-left:-%4px;margin-right:-%4px;border-radius:%5px;"
        "background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6 %1,stop:0.8 %2);}")
        .arg(handleColor).arg(handleBorderColor).arg(handleWidth).arg(handleOffset).arg(handleRadius));

    QString qss = list.join("");    // 将样式表字符串拼接成一个字符串
    slider->setStyleSheet(qss); // 设置滑块的样式表
    return qss;
}

QString FlatUI::setRadioButtonQss(QRadioButton* rbtn, 
    const QFont& font,
    int indicatorRadius,
    const QString& normalColor,
    const QString& checkColor)
{
    int indicatorWidth = indicatorRadius * 2;   // 计算指示器的宽度

    QStringList list;   // 创建字符串列表，存放不同状态下的样式
    // 未选中状态样式
    list.append(QString("QRadioButton::indicator{border-radius:%1px;width:%2px;height:%2px;}")
        .arg(indicatorRadius).arg(indicatorWidth));
    list.append(QString("QRadioButton::indicator::unchecked{background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,"
        "stop:0.6 #FFFFFF,stop:0.7 %1);}").arg(normalColor));
    // 选中状态样式
    list.append(QString("QRadioButton::indicator::checked{background:qradialgradient(spread:pad,cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,"
        "stop:0 %1,stop:0.3 %1,stop:0.4 #FFFFFF,stop:0.6 #FFFFFF,stop:0.7 %1);}").arg(checkColor));

    QString qss = list.join("");    // 将样式表字符串拼接成一个字符串
    rbtn->setStyleSheet(qss);
    rbtn->setFont(font);

    return qss;
}

QString FlatUI::setScrollBarQss(QWidget* scroll, int radius, int min, int max,
    const QString& bgColor,
    const QString& handleNormalColor,
    const QString& handleHoverColor,
    const QString& handlePressedColor)
{
    //滚动条离背景间隔
    int padding = 0;

    QStringList list;

    //handle:指示器,滚动条拉动部分 add-page:滚动条拉动时增加的部分 sub-page:滚动条拉动时减少的部分 add-line:递增按钮 sub-line:递减按钮

    //横向滚动条部分
    list.append(QString("QScrollBar:horizontal{background:%1;padding:%2px;border-radius:%3px;min-height:%4px;max-height:%4px;}")
        .arg(bgColor).arg(padding).arg(radius).arg(max));
    list.append(QString("QScrollBar::handle:horizontal{background:%1;min-width:%2px;border-radius:%3px;}")
        .arg(handleNormalColor).arg(min).arg(radius));
    list.append(QString("QScrollBar::handle:horizontal:hover{background:%1;}")
        .arg(handleHoverColor));
    list.append(QString("QScrollBar::handle:horizontal:pressed{background:%1;}")
        .arg(handlePressedColor));
    list.append(QString("QScrollBar::add-page:horizontal{background:none;}"));
    list.append(QString("QScrollBar::sub-page:horizontal{background:none;}"));
    list.append(QString("QScrollBar::add-line:horizontal{background:none;}"));
    list.append(QString("QScrollBar::sub-line:horizontal{background:none;}"));

    //纵向滚动条部分
    list.append(QString("QScrollBar:vertical{background:%1;padding:%2px;border-radius:%3px;min-width:%4px;max-width:%4px;}")
        .arg(bgColor).arg(padding).arg(radius).arg(max));
    list.append(QString("QScrollBar::handle:vertical{background:%1;min-height:%2px;border-radius:%3px;}")
        .arg(handleNormalColor).arg(min).arg(radius));
    list.append(QString("QScrollBar::handle:vertical:hover{background:%1;}")
        .arg(handleHoverColor));
    list.append(QString("QScrollBar::handle:vertical:pressed{background:%1;}")
        .arg(handlePressedColor));
    list.append(QString("QScrollBar::add-page:vertical{background:none;}"));
    list.append(QString("QScrollBar::sub-page:vertical{background:none;}"));
    list.append(QString("QScrollBar::add-line:vertical{background:none;}"));
    list.append(QString("QScrollBar::sub-line:vertical{background:none;}"));

    QString qss = list.join("");
    scroll->setStyleSheet(qss);
    return qss;
}

QString FlatUI::setCheckBoxQss(QCheckBox* checkbox,
    QFont font,
    int indicatorRadius,
    int indicatorBorderRadius,
    const QString& normalColor,
    const QString& checkColor)
{
    // 复选框
    int indicatorWidth = indicatorRadius * 2;

    QStringList list;
    list.append(QString("QCheckBox::indicator{width:%1px;height:%1px;border-radius:%2px;}").arg(indicatorWidth).arg(indicatorBorderRadius));
    list.append(QString("QCheckBox::indicator:unchecked{image:none;background:%1;}").arg(normalColor));
    list.append(QString("QCheckBox::indicator:checked{image:url(:/FlatUI/Resource/Images/Check_1.png);background:transparent;}"));

    QString qss = list.join("");
    checkbox->setStyleSheet(qss);
    checkbox->setFont(font);
    return qss;
}

QString FlatUI::setLabelQss(QLabel* label,
    const QFont& font,
    int borderRadius,
    const QString& bgColor,
    const QString& textColor
    )
{
    QStringList list;
    // 添加padding属性 -- 元素的上下边缘将有 2 像素的填充，而左右边缘将有 4 像素的填充
    list.append(QString("QLabel{border-radius:%1px;background:%2;color:%3;}").arg(borderRadius).arg(bgColor).arg(textColor));
    list.append(QString("QLabel:hover{background:%1;}").arg(bgColor));  // 鼠标悬停时的背景颜色
    list.append(QString("QLabel:pressed{background:%1;}").arg(bgColor));  // 鼠标按下时的背景颜色

    QString qss = list.join("");
    label->setStyleSheet(qss);
    label->setFont(font);
    label->setAlignment(Qt::AlignCenter);

    return qss;
}