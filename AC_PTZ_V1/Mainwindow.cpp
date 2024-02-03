#include "Mainwindow.h"
#include "HoverFillButton.h"
#include "Panelitem.h"
#include "FlatUI.h"
#include "NavLabel.h"
#include "savelog.h"
#include "SwitchButton.h"
#include "ProgressColor.h"
#include "QtTest.h"
#include "HintMessage.h"
#include "Protocol.h"

#include <QApplication>
#include <QScreen>                    // QScreen 类提供了有关计算机屏幕的信息，如分辨率和大小
#include <QFile>
#include <QFontDatabase>
#include <Windows.h>
#include <QDatetime>
#include<QRegularexpression>
#include <QThread>
#include <QMutexLocker>
#include <QPoint>
#include <QMenu>
#ifdef QT_Mainwindow_DEBUG
#include <QDebug>
#endif

/*
* 页面推荐颜色：
				1. 245,239,236
				2. 216,233,242
*/

// 主窗口宽度
#define MainWindow_W 1200
// 主窗口高度
#define MainWindow_H 780

// 窗口圆角
#define MainWindow_Radius 15

// 水平分割线高度
#define Line_H 40


MainwindowParameter_t MainwindowParameter =
{
	"",
	{
		{0, Line_H},	// [line] 水平分割线
	},
	{0, 0},
	"",
	false
};


Mainwindow::Mainwindow(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::MainwindowClass)
{
	ui->setupUi(this);

	mainpage1 = new MainPage1(this);
	mainpage1->MainPage1_ui = ui;

	mainpage2 = new MainPage2(this);
	mainpage2->MainPage2_ui = ui;

	mainpage3 = new MainPage3(this);
	mainpage3->MainPage3_ui = ui;

	mainpage4 = new MainPage4(this);
	mainpage4->MainPage4_ui = ui;

	mainpage5 = new MainPage5(nullptr);
	mainpage5->MainPage5_ui = ui;

	mainpage6 = new MainPage6(this);
	mainpage6->MainPage6_ui = ui;

	mainpage7 = new MainPage7(this);
	mainpage7->MainPage7_ui = ui;

	maintopbottom = new MainTopBottom(this);
	maintopbottom->MainTopBottom_ui = ui;

	Mainwindow_Config();
	Mainwindow_Get_CSS();
	Mainwindow_Init();
	Mainwindow_Thread_Init();
}


Mainwindow::~Mainwindow()
{
#ifdef QT_Mainwindow_DEBUG
	qDebug() << "delete Mainwindow";
#endif 
	threadOfSerial->quit();
	threadOfSerial->wait();
	delete ui;
}

void Mainwindow::Mainwindow_Init()
{
	/*单例初始化*/
	AppSettings::Instance()->AppSettings_Init();

	/*创建消息控件*/
	Main_Msg = new HintMessage(this);
	Main_Msg->SetDuration(500);

	maintopbottom->MainTopBottom_Init();	// TopBottom初始化
	mainpage1->MainPage1_Init();	// 页面1初始化
	mainpage2->MainPage2_Init();	// 页面2初始化
	mainpage3->MainPage3_Init();	// 页面3初始化
	mainpage4->MainPage4_Init();	// 页面4初始化
	mainpage5->MainPage5_Init();	// 页面5初始化
	mainpage6->MainPage6_Init();	// 页面6初始化
	mainpage7->MainPage7_Init();	// 页面7初始化

	UI_Test_Init();
	Mainwindow_Connect_Handler();

	/*======================================================================================手动触发信号 设置*/
	emit ui->left_navBar->NavBar_Signals_CurrentItemChanged(0, "云台中控");
	emit ui->Page7_navBar->NavBar_Signals_CurrentItemChanged(0, "关于软件");
}

void Mainwindow::Mainwindow_Connect_Handler()
{
	/*主页面的提示信息*/
	connect(this, &Mainwindow::Main_Signals_PromptMsg, this, [&](MessageType type, QString content)
		{
			Main_Msg->Push(type, content);
		});
	/*页面1的提示信息*/
	connect(mainpage1, &MainPage1::MainPage1_Signals_PromptMsg, this, [&](MessageType type, QString content)
		{
			Main_Msg->Push(type, content);
		});
	/*页面3的提示信息*/
	connect(mainpage3, &MainPage3::MainPage3_Signals_PromptMsg, this, [&](MessageType type, QString content)
		{
			Main_Msg->Push(type, content);
		});
	/*页面4的提示信息*/
	connect(mainpage4, &MainPage4::MainPage4_Signals_PromptMsg, this, [&](MessageType type, QString content)
		{
			Main_Msg->Push(type, content);
		});
	/*页面5的提示信息*/
	connect(mainpage5, &MainPage5::MainPage5_Signals_PromptMsg, this, [&](MessageType type, QString content)
		{
			Main_Msg->Push(type, content);
		});
	/*页面6的提示信息*/
	connect(mainpage6, &MainPage6::MainPage6_Signals_PromptMsg, this, [&](MessageType type, QString content)
		{
			Main_Msg->Push(type, content);
		});
	/*TopBottom的提示信息*/
	connect(maintopbottom, &MainTopBottom::MainTopBottom_Signals_PromptMsg, this, [&](MessageType type, QString content)
		{
			Main_Msg->Push(type, content);
		});

	/*左边导航栏改变触发*/
	connect(ui->left_navBar, &NavBar::NavBar_Signals_CurrentItemChanged, this, [&](int index, const QString& item)
		{
			ui->stackedWidget->setCurrentIndex(index);	// 设置右边stack显示的页面下标

#ifdef QT_Mainwindow_DEBUG
			qDebug() << "Index:" << index << "item:" << item;
#endif
		});

	/*最小化按钮点击后释放触发*/
	connect(ui->smallBtn, &QPushButton::clicked, this, [=]()
		{
			// 获取了全局鼠标位置
			QPoint mousePos = QCursor::pos();
			QPoint localPos = this->mapFromGlobal(mousePos);

			if (this->rect().contains(localPos))    // 检查局部坐标是否在窗口的矩形区域内
			{
				this->showMinimized();
			}
		});

	/*关闭按钮点击后释放触发*/
	connect(ui->closeBtn, &QPushButton::clicked, this, [=]()
		{
			// 获取了全局鼠标位置
			QPoint mousePos = QCursor::pos();
			QPoint localPos = this->mapFromGlobal(mousePos);

			if (this->rect().contains(localPos))    // 检查局部坐标是否在窗口的矩形区域内
			{
				this->close();
			}
		});

	// 页面1的连接
	mainpage1->MainPage1_Connect_Handler();
	// 页面2的连接
	mainpage2->MainPage2_Connect_Handler();
	// 页面3的连接
	mainpage3->MainPage3_Connect_Handler();
	// 页面4的连接
	mainpage4->MainPage4_Connect_Handler();
	// 页面5的连接
	mainpage5->MainPage5_Connect_Handler();
	// 页面6的连接
	mainpage6->MainPage6_Connect_Handler();
	// 页面7的连接
	mainpage7->MainPage7_Connect_Handler();
	// MainTopBottom的连接
	maintopbottom->MainTopBottom_Connect_Handler();
}

void Mainwindow::Mainwindow_Set_Bg_Style(const MainStyle& mainStyle, QLinearGradient* gradient)
{
	QColor start_color;
	QColor end_color;

	switch (mainStyle)
	{
	case MainStyle_JapanBlush:
	{
		start_color = QColor(221, 214, 243);
		end_color = QColor(250, 172, 168);
		break;
	}
	case MainStyle_Strong_Stick:
	{
		start_color = QColor(168, 202, 186);
		end_color = QColor(93, 65, 87);
		break;
	}
	case MainStyle_Confident_Cloud:
	{
		start_color = QColor(218, 212, 236);
		end_color = QColor(243, 231, 233);
		break;
	}
	case MainStyle_Flying_Lemon:
	{
		start_color = QColor(100, 179, 244);
		end_color = QColor(194, 229, 156);
		break;
	}
	case MainStyle_Forest_Inei:
	{
		start_color = QColor(223, 137, 181);
		end_color = QColor(191, 217, 254);
		break;
	}
	case MainStyle_Rich_Metal:
	{
		start_color = QColor(215, 210, 204);
		end_color = QColor(48, 67, 82);
		break;
	}
	default:break;
	}
	gradient->setColorAt(0, start_color);
	gradient->setColorAt(1, end_color);
}

void Mainwindow::paintEvent(QPaintEvent* even)
{
	// 绘制准备工作，启用反锯齿
	QPainter painter(this);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

	Mainwindow_Bg_Draw(&painter);	// 画背景

	QWidget::paintEvent(even);	// 调用基类 QWidget 的 paintEvent 函数
}

void Mainwindow::mousePressEvent(QMouseEvent* event)
{
	// 只处理主窗口上小于 Line_H 的区域
	if (event->y() < Line_H)
	{
		if (event->button() == Qt::LeftButton)
		{
			MainwindowParameter.m_click = event->pos();
			MainwindowParameter.MouseFlag = true;
		}
	}
	// 其他处理
	QWidget::mousePressEvent(event);
}

void Mainwindow::mouseReleaseEvent(QMouseEvent* event)
{
	// 只处理主窗口上小于 Line_H 的区域
	if (event->y() < Line_H && event->button() == Qt::LeftButton)
	{
		MainwindowParameter.MouseFlag = false;
		MainwindowParameter.m_click = { 0, 0 };
		//this->update();	// 需要改电脑分辨率100如果两个屏幕来回拖动就不需要加这个刷新
	}
	// 其他处理
	QWidget::mouseReleaseEvent(event);
}

void Mainwindow::mouseMoveEvent(QMouseEvent* event)
{
	if (MainwindowParameter.MouseFlag)
	{
		QPoint currentPos = mapFromGlobal(QCursor::pos());
		this->move(this->pos() + currentPos - MainwindowParameter.m_click);
	}
	QWidget::mouseMoveEvent(event);
}

void Mainwindow::closeEvent(QCloseEvent* event)
{
	// 关闭窗口前把保存日志复选框去掉，否则会异常
	// 检查复选框是否被勾选，如果是，则取消勾选
	if (ui->Debug_SaveLog_CheckBox->isChecked())
	{
		ui->Debug_SaveLog_CheckBox->setChecked(false);
	}
	// 调用父类的 closeEvent 函数
	QWidget::closeEvent(event);
}

void Mainwindow::Mainwindow_Get_CSS()
{
	// 读取css样式
	QFile file(":/Mainwindow/Resource/CSS/Mainwindow.css");
	if (true == file.open(QFile::ReadOnly))
	{
		MainwindowParameter.qss = file.readAll();
		file.close();	// 关闭文件
#ifdef QT_Mainwindow_DEBUG
		//qDebug() << MainwindowParameter.qss << Qt::endl;
#endif
	}
	else
	{
#ifdef QT_Mainwindow_DEBUG
		qDebug() << "open file error";
#endif
	}
	this->setStyleSheet(MainwindowParameter.qss);	// 设置窗口样式
}

void Mainwindow::Mainwindow_Config()
{
	/*窗口基本设置*/
	int w = QApplication::primaryScreen()->geometry().width();  // 获取屏幕宽度
	int h = QApplication::primaryScreen()->geometry().height(); // 获取屏幕高度

	this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口透明
	this->setFixedSize(MainWindow_W, MainWindow_H);    // 固定窗口大小为屏幕大小
	this->setObjectName(QStringLiteral("Main"));	// 给窗口设置对象名
	this->move((w - this->width()) / 2, (h - this->height()) / 2);	// 将窗口移动到屏幕中央
	this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);  // 去掉窗口边框
	//this->setWindowOpacity(0.99);	// 设置全局透明度
	this->setMouseTracking(true);	// 打开鼠标追踪
	//SetWindowPos(reinterpret_cast<HWND>(winId()), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);	// 将当前窗口置顶，并保持窗口的位置和大小不变（只能在window使用）

	/*设置exe*/ 
	this->setWindowTitle("AOCHAUN_V24.2.3");
	this->setWindowIcon(QIcon(":/Mainwindow/Resource/AC_logo1.ico"));
	// 托盘菜单
	 QMenu*  m_trayMenu = new QMenu(this);
	//m_trayMenu->addSeparator();	// 分割线
	m_trayMenu->addAction("退出", [] {qApp->quit(); });
	/*设置托盘*/
	// 创建托盘(一定要设置图标否则托盘不可见 )
	m_trayIcon = new QSystemTrayIcon(QIcon(":/Mainwindow/Resource/AC_logo1.ico"), this);
	// 给托盘设置菜单
	m_trayIcon->setContextMenu(m_trayMenu);
	m_trayIcon->setToolTip("AOCHAUN_V24.2.3");	// 这行是设置鼠标放在图标上显示的文字
	// 显示托盘
	m_trayIcon->show();


		/*水平分割线*/
	line = new QFrame(this);
	line->setFrameShape(QFrame::HLine);        // 水平分割线
	line->setFrameShadow(QFrame::Plain);      // 设置线的阴影效果为 Plain（无阴影）
	line->setLineWidth(1);                    // 设置线宽度
	line->setMidLineWidth(1);                 // 设置中线宽度
	line->setStyleSheet("border: 1px dashed;");// 设置为虚线样式
	line->move(MainwindowParameter.position[0]);
	line->resize(width(), 1);                 // 设置大小

	/*自定义字体添加与设置*/
	// 添加应用程序字体，返回字体的唯一标识符（fontId）
	int fontId = QFontDatabase::addApplicationFont(":/Mainwindow/Resource/YaHeiConsolas.ttf");	// 
	// 获取应用程序字体的家族名称列表
	QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
	// 如果至少有一个字体家族
	if (fontFamilies.size() > 0)
	{
		// 创建一个 QFont 对象
		QFont font;
		// 设置字体的家族名称为第一个字体家族
		font.setFamily(fontFamilies[0]);
		// 将应用程序的字体设置为自定义字体
		qApp->setFont(font);
	}
#ifdef QT_Mainwindow_DEBUG
	qDebug() << "控件字体id:" << qApp->font();
#endif
	MainwindowParameter.System_Font_Id = fontFamilies[0];	// 获取自定义字体
}

void Mainwindow::Mainwindow_Thread_Init()
{
	threadOfSerial = new QThread(nullptr);	// 初始化线程
	serialThread = new SerialThread(nullptr);

	connect(threadOfSerial, &QThread::finished, this, &QObject::deleteLater);
	connect(threadOfSerial, &QThread::started, this, &Mainwindow::Mainwindow_Thread_Connect_Handler);
	serialThread->moveToThread(threadOfSerial);

	threadOfSerial->start();	// 开始线程
}

void Mainwindow::showEvent(QShowEvent* e)
{
	this->update();
	this->setAttribute(Qt::WA_Mapped);	// 告诉系统界面已经显示出来了
	QWidget::showEvent(e);
}

void Mainwindow::Mainwindow_Bg_Draw(QPainter* ev)
{
	QLinearGradient g(0, 0, 1200, 750); // 创建线性渐变，起点坐标，终点坐标
	// 颜色设置需位于 QBrush bs(g)之前
	Mainwindow_Set_Bg_Style(Mainwindow::MainStyle_Rich_Metal, &g);	// 设置背景样式
	QBrush bs(g);
	ev->setBrush(bs);
	ev->setPen(Qt::NoPen); // 设置无边框
	QPainterPath painterPath;
	painterPath.addRoundedRect(rect(), MainWindow_Radius, MainWindow_Radius);	// 设置窗口圆角
	ev->drawPath(painterPath);
}

void Mainwindow::UI_Test_Init()
{
	ui->Page3_Update_progressBar->setValue(55);
}

#if 0
void Mainwindow::onTrayMenuActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Unknown:
	{
		qDebug() << "Unknown";
		break;
	}
	case QSystemTrayIcon::Context:			//右键
	{
		qDebug() << "Context";
		break;
	}
	case QSystemTrayIcon::DoubleClick:		//双击
	{
		qDebug() << "DoubleClick";
		break;
	}
	case QSystemTrayIcon::Trigger:			//左键点击
	{
			if (this->isMinimized())
			{
				showNormal();
				raise();
			}
			else
			{
				showMinimized();
			}
		qDebug() << "Trigger";
		break;
	}
	case QSystemTrayIcon::MiddleClick:		//中击
	{
		qDebug() << "MiddleClick";
		break;
	}
	default: break;
	}
}
#endif


/*================================= 串口多线程相关 =============================================*/

void Mainwindow::Mainwindow_Thread_Connect_Handler()
{
	/*TopBottom的提示信息*/
	connect(serialThread, &SerialThread::SerialThread_Signals_PromptMsg, this, [&](MessageType type, QString content)
		{
			Main_Msg->Push(type, content);
		});
	connect(mainpage5, &MainPage5::MainPage5_Signals_Serial_Init, serialThread, &SerialThread::Serial_Init);	// 进行打开串口
	connect(serialThread, &SerialThread::SerialThread_Signals_OpenPort, this, &Mainwindow::SerialThread_OnOffPort_UiControl);	// 串口打开---UI更新
	connect(mainpage5, &MainPage5::MainPage5_Signals_Serial_Close, serialThread, &SerialThread::Serial_Close);	// 关闭串口
	connect(serialThread, &SerialThread::SerialThread_Signals_PortClose, this, &Mainwindow::SerialThread_OnOffPort_UiControl);	// 关闭串口---UI更新
	connect(serialThread, &SerialThread::SerialThread_Signals_SendPortList, this, &Mainwindow::SerialThread_PortCheckStatus_UiContorl);	// 定时端口检测 --- UI更新
	connect(serialThread, &SerialThread::MainPage5_Signals_OldProtocol1_Serial_DataToUi, this, &Mainwindow::SerialThread_SerialDataDisplay_UiControl);	// 接收到数据 ->串口接收区 --- 文本框UI更新
	connect(mainpage5, &MainPage5::MainPage5_Signals_SendArea_Send, serialThread, &SerialThread::Serial_Thread_SendData);	// 发送区发送数据
	connect(serialThread, &SerialThread::SerialThread_Signals_SerialTxDataToUi, this, &Mainwindow::SerialThread_SerialDataDisplayTx_UiControl);  // f发送数据成功->串口接收区-- - 文本框UI更新
	connect(mainpage5, &MainPage5::MainPage5_Signals_StartStopTimer, serialThread, &SerialThread::Serial_Thread_TimingSend_Control);	// 定时器启动或者关闭
	connect(serialThread, &SerialThread::SerialThread_Signals_StartSendData, mainpage5, &MainPage5::Slots_Page5_DataSend_Btn_Clicked);	// 开始发送数据信号
	connect(serialThread, &SerialThread::SerialThread_Signals_TxDataCntToUi, mainpage5, &MainPage5::Slots_Page5_TxDataCnt_UiControl);	// 发送计数ui更新
	connect(serialThread, &SerialThread::SerialThread_Signals_PackCountToUi, mainpage1, &MainPage1::Slots_Page1_RecPackParsePack_UiControl);	// 收包/解包计数 ui更新
	connect(this, &Mainwindow::Main_Signals_SendPack, serialThread, &SerialThread::Serial_Thread_OldProtool1_SendPack);	// 控件操作发送命令包
	/*顶部*/
	connect(serialThread, &SerialThread::Pro1_Signals_VersionQuery, this, &Mainwindow::Pro1_ShowVersion);
	/*----------------------------------------------------Page1-------------------------------------------------------------*/
	connect(serialThread, &SerialThread::Pro1_Signals_PostureQuery, this, &Mainwindow::Pro1_Page1_ShowPostureQueryMsg);
	/*云台校准*/
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_Sound_Btn_Clicked, this, &Mainwindow::Page1_Pane6_Sound_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_MotorCalibration_Btn_Clicked, this, &Mainwindow::Page1_Pane6_MotorCalibration_Btn_Handler);
	connect(this, &Mainwindow::Main_Signals_SendReboot, this, &Mainwindow::Page1_Page1_Pane12_Restart_Btn_Handler);	// 重启
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_AttitudeCalibration_Btn_Clicked, this, &Mainwindow::Page1_Pane6_AttitudeCalibration_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_GyroCalibration_Btn_Clicked, this, &Mainwindow::Page1_Pane6_GyroCalibration_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6__SixNextStep_Btn_Clicked, this, &Mainwindow::Page1_Pane6_SixNextStep_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_SixCalibration_Btn_Clicked, this, &Mainwindow::Page1_Pane6_SixCalibration_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_IdentifySamples_Btn_Clicked, this, &Mainwindow::Page1_Pane6_IdentifySamples_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_ReadRecognition_Btn_Clicked, this, &Mainwindow::Page1_Pane6_ReadRecognition_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_Inception_Btn_Clicked, this, &Mainwindow::Page1_Pane6_Inception_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_TrackStart_Btn_Clicked, this, &Mainwindow::Page1_Pane6_TrackStart_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_TrackExecute_Btn_Clicked, this, &Mainwindow::Page1_Pane6_TrackExecute_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_TrackExit_Btn_Clicked, this, &Mainwindow::Page1_Pane6_TrackExit_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_DM1Start_Btn_Clicked, this, &Mainwindow::Page1_Pane6_DM1Start_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_DM1Execute_Btn_Clicked, this, &Mainwindow::Page1_Pane6_DM1Execute_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_DM1Exit_Btn_Clicked, this, &Mainwindow::Page1_Pane6_DM1Exit_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_ReadUD_Btn_Clicked, this, &Mainwindow::Page1_Pane6_ReadUD_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane6_WriteUD_Btn_Clicked, this, &Mainwindow::Page1_Pane6_WriteUD_Btn_Handler);
	/*测试命令*/
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_Restart_Btn_Clicked, this, &Mainwindow::Page1_Page1_Pane12_Restart_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_ShutDown_Btn_Clicked, this, &Mainwindow::Page1_Pane12_ShutDown_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_Selfie_Btn_Clicked, this, &Mainwindow::Page1_Pane12_Selfie_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_ReturnCenter_Btn_Clicked, this, &Mainwindow::Page1_Pane12_ReturnCenter_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_HVSwitch_Btn_Clicked, this, &Mainwindow::Page1_Pane12_HVSwitch_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_LeftControl_Btn_Clicked, this, &Mainwindow::Page1_Pane12_LeftControl_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_NotControl_Btn_Clicked, this, &Mainwindow::Page1_Pane12_NotControl_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_RightControl_Btn_Clicked, this, &Mainwindow::Page1_Pane12_RightControl_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_QuickFollow_Btn_Clicked, this, &Mainwindow::Page1_Pane12_QuickFollow_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_QuickFollowExit_Btn_Clicked, this, &Mainwindow::Page1_Pane12_QuickFollowExit_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_RollLedOn_Btn_Clicked, this, &Mainwindow::Page1_Pane12_RollLedOn_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_RollLedOff_Btn_Clicked, this, &Mainwindow::Page1_Pane12_RollLedOff_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_CalibrationClear_Btn_Clicked, this, &Mainwindow::Page1_Pane12_CalibrationClear_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_ReadHall_Btn_Clicked, this, &Mainwindow::Page1_Pane12_ReadHall_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_ReadHandlePlate_Btn_Clicked, this, &Mainwindow::Page1_Pane12_ReadHandlePlate_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_StartPanorama_Btn_Clicked, this, &Mainwindow::Page1_Pane12_StartPanorama_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_ExecutePanorama_Btn_Clicked, this, &Mainwindow::Page1_Pane12_ExecutePanorama_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane12_ExitPanorama_Btn_Clicked, this, &Mainwindow::Page1_Pane12_ExitPanorama_Btn_Handler);
	/*电机测试-力矩*/
	connect(mainpage1, &MainPage1::Signals_Page1_Pane7_SetValue_Btn_Clicked, this, &Mainwindow::Page1_Pane7_SetValue_Btn_Handler);
	/*电机测试-姿态*/
	connect(mainpage1, &MainPage1::Signals_Page1_Pane8_SetValue_Btn_Clicked, this, &Mainwindow::Page1_Pane8_SetValue_Btn_Handler);
	/*姿态微调-获取/设置*/
	connect(mainpage1, &MainPage1::Signals_Page1_Pane11_GetValue_Btn_Clicked, this, &Mainwindow::Page1_Pane11_GetValue_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane11_SetValue_Btn_Clicked, this, &Mainwindow::Page1_Pane11_SetValue_Btn_Handler);
	/*匀速运动速度 获取/设置*/
	connect(mainpage1, &MainPage1::Signals_Page1_Pane9_GetValue_Btn_Clicked, this, &Mainwindow::Page1_Pane9_GetValue_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane9_SetValue_Btn_Clicked, this, &Mainwindow::Page1_Pane9_SetValue_Btn_Handler);
	/*电机零位置微调*/
	connect(mainpage1, &MainPage1::Signals_Page1_Pane10_GetValue_Btn_Clicked, this, &Mainwindow::Page1_Pane10_GetValue_Btn_Handler);
	connect(mainpage1, &MainPage1::Signals_Page1_Pane10_SetValue_Btn_Clicked, this, &Mainwindow::Page1_Pane10_SetValue_Btn_Handler);

	/*----------------------------------------------------Page2-------------------------------------------------------------*/
	/*控制PID*/
	connect(mainpage2, &MainPage2::Signals_Page2_Pane2_GetValue_Btn_Clicked, this, &Mainwindow::Page2_Pane2_GetValue_Btn_Handler);
	connect(mainpage2, &MainPage2::Signals_Page2_Pane2_SetValue_Btn_Clicked, this, &Mainwindow::Page2_Pane2_SetValue_Btn_Handler);
	/*控制参数*/
	connect(mainpage2, &MainPage2::Signals_Page2_Pane3_DefaultValue_Btn_Clicked, this, &Mainwindow::Page2_Pane3_DefaultValue_Btn_Handler);
	connect(mainpage2, &MainPage2::Signals_Page2_Pane3_SetValue_Btn_Clicked, this, &Mainwindow::Page2_Pane3_SetValue_Btn_Handler);
	connect(mainpage2, &MainPage2::Signals_Page2_Pane3_GetValue_Btn_Clicked, this, &Mainwindow::Page2_Pane3_GetValue_Btn_Handler);
	/*跟随参数*/
	connect(mainpage2, &MainPage2::Signals_Page2_Pane4_DefaultValue_Btn_Clicked, this, &Mainwindow::Page2_Pane4_DefaultValue_Btn_Handler);
	connect(mainpage2, &MainPage2::Signals_Page2_Pane4_SetValue_Btn_Clicked, this, &Mainwindow::Page2_Pane4_SetValue_Btn_Handler);
	connect(mainpage2, &MainPage2::Signals_Page2_Pane4_GetValue_Btn_Clicked, this, &Mainwindow::Page2_Pane4_GetValue_Btn_Handler);

	/*----------------------------------------------------Page4-------------------------------------------------------------*/
	connect(mainpage4, &MainPage4::Signals_Page4_Pane1_IMU_NoiseTest_Btn_Clicked, this, &Mainwindow::Page2_Page4_Pane1_IMU_NoiseTest_Btn_Handler);
	connect(mainpage4, &MainPage4::Signals_Page4_Pane2_IMUZeroOffset_Btn_Clicked, this, &Mainwindow::Page2_Page4_Pane2_IMUZeroOffset_Btn_Handler);
	connect(mainpage4, &MainPage4::Signals_Page4_Experience_Btn_Clicked, this, &Mainwindow::Page2_Page4_Experience_Btn_Handler);
	connect(mainpage4, &MainPage4::Signals_Page4_Pane3_YawDriftSpeedTest_Btn_Clicked, this, &Mainwindow::Page4_Pane3_YawDriftSpeedTest_Btn_Handler);




	/*其他*/
	connect(serialThread, &SerialThread::Pro1_Signals_SystemStatusQuery, this, &Mainwindow::Pro1_ShowSystemStatusQuery);
	connect(serialThread, &SerialThread::Pro1_Signals_Verify, this, &Mainwindow::Pro1_VerifyHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_Deny, this, &Mainwindow::Pro1_DenyHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_DebugCmd, this, &Mainwindow::Pro1_DebugCmdHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_ReadHall, this, &Mainwindow::Pro1_ReadHallHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_AttitudeFineTuningGet, this, &Mainwindow::Pro1_AttitudeFineTuningGetHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_UniformMotionQuery, this, &Mainwindow::Pro1_UniformMotionQueryHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_MotorZeroPositionQuery, this, &Mainwindow::Pro1_MotorZeroPositionQueryHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_AttitudeCalibration, this, &Mainwindow::Pro1_AttitudeCalibrationHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_SixCalibrationNextStep, this, &Mainwindow::Pro1_SixCalibrationNextStepHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_SixCalibration, this, &Mainwindow::Pro1_SixCalibrationHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_RunControl, this, &Mainwindow::Pro1_RunControlHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_UserDataRead, this, &Mainwindow::Pro1_UserDataReadHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_ControlPIDQuery, this, &Mainwindow::Pro1_ControlPIDQueryHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_ControlParameterGet, this, &Mainwindow::Pro1_ControlParameterGetHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_FollowParameterGet, this, &Mainwindow::Pro1_FollowParameterGetHandler);
	connect(serialThread, &SerialThread::Pro1_Signals_PTZTestNoise, this, &Mainwindow::Pro1_PTZTestNoiseHandler);


}

void Mainwindow::SerialThread_OnOffPort_UiControl(AppSettings::RunStatus_et status)
{
	if (AppSettings::Status_PASS == status)	// 失能其他UI
	{
		ui->Top_SerialPort_comboBox->setEnabled(false);
		ui->Top_SerialBaund_comboBox->setEnabled(false);
		ui->Page5_SerialDataBit_comboBox->setEnabled(false);
		ui->Page5_SerialStopBit_comboBox->setEnabled(false);
		ui->Page5_SerialCheckBit_comboBox->setEnabled(false);

		ui->Page2_Pane1_Model_comboBox->setEnabled(false);
		ui->Page2_Pane1_PCAddr_comboBox->setEnabled(false);
		ui->Page2_Pane1_DefaultValue_Btn->setEnabled(false);
		ui->Page2_Pane1_Apply_Btn->setEnabled(false);
		ui->Page2_Pane1_NotWaitIdleFrames_checkBox->setEnabled(false);

		ui->Serial_Switch_Btn->setButtonOnOff(true);	// 更新按钮UI
	}
	else if (AppSettings::Status_FAIL == status)	// 使能其他UI
	{
		ui->Top_SerialPort_comboBox->setEnabled(true);
		ui->Top_SerialBaund_comboBox->setEnabled(true);
		ui->Page5_SerialDataBit_comboBox->setEnabled(true);
		ui->Page5_SerialStopBit_comboBox->setEnabled(true);
		ui->Page5_SerialCheckBit_comboBox->setEnabled(true);

		ui->Page2_Pane1_Model_comboBox->setEnabled(true);
		ui->Page2_Pane1_PCAddr_comboBox->setEnabled(true);
		ui->Page2_Pane1_DefaultValue_Btn->setEnabled(true);
		ui->Page2_Pane1_Apply_Btn->setEnabled(true);
		ui->Page2_Pane1_NotWaitIdleFrames_checkBox->setEnabled(true);

		ui->Serial_Switch_Btn->setButtonOnOff(false);	// 更新按钮UI

		/*清空版本数据*/
		ui->Top_ICVersion_lineEdit->setText("");
		ui->Top_ICID_lineEdit->setText("");
		ui->Bottom__RackNumber_lineEdit->setText("");
		ui->Bottom__CompileTime_lineEdit->setText("");
		ui->Bottom__ConfigVersion1_lineEdit->setText("");
	}
}

void Mainwindow::SerialThread_PortCheckStatus_UiContorl()
{
	ui->Top_SerialPort_comboBox->clear();	// 清除下拉框
	for (const auto& info : serialThread->get_SerialPortList())
	{
		ui->Top_SerialPort_comboBox->addItem(info.portName + ": " + info.description, info.portName);	// 添加数据到下拉框
	}
}

void Mainwindow::SerialThread_SerialDataDisplay_UiControl(QByteArray disBuff)
{
	if (true == AppSettings::Instance()->get_pSerialCommunicationParameter()->RecStopStart_Flag)	// 继续显示
	{
		auto textData = QString::fromLocal8Bit(disBuff);		// 转为本地编码
		QString Msg = "⚡Recv⚡";
		ui->Page5_SerialDebug_textEdit->moveCursor(QTextCursor::End);  // 将光标移动到文本末尾
		ui->Page5_SerialDebug_textEdit->insertHtml("<span style=\"color:red\">" + Msg + "</span>");	// 插入带有html的
		ui->Page5_SerialDebug_textEdit->setCurrentCharFormat(QTextCharFormat());	// 显示前清除格式否则上面颜色会影响导致全部变成红色
		// 十六进制显示
		if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->HexDisplay_Status)
		{
			QString hexData = disBuff.toHex().toUpper();
			QString formattedString;

			for (int i = 0; i < hexData.length(); i += 2)
			{
				QString hexValue = hexData.mid(i, 2); // 获取两个字符，即一个十六进制数
				formattedString += hexValue;
				formattedString += " "; // 十六进制数之间用一个空格分隔
			}
			// 显示自动换行
			if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->RecAutoNewLine_Status)
			{
				ui->Page5_SerialDebug_textEdit->append(formattedString + "\r\n");	// 插入带有html的
			}
			else
			{
				ui->Page5_SerialDebug_textEdit->append(formattedString);
			}
			ui->Page5_SerialDebug_textEdit->append("");	// 占位的换行
		}
		else	// ASCII显示
		{
			// 显示自动换行
			if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->RecAutoNewLine_Status)
			{
				ui->Page5_SerialDebug_textEdit->append(textData + "\r\n");
			}
			else
			{
				ui->Page5_SerialDebug_textEdit->append(textData);
			}
			ui->Page5_SerialDebug_textEdit->append("");	// 占位的换行
		}
		ui->Page5_SerialDebugTextEdit_scrollBar->setValue(ui->Page5_SerialDebugTextEdit_scrollBar->maximum());	// 滚动条保持到最后一行
	}
	/*接收计数更新*/
	auto rxDataLen = disBuff.size();	// 数据长度
	AppSettings::Instance()->get_pSerialCommunicationParameter()->RxDataCount += rxDataLen;
	ui->Page5_RxCount_lineEdit->setText(QString::number(AppSettings::Instance()->get_pSerialCommunicationParameter()->RxDataCount));	// 接收
}

void Mainwindow::SerialThread_SerialDataDisplayTx_UiControl(QByteArray disBuff)
{
#if 1
	auto textData = QString::fromLocal8Bit(disBuff);		// 转为本地编码
	QString Msg = "⚡Send⚡";
	ui->Page5_SerialDebug_textEdit->moveCursor(QTextCursor::End);  // 将光标移动到文本末尾
	ui->Page5_SerialDebug_textEdit->insertHtml("<span style=\"color:#9966ff\">" + Msg + "</span>");	// 插入带有html的
	ui->Page5_SerialDebug_textEdit->setCurrentCharFormat(QTextCharFormat());	// 显示前清除格式否则上面颜色会影响导致全部变成红色
	// 十六进制显示
	if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->HexDisplay_Status)
	{
		QString hexData = disBuff.toHex().toUpper();
		QString formattedString;

		for (int i = 0; i < hexData.length(); i += 2)
		{
			QString hexValue = hexData.mid(i, 2); // 获取两个字符，即一个十六进制数
			formattedString += hexValue;
			formattedString += " "; // 十六进制数之间用一个空格分隔
		}

		// 显示自动换行
		if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->RecAutoNewLine_Status)
		{
			ui->Page5_SerialDebug_textEdit->append(formattedString + "\r\n");
		}
		else
		{
			ui->Page5_SerialDebug_textEdit->append(formattedString);
		}
		ui->Page5_SerialDebug_textEdit->append("");	// 占位的换行
	}
	else	// ASCII显示
	{
		// 显示自动换行
		if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->RecAutoNewLine_Status)
		{
			ui->Page5_SerialDebug_textEdit->append(textData + "\r\n");
		}
		else
		{
			ui->Page5_SerialDebug_textEdit->append(textData);
		}
		ui->Page5_SerialDebug_textEdit->append("");	// 占位的换行
	}
	ui->Page5_SerialDebugTextEdit_scrollBar->setValue(ui->Page5_SerialDebugTextEdit_scrollBar->maximum());	// 滚动条保持到最后一行
#endif
	/*发送计数更新*/
	auto txDataLen = disBuff.size();	// 数据长度
	AppSettings::Instance()->get_pSerialCommunicationParameter()->TxDataCount += txDataLen;
	ui->Page5_TxCount_lineEdit->setText(QString::number(AppSettings::Instance()->get_pSerialCommunicationParameter()->TxDataCount));	// 发送
}




/*===============顶部/底部处理===================*/
void Mainwindow::Pro1_ShowVersion(QByteArray src, const QByteArray& array, int data_len)
{
	/*判断数据长度*/
	if (data_len != 70)
	{
		qDebug() << "Invalid data length70";
		return;
	}

	/* 数据解析 */
	// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	Protocol1_Addr_et addr = static_cast<Protocol1_Addr_et>(src.toHex().toUpper().toInt());	// QByteArray转换为枚举类型

	quint16 mainVersion;
	quint16 rackVersion;
	quint16 configVersion;
	QByteArray rackDescriptionBytes(32, '\0');	// 创建指定大小和初始值的字节数组对象(具体看协议规定的字节大小)
	QByteArray compileDateBytes(16, '\0');
	QByteArray id(12, '\0');

	// 从数据流中读取数据，并存入上述定义的变量中
	stream >> mainVersion; // 读取固件版本
	stream >> rackVersion; // 读取机架编号
	stream >> configVersion; // 读取配置版本1
	stream.readRawData(rackDescriptionBytes.data(), 32); // 读取机架描述（参数1是rackDescriptionBytes字节数组指针，参数2是长度）
	stream.readRawData(compileDateBytes.data(), 16); // 读取编译时间
	stream.readRawData(id.data(), 12); // 读取ID

	QString rackDescription = QString::fromUtf8(rackDescriptionBytes.constData()).trimmed();	// 需要转UTF-8   constData 字节数组的常量指针 trimmed用于移除字符串两端的空白字符
	QString compileDate = QString::fromUtf8(compileDateBytes.constData()).trimmed();
	QString idHex = QString(id.toHex()).toUpper();

	if (addr == PRO1_Roll)	// 云台版本
	{
		/* UI更新 */
		if (AppSettings::Instance()->getSerial_isOpen())
		{
			ui->Top_ICVersion_lineEdit->setText(QString::number(mainVersion));
			ui->Top_ICID_lineEdit->setText(idHex);
			ui->Bottom__RackNumber_lineEdit->setText(QString("%1: %2").arg(QString::number(rackVersion)).arg(rackDescription));
			ui->Bottom__CompileTime_lineEdit->setText(compileDate);
			ui->Bottom__ConfigVersion1_lineEdit->setText(QString::number(configVersion));
		}
	}
	else if (addr == PRO1_Handle)	// 手柄版本
	{
		SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("手柄版本: %1  硬件版本: %2  编译时间: %3").arg(mainVersion).arg(rackVersion).arg(compileDateBytes));
	}


}

void Mainwindow::Pro1_Status_To_Ui_Update()
{
	static bool reboot_flag = false;	// 重启标志位

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.pitch_following)	// 跟随P
	{
		ui->step_Fllow_P->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else
	{
		ui->step_Fllow_P->setStatusMode(StepProgress::ColorMode_Normal);
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.roll_following)	// 跟随R
	{
		ui->step_Fllow_R->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else
	{
		ui->step_Fllow_R->setStatusMode(StepProgress::ColorMode_Normal);
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.yaw_following)	// 跟随Y
	{
		ui->step_Fllow_Y->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else
	{
		ui->step_Fllow_Y->setStatusMode(StepProgress::ColorMode_Normal);
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.vertical_shoot_mode)	// 竖拍模式(正常颜色是横拍)
	{
		ui->step_HorizontalShootingMode->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else
	{
		ui->step_HorizontalShootingMode->setStatusMode(StepProgress::ColorMode_Normal);
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.work_mode)	// FG(疯狗模式)
	{
		ui->step_CommonMode->setText("FG模式");
	}
	else if (0 == serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.work_mode)	// 普通模式
	{
		ui->step_CommonMode->setText("普通模式");
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.roll_axis_comm_exception)	// 横滚通信异常
	{
		ui->step_RollCommunication->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else // 正常
	{
		ui->step_RollCommunication->setStatusMode(StepProgress::ColorMode_Normal);
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.yaw_axis_comm_exception)	// 航向通信异常
	{
		ui->step_YawCommunication->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else // 正常
	{
		ui->step_YawCommunication->setStatusMode(StepProgress::ColorMode_Normal);
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.gyro_exception)	// 陀螺仪异常
	{
		ui->step_IMU->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else // 正常
	{
		ui->step_IMU->setStatusMode(StepProgress::ColorMode_Normal);
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.motor_not_calibrated)	// 电机未校准
	{
		ui->step_MotorCalibration->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else // 正常
	{
		ui->step_MotorCalibration->setStatusMode(StepProgress::ColorMode_Normal);
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.motor_zero_angle_not_calibrated)	// 电机零角未校准
	{
		ui->step_ZeroAngleCalibration->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else // 正常
	{
		ui->step_ZeroAngleCalibration->setStatusMode(StepProgress::ColorMode_Normal);
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.accelerometer_not_calibrated)	// 加速度计未校准
	{
		ui->step_AccelerateCalibration->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else // 正常
	{
		ui->step_AccelerateCalibration->setStatusMode(StepProgress::ColorMode_Normal);
	}

	if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.gyro_not_calibrated)	// 陀螺仪未校准
	{
		ui->step_GyroCalibration->setStatusMode(StepProgress::ColorMode_Finish);
	}
	else // 正常
	{
		ui->step_GyroCalibration->setStatusMode(StepProgress::ColorMode_Normal);
	}

	/*进度框*/
	if (4 == serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.app_mode)	// 应用模式 - 盗梦空间1
	{
		ui->Bottom_label5->setText("🔥盗梦空间1");
	}
	else if (0 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_step)	// 校准状态 - 无
	{
		ui->Bottom_label5->setText("无");
		ui->Bottom_label6->setText("");

		switch (serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_status)
		{
		case 10:reboot_flag = true; break;	// 校准完成则重启
		default:break;
		}

		if (true == reboot_flag)
		{
			reboot_flag = false;
			// 重启
			emit Main_Signals_SendReboot();
		}
	}
	else if (1 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_step)	// 校准状态 - 电机校准
	{
		ui->Bottom_label5->setText("🔥电机校准");

		switch (serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_status)
		{
		case 0:ui->Bottom_label6->setText("校准开始"); break;
		case 1:ui->Bottom_label6->setText("校准航向"); break;
		case 2:ui->Bottom_label6->setText("校准横滚"); break;
		case 3:ui->Bottom_label6->setText("校准俯仰"); reboot_flag = true; break;
		case 10:ui->Bottom_label6->setText("校准完成"); break;
		case 11:ui->Bottom_label6->setText("校准超时"); break;
		default:ui->Bottom_label6->setText("校准错误"); break;
		}

	}
	else if (2 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_step)	//  校准状态 - 姿态校准
	{
		ui->Bottom_label5->setText("🔥姿态校准");

		switch (serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_status)
		{
		case 0:ui->Bottom_label6->setText("校准开始"); break;
		case 1:ui->Bottom_label6->setText("校准航向"); break;
		case 2:ui->Bottom_label6->setText("校准横滚"); break;
		case 3:ui->Bottom_label6->setText("校准俯仰"); break;
		case 10:ui->Bottom_label6->setText("校准完成"); break;
		case 11:ui->Bottom_label6->setText("校准超时"); break;
		default:ui->Bottom_label6->setText("校准错误"); break;
		}
	}
	else if (3 == serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_step)	// 校准状态 - 六面校准
	{
		ui->Bottom_label5->setText("🔥六面校准");

		switch (serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_status)
		{
		case 0:ui->Bottom_label6->setText("第一面"); break;
		case 1:ui->Bottom_label6->setText("第二面"); break;
		case 2:ui->Bottom_label6->setText("第三面"); break;
		case 3:ui->Bottom_label6->setText("第四面"); break;
		case 4:ui->Bottom_label6->setText("第五面"); break;
		case 5:ui->Bottom_label6->setText("第六面"); break;
		case 10:ui->Bottom_label6->setText("校准完成"); break;
		case 11:ui->Bottom_label6->setText("校准超时"); break;
		default:ui->Bottom_label6->setText("校准错误"); break;
		}
	}

	// 判断电机静止标志，全部为0则开始发送查询结果命令
	if ((0 == serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.motor_still_flag_x) && (0 == serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.motor_still_flag_y) && (0 == serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.motor_still_flag_z))
	{
		if (true == mainpage4->PTZ_Parameter->IMU_NoiseTest_Flag)
		{
			mainpage4->PTZ_Parameter->IMU_NoiseTest_Flag = false;
			// 发送获取结果命令
			QByteArray send_data;
			send_data.append(static_cast<char>(0x00));
			// 发送命令包
			emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_PTZTestNoise, 0x01, 0x01, send_data);
		}
	}

	//qserialThread->OldProtocol1_Parameter->Pro1_InsideStatus.motor_still_flag_zDebug() << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_status << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_step;
//qDebug() << "应用模式:" << serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.app_mode;
//qDebug() << "轨迹模式:" << serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.path_mode;
}

/*======================================= Page1 =======================================*/
void Mainwindow::Page1_Pane6_AttitudeCalibration_Btn_Handler()
{
	// 姿态校准 - 所有
	QByteArray send_data;
	send_data.append(static_cast<char>(0x00));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_AttitudeCalibration, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane6_GyroCalibration_Btn_Handler()
{
	// 姿态校准 - 陀螺仪
	QByteArray send_data;
	send_data.append(static_cast<char>(0x02));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_AttitudeCalibration, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane6_SixNextStep_Btn_Handler()
{
	// 六面校准下一步
	QByteArray send_data;
	send_data.append(static_cast<char>(0x01));
	send_data.append(static_cast<char>(0x00));
	send_data.append(static_cast<char>(0x00));
	send_data.append(static_cast<char>(0x00));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_SixCalibrationNextStep, 0x04, 0x04, send_data);
}

void Mainwindow::Page1_Pane6_SixCalibration_Btn_Handler()
{
	// 六面校准
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_SixCalibration, 0x00, 0x00, nullptr);
}

void Mainwindow::Page1_Pane6_IdentifySamples_Btn_Handler()
{
	// 辨识采样
	QByteArray send_data;
	send_data.append(static_cast<char>(0x00));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_Interim_Order, 0x01, 0x01, nullptr);
}

void Mainwindow::Page1_Pane6_ReadRecognition_Btn_Handler()
{
	// 读取识别 无
	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_WARNING, QString("此功能待开发"));
}

void Mainwindow::Page1_Pane6_Inception_Btn_Handler()
{
	// 盗梦空间
	QByteArray send_data;
	send_data.append(static_cast<char>(0x00));
	send_data.append(static_cast<char>(0x64));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RunControl, 0x02, 0x02, send_data);
}

void Mainwindow::Page1_Pane6_TrackStart_Btn_Handler()
{
	// 轨迹开始
	QByteArray send_data;
	send_data.append(static_cast<char>(0x01));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_TrackMode, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane6_TrackExecute_Btn_Handler()
{
	QByteArray send_data;
	quint16 send_data_len = 0;
	int text_len = 0;
	bool ok;
	quint16 sec = 0;

	// 获取轨迹点
	QString input_text = ui->Page1_Pane6_TrackPoint_lineEdit->text();

	QStringList points = input_text.trimmed().split(';', Qt::SkipEmptyParts);
	text_len = points.size();

	// 检查轨迹点数量
	if (text_len < 2 || text_len > 12)
	{
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数格式/数量错误!\n单个轨迹点n格式: x,x; (n > 2 且 n < 12)"));
		return;
	}
	sec = ui->Page1_Pane6_Sec_lineEdit->text().toInt(&ok);

	// 检查轨迹点时间
	if ((false == ok) || (sec > 65535) || (sec < 0))
	{
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("轨迹时间参数错误!\n参数范围: 0 <= sec <= 65535"));
		return;
	}

	/*数据*/
	send_data.append(static_cast<char>(0x02));	// 类型
	send_data.append(static_cast<char>(text_len));	// 轨迹点个数
	send_data.append(static_cast<char>(sec & 0xFF));	// 轨迹时间 低位
	send_data.append(static_cast<char>((sec >> 8) & 0xFF));	// 轨迹时间 高位

	// 遍历每一个轨迹点
	for (const QString& point : points)
	{
		// 使用 , 分割
		QStringList coordinates = point.split(',');

		if (coordinates.size() == 2)
		{
			// 提取坐标值并转换为整数
			int yaw_coordinnate = coordinates[0].toInt() * 100;	// 航向坐标
			int pitch_coordinnate = coordinates[1].toInt() * 100;	// 俯仰坐标

			send_data.append(static_cast<char>(yaw_coordinnate & 0xFF));	// 轨迹点  航向 低位
			send_data.append(static_cast<char>((yaw_coordinnate >> 8) & 0xFF));	// 轨迹点  航向 高位
			send_data.append(static_cast<char>(pitch_coordinnate & 0xFF));	// 轨迹点  俯仰 低位
			send_data.append(static_cast<char>((pitch_coordinnate >> 8) & 0xFF));	// 轨迹点  俯仰 高位
		}
	}
	send_data_len = send_data.size();

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_TrackMode, send_data_len, send_data_len, send_data);
	//qDebug() << send_data.toHex().toUpper();
}

void Mainwindow::Page1_Pane6_TrackExit_Btn_Handler()
{
	// 轨迹开始
	QByteArray send_data;
	send_data.append(static_cast<char>(0x00));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_TrackMode, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane6_DM1Start_Btn_Handler()
{
	// dm1启
	QByteArray send_data;
	send_data.append(static_cast<char>(0x01));
	send_data.append(static_cast<char>(0x00));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RunControl, 0x02, 0x02, send_data);
}

void Mainwindow::Page1_Pane6_DM1Execute_Btn_Handler()
{
	// dm1执行
	QByteArray send_data;
	send_data.append(static_cast<char>(0x01));
	send_data.append(static_cast<char>(0x01));
	send_data.append(static_cast<char>(0x00));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RunControl, 0x03, 0x03, send_data);
}

void Mainwindow::Page1_Pane6_DM1Exit_Btn_Handler()
{
	// dm1执行
	QByteArray send_data;
	send_data.append(static_cast<char>(0x01));
	send_data.append(static_cast<char>(0x02));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RunControl, 0x02, 0x02, send_data);
}

void Mainwindow::Page1_Pane6_ReadUD_Btn_Handler()
{
	// 用户数据UD 读
	QByteArray send_data;
	send_data.append(static_cast<char>(0x01));
	send_data.append(static_cast<char>(0x01));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_UserDataRead, 0x02, 0x02, send_data);
}

void Mainwindow::Page1_Pane6_WriteUD_Btn_Handler()
{
	bool ok;

	qint32 data = ui->Page1_Pane6_UD_lineEdit->text().toInt(&ok);

	if ((false == ok) || (data > 32768) || (data < -32768))
	{
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数错误!\n参数范围: -65535 ~ 65535"));
		return;
	}

	// 用户数据UD 写
	QByteArray send_data;
	send_data.append(static_cast<char>(0x01));
	send_data.append(static_cast<char>(0x01));
	send_data.append(static_cast<char>(data & 0xFF));
	send_data.append(static_cast<char>((data >> 8) & 0xFF));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_UserDataWrite, 0x04, 0x04, send_data);
}

void Mainwindow::Pro1_Page1_ShowPostureQueryMsg(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 24)
	{
		qDebug() << "Invalid data length24";
		return;
	}

	/*数据解析*/
	// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	qint16 roll, pitch, yaw;	// 姿态
	qint16 motorRoll, motorPitch, motorYaw;	// 电机位置
	qint16 targetRoll, targetPitch, targetYaw;	// 目标姿态
	qint16 motionSpeedRoll, motionSpeedPitch, motionSpeedYaw;	// 运动速度辐值

	// 从数据流中读取数据，并存入上述定义的变量中
	stream >> roll;	//姿态 - 横滚 俯仰 航向
	stream >> pitch;
	stream >> yaw;

	stream >> motorRoll;	//电机位置 - 横滚 俯仰 航向
	stream >> motorPitch;
	stream >> motorYaw;

	stream >> targetRoll;	//目标姿态 - 横滚 俯仰 航向
	stream >> targetPitch;
	stream >> targetYaw;

	stream >> motionSpeedRoll;	//运动速度辐值 - 横滚 俯仰 航向
	stream >> motionSpeedPitch;
	stream >> motionSpeedYaw;

	// 将读取的数据转换为浮点数值
	float rollValue = static_cast<float>(roll) / 100.0;
	float pitchValue = static_cast<float>(pitch) / 100.0;
	float yawValue = static_cast<float>(yaw) / 100.0;

	float motorRollValue = static_cast<float>(motorRoll) / 100.0;
	float motorPitchValue = static_cast<float>(motorPitch) / 100.0;
	float motorYawValue = static_cast<float>(motorYaw) / 100.0;

	float targetRollValue = static_cast<float>(targetRoll) / 100.0;
	float targetPitchValue = static_cast<float>(targetPitch) / 100.0;
	float targetYawValue = static_cast<float>(targetYaw) / 100.0;

	float motionSpeedRollValue = static_cast<float>(motionSpeedRoll) / 100.0;
	float motionSpeedPitchValue = static_cast<float>(motionSpeedPitch) / 100.0;
	float motionSpeedYawValue = static_cast<float>(motionSpeedYaw) / 100.0;

	/*Ui更新*/
	// 运动速度辐值
	ui->Page1_Pane1_Pitch_lineEdit->setText(QString::number(motionSpeedPitchValue, 'f', 2));
	ui->Page1_Pane1_Roll_lineEdit->setText(QString::number(motionSpeedRollValue, 'f', 2));
	ui->Page1_Pane1_Yaw_lineEdit->setText(QString::number(motionSpeedYawValue, 'f', 2));
	// 姿态角
	ui->Page1_Pane2_Pitch_lineEdit->setText(QString::number(pitchValue, 'f', 2));
	ui->Page1_Pane2_Roll_lineEdit->setText(QString::number(rollValue, 'f', 2));
	ui->Page1_Pane2_Yaw_lineEdit->setText(QString::number(yawValue, 'f', 2));
	// 电机位置
	ui->Page1_Pane3_Pitch_lineEdit->setText(QString::number(motorPitchValue, 'f', 2));
	ui->Page1_Pane3_Roll_lineEdit->setText(QString::number(motorRollValue, 'f', 2));
	ui->Page1_Pane3_Yaw_lineEdit->setText(QString::number(motorYawValue, 'f', 2));
	// 目标姿态
	ui->Page1_Pane4_Pitch_lineEdit->setText(QString::number(targetPitchValue, 'f', 2));
	ui->Page1_Pane4_Roll_lineEdit->setText(QString::number(targetRollValue, 'f', 2));
	ui->Page1_Pane4_Yaw_lineEdit->setText(QString::number(targetYawValue, 'f', 2));

#if 0
	qDebug() << "横滚:" << rollValue << "俯仰:" << pitchValue << "航向:" << yawValue;
	qDebug() << "电机位置-横滚:" << motorRollValue << "电机位置-俯仰:" << motorPitchValue << "电机位置-航向:" << motorYawValue;
	qDebug() << "目标姿态-横滚:" << targetRollValue << "目标姿态-俯仰:" << targetPitchValue << "目标姿态-航向:" << targetYawValue;
	qDebug() << "运动速度辐值-横滚:" << motionSpeedRollValue << "运动速度辐值-俯仰:" << motionSpeedPitchValue << "运动速度辐值-航向:" << motionSpeedYawValue;
#endif
}

void Mainwindow::Page1_Pane6_Sound_Btn_Handler()
{
	bool result = true;

	QByteArray send_data;

	QStringList dataList = ui->Page1_Pane6_SoundPoint_lineEdit->text().split(",");

	for (const QString& str : dataList)
	{
		bool ok;
		int value = str.toInt(&ok);

		if (ok)
		{
			if (value <= 0)
			{
				value = 0;
			}
			if (value > 255)
			{
				value = 255;
			}
			send_data.append(static_cast<char>(value));
		}
		else
		{
			result = false;
			break;
		}
	}

	if (send_data.size() != 3)
	{
		result = false;
	}

	if (!result)
	{
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数错误!\n参数格式:xxx,xxx,xxx"));
		return;
	}

	quint16 data_len = 0x04;	// 数据长度固定4
	send_data.prepend(0x01);	// 数据第一位插入0x01

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_Interim_Order, data_len, data_len, send_data);
}

void Mainwindow::Page1_Pane6_MotorCalibration_Btn_Handler()
{
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_MotorCalibration, 0x00, 0x00, nullptr);
}

void Mainwindow::Page1_Page1_Pane12_Restart_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0xFF));
	send_data.append(static_cast <char>(0x00));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RebootCalibrationClear, 0x02, 0x02, send_data);
}

void Mainwindow::Page1_Pane12_ShutDown_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x01));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_ShutDown, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane12_Selfie_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x02));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_SelfieReturnCenter, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane12_ReturnCenter_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x00));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_SelfieReturnCenter, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane12_HVSwitch_Btn_Handler()
{
	static quint8 mode = 0;
	QByteArray send_data;

	mode = (mode - 0 + 1) % (1 - 0 + 1) + 0;

	send_data.append(static_cast <char>(mode));	// 横竖屏切换
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_HVSwitch, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane12_LeftControl_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x06));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_LeftNoneRightControl, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane12_NotControl_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x07));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_LeftNoneRightControl, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane12_RightControl_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x08));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_LeftNoneRightControl, 0x01, 0x01, send_data);
}

void Mainwindow::Page1_Pane12_QuickFollow_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x02));
	send_data.append(static_cast <char>(0x00));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_QuickFollow, 0x02, 0x02, send_data);
}

void Mainwindow::Page1_Pane12_QuickFollowExit_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x00));
	send_data.append(static_cast <char>(0x00));
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_QuickFollow, 0x02, 0x02, send_data);
}

void Mainwindow::Page1_Pane12_RollLedOn_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x01));
	send_data.append(static_cast <char>(0x00));
	send_data.append(static_cast <char>(0x00));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RollLed, 0x03, 0x03, send_data);
}

void Mainwindow::Page1_Pane12_RollLedOff_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x00));
	send_data.append(static_cast <char>(0x00));
	send_data.append(static_cast <char>(0x00));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RollLed, 0x03, 0x03, send_data);
}

void Mainwindow::Page1_Pane12_CalibrationClear_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0xFF));
	send_data.append(static_cast <char>(0xCC));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RebootCalibrationClear, 0x02, 0x02, send_data);
}

void Mainwindow::Page1_Pane12_ReadHall_Btn_Handler()
{
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_ReadHall, 0x00, 0x00, nullptr);
}

void Mainwindow::Page1_Pane12_ReadHandlePlate_Btn_Handler()
{
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Handle, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_VersionQuery, 0x00, 0x00, nullptr);
}

void Mainwindow::Page1_Pane12_StartPanorama_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x02));
	send_data.append(static_cast <char>(0x00));
	send_data.append(static_cast <char>(0x24));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RunControl, 0x03, 0x03, send_data);
}

void Mainwindow::Page1_Pane12_ExecutePanorama_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x02));
	send_data.append(static_cast <char>(0x01));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RunControl, 0x02, 0x02, send_data);
}

void Mainwindow::Page1_Pane12_ExitPanorama_Btn_Handler()
{
	QByteArray send_data;

	send_data.append(static_cast <char>(0x02));
	send_data.append(static_cast <char>(0xFF));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_RunControl, 0x02, 0x02, send_data);
}

void Mainwindow::Page1_Pane7_SetValue_Btn_Handler(qint16 pitch, qint16 roll, qint16 yaw)
{
	QByteArray send_data;

	if (-1 == roll)
	{
		send_data.append(static_cast<char>(0xFF));	// 横滚
		send_data.append(static_cast<char>(0xFF));	// 横滚
	}
	else
	{
		send_data.append(static_cast<char>(roll & 0xFF));	// 横滚 - 低位
		send_data.append(static_cast<char>((roll >> 8) & 0xFF));	// 横滚 - 高位
	}

	if (-1 == pitch)
	{
		send_data.append(static_cast<char>(0xFF));	// 俯仰
		send_data.append(static_cast<char>(0xFF));	// 俯仰
	}
	else
	{
		send_data.append(static_cast<char>(pitch & 0xFF));	// 俯仰 - 低位
		send_data.append(static_cast<char>((pitch >> 8) & 0xFF));	// 俯仰 - 高位
	}

	if (-1 == yaw)
	{
		send_data.append(static_cast<char>(0xFF));	// 航向
		send_data.append(static_cast<char>(0xFF));	// 航向
	}
	else
	{
		send_data.append(static_cast<char>(yaw & 0xFF));	// 航向 - 低位
		send_data.append(static_cast<char>((yaw >> 8) & 0xFF));	// 航向 - 高位
	}

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_MotorTestTorqueSet, 0x06, 0x06, send_data);
}

void Mainwindow::Page1_Pane8_SetValue_Btn_Handler(float pitch, float roll, float yaw)
{
	QByteArray send_data;

	qint16 pitch_temp = pitch * 100;
	qint16 roll_temp = roll * 100;
	qint16 yaw_temp = yaw * 100;

	send_data.append(static_cast<char>(roll_temp & 0xFF));	// 横滚 - 低位
	send_data.append(static_cast<char>((roll_temp >> 8) & 0xFF));	// 横滚 - 高位

	send_data.append(static_cast<char>(pitch_temp & 0xFF));	// 俯仰 - 低位
	send_data.append(static_cast<char>((pitch_temp >> 8) & 0xFF));	// 俯仰 - 高位

	send_data.append(static_cast<char>(yaw_temp & 0xFF));	// 航向 - 低位
	send_data.append(static_cast<char>((yaw_temp >> 8) & 0xFF));	// 航向 - 高位

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_MotorTestAttitudeSet, 0x06, 0x06, send_data);
}

void Mainwindow::Page1_Pane11_GetValue_Btn_Handler()
{
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_AttitudeFineTuningGet, 0x00, 0x00, nullptr);
}

void Mainwindow::Page1_Pane11_SetValue_Btn_Handler(float pitch, float roll)
{
	QByteArray send_data;

	qint16 pitch_temp = pitch;
	qint16 roll_temp = roll;

	/*限制范围在-100 ~ 100*/

	if (pitch_temp < -100)
	{
		pitch_temp = -100;
	}
	if (pitch_temp > 100)
	{
		pitch_temp = 100;
	}

	if (roll_temp < -100)
	{
		roll_temp = -100;
	}
	if (roll_temp > 100)
	{
		roll_temp = 100;
	}

	send_data.append(static_cast<char>(roll_temp & 0xFF));	// 横滚 - 低位
	send_data.append(static_cast<char>((roll_temp >> 8) & 0xFF));	// 横滚 - 高位

	send_data.append(static_cast<char>(pitch_temp & 0xFF));	// 俯仰 - 低位
	send_data.append(static_cast<char>((pitch_temp >> 8) & 0xFF));	// 俯仰 - 高位

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_AttitudeFineTuningSet, 0x04, 0x04, send_data);
}

void Mainwindow::Page1_Pane9_GetValue_Btn_Handler()
{
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_UniformMotionQuery, 0x00, 0x00, nullptr);
}

void Mainwindow::Page1_Pane9_SetValue_Btn_Handler(qint16 pitch, qint16 yaw)
{
	QByteArray send_data;

	// 横滚不设置，为0即可
	send_data.append(static_cast<char>(0x00));	// 横滚 - 低位
	send_data.append(static_cast<char>(0x00));	// 横滚 - 高位

	send_data.append(static_cast<char>(pitch & 0xFF));	// 俯仰 - 低位
	send_data.append(static_cast<char>((pitch >> 8) & 0xFF));	// 俯仰 - 高位

	send_data.append(static_cast<char>(yaw & 0xFF));	// 航向 - 低位
	send_data.append(static_cast<char>((yaw >> 8) & 0xFF));	// 航向 - 高位

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_UniformMotionSet, 0x06, 0x06, send_data);
}

void Mainwindow::Page1_Pane10_GetValue_Btn_Handler()
{
	/*电机零位置微调*/
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_MotorZeroPositionQuery, 0x00, 0x00, nullptr);
}

void Mainwindow::Page1_Pane10_SetValue_Btn_Handler(float pitch, float yaw)
{
	QByteArray send_data;

	qint16 pitch_temp = pitch * 100;
	qint16 yaw_temp = yaw * 100;

	// 横滚不设置，为0xFF即可
	send_data.append(static_cast<char>(0xFF));	// 横滚 - 低位
	send_data.append(static_cast<char>(0xFF));	// 横滚 - 高位

	send_data.append(static_cast<char>(pitch_temp & 0xFF));	// 俯仰 - 低位
	send_data.append(static_cast<char>((pitch_temp >> 8) & 0xFF));	// 俯仰 - 高位

	send_data.append(static_cast<char>(yaw_temp & 0xFF));	// 航向 - 低位
	send_data.append(static_cast<char>((yaw_temp >> 8) & 0xFF));	// 航向 - 高位

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_MotorZeroPositionSet, 0x06, 0x06, send_data);
}

/*======================================= Page2 =======================================*/

void Mainwindow::Page2_Pane2_GetValue_Btn_Handler()
{
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_ControlPIDQuery, 0x00, 0x00, nullptr);
}

void Mainwindow::Page2_Pane2_SetValue_Btn_Handler()
{
	float roll_kp, roll_ki, roll_kd;	// 横滚
	float pitch_kp, pitch_ki, pitch_kd;	// 俯仰
	float yaw_kp, yaw_ki, yaw_kd;	// 航向
	bool ok;
	QByteArray send_data;

	roll_kp = ui->Page2_Pane2_1_KP_lineEdit->text().toFloat(&ok) * 10000;
	if (false == ok) { goto ParameterError; }
	roll_ki = ui->Page2_Pane2_1_KI_lineEdit->text().toFloat(&ok) * 10000;
	if (false == ok) { goto ParameterError; }
	roll_kd = ui->Page2_Pane2_1_KD_lineEdit->text().toFloat(&ok) * 10000;
	if (false == ok) { goto ParameterError; }
	pitch_kp = ui->Page2_Pane2_2_KP_lineEdit->text().toFloat(&ok) * 10000;
	if (false == ok) { goto ParameterError; }
	pitch_ki = ui->Page2_Pane2_2_KI_lineEdit->text().toFloat(&ok) * 10000;
	if (false == ok) { goto ParameterError; }
	pitch_kd = ui->Page2_Pane2_2_KD_lineEdit->text().toFloat(&ok) * 10000;
	if (false == ok) { goto ParameterError; }
	yaw_kp = ui->Page2_Pane2_3_KP_lineEdit->text().toFloat(&ok) * 10000;
	if (false == ok) { goto ParameterError; }
	yaw_ki = ui->Page2_Pane2_3_KI_lineEdit->text().toFloat(&ok) * 10000;
	if (false == ok) { goto ParameterError; }
	yaw_kd = ui->Page2_Pane2_3_KD_lineEdit->text().toFloat(&ok) * 10000;
	if (false == ok) { goto ParameterError; }

	send_data.append(static_cast<char>((qint16)roll_kp & 0xFF));
	send_data.append(static_cast<char>(((qint16)roll_kp >> 8) & 0xFF));

	send_data.append(static_cast<char>((qint16)roll_ki & 0xFF));
	send_data.append(static_cast<char>(((qint16)roll_ki >> 8) & 0xFF));

	send_data.append(static_cast<char>((qint16)roll_kd & 0xFF));
	send_data.append(static_cast<char>(((qint16)roll_kd >> 8) & 0xFF));

	send_data.append(static_cast<char>((qint16)pitch_kp & 0xFF));
	send_data.append(static_cast<char>(((qint16)pitch_kp >> 8) & 0xFF));

	send_data.append(static_cast<char>((qint16)pitch_ki & 0xFF));
	send_data.append(static_cast<char>(((qint16)pitch_ki >> 8) & 0xFF));

	send_data.append(static_cast<char>((qint16)pitch_kd & 0xFF));
	send_data.append(static_cast<char>(((qint16)pitch_kd >> 8) & 0xFF));

	send_data.append(static_cast<char>((qint16)yaw_kp & 0xFF));
	send_data.append(static_cast<char>(((qint16)yaw_kp >> 8) & 0xFF));

	send_data.append(static_cast<char>((qint16)yaw_ki & 0xFF));
	send_data.append(static_cast<char>(((qint16)yaw_ki >> 8) & 0xFF));

	send_data.append(static_cast<char>((qint16)yaw_kd & 0xFF));
	send_data.append(static_cast<char>(((qint16)yaw_kd >> 8) & 0xFF));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_ControlPIDSet, 0x12, 0x12, send_data);
	return;
ParameterError:
	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数设置错误!"));
}

void Mainwindow::Page2_Pane3_DefaultValue_Btn_Handler()
{
	QByteArray send_data;
	send_data.append(static_cast<char>(0x01));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_ParameterDefault, 0x01, 0x01, send_data);
}

void Mainwindow::Page2_Pane3_SetValue_Btn_Handler()
{
	QByteArray send_data;
	qint8 pitch_speed, yaw_speed;
	bool ok;

	pitch_speed = ui->Page2_Pane3_StickPitchSpeed_lineEdit->text().toInt(&ok);
	if (false == ok) { goto ParameterError; }
	yaw_speed = ui->Page2_Pane3_StickYawSpeed_lineEdit->text().toInt(&ok);
	if (false == ok) { goto ParameterError; }

	send_data.append(static_cast<char>(0x00));	// 横滚摇杆反向  默认00即可

	// 判断俯仰反向 勾选
	if (ui->Page2_Pane3_PitchStickReverse_checkBox->checkState() == AppSettings::Status_Enable)
	{
		send_data.append(static_cast<char>(0x01));
	}
	else if (ui->Page2_Pane3_PitchStickReverse_checkBox->checkState() == AppSettings::Status_Disable)
	{
		send_data.append(static_cast<char>(0x00));
	}
	// 判断航向反向 勾选
	if (ui->Page2_Pane3_YawRockerReverse_checkBox->checkState() == AppSettings::Status_Enable)
	{
		send_data.append(static_cast<char>(0x01));
	}
	else if (ui->Page2_Pane3_YawRockerReverse_checkBox->checkState() == AppSettings::Status_Disable)
	{
		send_data.append(static_cast<char>(0x00));
	}

	send_data.append(static_cast<char>(0x00));	// 横滚摇杆速度 00即可
	send_data.append(static_cast<char>(pitch_speed));	// 俯仰摇杆速度 
	send_data.append(static_cast<char>(yaw_speed));	// 航向摇杆速度

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_ControlParameterSet, 0x06, 0x06, send_data);
	return;
ParameterError:
	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数设置错误!"));
}

void Mainwindow::Page2_Pane3_GetValue_Btn_Handler()
{
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_ControlParameterGet, 0x00, 0x00, nullptr);
}

void Mainwindow::Page2_Pane4_DefaultValue_Btn_Handler()
{
	QByteArray send_data;
	send_data.append(static_cast<char>(0x00));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_ParameterDefault, 0x01, 0x01, send_data);
}

void Mainwindow::Page2_Pane4_SetValue_Btn_Handler()
{
	QByteArray send_data;
	qint16 yaw_deadArea, pitch_deadArea;	// 航向死区，俯仰死区
	qint16 yaw_speed, pitch_speed;	// 航向速度，俯仰速度
	bool ok;

	yaw_deadArea = ui->Page2_Pane4_YawDeadZone_lineEdit->text().toInt(&ok);
	if (false == ok) { goto ParameterError; }
	pitch_deadArea = ui->Page2_Pane4_PitchDeadZone_lineEdit->text().toInt(&ok);
	if (false == ok) { goto ParameterError; }
	yaw_speed = ui->Page2_Pane4_YawSpeed_lineEdit->text().toInt(&ok);
	if (false == ok) { goto ParameterError; }
	pitch_speed = ui->Page2_Pane4_PitchSpeed_lineEdit->text().toInt(&ok);
	if (false == ok) { goto ParameterError; }

	send_data.append(static_cast<char>(yaw_deadArea & 0xFF));
	send_data.append(static_cast<char>((yaw_deadArea >> 8) & 0xFF));

	send_data.append(static_cast<char>(pitch_deadArea & 0xFF));
	send_data.append(static_cast<char>((pitch_deadArea >> 8) & 0xFF));

	send_data.append(static_cast<char>(yaw_speed & 0xFF));
	send_data.append(static_cast<char>((yaw_speed >> 8) & 0xFF));

	send_data.append(static_cast<char>(pitch_speed & 0xFF));
	send_data.append(static_cast<char>((pitch_speed >> 8) & 0xFF));

	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_FollowParameterSet, 0x08, 0x08, send_data);

	return;
ParameterError:
	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数设置错误!"));

}

void Mainwindow::Page2_Pane4_GetValue_Btn_Handler()
{
	// 发送命令包
	emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_FollowParameterGet, 0x00, 0x00, nullptr);
}

/*======================================= Page4 =======================================*/

void Mainwindow::Page2_Page4_Pane1_IMU_NoiseTest_Btn_Handler()
{
	if (AppSettings::Instance()->getSerial_isOpen())
	{
		QByteArray send_data;
		send_data.append(static_cast<char>(0x02));
		// 发送命令包
		emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_PTZTestNoise, 0x01, 0x01, send_data);

		// 传送到调试区显示
		SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("正在测试...(过程大概需要10s)"));
	}
	else
	{
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("串口未打开!"));
		return;
	}
}

void Mainwindow::Page2_Page4_Pane2_IMUZeroOffset_Btn_Handler()
{
	if (AppSettings::Instance()->getSerial_isOpen())
	{
		QByteArray send_data;
		send_data.append(static_cast<char>(0x04));
		// 发送命令包
		emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_PTZTestNoise, 0x01, 0x01, send_data);

		// 传送到调试区显示
		SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("正在测试...(过程大概需要5s)"));
	}
	else
	{
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("串口未打开!"));
		return;
	}
}

void Mainwindow::Page2_Page4_Experience_Btn_Handler()
{
	if (AppSettings::Instance()->getSerial_isOpen())
	{
		QByteArray send_data;
		send_data.append(static_cast<char>(0x01));
		// 发送命令包
		emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_PTZTestNoise, 0x01, 0x01, send_data);

		// 传送到调试区显示
		SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("正在一键体检...(过程大概需要10s)"));
	}
	else
	{
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("串口未打开!"));
		return;
	}
}

void Mainwindow::Page4_Pane3_YawDriftSpeedTest_Btn_Handler()
{
	if (AppSettings::Instance()->getSerial_isOpen())
	{
		QByteArray send_data;
		send_data.append(static_cast<char>(0x03));
		// 发送命令包
		emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_PTZTestNoise, 0x01, 0x01, send_data);
		// 传送到调试区显示
		SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("正在测试...(过程大概需要8s)"));
	}
	else
	{
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("串口未打开!"));
		return;
	}
}



/*===============其他===================*/
void Mainwindow::Pro1_ShowSystemStatusQuery(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 19)
	{
		qDebug() << "Invalid data length19";
		return;
	}

	/*数据解析*/
	// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	quint16 device_run_time;	// 设备运行时间 2
	quint32 sys_status;	// 系统状态 4
	quint32 extended_status;	// 扩展状态 4
	quint8 roll_temp, pitch_temp, yaw_temp;	// 3
	quint32 inside_status;	// 内部状态 4
	quint16 io_input;	// IO输入 2

	// 从数据流中读取数据，并存入上述定义的变量中
	stream >> device_run_time;	// 设备运行时间
	stream >> sys_status;	// 系统状态
	stream >> extended_status;	// 扩展状态
	stream >> roll_temp;		// 横滚温度
	stream >> pitch_temp;	// 俯仰温度
	stream >> yaw_temp;	// 航向温度
	stream >> inside_status;	// 内部状态
	stream >> io_input;	// IO输入

	// 复制到系统状态位域结构体里
	memcpy(&serialThread->OldProtocol1_Parameter->Pro1_SystemStatus, &sys_status, sizeof(serialThread->OldProtocol1_Parameter->Pro1_SystemStatus));
	// 复制到扩展状态位域结构体里
	memcpy(&serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus, &extended_status, sizeof(serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus));
	// 复制到内部状态位域结构体里
	memcpy(&serialThread->OldProtocol1_Parameter->Pro1_InsideStatus, &inside_status, sizeof(serialThread->OldProtocol1_Parameter->Pro1_InsideStatus));

	/*Ui更新*/
	ui->Page1_DeviceRunTime_lineEdit->setText(QString::number(device_run_time));

	/*底部步骤Ui更新*/
	Pro1_Status_To_Ui_Update();


#if 0
	qDebug() << "设备运行时间: " << device_run_time;
	qDebug() << "系统状态：" << sys_status;
	qDebug() << "扩展状态：" << extended_status;
	qDebug() << "横滚温度：" << roll_temp;
	qDebug() << "俯仰温度：" << pitch_temp;
	qDebug() << "航向温度：" << yaw_temp;
	qDebug() << "内部状态：" << inside_status;
	qDebug() << "IO输入：" << io_input;
	// 输出各个位的值
	qDebug() << "校准状态: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_step;
	qDebug() << "校准步骤: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.calibration_status;
	qDebug() << "陀螺仪异常: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.gyro_exception;
	qDebug() << "航向轴通信异常: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.yaw_axis_comm_exception;
	qDebug() << "横滚轴通信异常: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.roll_axis_comm_exception;
	qDebug() << "电机零点未校准: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.motor_zero_angle_not_calibrated;
	qDebug() << "加速度计未校准: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.accelerometer_not_calibrated;
	qDebug() << "陀螺仪未校准: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.gyro_not_calibrated;
	qDebug() << "电机未校准: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.motor_not_calibrated;
	qDebug() << "保留: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.reserved;
	qDebug() << "运行模式: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.run_mode;
	qDebug() << "横滚编码器错误: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.roll_encoder_error;
	qDebug() << "俯仰编码器错误: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.pitch_encoder_error;
	qDebug() << "航向编码器错误: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.yaw_encoder_error;
	qDebug() << "电机过热警告: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.motor_overheat_warning;
	qDebug() << "堵转警告: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.block_warning;
	qDebug() << "电机角度保护: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.motor_angle_protection;
	qDebug() << "横滚跟随: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.roll_following;
	qDebug() << "俯仰跟随: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.pitch_following;
	qDebug() << "航向跟随: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.yaw_following;
	qDebug() << "竖拍模式: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.vertical_shoot_mode;
	qDebug() << "状态: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.status;
	qDebug() << "控制器正在重启: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.controller_rebooting;
	qDebug() << "允许外部控制: " << serialThread->OldProtocol1_Parameter->Pro1_SystemStatus.external_control_allowed;

	qDebug() << "姿态移动状态: " << serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.posture_shift_state;
	qDebug() << "轨迹模式: " << serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.path_mode;
	qDebug() << "轨迹运行是否进入了开始位置: " << serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.path_running_whether_reached_start;
	qDebug() << "工作模式: " << serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.work_mode;
	qDebug() << "扩展模式通知: " << serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.extended_mode_notification;
	qDebug() << "应用模式: " << serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.app_mode;
	qDebug() << "应用模式下-速度: " << serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.app_mode_running_data_speed;
	qDebug() << "应用模式下-步骤: " << serialThread->OldProtocol1_Parameter->Pro1_ExtendedStatus.app_mode_running_data_step;

	qDebug() << "X电机静止标志: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.motor_still_flag_x;
	qDebug() << "Y电机静止标志: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.motor_still_flag_y;
	qDebug() << "Z电机静止标志: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.motor_still_flag_z;
	qDebug() << "外部力矩标志X: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.external_moment_flag_x;
	qDebug() << "外部力矩标志Y: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.external_moment_flag_y;
	qDebug() << "外部力矩标志Z: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.external_moment_flag_z;
	qDebug() << "堵转标志X: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.stalled_flag_x;
	qDebug() << "堵转标志Y: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.stalled_flag_y;
	qDebug() << "堵转标志Z: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.stalled_flag_z;
	qDebug() << "运行模式修改: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.running_mode_revise;
	qDebug() << "竖横屏切换中: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.vertical_horizontal_switching;
	qDebug() << "欧拉角计算切换中: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.euler_angle_calculation_switching;
	qDebug() << "是否为手电筒模式: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.flashlight_mode;
	qDebug() << "手柄是否倒立: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.handle_handstand;
	qDebug() << "保留: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.reserved1;
	qDebug() << "校准操作允许: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.calibration_operations_allowed;
	qDebug() << "AI摄像头在线: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.ai_camera_online;
	qDebug() << "保留: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.reserved2;
	qDebug() << "外部横竖拍切命令: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.external_horizontal_vertical_shot_switch;
	qDebug() << "保留: " << serialThread->OldProtocol1_Parameter->Pro1_InsideStatus.reserved3;
#endif
}

void Mainwindow::Pro1_VerifyHandler(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 2)
	{
		qDebug() << "Invalid data length2";
		return;
	}

	/*数据解析*/
// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	quint8 orderID, reserved;	// 命令ID,保留位

	stream >> orderID;
	stream >> reserved;

	if ((orderID == PRO1_FUNC_PTZTestNoise) && (true == mainpage4->PTZ_Parameter->IMU_ZeroOffsetTest_Flag))	// 零偏测试
	{
		mainpage4->PTZ_Parameter->IMU_ZeroOffsetTest_Flag = false;
		// 阻塞5s
		// 创建 QTimer 对象
		QTimer* delayTimer1 = new QTimer(this);
		// 设置单次触发，即在延时结束后触发一次
		delayTimer1->setSingleShot(true);
		// 延时2秒
		int delayDuration = 5000; // 单位：毫秒
		delayTimer1->start(delayDuration);
		// 连接延时结束后的槽函数
		connect(delayTimer1, &QTimer::timeout, this, [=]()
			{
				// 发送获取结果命令
				QByteArray send_data;
				send_data.append(static_cast<char>(0x00));
				// 发送命令包
				emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_PTZTestNoise, 0x01, 0x01, send_data);
				// 延时操作完成后释放定时器内存
				delayTimer1->deleteLater();
			});
	}
	else if ((orderID == PRO1_FUNC_PTZTestNoise) && (true == mainpage4->PTZ_Parameter->IMU_YawDriftSpeedTest_Flag))	// 航向漂移速度测试
	{
		mainpage4->PTZ_Parameter->IMU_YawDriftSpeedTest_Flag = false;
		// 阻塞8s
		// 创建 QTimer 对象
		QTimer* delayTimer2 = new QTimer(this);
		// 设置单次触发，即在延时结束后触发一次
		delayTimer2->setSingleShot(true);
		// 延时8秒
		int delayDuration = 8000; // 单位：毫秒
		delayTimer2->start(delayDuration);
		// 连接延时结束后的槽函数 -- 发送查询命令
		connect(delayTimer2, &QTimer::timeout, this, [=]()
			{
				// 发送获取结果命令
				QByteArray send_data;
				send_data.append(static_cast<char>(0x00));
				// 发送命令包
				emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_PTZTestNoise, 0x01, 0x01, send_data);
				// 延时操作完成后释放定时器内存
				delayTimer2->deleteLater();
			});
	}
	else if ((orderID == PRO1_FUNC_PTZTestNoise) && (true == mainpage4->PTZ_Parameter->IMU_Experience_Flag))	// 一键体检
	{
		mainpage4->PTZ_Parameter->IMU_Experience_Flag = false;
		// 阻塞10s
		// 创建 QTimer 对象
		QTimer* delayTimer3 = new QTimer(this);
		// 设置单次触发，即在延时结束后触发一次
		delayTimer3->setSingleShot(true);
		// 延时10秒
		int delayDuration = 10000; // 单位：毫秒
		delayTimer3->start(delayDuration);
		// 连接延时结束后的槽函数
		connect(delayTimer3, &QTimer::timeout, this, [=]()
			{
				// 发送获取结果命令
				QByteArray send_data;
				send_data.append(static_cast<char>(0x00));
				// 发送命令包
				emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_PTZTestNoise, 0x01, 0x01, send_data);
				// 延时操作完成后释放定时器内存
				delayTimer3->deleteLater();
			});
	}


	SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", QString("0x%1 命令执行成功...").arg(QString::number(orderID, 16).toUpper()));
}

void Mainwindow::Pro1_DenyHandler(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 4)
	{
		qDebug() << "Invalid data length2";
		return;
	}

	/*数据解析*/
	// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	quint8 orderID, reserved;	// 命令ID,保留位
	quint16 reason;	// 原因

	stream >> orderID;
	stream >> reserved;
	stream >> reason;

	SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", QString("0x%1 命令执行失败, 原因码: %2 ...").arg(QString::number(orderID, 16).toUpper()).arg(reason));
}

void Mainwindow::Pro1_DebugCmdHandler(const QByteArray& array, int data_len)
{
	// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);
	QByteArray rackDescriptionBytes(data_len, '\0');
	stream.readRawData(rackDescriptionBytes.data(), data_len); // 读取
	QString compileDate = QString::fromUtf8(rackDescriptionBytes.constData()).trimmed();

	if (compileDate == "auto_ad_ps=0")	// 复位信息
	{
		// 进行版本查询 发送命令包
		emit Main_Signals_SendPack(PRO1_FrameHead, PRO1_Roll, static_cast<Protocol1_Addr_et>(AppSettings::Instance()->getDevicePCAddr()), PRO1_FUNC_VersionQuery, 0x00, 0x00, nullptr);
	}

	// 传送到调试区显示
	SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString(compileDate));
	//qDebug() << compileDate;
}

void Mainwindow::Pro1_ReadHallHandler(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 12)
	{
		qDebug() << "Invalid data length3";
		return;
	}

	/*数据解析*/
// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	quint16 hall_x1, hall_x2, hall_y1, hall_y2, hall_z1, hall_z2;

	stream >> hall_x1;
	stream >> hall_x2;
	stream >> hall_y1;
	stream >> hall_y2;
	stream >> hall_z1;
	stream >> hall_z2;

	// 传送到调试区显示
	SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("Hall_x: %1, %2  Hall_y: %3, %4  Hall_z: %5, %6").arg(hall_x1).arg(hall_x2).arg(hall_y1).arg(hall_y2).arg(hall_z1).arg(hall_z2));
}

void Mainwindow::Pro1_AttitudeFineTuningGetHandler(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 4)
	{
		qDebug() << "Invalid data length4";
		return;
	}
	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("读取成功"));
	/*数据解析*/
// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	qint16 roll, pitch;

	stream >> roll;
	stream >> pitch;

	/*ui更新*/
	ui->Page1_Pane11_Pitch_lineEdit->setText(QString::number(pitch));
	ui->Page1_Pane11_Roll_lineEdit->setText(QString::number(roll));
	//qDebug() << roll << pitch;
}

void Mainwindow::Pro1_UniformMotionQueryHandler(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 6)
	{
		qDebug() << "Invalid data length5";
		return;
	}
	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("读取成功"));
	/*数据解析*/
// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	qint16 roll, pitch, yaw;

	stream >> roll;
	stream >> pitch;
	stream >> yaw;

	/*ui更新*/
	ui->Page1_Pane9_Pitch_lineEdit->setText(QString::number(pitch));	// 俯仰
	ui->Page1_Pane9_Yaw_lineEdit->setText(QString::number(yaw));	// 航向

	//qDebug() << roll << pitch << yaw;
}

void Mainwindow::Pro1_MotorZeroPositionQueryHandler(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 6)
	{
		qDebug() << "Invalid data length6";
		return;
	}
	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("读取成功"));
	/*数据解析*/
	// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	qint16 roll, pitch, yaw;
	float pitch_temp, yaw_temp;

	stream >> roll;
	stream >> pitch;
	stream >> yaw;

	// 获取到的数据除以100

	pitch_temp = pitch / 100.0;
	yaw_temp = yaw / 100.0;

	/*ui更新*/
	ui->Page1_Pane10_Pitch_lineEdit->setText(QString::number(pitch_temp, 'f', 2));	// 俯仰
	ui->Page1_Pane10_Yaw_lineEdit->setText(QString::number(yaw_temp, 'f', 2));	// 航向

	//qDebug() << roll << pitch << yaw;
}

void Mainwindow::Pro1_AttitudeCalibrationHandler(const QByteArray& array, int data_len)
{
	// 姿态校准
	qDebug() << "姿态校准" << array;
}

void Mainwindow::Pro1_SixCalibrationNextStepHandler(const QByteArray& array, int data_len)
{
	// 六面下一步
	qDebug() << "六面下一步" << array;
}

void Mainwindow::Pro1_SixCalibrationHandler(const QByteArray& array, int data_len)
{
	// 六面校准
	qDebug() << "六面校准" << array;
}

void Mainwindow::Pro1_RunControlHandler(const QByteArray& array, int data_len)
{
	qDebug() << "RunControl";
}

void Mainwindow::Pro1_UserDataReadHandler(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 4)
	{
		qDebug() << "Invalid data length7";
		return;
	}

	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("读取成功"));

	/*数据解析*/
	// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	quint8 start_addr, len;	// 起始地址  数据长度
	qint16 data1;	// 数据1

	stream >> start_addr;
	stream >> len;
	stream >> data1;

	SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("数据起始地址: %1 数据长度: %2 数据1: %3").arg(start_addr).arg(len).arg(data1));
}

void Mainwindow::Pro1_ControlPIDQueryHandler(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 18)
	{
		qDebug() << "Invalid data length8";
		return;
	}
	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("读取成功"));
	/*数据解析*/
	// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	qint16 roll_kp, roll_ki, roll_kd;	// 横滚
	qint16 pitch_kp, pitch_ki, pitch_kd;	// 俯仰
	qint16 yaw_kp, yaw_ki, yaw_kd;	// 航向

	stream >> roll_kp;
	stream >> roll_ki;
	stream >> roll_kd;
	stream >> pitch_kp;
	stream >> pitch_ki;
	stream >> pitch_kd;
	stream >> yaw_kp;
	stream >> yaw_ki;
	stream >> yaw_kd;

	float rollKP = (float)roll_kp / 10000;
	float rollKI = (float)roll_ki / 10000;
	float rollKD = (float)roll_kd / 10000;
	float pitchKP = (float)pitch_kp / 10000;
	float pitchKI = (float)pitch_ki / 10000;
	float pitchKD = (float)pitch_kd / 10000;
	float yawKP = (float)yaw_kp / 10000;
	float yawKI = (float)yaw_ki / 10000;
	float yawKD = (float)yaw_kd / 10000;

	/*ui更新*/
	// 横滚
	ui->Page2_Pane2_1_KP_lineEdit->setText(QString::number(rollKP, 'f', 4));
	ui->Page2_Pane2_1_KI_lineEdit->setText(QString::number(rollKI, 'f', 4));
	ui->Page2_Pane2_1_KD_lineEdit->setText(QString::number(rollKD, 'f', 4));
	// 俯仰
	ui->Page2_Pane2_2_KP_lineEdit->setText(QString::number(pitchKP, 'f', 4));
	ui->Page2_Pane2_2_KI_lineEdit->setText(QString::number(pitchKI, 'f', 4));
	ui->Page2_Pane2_2_KD_lineEdit->setText(QString::number(pitchKD, 'f', 4));
	// 航向
	ui->Page2_Pane2_3_KP_lineEdit->setText(QString::number(yawKP, 'f', 4));
	ui->Page2_Pane2_3_KI_lineEdit->setText(QString::number(yawKI, 'f', 4));
	ui->Page2_Pane2_3_KD_lineEdit->setText(QString::number(yawKD, 'f', 4));

	//qDebug() << rollKP << rollKI << rollKD << pitchKP << pitchKI << pitchKD << yawKP << yawKI << yawKD;
}

void Mainwindow::Pro1_ControlParameterGetHandler(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 6)
	{
		qDebug() << "Invalid data length9";
		return;
	}
	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("读取成功"));
	/*数据解析*/
	// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	qint8 roll_checkBox_status, pitch_checkBox_status, yaw_checkBox_status;
	qint8 roll_speed, pitch_speed, yaw_speed;

	stream >> roll_checkBox_status;
	stream >> pitch_checkBox_status;
	stream >> yaw_checkBox_status;
	stream >> roll_speed;
	stream >> pitch_speed;
	stream >> yaw_speed;

	/*ui更新*/
	if (1 == pitch_checkBox_status)
	{
		ui->Page2_Pane3_PitchStickReverse_checkBox->setCheckState(static_cast<Qt::CheckState>(AppSettings::Status_Enable));
	}
	else
	{
		ui->Page2_Pane3_PitchStickReverse_checkBox->setCheckState(static_cast<Qt::CheckState>(AppSettings::Status_Disable));
	}
	if (1 == yaw_checkBox_status)
	{
		ui->Page2_Pane3_YawRockerReverse_checkBox->setCheckState(static_cast<Qt::CheckState>(AppSettings::Status_Enable));
	}
	else
	{
		ui->Page2_Pane3_YawRockerReverse_checkBox->setCheckState(static_cast<Qt::CheckState>(AppSettings::Status_Disable));
	}

	ui->Page2_Pane3_StickPitchSpeed_lineEdit->setText(QString::number(pitch_speed));
	ui->Page2_Pane3_StickYawSpeed_lineEdit->setText(QString::number(yaw_speed));
}

void Mainwindow::Pro1_FollowParameterGetHandler(const QByteArray& array, int data_len)
{
	// 判断数据长度
	if (data_len != 8)
	{
		qDebug() << "Invalid data length10";
		return;
	}
	emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("读取成功"));
	/*数据解析*/
// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	qint16 yaw_deadArea, pitch_deadArea;	// 航向死区，俯仰死区
	qint16 yaw_speed, pitch_speed;	// 航向速度，俯仰速度

	stream >> yaw_deadArea;
	stream >> pitch_deadArea;
	stream >> yaw_speed;
	stream >> pitch_speed;

	/*ui更新*/
	ui->Page2_Pane4_YawDeadZone_lineEdit->setText(QString::number(yaw_deadArea));
	ui->Page2_Pane4_PitchDeadZone_lineEdit->setText(QString::number(pitch_deadArea));
	ui->Page2_Pane4_YawSpeed_lineEdit->setText(QString::number(yaw_speed));
	ui->Page2_Pane4_PitchSpeed_lineEdit->setText(QString::number(pitch_speed));
}

void Mainwindow::Pro1_PTZTestNoiseHandler(const QByteArray& array, int data_len)
{
	/*数据解析*/
	// 将字节数组转换为数据流
	QDataStream stream(array);
	// 设置字节序为小端模式，与协议说明中一致
	stream.setByteOrder(QDataStream::LittleEndian);

	quint8 order;

	stream >> order;

	if (0x01 == order)	// 一键体检
	{
		// 判断数据长度
		if (data_len != 17)
		{
			qDebug() << "Invalid data length11";
			return;
		}
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("一键体检完成"));
		QString arr[8] = { "失败", "失败", "失败", "失败", "失败", "失败", "失败", "失败" };
		QStringList strList; // 用于保存每行字符串

		// 00编码器磁场强度，01IMU温度补偿范围，02陀螺仪校准，03加速度计校准，04卡位校准，05IMU噪声，06校准后零偏，07原始零偏
		quint16 Encoder_result, Temp_result, Gyro_result, Accelerometer_result, CardSlot_result, IMUNoise_result, AfterZero_rersult, OriginalZero_result;

		stream >> Encoder_result;
		stream >> Temp_result;
		stream >> Gyro_result;
		stream >> Accelerometer_result;
		stream >> CardSlot_result;
		stream >> IMUNoise_result;
		stream >> AfterZero_rersult;
		stream >> OriginalZero_result;

		//qDebug() << Encoder_result << Temp_result << Gyro_result << Accelerometer_result << CardSlot_result << IMUNoise_result << AfterZero_rersult << OriginalZero_result;

		// 判断结果则进行显示
		if ((0x00 == (Encoder_result & 0XFF)) && (0x00 == ((Encoder_result >> 8) & 0xFF)))	// 判断结果(检查项 && 检测结果)
		{
			arr[0] = "成功";
		}
		if ((0x01 == (Temp_result & 0XFF)) && (0x00 == ((Temp_result >> 8) & 0xFF)))	// 判断结果
		{
			arr[1] = "成功";
		}
		if ((0x02 == (Gyro_result & 0XFF)) && (0x00 == ((Gyro_result >> 8) & 0xFF)))	// 判断结果
		{
			arr[2] = "成功";
		}
		if ((0x03 == (Accelerometer_result & 0XFF)) && (0x00 == ((Accelerometer_result >> 8) & 0xFF)))	// 判断结果
		{
			arr[3] = "成功";
		}
		if ((0x04 == (CardSlot_result & 0XFF)) && (0x00 == ((CardSlot_result >> 8) & 0xFF)))	// 判断结果
		{
			arr[4] = "成功";
		}
		if ((0x05 == (IMUNoise_result & 0XFF)) && (0x00 == ((IMUNoise_result >> 8) & 0xFF)))	// 判断结果
		{
			arr[5] = "成功";
		}
		if ((0x06 == (AfterZero_rersult & 0XFF)) && (0x00 == ((AfterZero_rersult >> 8) & 0xFF)))	// 判断结果
		{
			arr[6] = "成功";
		}
		if ((0x07 == (OriginalZero_result & 0XFF)) && (0x00 == ((OriginalZero_result >> 8) & 0xFF)))	// 判断结果
		{
			arr[7] = "成功";
		}

		// 生成每行字符串
		strList << "编码器磁场强度............." + arr[0];
		strList << "IMU温度补偿范围............." + arr[1];
		strList << "陀螺仪校准............." + arr[2];
		strList << "加速度计校准............." + arr[3];
		strList << "卡位校准............." + arr[4];
		strList << "IMU噪声............." + arr[5];
		strList << "校准后零偏............." + arr[6];
		strList << "原始零偏............." + arr[7];

		// 写入每行字符串，并进行颜色标记 更新Ui
		for (int i = 0; i < strList.count(); i++)
		{
			if (strList[i].contains("失败")) 
			{
				ui->Page4_Experience_textEdit->append("<font color='red'>" + strList[i] + "</font>");
			}
			else 
			{
				ui->Page4_Experience_textEdit->append("<font color='green'>" + strList[i] + "</font>");
			}
		}
		// 传送到调试区显示
		SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("测试完成"));
	}
	else if (0x02 == order)	// IMU噪声测试回传
	{
		// 判断数据长度
		if (data_len != 4)
		{
			qDebug() << "Invalid data length11";
			return;
		}
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("测试完成"));
		quint8 noisse_x, noise_y, noise_z;

		stream >> noisse_x;
		stream >> noise_y;
		stream >> noise_z;

		/*ui更新*/
		ui->Page4_Pane1_X_lineEdit->setText(QString::number((float)noisse_x / 100.0, 'f', 2));
		ui->Page4_Pane1_Y_lineEdit->setText(QString::number((float)noise_y / 100.0, 'f', 2));
		ui->Page4_Pane1_Z_lineEdit->setText(QString::number((float)noise_z / 100.0, 'f', 2));

		// 传送到调试区显示
		SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("测试完成"));
	}
	else if (0x03 == order)	// 航向漂移速度测试
	{
		// 判断数据长度
		if (data_len != 2)
		{
			qDebug() << "Invalid data length12";
			return;
		}
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("测试完成"));
		quint8 speed;

		stream >> speed;

		/*ui更新*/
		ui->Page4_Pane3_YawDriftSpeedTest_lineEdit->setText(QString::number((float)speed / 100.0, 'f', 2));

		// 传送到调试区显示
		SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("测试完成"));
	}
	else if (0x04 == order)	// IMU零偏测试
	{
		// 判断数据长度
		if (data_len != 7)
		{
			qDebug() << "Invalid data length13";
			return;
		}
		emit Main_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("测试完成"));

		quint8 After_x, After_y, After_z;
		quint8 Original_x, Original_y, Original_z;

		stream >> After_x;
		stream >> After_y;
		stream >> After_z;
		stream >> Original_x;
		stream >> Original_y;
		stream >> Original_z;

		/*ui更新*/
		ui->Page4_Pane2_XAfterCalibration_lineEdit->setText(QString::number((float)After_x / 100.0, 'f', 2));	// 校准后零偏XYZ
		ui->Page4_Pane2_YAfterCalibration_lineEdit->setText(QString::number((float)After_y / 100.0, 'f', 2));
		ui->Page4_Pane2_ZAfterCalibration_lineEdit->setText(QString::number((float)After_z / 100.0, 'f', 2));
		ui->Page4_Pane2_XOriginal_lineEdit->setText(QString::number((float)Original_x / 100.0, 'f', 2));	// 原始零偏XYZ
		ui->Page4_Pane2_YOriginal_lineEdit->setText(QString::number((float)Original_y / 100.0, 'f', 2));
		ui->Page4_Pane2_ZOriginal_lineEdit->setText(QString::number((float)Original_z / 100.0, 'f', 2));

		// 传送到调试区显示
		SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#8B3A3A", QString("测试完成"));
	}
}


