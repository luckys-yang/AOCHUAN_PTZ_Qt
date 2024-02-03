#include "MainPage4.h"

MainPage4::MainPage4(QWidget* parent)
	: QWidget(parent)
{
	MainPage4_ui = nullptr;
}

MainPage4::~MainPage4()
{
#if QT_MainPage4_Debug
	qDebug() << "delete MainPage4";
#endif
}

void MainPage4::MainPage4_Init()
{
	/*IMU噪声测试*/
	// 【标题框】
	MainPage4_ui->Page4_Pane1->setTitleHeight(15);
	MainPage4_ui->Page4_Pane1->setTitleText("IMU噪声测试");
	MainPage4_ui->Page4_Pane1->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	//【标签】
	FlatUI::Instance()->setLabelQss(MainPage4_ui->Page4_Pane1_label1, QFont(MainwindowParameter.System_Font_Id, 11));		// X轴
	FlatUI::Instance()->setLabelQss(MainPage4_ui->Page4_Pane1_label2, QFont(MainwindowParameter.System_Font_Id, 11));		// Y轴
	FlatUI::Instance()->setLabelQss(MainPage4_ui->Page4_Pane1_label3, QFont(MainwindowParameter.System_Font_Id, 11));		// Z轴
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage4_ui->Page4_Pane1_X_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// X轴
	FlatUI::Instance()->setLineEditQss(MainPage4_ui->Page4_Pane1_Y_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// Y轴
	FlatUI::Instance()->setLineEditQss(MainPage4_ui->Page4_Pane1_Z_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// Z轴
	// 【按键】
	MainPage4_ui->Page4_Pane1_IMU_NoiseTest_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// IMU噪声测试

	/*IMU零偏测试*/
	// 【标题框】
	MainPage4_ui->Page4_Pane2->setTitleHeight(15);
	MainPage4_ui->Page4_Pane2->setTitleText("IMU零偏测试");
	MainPage4_ui->Page4_Pane2->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	//【标签】
	FlatUI::Instance()->setLabelQss(MainPage4_ui->Page4_Pane2_label1, QFont(MainwindowParameter.System_Font_Id, 11));		// X轴
	FlatUI::Instance()->setLabelQss(MainPage4_ui->Page4_Pane2_label2, QFont(MainwindowParameter.System_Font_Id, 11));		// Y轴
	FlatUI::Instance()->setLabelQss(MainPage4_ui->Page4_Pane2_label3, QFont(MainwindowParameter.System_Font_Id, 11));		// Z轴
	FlatUI::Instance()->setLabelQss(MainPage4_ui->Page4_Pane2_label5, QFont(MainwindowParameter.System_Font_Id, 11));		// X轴
	FlatUI::Instance()->setLabelQss(MainPage4_ui->Page4_Pane2_label6, QFont(MainwindowParameter.System_Font_Id, 11));		// Y轴
	FlatUI::Instance()->setLabelQss(MainPage4_ui->Page4_Pane2_label7, QFont(MainwindowParameter.System_Font_Id, 11));		// Z轴
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage4_ui->Page4_Pane2_XAfterCalibration_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// X轴
	FlatUI::Instance()->setLineEditQss(MainPage4_ui->Page4_Pane2_YAfterCalibration_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// Y轴
	FlatUI::Instance()->setLineEditQss(MainPage4_ui->Page4_Pane2_ZAfterCalibration_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// Z轴
	FlatUI::Instance()->setLineEditQss(MainPage4_ui->Page4_Pane2_XOriginal_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// X轴
	FlatUI::Instance()->setLineEditQss(MainPage4_ui->Page4_Pane2_YOriginal_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// Y轴
	FlatUI::Instance()->setLineEditQss(MainPage4_ui->Page4_Pane2_ZOriginal_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// Z轴
	// 【按键】
	MainPage4_ui->Page4_Pane2_IMUZeroOffset_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// IMU零偏测试
	/*航向漂移速度测试*/
	// 【标题框】
	MainPage4_ui->Page4_Pane3->setTitleHeight(15);
	MainPage4_ui->Page4_Pane3->setTitleText("航向漂移速度测试");
	MainPage4_ui->Page4_Pane3->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage4_ui->Page4_Pane3_YawDriftSpeedTest_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 航向漂移速度测试
	// 【按键】
	MainPage4_ui->Page4_Pane3_YawDriftSpeedTest_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 航向漂移速度测试

	/*其他*/
	// 【按键】
	MainPage4_ui->Page4_Experience_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 一键体检
	MainPage4_ui->Page4_ClearTest_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 清空IMU测试数据
	//【文本框】
	MainPage4_ui->Page4_Experience_textEdit->setFont(QFont(MainwindowParameter.System_Font_Id, 11));	// 一键体检文本框
	MainPage4_ui->Page4_Experience_textEdit->setVerticalScrollBar(MainPage4_ui->Page4_ExperienceTextEdit_scrollBar);	// 重新指定滚动条

	this->PTZ_Parameter = new PTZ_Parameter_st();

	PTZ_Parameter->IMU_NoiseTest_Flag = false;
	PTZ_Parameter->IMU_ZeroOffsetTest_Flag = false;
	PTZ_Parameter->IMU_YawDriftSpeedTest_Flag = false;
	PTZ_Parameter->IMU_Experience_Flag = false;
}

void MainPage4::MainPage4_Connect_Handler()
{
	/*IMU噪声测试*/
	connect(MainPage4_ui->Page4_Pane1_IMU_NoiseTest_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage4::Slots_Page4_Pane1_IMU_NoiseTest_Btn_Clicked);
	/*IMU零偏测试*/
	connect(MainPage4_ui->Page4_Pane2_IMUZeroOffset_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage4::Slots_Page4_Pane2_IMUZeroOffset_Btn_Clicked);
	/*航向漂移速度测试*/
	connect(MainPage4_ui->Page4_Pane3_YawDriftSpeedTest_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage4::Slots_Page4_Pane3_YawDriftSpeedTest_Btn_Clicked);
	/*其他*/
	connect(MainPage4_ui->Page4_ClearTest_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage4::Slots_Page4_ClearTest_Btn_Clicked);
	connect(MainPage4_ui->Page4_Experience_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage4::Slots_Page4_Experience_Btn_Clicked);
}

void MainPage4::Slots_Page4_Pane1_IMU_NoiseTest_Btn_Clicked()
{
	// IMU噪声测试
	emit Signals_Page4_Pane1_IMU_NoiseTest_Btn_Clicked();
	PTZ_Parameter->IMU_NoiseTest_Flag = true;
}

void MainPage4::Slots_Page4_Pane2_IMUZeroOffset_Btn_Clicked()
{
	// IMU零偏测试
	emit Signals_Page4_Pane2_IMUZeroOffset_Btn_Clicked();
	PTZ_Parameter->IMU_ZeroOffsetTest_Flag = true;
}

void MainPage4::Slots_Page4_Pane3_YawDriftSpeedTest_Btn_Clicked()
{
	// 航向漂移速度测试
	emit Signals_Page4_Pane3_YawDriftSpeedTest_Btn_Clicked();
	PTZ_Parameter->IMU_YawDriftSpeedTest_Flag = true;
}

void MainPage4::Slots_Page4_ClearTest_Btn_Clicked()
{
	MainPage4_ui->Page4_Pane1_X_lineEdit->clear();	// 清空显示
	MainPage4_ui->Page4_Pane1_Y_lineEdit->clear();	// 清空显示
	MainPage4_ui->Page4_Pane1_Z_lineEdit->clear();	// 清空显示

	MainPage4_ui->Page4_Pane2_XAfterCalibration_lineEdit->clear();	// 清空显示
	MainPage4_ui->Page4_Pane2_YAfterCalibration_lineEdit->clear();	// 清空显示
	MainPage4_ui->Page4_Pane2_ZAfterCalibration_lineEdit->clear();	// 清空显示
	MainPage4_ui->Page4_Pane2_XOriginal_lineEdit->clear();	// 清空显示
	MainPage4_ui->Page4_Pane2_YOriginal_lineEdit->clear();	// 清空显示
	MainPage4_ui->Page4_Pane2_ZOriginal_lineEdit->clear();	// 清空显示

	MainPage4_ui->Page4_Pane3_YawDriftSpeedTest_lineEdit->clear();	// 清空显示

	MainPage4_ui->Page4_Experience_textEdit->clear();	// 清空显示
}

void MainPage4::Slots_Page4_Experience_Btn_Clicked()
{
	// 一键体检
	emit Signals_Page4_Experience_Btn_Clicked();
	PTZ_Parameter->IMU_Experience_Flag = true;
}
