#include "MainPage2.h"

MainPage2::MainPage2(QWidget *parent)
	: QWidget(parent)
{
	MainPage2_ui = nullptr;
}

MainPage2::~MainPage2()
{
#if QT_MainPage2_Debug
	qDebug() << "delete MainPage2";
#endif
}

void MainPage2::MainPage2_Init()
{
	QValidator* validator_1 = PublicClass::getValidator(PublicClass::Re_Burden9999P0000To9999);    // 限制
	QValidator* validator_2 = PublicClass::getValidator(PublicClass::Re_0P000To100);    // 限制


	/*软件配置*/
	// 【标题框】
	MainPage2_ui->Page2_Pane1->setTitleHeight(15);
	MainPage2_ui->Page2_Pane1->setTitleText("软件配置");
	MainPage2_ui->Page2_Pane1->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));

	// 【下拉框】
	// 机型选择
	MainPage2_ui->Page2_Pane1_Model_comboBox->setItemHeight(25);
	MainPage2_ui->Page2_Pane1_Model_comboBox->setAutoWidth(true);
	MainPage2_ui->Page2_Pane1_Model_comboBox->setTextFont(QFont(MainwindowParameter.System_Font_Id, 15));

	MainPage2_ui->Page2_Pane1_Model_comboBox->addItem("V5 + 旧按键板", AppSettings::Model_V5OldKeyBoard);
	MainPage2_ui->Page2_Pane1_Model_comboBox->addItem("V5 + 新按键板", AppSettings::Model_V5NewKeyBoard);
	MainPage2_ui->Page2_Pane1_Model_comboBox->addItem("D2 + 直连", AppSettings::Model_D2Direct);
	MainPage2_ui->Page2_Pane1_Model_comboBox->addItem("D2 + 新按键板", AppSettings::Model_D2NewKeyBoard);

	// PC地址
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->setItemHeight(25);
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->setAutoWidth(true);
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->setTextFont(QFont(MainwindowParameter.System_Font_Id, 15));

	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->addItem("1", AppSettings::PCAddr_1);
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->addItem("2", AppSettings::PCAddr_2);
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->addItem("3", AppSettings::PCAddr_3);
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->addItem("4", AppSettings::PCAddr_4);
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->addItem("11", AppSettings::PCAddr_11);
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->addItem("12", AppSettings::PCAddr_12);
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->addItem("13", AppSettings::PCAddr_13);
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->addItem("14", AppSettings::PCAddr_14);

	//【标签】
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane1_Label1, QFont(MainwindowParameter.System_Font_Id, 11));	// 机型
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane1_Label3, QFont(MainwindowParameter.System_Font_Id, 11));	// PC地址
	// 【复选框】
	FlatUI::Instance()->setCheckBoxQss(MainPage2_ui->Page2_Pane1_NotWaitIdleFrames_checkBox, QFont(MainwindowParameter.System_Font_Id, 11));	// 不等待空闲帧
	// 【按键】
	MainPage2_ui->Page2_Pane1_DefaultValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 缺省值
	MainPage2_ui->Page2_Pane1_Apply_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 应用

	/*控制PID*/
	// 【标题框】
	MainPage2_ui->Page2_Pane2->setTitleHeight(15);
	MainPage2_ui->Page2_Pane2->setTitleText("控制PID");
	MainPage2_ui->Page2_Pane2->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	// 按键
	MainPage2_ui->Page2_Pane2_GetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 读取
	MainPage2_ui->Page2_Pane2_SetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 设置

	/*横滚*/
	// 【标题框】
	MainPage2_ui->Page2_Pane2_1->setTitleHeight(15);
	MainPage2_ui->Page2_Pane2_1->setTitleText("横滚");
	MainPage2_ui->Page2_Pane2_1->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	// 【标签】
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane2_1_label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#d999c3");	// KP
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane2_1_label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#d999c3");	// KI
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane2_1_label3, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#d999c3");	// KD
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane2_1_KP_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// KP
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane2_1_KI_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// KI
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane2_1_KD_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// KD

	this->MainPage2_ui->Page2_Pane2_1_KP_lineEdit->setValidator(validator_1);
	this->MainPage2_ui->Page2_Pane2_1_KI_lineEdit->setValidator(validator_1);
	this->MainPage2_ui->Page2_Pane2_1_KD_lineEdit->setValidator(validator_1);

	/*俯仰*/
	// 【标题框】
	MainPage2_ui->Page2_Pane2_2->setTitleHeight(15);
	MainPage2_ui->Page2_Pane2_2->setTitleText("俯仰");
	MainPage2_ui->Page2_Pane2_2->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	// 【标签】
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane2_2_label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#e19344");	// KP
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane2_2_label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#e19344");	// KI
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane2_2_label3, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#e19344");	// KD
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane2_2_KP_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// KP
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane2_2_KI_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// KI
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane2_2_KD_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// KD

	this->MainPage2_ui->Page2_Pane2_2_KP_lineEdit->setValidator(validator_1);
	this->MainPage2_ui->Page2_Pane2_2_KI_lineEdit->setValidator(validator_1);
	this->MainPage2_ui->Page2_Pane2_2_KD_lineEdit->setValidator(validator_1);

	/*航向*/
	// 【标题框】
	MainPage2_ui->Page2_Pane2_3->setTitleHeight(15);
	MainPage2_ui->Page2_Pane2_3->setTitleText("航向");
	MainPage2_ui->Page2_Pane2_3->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	// 【标签】
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane2_3_label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#227689");	// KP
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane2_3_label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#227689");	// KI
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane2_3_label3, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#227689");	// KD
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane2_3_KP_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// KP
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane2_3_KI_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// KI
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane2_3_KD_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// KD

	this->MainPage2_ui->Page2_Pane2_3_KP_lineEdit->setValidator(validator_1);
	this->MainPage2_ui->Page2_Pane2_3_KI_lineEdit->setValidator(validator_1);
	this->MainPage2_ui->Page2_Pane2_3_KD_lineEdit->setValidator(validator_1);

	/*控制参数*/
	// 【标题框】
	MainPage2_ui->Page2_Pane3->setTitleHeight(15);
	MainPage2_ui->Page2_Pane3->setTitleText("控制参数");
	MainPage2_ui->Page2_Pane3->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	// 【复选框】
	FlatUI::Instance()->setCheckBoxQss(MainPage2_ui->Page2_Pane3_PitchStickReverse_checkBox, QFont(MainwindowParameter.System_Font_Id, 11));	// 俯仰摇杆反向
	FlatUI::Instance()->setCheckBoxQss(MainPage2_ui->Page2_Pane3_YawRockerReverse_checkBox, QFont(MainwindowParameter.System_Font_Id, 11));	// 航向摇杆反向
	// 【标签】
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane3_label1, QFont(MainwindowParameter.System_Font_Id, 11));	// 摇杆俯仰速度
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane3_label2, QFont(MainwindowParameter.System_Font_Id, 11));	// 摇杆航向速度
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane3_StickPitchSpeed_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 摇杆俯仰速度
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane3_StickYawSpeed_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 摇杆航向速度

	this->MainPage2_ui->Page2_Pane3_StickPitchSpeed_lineEdit->setValidator(validator_2);
	this->MainPage2_ui->Page2_Pane3_StickYawSpeed_lineEdit->setValidator(validator_2);

	// 【按键】
	MainPage2_ui->Page2_Pane3_DefaultValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 缺省
	MainPage2_ui->Page2_Pane3_SetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 设置
	MainPage2_ui->Page2_Pane3_GetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 读取

	/*跟随模式参数*/
	// 【标题框】
	MainPage2_ui->Page2_Pane4->setTitleHeight(15);
	MainPage2_ui->Page2_Pane4->setTitleText("跟随模式参数");
	MainPage2_ui->Page2_Pane4->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	// 【标签】
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane4_label1, QFont(MainwindowParameter.System_Font_Id, 11));	// 航向死区
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane4_label2, QFont(MainwindowParameter.System_Font_Id, 11));	// 俯仰死区
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane4_label3, QFont(MainwindowParameter.System_Font_Id, 11));	// 航向速度
	FlatUI::Instance()->setLabelQss(MainPage2_ui->Page2_Pane4_label4, QFont(MainwindowParameter.System_Font_Id, 11));	// 俯仰速度
	// 【按键】
	MainPage2_ui->Page2_Pane4_DefaultValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 缺省
	MainPage2_ui->Page2_Pane4_SetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 设置
	MainPage2_ui->Page2_Pane4_GetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 读取
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane4_YawDeadZone_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 航向死区
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane4_PitchDeadZone_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 俯仰死区	
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane4_YawSpeed_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 航向速度
	FlatUI::Instance()->setLineEditQss(MainPage2_ui->Page2_Pane4_PitchSpeed_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 俯仰速度	

	this->MainPage2_ui->Page2_Pane4_YawDeadZone_lineEdit->setValidator(validator_2);	// 实际需要限制0~60
	this->MainPage2_ui->Page2_Pane4_PitchDeadZone_lineEdit->setValidator(validator_2);
	this->MainPage2_ui->Page2_Pane4_YawSpeed_lineEdit->setValidator(validator_2);
	this->MainPage2_ui->Page2_Pane4_PitchSpeed_lineEdit->setValidator(validator_2);
}

void MainPage2::MainPage2_Connect_Handler()
{
	/*软件配置*/
	connect(MainPage2_ui->Page2_Pane1_DefaultValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage2::Slots_Page2_Pane1_DefaultValue_Btn_Clicked);
	connect(MainPage2_ui->Page2_Pane1_Apply_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage2::Slots_Page2_Pane1_Apply_Btn_Clicked);
	connect(MainPage2_ui->Page2_Pane1_Model_comboBox, &QComboBox::currentIndexChanged, this, &MainPage2::Slots_Page2_Pane1_Model_comboBox_currentlndexChanged);
	connect(MainPage2_ui->Page2_Pane1_PCAddr_comboBox, &QComboBox::currentIndexChanged, this, &MainPage2::Slots_Page2_Pane1_PCAddr_comboBox_currentlndexChanged);
	connect(MainPage2_ui->Page2_Pane1_NotWaitIdleFrames_checkBox, &QCheckBox::stateChanged, this, &MainPage2::Slots_Page2_Pane1_NotWaitIdleFrames_checkBox_StateChanged);
	/*控制PID*/
	connect(MainPage2_ui->Page2_Pane2_GetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage2::Slots_Page2_Pane2_GetValue_Btn_Clicked);
	connect(MainPage2_ui->Page2_Pane2_SetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage2::Slots_Page2_Pane2_SetValue_Btn_Clicked);
	/*控制参数*/
	connect(MainPage2_ui->Page2_Pane3_DefaultValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage2::Slots_Page2_Pane3_DefaultValue_Btn_Clicked);
	connect(MainPage2_ui->Page2_Pane3_SetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage2::Slots_Page2_Pane3_SetValue_Btn_Clicked);
	connect(MainPage2_ui->Page2_Pane3_GetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage2::Slots_Page2_Pane3_GetValue_Btn_Clicked);
	connect(MainPage2_ui->Page2_Pane3_PitchStickReverse_checkBox, &QCheckBox::stateChanged, this, &MainPage2::Slots_Page2_Pane3_PitchStickReverse_checkBox_StateChanged);
	connect(MainPage2_ui->Page2_Pane3_YawRockerReverse_checkBox, &QCheckBox::stateChanged, this, &MainPage2::Slots_Page2_Pane3_YawRockerReverse_checkBox_StateChanged);
	/*跟随模式参数*/
	connect(MainPage2_ui->Page2_Pane4_DefaultValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage2::Slots_Page2_Pane4_DefaultValue_Btn_Clicked);
	connect(MainPage2_ui->Page2_Pane4_SetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage2::Slots_Page2_Pane4_SetValue_Btn_Clicked);
	connect(MainPage2_ui->Page2_Pane4_GetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage2::Slots_Page2_Pane4_GetValue_Btn_Clicked);
}

void MainPage2::Slots_Page2_Pane1_DefaultValue_Btn_Clicked()
{
	auto current = MainPage2_ui->Page2_Pane1_Model_comboBox->currentIndex();	// 获取当前机型类型下标
	auto current_data = MainPage2_ui->Page2_Pane1_Model_comboBox->itemData(current).value<AppSettings::Model_et>();	// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDeviceDefault(current_data);	// 根据选择机型设置对应缺省值
	// 通过对应绑定数据找出对应下标
	auto model_index = MainPage2_ui->Page2_Pane1_Model_comboBox->findData(static_cast<int>(AppSettings::Instance()->getDeviceModel()));	// 机型
	auto pcAddr_index = MainPage2_ui->Page2_Pane1_PCAddr_comboBox->findData(static_cast<int>(AppSettings::Instance()->getDevicePCAddr()));	// PC地址
	auto baund_index = MainPage2_ui->Top_SerialBaund_comboBox->findData(static_cast<int>(AppSettings::Instance()->getDeviceBaund()));	// 波特率
	auto dataBit_index = MainPage2_ui->Page5_SerialDataBit_comboBox->findData(static_cast<int>(AppSettings::Instance()->getDeviceDataBit()));	// 数据位
	auto stopBit_index = MainPage2_ui->Page5_SerialStopBit_comboBox->findData(static_cast<int>(AppSettings::Instance()->getDeviceStopBit()));	// 停止位
	auto checkBit_index = MainPage2_ui->Page5_SerialCheckBit_comboBox->findData(static_cast<int>(AppSettings::Instance()->getDeviceCheckBit()));	// 校验位
	auto waitIdleFrame_status = static_cast<Qt::CheckState>(AppSettings::Instance()->getDeviceWaitIdleFrame());	// 是否等待空闲帧

	// 更新控件显示
	MainPage2_ui->Page2_Pane1_Model_comboBox->setCurrentIndex(model_index);
	MainPage2_ui->Page2_Pane1_PCAddr_comboBox->setCurrentIndex(pcAddr_index);
	MainPage2_ui->Top_SerialBaund_comboBox->setCurrentIndex(baund_index);
	MainPage2_ui->Page5_SerialDataBit_comboBox->setCurrentIndex(dataBit_index);
	MainPage2_ui->Page5_SerialStopBit_comboBox->setCurrentIndex(stopBit_index);
	MainPage2_ui->Page5_SerialCheckBit_comboBox->setCurrentIndex(checkBit_index);
	MainPage2_ui->Page2_Pane1_NotWaitIdleFrames_checkBox->setCheckState(waitIdleFrame_status);
}

void MainPage2::Slots_Page2_Pane1_Apply_Btn_Clicked()
{
	/*机型下拉框数据*/
	auto model_current = MainPage2_ui->Page2_Pane1_Model_comboBox->currentIndex();	// 获取当前选中的下标
	auto model_current_data = MainPage2_ui->Page2_Pane1_Model_comboBox->itemData(model_current).value<AppSettings::Model_et>();	// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDeviceModel(model_current_data);
	/*PC地址下拉框数据*/
	auto pcAddr_current = MainPage2_ui->Page2_Pane1_PCAddr_comboBox->currentIndex();	// 获取当前选中的下标
	auto pcAddr_current_data = MainPage2_ui->Page2_Pane1_PCAddr_comboBox->itemData(pcAddr_current).value<AppSettings::PCAddr_et>();	// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDevicePCAddr(pcAddr_current_data);
	/*波特率下拉框数据*/
	auto baund_current = MainPage2_ui->Top_SerialBaund_comboBox->currentIndex();	// 获取当前选中的下标
	auto baund_current_data = MainPage2_ui->Top_SerialBaund_comboBox->itemData(baund_current).value<AppSettings::SerialBaund_et>();	// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDeviceBaund(baund_current_data);
	/*数据位下拉框数据*/
	auto dataBit_current = MainPage2_ui->Page5_SerialDataBit_comboBox->currentIndex();	// 获取当前选中的下标
	auto dataBit_current_data = MainPage2_ui->Page5_SerialDataBit_comboBox->itemData(dataBit_current).value<AppSettings::SerialDataBit_et>();	// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDeviceDataBit(dataBit_current_data);
	/*停止位下拉框数据*/
	auto stopBit_current = MainPage2_ui->Page5_SerialStopBit_comboBox->currentIndex();	// 获取当前选中的下标
	auto stopBit_current_data = MainPage2_ui->Page5_SerialStopBit_comboBox->itemData(stopBit_current).value<AppSettings::SerialStopBit_et>();	// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDeviceStopBit(stopBit_current_data);
	/*校验位下拉框数据*/
	auto checkBit_current = MainPage2_ui->Page5_SerialCheckBit_comboBox->currentIndex();	// 获取当前选中的下标
	auto checkBit_current_data = MainPage2_ui->Page5_SerialCheckBit_comboBox->itemData(checkBit_current).value<AppSettings::SerialCheckBit_et>();	// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDeviceCheckBit(checkBit_current_data);
	/*是否不等待空闲帧勾选*/
	auto waitIdleFrame_status = MainPage2_ui->Page2_Pane1_NotWaitIdleFrames_checkBox->checkState();	// 查询当前是否勾选
	AppSettings::Instance()->setDeviceWaitIdleFrame(static_cast<AppSettings::StatusCheckBox_et>(waitIdleFrame_status));	// 静态类型转换然后设置

#if QT_MainPage2_Debug
	qDebug() << "当前机型:" << AppSettings::Instance()->getDeviceModel() << Qt::endl;
	qDebug() << "当前PC地址:" << AppSettings::Instance()->getDevicePCAddr() << Qt::endl;
	qDebug() << "当前数据位:" << AppSettings::Instance()->getDeviceDataBit() << Qt::endl;
	qDebug() << "当前停止位:" << AppSettings::Instance()->getDeviceStopBit() << Qt::endl;
	qDebug() << "当前校验位:" << AppSettings::Instance()->getDeviceCheckBit() << Qt::endl;
	qDebug() << "当前波特率:" << AppSettings::Instance()->getDeviceBaund() << Qt::endl;
	qDebug() << "当前是否不等待空闲:" << AppSettings::Instance()->getDeviceWaitIdleFrame() << Qt::endl;
#endif
}

void MainPage2::Slots_Page2_Pane1_Model_comboBox_currentlndexChanged(int index)
{
}

void MainPage2::Slots_Page2_Pane1_PCAddr_comboBox_currentlndexChanged(int index)
{
}

void MainPage2::Slots_Page2_Pane1_NotWaitIdleFrames_checkBox_StateChanged(int status)
{
}

void MainPage2::Slots_Page2_Pane2_GetValue_Btn_Clicked()
{
	emit Signals_Page2_Pane2_GetValue_Btn_Clicked();
	//qDebug() << "控制PID - 读取";
}

void MainPage2::Slots_Page2_Pane2_SetValue_Btn_Clicked()
{
	emit Signals_Page2_Pane2_SetValue_Btn_Clicked();
	//qDebug() << "控制PID - 设置";
}

void MainPage2::Slots_Page2_Pane3_DefaultValue_Btn_Clicked()
{
	emit Signals_Page2_Pane3_DefaultValue_Btn_Clicked();
	//qDebug() << "控制参数-缺省";
}

void MainPage2::Slots_Page2_Pane3_SetValue_Btn_Clicked()
{
	emit Signals_Page2_Pane3_SetValue_Btn_Clicked();
	//qDebug() << "控制参数-设置";
}

void MainPage2::Slots_Page2_Pane3_GetValue_Btn_Clicked()
{
	emit Signals_Page2_Pane3_GetValue_Btn_Clicked();
	//qDebug() << "控制参数-获取";
}

void MainPage2::Slots_Page2_Pane3_PitchStickReverse_checkBox_StateChanged(int status)
{
	//qDebug() << status;
}

void MainPage2::Slots_Page2_Pane3_YawRockerReverse_checkBox_StateChanged(int status)
{
	//qDebug() << status;
}

void MainPage2::Slots_Page2_Pane4_DefaultValue_Btn_Clicked()
{
	emit Signals_Page2_Pane4_DefaultValue_Btn_Clicked();
	//qDebug() << "跟随参数 - 缺省";
}

void MainPage2::Slots_Page2_Pane4_SetValue_Btn_Clicked()
{
	emit Signals_Page2_Pane4_SetValue_Btn_Clicked();
	//qDebug() << "跟随参数 - 设置";
}

void MainPage2::Slots_Page2_Pane4_GetValue_Btn_Clicked()
{
	emit Signals_Page2_Pane4_GetValue_Btn_Clicked();
	//qDebug() << "跟随参数 - 获取";
}
