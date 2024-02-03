#pragma once
#ifndef MAINPAGE4_H
#define MAINPAGE4_H
#include <QWidget>
#include "ui_Mainwindow.h"
#include "Mainwindow.h"
#include "FlatUI.h"
#include "AppSettings.h"
#include "SaveLog.h"
#include "HoverFillButton.h"
#include<QRegularexpression>	// 正则表达式
#include<QFileDialog>
#include<QFile>
#include<QStandardpaths>
#include "PublicClass.h"
#include "HintMessage.h"

#define QT_MainPage4_Debug 1

class MainPage4 : public QWidget
{
	Q_OBJECT

public:
	MainPage4(QWidget* parent = nullptr);
	~MainPage4();
	// 页面初始化
	void MainPage4_Init();
	// 页面连接
	void MainPage4_Connect_Handler();
	/*云台测试参数*/
	typedef struct
	{
		bool IMU_NoiseTest_Flag;	// 噪声测试标志位
		bool IMU_ZeroOffsetTest_Flag;	// 零偏测试标志位
		bool IMU_YawDriftSpeedTest_Flag;	// 航向漂移速度测试标志位
		bool IMU_Experience_Flag;	// 一键体检标志位
	} PTZ_Parameter_st;

private slots:
	/*IMU噪声测试*/
	void Slots_Page4_Pane1_IMU_NoiseTest_Btn_Clicked();	// IMU噪声测试 【点击】
	/*IMU零偏测试*/
	void Slots_Page4_Pane2_IMUZeroOffset_Btn_Clicked();	// IMU零偏测试 【点击】
	/*航向漂移速度测试*/
	void Slots_Page4_Pane3_YawDriftSpeedTest_Btn_Clicked();	// 航向漂移速度测试 【点击】
	/*其他*/
	void Slots_Page4_ClearTest_Btn_Clicked();	// 清空IMU测试数据 【点击】
	void Slots_Page4_Experience_Btn_Clicked();	// 一键体检 【点击】

signals:
	void Signals_Page4_Pane1_IMU_NoiseTest_Btn_Clicked();	// IMU噪声测试
	void Signals_Page4_Pane2_IMUZeroOffset_Btn_Clicked();	// IMU零偏测试
	void Signals_Page4_Experience_Btn_Clicked();	// 一键体检
	void Signals_Page4_Pane3_YawDriftSpeedTest_Btn_Clicked();	// 航向漂移速度测试
public:
	Ui::MainwindowClass* MainPage4_ui;	// ui指针
	PTZ_Parameter_st* PTZ_Parameter;
signals:
	// 发送提示信息信号
	void MainPage4_Signals_PromptMsg(MessageType type, QString content);
};

#endif
