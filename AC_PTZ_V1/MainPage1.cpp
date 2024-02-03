#include "MainPage1.h"



MainPage1::MainPage1(QWidget* parent)
    : QWidget(parent)
{
    MainPage1_ui = nullptr;
}

MainPage1::~MainPage1()
{
#if QT_MainPage1_Debug
    qDebug() << "delete MainPage1";
#endif
}

void MainPage1::MainPage1_Init()
{
    QValidator* validator_1 = PublicClass::getValidator(PublicClass::Re_Burden9999P00To9999);    // 限制
    QValidator* validator_2 = PublicClass::getValidator(PublicClass::Re_Burden100P00To100);    // 限制
    QValidator* validator_3 = PublicClass::getValidator(PublicClass::Re_Burden30P00To30);    // 限制
    QValidator* validator_4 = PublicClass::getValidator(PublicClass::Re_0To65535);    // 限制
    QValidator* validator_5 = PublicClass::getValidator(PublicClass::Re_Burden99999To99999);    // 限制
    QValidator* validator_6 = PublicClass::getValidator(PublicClass::Re_ThreeNumRanggeBurden99999To99999);    // 限制
    QValidator* validator_7 = PublicClass::getValidator(PublicClass::Re_ValidCharactersRegex);    // 限制

    /*运动速度幅值*/
    // 标题框
    MainPage1_ui->Page1_Pane1->setTitleHeight(15);
    MainPage1_ui->Page1_Pane1->setTitleText("运动速度幅值");
    MainPage1_ui->Page1_Pane1->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane1_Pitch_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 俯仰
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane1_Roll_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 横滚
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane1_Yaw_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 航向
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane1_Label1, QFont(MainwindowParameter.System_Font_Id, 11));
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane1_Label2, QFont(MainwindowParameter.System_Font_Id, 11));
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane1_Label3, QFont(MainwindowParameter.System_Font_Id, 11));

    /*姿态角*/
    // 标题框
    MainPage1_ui->Page1_Pane2->setTitleHeight(15);
    MainPage1_ui->Page1_Pane2->setTitleText("姿态角");
    MainPage1_ui->Page1_Pane2->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane2_Pitch_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 俯仰
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane2_Roll_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 横滚
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane2_Yaw_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 航向
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane2_Label1, QFont(MainwindowParameter.System_Font_Id, 11));
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane2_Label2, QFont(MainwindowParameter.System_Font_Id, 11));
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane2_Label3, QFont(MainwindowParameter.System_Font_Id, 11));

    /*电机位置*/
    // 标题框
    MainPage1_ui->Page1_Pane3->setTitleHeight(15);
    MainPage1_ui->Page1_Pane3->setTitleText("电机位置");
    MainPage1_ui->Page1_Pane3->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane3_Pitch_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 俯仰
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane3_Roll_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 横滚
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane3_Yaw_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 航向
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane3_Label1, QFont(MainwindowParameter.System_Font_Id, 11));
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane3_Label2, QFont(MainwindowParameter.System_Font_Id, 11));
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane3_Label3, QFont(MainwindowParameter.System_Font_Id, 11));

    /*目标姿态*/
    // 标题框
    MainPage1_ui->Page1_Pane4->setTitleHeight(15);
    MainPage1_ui->Page1_Pane4->setTitleText("目标姿态");
    MainPage1_ui->Page1_Pane4->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane4_Pitch_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 俯仰
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane4_Roll_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 横滚
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane4_Yaw_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 航向
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane4_Label1, QFont(MainwindowParameter.System_Font_Id, 11));
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane4_Label2, QFont(MainwindowParameter.System_Font_Id, 11));
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane4_Label3, QFont(MainwindowParameter.System_Font_Id, 11));
    /*模式设置*/
    // 标题框
    MainPage1_ui->Page1_Pane5->setTitleHeight(15);
    MainPage1_ui->Page1_Pane5->setTitleText("模式设置");
    MainPage1_ui->Page1_Pane5->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 单选框
    FlatUI::Instance()->setRadioButtonQss(MainPage1_ui->Page1_Pane5_NormalMode_radioBtn, QFont(MainwindowParameter.System_Font_Id, 10), 8, "#D7DBDE", "#34495E");
    FlatUI::Instance()->setRadioButtonQss(MainPage1_ui->Page1_Pane5_CalibrationMode_radioBtn, QFont(MainwindowParameter.System_Font_Id, 10), 8, "#D7DBDE", "#1ABC9C");
    FlatUI::Instance()->setRadioButtonQss(MainPage1_ui->Page1_Pane5_StaticCalibrationMode_radioBtn, QFont(MainwindowParameter.System_Font_Id, 10), 8, "#D7DBDE", "#3498DB");
    FlatUI::Instance()->setRadioButtonQss(MainPage1_ui->Page1_Pane5_MotorLockMode_radioBtn, QFont(MainwindowParameter.System_Font_Id, 10), 8, "#D7DBDE", "#E74C3C");

    /*云台校准*/
    // 标题框
    MainPage1_ui->Page1_Pane6->setTitleHeight(15);
    MainPage1_ui->Page1_Pane6->setTitleText("云台校准");
    MainPage1_ui->Page1_Pane6->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 按钮
    MainPage1_ui->Page1_Pane6_MotorCalibration_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 电机校准
    MainPage1_ui->Page1_Pane6_AttitudeCalibration_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 姿态校准
    MainPage1_ui->Page1_Pane6_GyroCalibration_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// GYRO校准
    MainPage1_ui->Page1_Pane6__SixNextStep_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 六面下一步
    MainPage1_ui->Page1_Pane6_SixCalibration_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 六面校准
    MainPage1_ui->Page1_Pane6_WaveRecordRead_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 录波读取
    MainPage1_ui->Page1_Pane6_IdentifySamples_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 辨识采样
    MainPage1_ui->Page1_Pane6_ReadRecognition_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 读取识别
    MainPage1_ui->Page1_Pane6_Inception_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 盗梦空间
    MainPage1_ui->Page1_Pane6_TrackStart_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 轨迹开始
    MainPage1_ui->Page1_Pane6_TrackExecute_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 轨迹执行
    MainPage1_ui->Page1_Pane6_TrackExit_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 轨迹退出
    MainPage1_ui->Page1_Pane6_Sound_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// 声音
    MainPage1_ui->Page1_Pane6_DM1Start_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// DM1启
    MainPage1_ui->Page1_Pane6_DM1Execute_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// DM1执行
    MainPage1_ui->Page1_Pane6_DM1Exit_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 25);	// DM1退
    MainPage1_ui->Page1_Pane6_ReadUD_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 15);	// 读UD
    MainPage1_ui->Page1_Pane6_WriteUD_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 12), 15);	// 写UD
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane6_Label1, QFont(MainwindowParameter.System_Font_Id, 11));	// 轨迹点
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane6_Label2, QFont(MainwindowParameter.System_Font_Id, 11));	// 秒
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane6_TrackPoint_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 轨迹点
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane6_Sec_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 秒
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane6_SoundPoint_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 声音点
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane6_UD_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// UD

    this->MainPage1_ui->Page1_Pane6_Sec_lineEdit->setValidator(validator_4);
    this->MainPage1_ui->Page1_Pane6_UD_lineEdit->setValidator(validator_5); // 正常是限制为 -32768 ~ 32768
    this->MainPage1_ui->Page1_Pane6_SoundPoint_lineEdit->setValidator(validator_6); // 正常是限制为 xxx,xxx,xxx (xxx范围: -99999~99999)
    this->MainPage1_ui->Page1_Pane6_TrackPoint_lineEdit->setValidator(validator_7);

    /*命令*/
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#00cdac");	// 命令
    // 按键
    FlatUI::Instance()->setPushButtonQss(MainPage1_ui->Page1_OftenUse_Btn, QFont(MainwindowParameter.System_Font_Id, 10), 5, 8, "#E74C3C", "#000000", "#EC7064", "#000000", "#DC2D1A", "#F5A996");	// 常用命令
    MainPage1_ui->Page1_OrderSend_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 发送
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_OrderInput_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 命令

    /*电机测试-力矩*/
    // 标题框
    MainPage1_ui->Page1_Pane7->setTitleHeight(15);
    MainPage1_ui->Page1_Pane7->setTitleText("电机测试 - 力矩");
    MainPage1_ui->Page1_Pane7->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane7_Label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 俯仰
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane7_Label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 横滚
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane7_Label3, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 航向
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane7_Pitch_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 俯仰
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane7_Roll_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 横滚
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane7_Yaw_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 航向

    this->MainPage1_ui->Page1_Pane7_Pitch_lineEdit->setValidator(validator_1);
    this->MainPage1_ui->Page1_Pane7_Roll_lineEdit->setValidator(validator_1);
    this->MainPage1_ui->Page1_Pane7_Yaw_lineEdit->setValidator(validator_1);
    

    // 按键
    MainPage1_ui->Page1_Pane7_SetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 设置
    // 复选框
    FlatUI::Instance()->setCheckBoxQss(MainPage1_ui->Page1_Pane7_CloseTorque_checkBox, QFont(MainwindowParameter.System_Font_Id, 11));	// 关闭力矩

    /*电机测试-姿态*/
    // 标题框
    MainPage1_ui->Page1_Pane8->setTitleHeight(15);
    MainPage1_ui->Page1_Pane8->setTitleText("电机测试 - 姿态");
    MainPage1_ui->Page1_Pane8->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane8_Label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 俯仰
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane8_Label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 横滚
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane8_Label3, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 航向
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane8_Pitch_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 俯仰
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane8_Roll_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 横滚
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane8_Yaw_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 航向

    this->MainPage1_ui->Page1_Pane8_Pitch_lineEdit->setValidator(validator_1);
    this->MainPage1_ui->Page1_Pane8_Roll_lineEdit->setValidator(validator_1);
    this->MainPage1_ui->Page1_Pane8_Yaw_lineEdit->setValidator(validator_1);

    // 按键
    MainPage1_ui->Page1_Pane8_SetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 设置

    /*匀速运动-速度*/
    // 标题框
    MainPage1_ui->Page1_Pane9->setTitleHeight(15);
    MainPage1_ui->Page1_Pane9->setTitleText("匀速运动 - 速度");
    MainPage1_ui->Page1_Pane9->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane9_Label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 俯仰
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane9_Label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 横滚
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane9_Label3, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 航向
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane9_Pitch_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 俯仰
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane9_Roll_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 横滚
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane9_Yaw_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 航向

    this->MainPage1_ui->Page1_Pane9_Pitch_lineEdit->setValidator(validator_1);
    this->MainPage1_ui->Page1_Pane9_Roll_lineEdit->setValidator(validator_1);
    this->MainPage1_ui->Page1_Pane9_Yaw_lineEdit->setValidator(validator_1);

    // 按键
    MainPage1_ui->Page1_Pane9_SetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 设置
    MainPage1_ui->Page1_Pane9_GetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 查询

    /*电机零位置-微调*/
    // 标题框
    MainPage1_ui->Page1_Pane10->setTitleHeight(15);
    MainPage1_ui->Page1_Pane10->setTitleText("电机零位置 - 微调");
    MainPage1_ui->Page1_Pane10->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane10_Label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 俯仰
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane10_Label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 航向
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane10_Pitch_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 俯仰
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane10_Yaw_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 航向

    this->MainPage1_ui->Page1_Pane10_Pitch_lineEdit->setValidator(validator_3);
    this->MainPage1_ui->Page1_Pane10_Yaw_lineEdit->setValidator(validator_3);

    // 按键
    MainPage1_ui->Page1_Pane10_SetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 设置
    MainPage1_ui->Page1_Pane10_GetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 读取

    /*姿态微调*/
    // 标题框
    MainPage1_ui->Page1_Pane11->setTitleHeight(15);
    MainPage1_ui->Page1_Pane11->setTitleText("姿态微调");
    MainPage1_ui->Page1_Pane11->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane11_Label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 俯仰
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_Pane11_Label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#cecc3d");	// 横滚
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane11_Pitch_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 俯仰
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_Pane11_Roll_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 横滚

    this->MainPage1_ui->Page1_Pane11_Pitch_lineEdit->setValidator(validator_2);
    this->MainPage1_ui->Page1_Pane11_Roll_lineEdit->setValidator(validator_2);

    // 按键
    MainPage1_ui->Page1_Pane11_SetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 设置
    MainPage1_ui->Page1_Pane11_GetValue_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 读取

    /*测试命令*/
    // 标题框
    MainPage1_ui->Page1_Pane12->setTitleHeight(15);
    MainPage1_ui->Page1_Pane12->setTitleText("测试命令");
    MainPage1_ui->Page1_Pane12->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
    // 按键
    MainPage1_ui->Page1_Pane12_ShutDown_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 关机
    MainPage1_ui->Page1_Pane12_Restart_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 重启
    MainPage1_ui->Page1_Pane12_Selfie_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 自拍
    MainPage1_ui->Page1_Pane12_ReturnCenter_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 回中
    MainPage1_ui->Page1_Pane12_HVSwitch_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// HV切换
    MainPage1_ui->Page1_Pane12_LeftControl_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 左控
    MainPage1_ui->Page1_Pane12_NotControl_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 无控
    MainPage1_ui->Page1_Pane12_RightControl_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 右控
    MainPage1_ui->Page1_Pane12_QuickFollow_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 快速跟随
    MainPage1_ui->Page1_Pane12_QuickFollowExit_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 退出快速跟随
    MainPage1_ui->Page1_Pane12_RollLedOn_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 横滚灯亮
    MainPage1_ui->Page1_Pane12_RollLedOff_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 横滚灯灭
    MainPage1_ui->Page1_Pane12_CalibrationClear_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 校准清除
    MainPage1_ui->Page1_Pane12_ReadHall_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 读霍尔
    MainPage1_ui->Page1_Pane12_ReadHandlePlate_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 读手柄板
    MainPage1_ui->Page1_Pane12_StartPanorama_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 开始全景
    MainPage1_ui->Page1_Pane12_ExecutePanorama_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 执行全景
    MainPage1_ui->Page1_Pane12_ExitPanorama_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 11), 15, "#c7c5eb", "#000000", "#659be1", "#000000", "#0ea2bb", "#000000");	// 退出全景

    /*其他*/
    // 标签
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#FFD700");	// 设备运行时间
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_label3, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#FFD700");	// 收包/解包数
    FlatUI::Instance()->setLabelQss(MainPage1_ui->Page1_label4, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#FFD700");	// 丢包率
    // 单行输入框
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_DeviceRunTime_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10), 5, 2, "#DCE4EC", "#1ABC9C");	// 设备运行时间
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_RecPackParsePack_lineEdit, QFont(MainwindowParameter.System_Font_Id, 8), 5, 2, "#DCE4EC", "#1ABC9C");	// 收包/解包数
    FlatUI::Instance()->setLineEditQss(MainPage1_ui->Page1_PacketLossRate_lineEdit, QFont(MainwindowParameter.System_Font_Id, 8), 5, 2, "#DCE4EC", "#1ABC9C");	// 丢包率
}

void MainPage1::MainPage1_Connect_Handler()
{
    /*模式设置*/
    connect(MainPage1_ui->Page1_Pane5_NormalMode_radioBtn, &QRadioButton::clicked, this ,&MainPage1::Slots_Page1_Pane5_NormalMode_radioBtn_Clicked);
    connect(MainPage1_ui->Page1_Pane5_CalibrationMode_radioBtn, &QRadioButton::clicked, this, &MainPage1::Slots_Page1_Pane5_CalibrationMode_radioBtn_Clicked);
    connect(MainPage1_ui->Page1_Pane5_MotorLockMode_radioBtn, &QRadioButton::clicked, this, &MainPage1::Slots_Page1_Pane5_MotorLockMode_radioBtn_Clicked);
    connect(MainPage1_ui->Page1_Pane5_StaticCalibrationMode_radioBtn, &QRadioButton::clicked, this, &MainPage1::Slots_Page1_Pane5_StaticCalibrationMode_radioBtn_Clicked);

    /*云台校准*/
    connect(MainPage1_ui->Page1_Pane6_MotorCalibration_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_MotorCalibration_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_AttitudeCalibration_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_AttitudeCalibration_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_GyroCalibration_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_GyroCalibration_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6__SixNextStep_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6__SixNextStep_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_SixCalibration_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_SixCalibration_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_WaveRecordRead_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_WaveRecordRead_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_IdentifySamples_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_IdentifySamples_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_ReadRecognition_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_ReadRecognition_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_Inception_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_Inception_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_TrackStart_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_TrackStart_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_TrackExecute_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_TrackExecute_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_TrackExit_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_TrackExit_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_Sound_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_Sound_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_DM1Start_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_DM1Start_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_DM1Execute_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_DM1Execute_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_DM1Exit_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_DM1Exit_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_ReadUD_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_ReadUD_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane6_WriteUD_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane6_WriteUD_Btn_Clicked);

    /*电机测试 - 力矩*/
    connect(MainPage1_ui->Page1_Pane7_CloseTorque_checkBox, &QCheckBox::stateChanged, this, &MainPage1::Slots_Page1_Pane7_CloseTorque_checkBox_StateChanged);
    connect(MainPage1_ui->Page1_Pane7_SetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane7_SetValue_Btn_Clicked);

    /*电机测试 - 状态*/
    connect(MainPage1_ui->Page1_Pane8_SetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane8_SetValue_Btn_Clicked);

    /*姿态微调*/
    connect(MainPage1_ui->Page1_Pane11_GetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane11_GetValue_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane11_SetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane11_SetValue_Btn_Clicked);

    /*匀速运动－速度*/
    connect(MainPage1_ui->Page1_Pane9_GetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane9_GetValue_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane9_SetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane9_SetValue_Btn_Clicked);

    /*电机零位置－微调*/
    connect(MainPage1_ui->Page1_Pane10_GetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane10_GetValue_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane10_SetValue_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane10_SetValue_Btn_Clicked);

    /*测试命令*/
    connect(MainPage1_ui->Page1_Pane12_ShutDown_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_ShutDown_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_Restart_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_Restart_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_Selfie_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_Selfie_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_ReturnCenter_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_ReturnCenter_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_HVSwitch_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_HVSwitch_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_LeftControl_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_LeftControl_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_NotControl_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_NotControl_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_RightControl_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_RightControl_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_QuickFollow_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_QuickFollow_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_QuickFollowExit_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_QuickFollowExit_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_RollLedOn_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_RollLedOn_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_RollLedOff_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_RollLedOff_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_CalibrationClear_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_CalibrationClear_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_ReadHall_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_ReadHall_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_ReadHandlePlate_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_ReadHandlePlate_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_StartPanorama_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_StartPanorama_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_ExecutePanorama_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_ExecutePanorama_Btn_Clicked);
    connect(MainPage1_ui->Page1_Pane12_ExitPanorama_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_Pane12_ExitPanorama_Btn_Clicked);

    /*常用命令*/
    connect(MainPage1_ui->Page1_OftenUse_Btn, &QPushButton::clicked, this, &MainPage1::Slots_Page1_OftenUse_Btn_Clicked);
    connect(MainPage1_ui->Page1_OrderSend_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage1::Slots_Page1_OrderSend_Btn_Clicked);
}

/*===================================== 槽函数实现 ==================================*/

void MainPage1::Slots_Page1_Pane5_NormalMode_radioBtn_Clicked()
{
    if (AppSettings::Instance()->getPTZMode() != AppSettings::PTZ_Mode_Normal)
    {
        AppSettings::Instance()->setPTZMode(AppSettings::PTZ_Mode_Normal);   // 设置为普通模式
        SaveLog::Instance()->UI_SendDebugMsg_DebugArea("green", "已切换至普通模式");
    }
}

void MainPage1::Slots_Page1_Pane5_CalibrationMode_radioBtn_Clicked()
{
    if (AppSettings::Instance()->getPTZMode() != AppSettings::PTZ_Mode_Calibration)
    {
        AppSettings::Instance()->setPTZMode(AppSettings::PTZ_Mode_Calibration);   // 设置为校准模式
        SaveLog::Instance()->UI_SendDebugMsg_DebugArea("green", "已切换至校准模式");
    }
}

void MainPage1::Slots_Page1_Pane5_MotorLockMode_radioBtn_Clicked()
{
    if (AppSettings::Instance()->getPTZMode() != AppSettings::PTZ_Mode_MotorLock)
    {
        AppSettings::Instance()->setPTZMode(AppSettings::PTZ_Mode_MotorLock);   // 设置为电机锁定模式
        SaveLog::Instance()->UI_SendDebugMsg_DebugArea("green", "已切换至电机锁定模式");
    }
}

void MainPage1::Slots_Page1_Pane5_StaticCalibrationMode_radioBtn_Clicked()
{
    if (AppSettings::Instance()->getPTZMode() != AppSettings::PTZ_Mode_StaticCalibration)
    {
        AppSettings::Instance()->setPTZMode(AppSettings::PTZ_Mode_StaticCalibration);   // 设置为静态校准模式
        SaveLog::Instance()->UI_SendDebugMsg_DebugArea("green", "已切换至静态校准模式");
    }
}

void MainPage1::Slots_Page1_Pane6_MotorCalibration_Btn_Clicked()
{
    emit Signals_Page1_Pane6_MotorCalibration_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "电机校准");
}

void MainPage1::Slots_Page1_Pane6_AttitudeCalibration_Btn_Clicked()
{
    emit Signals_Page1_Pane6_AttitudeCalibration_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "姿态校准");
}

void MainPage1::Slots_Page1_Pane6_GyroCalibration_Btn_Clicked()
{
    emit Signals_Page1_Pane6_GyroCalibration_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "GYRO校准");
}

void MainPage1::Slots_Page1_Pane6__SixNextStep_Btn_Clicked()
{
    emit Signals_Page1_Pane6__SixNextStep_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "六面下一步");
}

void MainPage1::Slots_Page1_Pane6_SixCalibration_Btn_Clicked()
{
    emit Signals_Page1_Pane6_SixCalibration_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "六面校准");
}

void MainPage1::Slots_Page1_Pane6_WaveRecordRead_Btn_Clicked()
{
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "录波读取");

    // 弹出文件选择对话框，获取选中的文件名
    // 当前类的对象指针  获取程序路径作为默认打开路径  文件过滤器指定只显示扩展名为bin的文件
    auto filename = QFileDialog::getOpenFileName(this, "打开文件", qApp->applicationDirPath(), QString::fromUtf8("采样 File(*.jd)"));

    // 判断文件为空则
    if (filename.isEmpty())
    {
        emit MainPage1_Signals_PromptMsg(MessageType::MESSAGE_TYPE_INFORMATION, QString("取消打开!"));
        return;
    }
    QFile file(filename);
    // 判断读取文件失败则
    if (!file.open(QFile::ReadOnly))
    {
        emit MainPage1_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("读取失败 %1: \n%2").arg(filename).arg(file.errorString()));
        return;
    }
    file.close();
}

void MainPage1::Slots_Page1_Pane6_IdentifySamples_Btn_Clicked()
{
    emit Signals_Page1_Pane6_IdentifySamples_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "辨识采样");
}

void MainPage1::Slots_Page1_Pane6_ReadRecognition_Btn_Clicked()
{
    emit Signals_Page1_Pane6_ReadRecognition_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "读取识别");
}

void MainPage1::Slots_Page1_Pane6_Inception_Btn_Clicked()
{
    emit Signals_Page1_Pane6_Inception_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "盗梦空间");
}

void MainPage1::Slots_Page1_Pane6_TrackStart_Btn_Clicked()
{
    emit Signals_Page1_Pane6_TrackStart_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "轨迹开始");
}

void MainPage1::Slots_Page1_Pane6_TrackExecute_Btn_Clicked()
{
    emit Signals_Page1_Pane6_TrackExecute_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "轨迹执行");
}

void MainPage1::Slots_Page1_Pane6_TrackExit_Btn_Clicked()
{
    emit Signals_Page1_Pane6_TrackExit_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "轨迹退出");
}

void MainPage1::Slots_Page1_Pane6_Sound_Btn_Clicked()
{
    emit Signals_Page1_Pane6_Sound_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "声音");
}

void MainPage1::Slots_Page1_Pane6_DM1Start_Btn_Clicked()
{
    emit Signals_Page1_Pane6_DM1Start_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "DM1启");
}

void MainPage1::Slots_Page1_Pane6_DM1Execute_Btn_Clicked()
{
    emit Signals_Page1_Pane6_DM1Execute_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "DM1执行");
}

void MainPage1::Slots_Page1_Pane6_DM1Exit_Btn_Clicked()
{
    emit Signals_Page1_Pane6_DM1Exit_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "DM1退");
}

void MainPage1::Slots_Page1_Pane6_ReadUD_Btn_Clicked()
{
    emit Signals_Page1_Pane6_ReadUD_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "读UD");
}

void MainPage1::Slots_Page1_Pane6_WriteUD_Btn_Clicked()
{
    emit Signals_Page1_Pane6_WriteUD_Btn_Clicked();
    //SaveLog::Instance()->UI_SendDebugMsg_DebugArea("black", "写UD");
}

void MainPage1::Slots_Page1_Pane7_CloseTorque_checkBox_StateChanged(int status)
{
    // 关闭力矩
    
    if (status == AppSettings::Status_Enable)
    {
        MainPage1_ui->Page1_Pane7_Pitch_lineEdit->setText("-1");
        MainPage1_ui->Page1_Pane7_Roll_lineEdit->setText("-1");
        MainPage1_ui->Page1_Pane7_Yaw_lineEdit->setText("-1");
    }
    else if (status == AppSettings::Status_Disable)
    {
        MainPage1_ui->Page1_Pane7_Pitch_lineEdit->setText("0");
        MainPage1_ui->Page1_Pane7_Roll_lineEdit->setText("0");
        MainPage1_ui->Page1_Pane7_Yaw_lineEdit->setText("0");
    }
}

void MainPage1::Slots_Page1_Pane7_SetValue_Btn_Clicked()
{
    // 电机测试-力矩
    qint16 pitch_toque, roll_toque, yaw_toque;
    bool ok;

    pitch_toque = MainPage1_ui->Page1_Pane7_Pitch_lineEdit->text().toInt(&ok, 10);
    roll_toque = MainPage1_ui->Page1_Pane7_Roll_lineEdit->text().toInt(&ok, 10);
    yaw_toque = MainPage1_ui->Page1_Pane7_Yaw_lineEdit->text().toInt(&ok, 10);
    
    if (false == ok)
    {
        emit MainPage1_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数错误!"));
    }
    else
    {
        emit Signals_Page1_Pane7_SetValue_Btn_Clicked(pitch_toque, roll_toque, yaw_toque);
    }
 
   // qDebug() << MainPage1_ui->Page1_Pane7_Pitch_lineEdit->text().toFloat() << " " << MainPage1_ui->Page1_Pane7_Roll_lineEdit->text().toFloat() << " " << MainPage1_ui->Page1_Pane7_Yaw_lineEdit->text().toFloat();
}

void MainPage1::Slots_Page1_Pane8_SetValue_Btn_Clicked()
{
    // 电机测试-姿态
    float pitch_attitude, roll_attitude, yaw_attitude;
    bool ok;

    pitch_attitude = MainPage1_ui->Page1_Pane8_Pitch_lineEdit->text().toFloat(&ok);
    roll_attitude = MainPage1_ui->Page1_Pane8_Roll_lineEdit->text().toFloat(&ok);
    yaw_attitude = MainPage1_ui->Page1_Pane8_Yaw_lineEdit->text().toFloat(&ok);

    if (false == ok)
    {
        emit MainPage1_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数错误!"));
    }
    else
    {
        emit Signals_Page1_Pane8_SetValue_Btn_Clicked(pitch_attitude, roll_attitude, yaw_attitude);
    }

   // qDebug() << MainPage1_ui->Page1_Pane8_Pitch_lineEdit->text().toFloat() << " " << MainPage1_ui->Page1_Pane8_Roll_lineEdit->text().toFloat() << " " << MainPage1_ui->Page1_Pane8_Yaw_lineEdit->text().toFloat();
}

void MainPage1::Slots_Page1_Pane11_GetValue_Btn_Clicked()
{
    /*姿态微调 - 获取*/
    emit Signals_Page1_Pane11_GetValue_Btn_Clicked();
}

void MainPage1::Slots_Page1_Pane11_SetValue_Btn_Clicked()
{
    /*姿态微调 - 设置*/
    float pitch_attitude, roll_attitude;
    bool ok;

    pitch_attitude = MainPage1_ui->Page1_Pane11_Pitch_lineEdit->text().toFloat(&ok);
    roll_attitude = MainPage1_ui->Page1_Pane11_Roll_lineEdit->text().toFloat(&ok);

    if (false == ok)
    {
        emit MainPage1_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数错误!"));
    }
    else
    {
        emit Signals_Page1_Pane11_SetValue_Btn_Clicked(pitch_attitude, roll_attitude);
    }

    //qDebug() << MainPage1_ui->Page1_Pane11_Pitch_lineEdit->text().toFloat() << " " << MainPage1_ui->Page1_Pane11_Roll_lineEdit->text().toFloat();
}

void MainPage1::Slots_Page1_Pane9_GetValue_Btn_Clicked()
{
    // 匀速运动 -  速度 查询
    emit Signals_Page1_Pane9_GetValue_Btn_Clicked();

    //qDebug() << MainPage1_ui->Page1_Pane9_Pitch_lineEdit->text().toFloat() << " " << MainPage1_ui->Page1_Pane9_Roll_lineEdit->text().toFloat() << " " << MainPage1_ui->Page1_Pane9_Yaw_lineEdit->text().toFloat();
}

void MainPage1::Slots_Page1_Pane9_SetValue_Btn_Clicked()
{
    // 匀速运动 - 速度 设置
    qint16 pitch, yaw;
    bool ok;

    pitch = MainPage1_ui->Page1_Pane9_Pitch_lineEdit->text().toInt(&ok);
    yaw = MainPage1_ui->Page1_Pane9_Yaw_lineEdit->text().toInt(&ok);

    if (false == ok)
    {
        emit MainPage1_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数错误!"));
    }
    else
    {
        emit Signals_Page1_Pane9_SetValue_Btn_Clicked(pitch, yaw);
    }
}

void MainPage1::Slots_Page1_Pane10_GetValue_Btn_Clicked()
{
    /*电机零位置 - 查询*/
    emit Signals_Page1_Pane10_GetValue_Btn_Clicked();

    //qDebug() << MainPage1_ui->Page1_Pane10_Pitch_lineEdit->text().toFloat() << " " << MainPage1_ui->Page1_Pane10_Yaw_lineEdit->text().toFloat();
}

void MainPage1::Slots_Page1_Pane10_SetValue_Btn_Clicked()
{
    /*电机零位置 - 设置*/
    float pitch, yaw;
    bool ok;

    pitch = MainPage1_ui->Page1_Pane10_Pitch_lineEdit->text().toFloat(&ok);
    yaw = MainPage1_ui->Page1_Pane10_Yaw_lineEdit->text().toFloat(&ok);

    if (false == ok)
    {
        emit MainPage1_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("参数错误!"));
    }
    else
    {
        emit Signals_Page1_Pane10_SetValue_Btn_Clicked(pitch, yaw);
    }
}

void MainPage1::Slots_Page1_Pane12_ShutDown_Btn_Clicked()
{
    emit Signals_Page1_Pane12_ShutDown_Btn_Clicked();
    //qDebug() << "关机";
}

void MainPage1::Slots_Page1_Pane12_Restart_Btn_Clicked()
{
    emit Signals_Page1_Pane12_Restart_Btn_Clicked();
    //qDebug() << "重启";
}

void MainPage1::Slots_Page1_Pane12_Selfie_Btn_Clicked()
{
    emit Signals_Page1_Pane12_Selfie_Btn_Clicked();
    //qDebug() << "自拍";
}

void MainPage1::Slots_Page1_Pane12_ReturnCenter_Btn_Clicked()
{
    emit Signals_Page1_Pane12_ReturnCenter_Btn_Clicked();
    //qDebug() << "回中";
}

void MainPage1::Slots_Page1_Pane12_HVSwitch_Btn_Clicked()
{
    emit Signals_Page1_Pane12_HVSwitch_Btn_Clicked();
    //qDebug() << "HV切换";
}

void MainPage1::Slots_Page1_Pane12_LeftControl_Btn_Clicked()
{
    emit Signals_Page1_Pane12_LeftControl_Btn_Clicked();
    //qDebug() << "左控";
}

void MainPage1::Slots_Page1_Pane12_NotControl_Btn_Clicked()
{
    emit Signals_Page1_Pane12_NotControl_Btn_Clicked();
    //qDebug() << "无控";
}

void MainPage1::Slots_Page1_Pane12_RightControl_Btn_Clicked()
{
    emit Signals_Page1_Pane12_RightControl_Btn_Clicked();
    //qDebug() << "右控";
}

void MainPage1::Slots_Page1_Pane12_QuickFollow_Btn_Clicked()
{
    emit Signals_Page1_Pane12_QuickFollow_Btn_Clicked();
    //qDebug() << "快速跟随";
}

void MainPage1::Slots_Page1_Pane12_QuickFollowExit_Btn_Clicked()
{
    emit Signals_Page1_Pane12_QuickFollowExit_Btn_Clicked();
    //qDebug() << "退出快速跟随";
}

void MainPage1::Slots_Page1_Pane12_RollLedOn_Btn_Clicked()
{
    emit Signals_Page1_Pane12_RollLedOn_Btn_Clicked();
    //qDebug() << "横滚灯亮";
}

void MainPage1::Slots_Page1_Pane12_RollLedOff_Btn_Clicked()
{
    emit Signals_Page1_Pane12_RollLedOff_Btn_Clicked();
    //qDebug() << "横滚灯灭";
}

void MainPage1::Slots_Page1_Pane12_CalibrationClear_Btn_Clicked()
{
    emit Signals_Page1_Pane12_CalibrationClear_Btn_Clicked();
    //qDebug() << "校准清除";
}

void MainPage1::Slots_Page1_Pane12_ReadHall_Btn_Clicked()
{
    emit Signals_Page1_Pane12_ReadHall_Btn_Clicked();
    //qDebug() << "读霍尔";
}

void MainPage1::Slots_Page1_Pane12_ReadHandlePlate_Btn_Clicked()
{
    emit Signals_Page1_Pane12_ReadHandlePlate_Btn_Clicked();
    //qDebug() << "读手柄";
}

void MainPage1::Slots_Page1_Pane12_StartPanorama_Btn_Clicked()
{
    emit Signals_Page1_Pane12_StartPanorama_Btn_Clicked();
    //qDebug() << "开始全景";
}

void MainPage1::Slots_Page1_Pane12_ExecutePanorama_Btn_Clicked()
{
    emit Signals_Page1_Pane12_ExecutePanorama_Btn_Clicked();
    //qDebug() << "执行全景";
}

void MainPage1::Slots_Page1_Pane12_ExitPanorama_Btn_Clicked()
{
    emit Signals_Page1_Pane12_ExitPanorama_Btn_Clicked();
    //qDebug() << "退出全景";
}

void MainPage1::Slots_Page1_OftenUse_Btn_Clicked()
{
    qDebug() << "test";
}

void MainPage1::Slots_Page1_OrderSend_Btn_Clicked()
{
    qDebug() << "test";
}

void MainPage1::Slots_Page1_RecPackParsePack_UiControl()
{
    MainPage1_ui->Page1_RecPackParsePack_lineEdit->setText(QString("%1/%2").arg(AppSettings::Instance()->RecPack_Count).arg(AppSettings::Instance()->ParsePack_Count));

    float pack_loss_rate = 0.000;
    pack_loss_rate = (float)(AppSettings::Instance()->RecPack_Count - AppSettings::Instance()->ParsePack_Count) / (float)AppSettings::Instance()->RecPack_Count * 100.0;

    MainPage1_ui->Page1_PacketLossRate_lineEdit->setText(QString::number(pack_loss_rate, 'f', 3).append(" %"));  // 保留4个小数
}

