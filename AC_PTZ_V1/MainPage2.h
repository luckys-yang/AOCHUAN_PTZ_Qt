#pragma once
#ifndef MAINPAGE2_H
#define MAINPAGE2_H
#include <QWidget>
#include "ui_Mainwindow.h"
#include "Mainwindow.h"
#include "FlatUI.h"
#include "AppSettings.h"
#include "SaveLog.h"
#include "HoverFillButton.h"
#include<QRegularexpression>	// 正则表达式
#include "PublicClass.h"

#define QT_MainPage2_Debug 1

class MainPage2  : public QWidget
{
	Q_OBJECT

public:
	MainPage2(QWidget *parent = nullptr);
	~MainPage2();
	// 页面初始化
	void MainPage2_Init();
	// 页面连接
	void MainPage2_Connect_Handler();

private slots:
	/*软件配置*/
	void Slots_Page2_Pane1_DefaultValue_Btn_Clicked();	// 缺省值【点击】
	void Slots_Page2_Pane1_Apply_Btn_Clicked();	// 应用【点击】
	void Slots_Page2_Pane1_Model_comboBox_currentlndexChanged(int index);	// 机型 【当前选项下标改变】
	void Slots_Page2_Pane1_PCAddr_comboBox_currentlndexChanged(int index);	// PC地址 【当前选项下标改变】
	void Slots_Page2_Pane1_NotWaitIdleFrames_checkBox_StateChanged(int status);	// 不等待空闲 【状态改变】
	/*控制PID*/
	void Slots_Page2_Pane2_GetValue_Btn_Clicked();	// 读取【点击】
	void Slots_Page2_Pane2_SetValue_Btn_Clicked();	// 设置【点击】
	/*控制参数*/
	void Slots_Page2_Pane3_DefaultValue_Btn_Clicked();	// 缺省【点击】
	void Slots_Page2_Pane3_SetValue_Btn_Clicked();	// 设置【点击】
	void Slots_Page2_Pane3_GetValue_Btn_Clicked();	// 读取【点击】
	void Slots_Page2_Pane3_PitchStickReverse_checkBox_StateChanged(int status);	// 俯仰摇杆反向 【状态改变】
	void Slots_Page2_Pane3_YawRockerReverse_checkBox_StateChanged(int status);	// 航向摇杆反向 【状态改变】
	/*跟随模式参数*/
	void Slots_Page2_Pane4_DefaultValue_Btn_Clicked();	// 缺省【点击】
	void Slots_Page2_Pane4_SetValue_Btn_Clicked();	// 设置【点击】
	void Slots_Page2_Pane4_GetValue_Btn_Clicked();	// 读取【点击】

signals:
	void Signals_Page2_Pane2_GetValue_Btn_Clicked();	// 控制PID - 读取
	void Signals_Page2_Pane2_SetValue_Btn_Clicked();	// 控制PID - 设置
	void Signals_Page2_Pane3_DefaultValue_Btn_Clicked();	// 控制参数 - 缺省
	void Signals_Page2_Pane3_SetValue_Btn_Clicked();	// 控制参数 - 设置
	void Signals_Page2_Pane3_GetValue_Btn_Clicked();	// 控制参数 - 获取
	void Signals_Page2_Pane4_DefaultValue_Btn_Clicked();	// 跟随参数 - 缺省
	void Signals_Page2_Pane4_SetValue_Btn_Clicked();	// 跟随参数 - 设置
	void Signals_Page2_Pane4_GetValue_Btn_Clicked();	// 跟随参数 - 获取

public:
	Ui::MainwindowClass* MainPage2_ui;	// ui指针

	/*读取与设置 控制PID 存储变量*/
	float Roll_KP;		// 横滚KP
	float Roll_KI;	// 横滚KI
	float Roll_KD;	// 横滚KD

	float Pitch_KP;		// 俯仰KP
	float Pitch_KI;	// 俯仰KI
	float Pitch_KD;	// 俯仰KD

	float Yaw_KP;		// 航向KP
	float Yaw_KI;	// 航向KI
	float Yaw_KD;	// 航向KD

	/*控制参数*/
	float StickPitchSpeed;	// 摇杆俯仰速度
	float StickYawSpeed;	// 摇杆航向速度
	AppSettings::StatusCheckBox_et PitchStickReverse_Status;	// 俯仰摇杆反向 勾选状态
	AppSettings::StatusCheckBox_et YawRockerReverse_Status;	// 航向摇杆反向 勾选状态

	/*跟随模式参数*/
	float YawDeadZone;	// 航向死区
	float PitchDeadZone;	// 俯仰死区
	float YawSpeed;	// 航向速度
	float PitchSpeed;	// 俯仰速度
};

#endif
