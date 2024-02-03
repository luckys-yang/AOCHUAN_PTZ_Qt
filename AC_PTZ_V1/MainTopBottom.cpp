#include "MainTopBottom.h"

MainTopBottom::MainTopBottom(QWidget* parent)
	: QWidget(parent)
{
	MainTopBottom_ui = nullptr;
}

MainTopBottom::~MainTopBottom()
{
#if QT_MainTopBottom_Debug
	qDebug() << "delete MainTopBottom";
#endif
}

// 串口部分写在Page5.cpp
void MainTopBottom::MainTopBottom_Init()
{
	SaveLog::Instance()->setPath(qApp->applicationDirPath());	// 设置日志保存路径为应用程序目录

	/*widgetLeft 设置*/
	MainTopBottom_ui->left_navBar->setBarColorStart(QColor("#74ebd5"));
	MainTopBottom_ui->left_navBar->setBarColorEnd(QColor("#9face6"));
	MainTopBottom_ui->left_navBar->setItems("云台中控;参数设置;固件更新;云台测试;串口调试助手;波形显示;关于");
	MainTopBottom_ui->left_navBar->setTextFont(QFont(MainwindowParameter.System_Font_Id, 11));	// 设置字体和大小

	// 标签
	FlatUI::Instance()->setLabelQss(MainTopBottom_ui->Top_label3, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#b43f4f");	// ID
	FlatUI::Instance()->setLabelQss(MainTopBottom_ui->Top_label4, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#b43f4f");	// 固件版本
	FlatUI::Instance()->setLabelQss(MainTopBottom_ui->Bottom_label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#b43f4f");	// 机架编号
	FlatUI::Instance()->setLabelQss(MainTopBottom_ui->Bottom_label3, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#b43f4f");	// 编译时间
	FlatUI::Instance()->setLabelQss(MainTopBottom_ui->Bottom_label4, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#b43f4f");	// 配置版本1

	// 单行输入框
	FlatUI::Instance()->setLineEditQss(MainTopBottom_ui->Top_ICID_lineEdit, QFont(MainwindowParameter.System_Font_Id, 11));	// IC ID
	FlatUI::Instance()->setLineEditQss(MainTopBottom_ui->Top_ICVersion_lineEdit, QFont(MainwindowParameter.System_Font_Id, 11));	// 固件版本
	FlatUI::Instance()->setLineEditQss(MainTopBottom_ui->Bottom__RackNumber_lineEdit, QFont(MainwindowParameter.System_Font_Id, 11));	// 机架编号
	FlatUI::Instance()->setLineEditQss(MainTopBottom_ui->Bottom__CompileTime_lineEdit, QFont(MainwindowParameter.System_Font_Id, 11));	// 编译时间
	FlatUI::Instance()->setLineEditQss(MainTopBottom_ui->Bottom__ConfigVersion1_lineEdit, QFont(MainwindowParameter.System_Font_Id, 11));	// 配置版本1

	/*右上角按钮 设置*/
	MainTopBottom_ui->smallBtn->setToolTip("最小化");
	MainTopBottom_ui->closeBtn->setToolTip("关闭");

	/*设置Debug区的字体和字体大小*/
	MainTopBottom_ui->Debug_TextEdit->setFont(QFont(MainwindowParameter.System_Font_Id, 11));	// 设置Debug框的文字大小和字体
	MainTopBottom_ui->Debug_TextEdit->setVerticalScrollBar(MainTopBottom_ui->Debug_TextEdit_ScrollBar);	// 重新指定滚动条
	/*按钮*/
	MainTopBottom_ui->Debug_Clear_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 清空调试
	MainTopBottom_ui->Bottom_LogPath_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 日志路径
	/*复选框*/
	FlatUI::Instance()->setCheckBoxQss(MainTopBottom_ui->Debug_SaveLog_CheckBox, QFont(MainwindowParameter.System_Font_Id, 11));	// 保存日志

	/*名称*/
	MainTopBottom_ui->navLabel_1->setArrowPosition(NavLabel::ArrowPosition_Right);
	MainTopBottom_ui->navLabel_1->setBackground(QColor("#64b3f4"), QColor("#c2e59c"));
	MainTopBottom_ui->navLabel_1->setTextFont(QFont(MainwindowParameter.System_Font_Id, 11));
	
	/*底部校准进度 设置*/
	MainTopBottom_ui->step_RollCommunication->setText("横滚通讯");
	MainTopBottom_ui->step_RollCommunication->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_YawCommunication->setText("航向通讯");
	MainTopBottom_ui->step_YawCommunication->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_IMU->setText("IMU");
	MainTopBottom_ui->step_IMU->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_BE->setText("BE");
	MainTopBottom_ui->step_BE->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_TE->setText("TE");
	MainTopBottom_ui->step_TE->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_RB->setText("RB");
	MainTopBottom_ui->step_RB->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_PB->setText("PB");
	MainTopBottom_ui->step_PB->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_YB->setText("YB");
	MainTopBottom_ui->step_YB->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_MotorCalibration->setText("电机校准");
	MainTopBottom_ui->step_MotorCalibration->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_ZeroAngleCalibration->setText("零角校准");
	MainTopBottom_ui->step_ZeroAngleCalibration->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_AccelerateCalibration->setText("加速校准");
	MainTopBottom_ui->step_AccelerateCalibration->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_GyroCalibration->setText("陀螺仪校准");
	MainTopBottom_ui->step_GyroCalibration->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_FollowRPY->setText("跟随");
	MainTopBottom_ui->step_FollowRPY->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_Fllow_R->setText("R");
	MainTopBottom_ui->step_Fllow_R->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_Fllow_P->setText("P");
	MainTopBottom_ui->step_Fllow_P->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_Fllow_Y->setText("Y");
	MainTopBottom_ui->step_Fllow_Y->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_HorizontalShootingMode->setText("横拍模式");
	MainTopBottom_ui->step_HorizontalShootingMode->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_CommonMode->setText("普通模式");
	MainTopBottom_ui->step_CommonMode->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	MainTopBottom_ui->step_Running->setText("运行");
	MainTopBottom_ui->step_Running->setTextFont(QFont(MainwindowParameter.System_Font_Id, 10));

	/*版本标签*/
	FlatUI::Instance()->setLabelQss(MainTopBottom_ui->Bottom_label1, QFont(MainwindowParameter.System_Font_Id, 10), 5, "#C6E2FF");
}

void MainTopBottom::MainTopBottom_Connect_Handler()
{
	/*debug区刷新*/
	connect(SaveLog::Instance(), &SaveLog::UI_Signals_SendDebugMsg_DebugArea, this, &MainTopBottom::Slots_MainTopBottom_DebugArea_Display);
	connect(MainTopBottom_ui->Debug_Clear_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainTopBottom::Slots_MainTopBottom_Debug_Clear_Btn_Clicked);
	connect(MainTopBottom_ui->Debug_SaveLog_CheckBox, &QCheckBox::stateChanged, this, &MainTopBottom::Slots_MainTopBottom_Debug_SaveLog_CheckBox_stateChanged);
	connect(MainTopBottom_ui->Bottom_LogPath_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainTopBottom::Slots_MainTopBottom_Bottom_LogPath_Btn_Clicked);
}

void MainTopBottom::Slots_MainTopBottom_DebugArea_Display(const QString& msg)
{
	MainTopBottom_ui->Debug_TextEdit->append(msg);
	MainTopBottom_ui->Debug_TextEdit_ScrollBar->setValue(MainTopBottom_ui->Debug_TextEdit_ScrollBar->maximum());	// 滚动条保持到最后一行
}

void MainTopBottom::Slots_MainTopBottom_Debug_Clear_Btn_Clicked()
{
	//static bool flag = false;
	//QString imageName1 = ":/Page7/Resource/Images/s1_video.png";
	//QString imageName2 = ":/Page7/Resource/Images/s2_video.png";

	//if (false == flag)
	//{
	//	MainTopBottom_ui->Page7_page3_Image->setPixmap1(QPixmap(imageName1));
	//	MainTopBottom_ui->Page7_page3_Image->setPixmap2(QPixmap(imageName2));
	//}
	//else
	//{
	//	MainTopBottom_ui->Page7_page3_Image->setPixmap1(QPixmap(imageName2));
	//	MainTopBottom_ui->Page7_page3_Image->setPixmap2(QPixmap(imageName1));
	//}

	//
	//MainTopBottom_ui->Page7_page3_Image->start();
	MainTopBottom_ui->Debug_TextEdit->clear();	// 清空
	//flag = !flag;
}

void MainTopBottom::Slots_MainTopBottom_Debug_SaveLog_CheckBox_stateChanged(int status)
{
	if (AppSettings::Status_Enable == status)
	{
		SaveLog::Instance()->SaveLogFile_Flag = true;	// 保存标志位置1
		SaveLog::Instance()->start();	// 启动钩子
		emit MainTopBottom_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("已启动日志保存！"));
		if (SaveLog::Instance()->getFileName() != nullptr)
		{
			SaveLog::Instance()->UI_SendDebugMsg_DebugArea("#EE9A00", QString("日志文件名称为: %1").arg(SaveLog::Instance()->getFileName()));	// 输出文件名称
		}
	}
	else if (AppSettings::Status_Disable == status)
	{
		SaveLog::Instance()->SaveLogFile_Flag = false;
		SaveLog::Instance()->stop();	// 卸载钩子
		emit MainTopBottom_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("已关闭日志保存！"));
	}
}

void MainTopBottom::Slots_MainTopBottom_Bottom_LogPath_Btn_Clicked()
{
	QString filePath = SaveLog::Instance()->getFilePath();
	if (filePath != nullptr)
	{
		if (false == QDesktopServices::openUrl(QUrl::fromLocalFile(filePath)))
		{
			emit MainTopBottom_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("打开日志路径失败！"));
		}
	}
}
