#pragma once
#ifndef MAINPAGE1_H
#define MAINPAGE1_H

#include <QWidget>
#include "ui_Mainwindow.h"
#include "Mainwindow.h"
#include "FlatUI.h"
#include "AppSettings.h"
#include "SaveLog.h"
#include "HoverFillButton.h"
#include<QRegularexpression>	// 正则表达式
#include "PublicClass.h"

#define QT_MainPage1_Debug 1

class MainPage1 : public QWidget
{
	Q_OBJECT
public:
	MainPage1(QWidget* parent = nullptr);
	~MainPage1();
	// 页面初始化
	void MainPage1_Init();
	// 页面连接
	void MainPage1_Connect_Handler();
public slots:
	/*其他*/
	void Slots_Page1_RecPackParsePack_UiControl();	// 收包/解包计数 ui更新
private slots:
	/*模式设置*/
	void Slots_Page1_Pane5_NormalMode_radioBtn_Clicked();	// 普通模式【点击】
	void Slots_Page1_Pane5_CalibrationMode_radioBtn_Clicked();	// 校准模式【点击】
	void Slots_Page1_Pane5_MotorLockMode_radioBtn_Clicked();	// 电机锁定模式【点击】
	void Slots_Page1_Pane5_StaticCalibrationMode_radioBtn_Clicked();	// 静态校准模式【点击】
	/*云台校准*/
	void Slots_Page1_Pane6_MotorCalibration_Btn_Clicked();	// 电机校准【点击】
	void Slots_Page1_Pane6_AttitudeCalibration_Btn_Clicked();	// 姿态校准【点击】
	void Slots_Page1_Pane6_GyroCalibration_Btn_Clicked();	// GYRO校准【点击】
	void Slots_Page1_Pane6__SixNextStep_Btn_Clicked();	// 六面下一步【点击】
	void Slots_Page1_Pane6_SixCalibration_Btn_Clicked();	// 六面校准【点击】
	void Slots_Page1_Pane6_WaveRecordRead_Btn_Clicked();	// 录波读取【点击】
	void Slots_Page1_Pane6_IdentifySamples_Btn_Clicked();	// 辨识采样【点击】
	void Slots_Page1_Pane6_ReadRecognition_Btn_Clicked();	// 读取识别【点击】
	void Slots_Page1_Pane6_Inception_Btn_Clicked();	// 盗梦空间【点击】
	void Slots_Page1_Pane6_TrackStart_Btn_Clicked();	// 轨迹开始【点击】
	void Slots_Page1_Pane6_TrackExecute_Btn_Clicked();	// 轨迹执行【点击】
	void Slots_Page1_Pane6_TrackExit_Btn_Clicked();	// 轨迹退出【点击】
	void Slots_Page1_Pane6_Sound_Btn_Clicked();	// 声音【点击】
	void Slots_Page1_Pane6_DM1Start_Btn_Clicked();	// DM1启【点击】
	void Slots_Page1_Pane6_DM1Execute_Btn_Clicked();	// DM1执行【点击】
	void Slots_Page1_Pane6_DM1Exit_Btn_Clicked();	// DM1退【点击】
	void Slots_Page1_Pane6_ReadUD_Btn_Clicked();	// 读UD【点击】
	void Slots_Page1_Pane6_WriteUD_Btn_Clicked();	// 写UD【点击】
	/*电机测试-力矩*/
	void Slots_Page1_Pane7_CloseTorque_checkBox_StateChanged(int status);	// 关闭力矩 【状态改变】
	void Slots_Page1_Pane7_SetValue_Btn_Clicked();	// 设置【点击】
	/*电机测试-姿态*/
	void Slots_Page1_Pane8_SetValue_Btn_Clicked();	// 设置【点击】
	/*姿态微调*/
	void Slots_Page1_Pane11_GetValue_Btn_Clicked();	// 读取【点击】
	void Slots_Page1_Pane11_SetValue_Btn_Clicked();	// 设置【点击】
	/*匀速运动-速度*/
	void Slots_Page1_Pane9_GetValue_Btn_Clicked();	// 查询【点击】
	void Slots_Page1_Pane9_SetValue_Btn_Clicked();	// 设置【点击】
	/*电机零位置－微调*/
	void Slots_Page1_Pane10_GetValue_Btn_Clicked();	// 读取【点击】
	void Slots_Page1_Pane10_SetValue_Btn_Clicked();	// 设置【点击】
	/*测试命令*/
	void Slots_Page1_Pane12_ShutDown_Btn_Clicked();	// 关机【点击】
	void Slots_Page1_Pane12_Restart_Btn_Clicked();	// 重启【点击】
	void Slots_Page1_Pane12_Selfie_Btn_Clicked();	// 自拍【点击】
	void Slots_Page1_Pane12_ReturnCenter_Btn_Clicked();	// 回中【点击】
	void Slots_Page1_Pane12_HVSwitch_Btn_Clicked();	// HV切换【点击】
	void Slots_Page1_Pane12_LeftControl_Btn_Clicked();	// 左控【点击】
	void Slots_Page1_Pane12_NotControl_Btn_Clicked();	// 无控【点击】
	void Slots_Page1_Pane12_RightControl_Btn_Clicked();	// 右控【点击】
	void Slots_Page1_Pane12_QuickFollow_Btn_Clicked();	// 快速跟随【点击】
	void Slots_Page1_Pane12_QuickFollowExit_Btn_Clicked();	// 退出快速跟随【点击】
	void Slots_Page1_Pane12_RollLedOn_Btn_Clicked();	// 横滚灯亮【点击】
	void Slots_Page1_Pane12_RollLedOff_Btn_Clicked();	// 横滚灯灭【点击】
	void Slots_Page1_Pane12_CalibrationClear_Btn_Clicked();	// 校准清除【点击】
	void Slots_Page1_Pane12_ReadHall_Btn_Clicked();	// 读霍尔【点击】
	void Slots_Page1_Pane12_ReadHandlePlate_Btn_Clicked();	// 读手柄板 【点击】
	void Slots_Page1_Pane12_StartPanorama_Btn_Clicked();	// 开始全景【点击】
	void Slots_Page1_Pane12_ExecutePanorama_Btn_Clicked();	// 执行全景【点击】
	void Slots_Page1_Pane12_ExitPanorama_Btn_Clicked();	// 退出全景【点击】
	/*常用命令*/
	void Slots_Page1_OftenUse_Btn_Clicked();	// 常用命令【点击】
	void Slots_Page1_OrderSend_Btn_Clicked();	// 发送【点击】

signals:
		/*云台校准*/
		void Signals_Page1_Pane6_AttitudeCalibration_Btn_Clicked();	// 姿态校准
		void Signals_Page1_Pane6_GyroCalibration_Btn_Clicked();	// GYRO校准
		void Signals_Page1_Pane6__SixNextStep_Btn_Clicked();	// 六面下一步
		void Signals_Page1_Pane6_SixCalibration_Btn_Clicked();	// 六面校准
		void Signals_Page1_Pane6_IdentifySamples_Btn_Clicked();	// 辨识采样
		void Signals_Page1_Pane6_ReadRecognition_Btn_Clicked();	// 读取识别
		void Signals_Page1_Pane6_Inception_Btn_Clicked();	// 盗梦空间
		void Signals_Page1_Pane6_TrackStart_Btn_Clicked();	// 轨迹开始
		void Signals_Page1_Pane6_TrackExecute_Btn_Clicked();	// 轨迹执行
		void Signals_Page1_Pane6_TrackExit_Btn_Clicked();	// 轨迹退出
		void Signals_Page1_Pane6_DM1Start_Btn_Clicked();	// DM1启
		void Signals_Page1_Pane6_DM1Execute_Btn_Clicked();	// DM1执行
		void Signals_Page1_Pane6_DM1Exit_Btn_Clicked();	// DM1退
		void Signals_Page1_Pane6_ReadUD_Btn_Clicked();	// 读UD
		void Signals_Page1_Pane6_WriteUD_Btn_Clicked();	// 写UD


		void Signals_Page1_Pane6_Sound_Btn_Clicked();	// 声音 发送信号
		void Signals_Page1_Pane6_MotorCalibration_Btn_Clicked();		// 电机校准
		/*测试命令*/
		void Signals_Page1_Pane12_Restart_Btn_Clicked();	// 重启
		void Signals_Page1_Pane12_ShutDown_Btn_Clicked();	// 关机
		void Signals_Page1_Pane12_Selfie_Btn_Clicked();	// 自拍
		void Signals_Page1_Pane12_ReturnCenter_Btn_Clicked();	// 回中
		void Signals_Page1_Pane12_HVSwitch_Btn_Clicked();	// HV切换
		void Signals_Page1_Pane12_LeftControl_Btn_Clicked();	// 左控
		void Signals_Page1_Pane12_NotControl_Btn_Clicked();	// 无控
		void Signals_Page1_Pane12_RightControl_Btn_Clicked();	// 右控
		void Signals_Page1_Pane12_QuickFollow_Btn_Clicked();	// 快速跟随
		void Signals_Page1_Pane12_QuickFollowExit_Btn_Clicked();	// 退出快速跟随
		void Signals_Page1_Pane12_RollLedOn_Btn_Clicked();	// 横滚灯亮
		void Signals_Page1_Pane12_RollLedOff_Btn_Clicked();	// 横滚灯灭
		void Signals_Page1_Pane12_CalibrationClear_Btn_Clicked();	// 校准清除
		void Signals_Page1_Pane12_ReadHall_Btn_Clicked();	// 读霍尔
		void Signals_Page1_Pane12_ReadHandlePlate_Btn_Clicked();	// 读手柄
		void Signals_Page1_Pane12_StartPanorama_Btn_Clicked();	// 开始全景
		void Signals_Page1_Pane12_ExecutePanorama_Btn_Clicked();	// 执行全景
		void Signals_Page1_Pane12_ExitPanorama_Btn_Clicked();	// 退出全景
		/*电机测试-力矩*/
		void Signals_Page1_Pane7_SetValue_Btn_Clicked(qint16 pitch, qint16 roll, qint16 yaw);
		/*电机测试-姿态*/
		void Signals_Page1_Pane8_SetValue_Btn_Clicked(float pitch, float roll, float yaw);
		/*姿态微调*/
		void Signals_Page1_Pane11_GetValue_Btn_Clicked();
		void Signals_Page1_Pane11_SetValue_Btn_Clicked(float pitch, float roll);
		/*匀速运动-速度*/
		void Signals_Page1_Pane9_GetValue_Btn_Clicked();	// 查询
		void Signals_Page1_Pane9_SetValue_Btn_Clicked(qint16 pitch, qint16 yaw);	// 设置
		/*电机零位置微调*/
		void Signals_Page1_Pane10_GetValue_Btn_Clicked();	// 查询
		void Signals_Page1_Pane10_SetValue_Btn_Clicked(float pitch, float yaw);	// 设置

		// 发送提示信息信号
		void MainPage1_Signals_PromptMsg(MessageType type, QString content);
public:
	Ui::MainwindowClass* MainPage1_ui;	// ui指针
};

#endif
