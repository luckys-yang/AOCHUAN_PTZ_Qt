#include "MainPage7.h"
#include "ImageAnimation.h"

MainPage7::MainPage7(QWidget* parent)
    : QWidget(parent)
{
    MainPage7_ui = nullptr;
}

MainPage7::~MainPage7()
{}

void MainPage7::MainPage7_Init()
{
    /*导航 设置*/
    MainPage7_ui->Page7_navBar->setBarColorStart(QColor("#74ebd5"));
    MainPage7_ui->Page7_navBar->setBarColorEnd(QColor("#9face6"));
    MainPage7_ui->Page7_navBar->setItems("关于软件;开发与维护;关于稳定器");
    MainPage7_ui->Page7_navBar->setTextFont(QFont(MainwindowParameter.System_Font_Id, 11));	// 设置字体和大小
    MainPage7_ui->Page7_navBar->setLineWidth(4);
    MainPage7_ui->Page7_navBar->setLineColor(QColor(24, 189, 155));
    MainPage7_ui->Page7_navBar->setBgColorStart(Qt::transparent);
    MainPage7_ui->Page7_navBar->setBgColorEnd(Qt::transparent);
    MainPage7_ui->Page7_navBar->setBarColorStart(Qt::transparent);
    MainPage7_ui->Page7_navBar->setBarColorEnd(Qt::transparent);
    MainPage7_ui->Page7_navBar->setTextNormalColor(QColor(50, 50, 50));
    MainPage7_ui->Page7_navBar->setTextSelectColor(QColor(255, 107, 107));
    MainPage7_ui->Page7_navBar->setBarStyle(NavBar::BarStyle_Line_Bottom);
    MainPage7_ui->Page7_navBar->setHorizontal(true);

    /*图片动画*/
    imageList.addItem(":/Page7/Resource/Images/s1_video.png", "SMART S1");
    imageList.addItem(":/Page7/Resource/Images/s2_video.png", "SMART S2");
    imageList.addItem(":/Page7/Resource/Images/x_video.png", "SMART X");
    imageList.addItem(":/Page7/Resource/Images/xe_video.png", "SMART XE");
    imageList.addItem(":/Page7/Resource/Images/xpro_video.png", "SMART X PRO");
    imageList.addItem(":/Page7/Resource/Images/xr_video.jpg", "SMART XR");

    MainPage7_ui->Page7_page3_Image->setAnimationType(ImageAnimation::FlipRightToLeft);	// 设置模式
}

void MainPage7::MainPage7_Connect_Handler()
{
    /*左边导航栏改变触发*/
    connect(MainPage7_ui->Page7_navBar, &NavBar::NavBar_Signals_CurrentItemChanged, this, [&](int index, const QString& item)
        {
            MainPage7_ui->Page7_stackedWidget->setCurrentIndex(index);	// 设置下边stack显示的页面下标
#ifdef QT_MainPage7_Debug
            qDebug() << "Index:" << index << "item:" << item;
#endif
        });

    /*点击图片触发*/
    connect(MainPage7_ui->Page7_page3_Image, &ImageAnimation::ImageAnimation_Signals_mose_isRelease, this, &MainPage7::MainPage7_Image_Clicked_Hanndler);

    emit MainPage7_ui->Page7_page3_Image->ImageAnimation_Signals_mose_isRelease();	// 触发信号一次
}

void MainPage7::MainPage7_Image_Clicked_Hanndler()
{
    QString currentImagePath = imageList.getCurrentImagePath();
    QString nextImagePath = imageList.getNextImagePath();
    MainPage7_ui->Page7_page3_Image->setPixmap1(QPixmap(currentImagePath));
    MainPage7_ui->Page7_page3_Image->setPixmap2(QPixmap(nextImagePath));
    MainPage7_ui->Page7_page3_Image->start();
    // 对应名称也改变
    MainPage7_ui->Page7_label1->setText(imageList.getCurrentImageName());
}