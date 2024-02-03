#pragma once
#ifndef MAINPAGE3_H
#define MAINPAGE3_H
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

#define QT_MainPage3_Debug 1

class MainPage3  : public QWidget
{
	Q_OBJECT

public:
	MainPage3(QWidget *parent = nullptr);
	~MainPage3();
	// 页面初始化
	void MainPage3_Init();
	// 页面连接
	void MainPage3_Connect_Handler();

private slots:
	/*云台固件更新*/
	void Slots_Page3_Pane1_ChooseFile_Btn_Clicked();	// 选择文件 【点击】
	void Slots_Page3_Pane1_Update_Btn_Clicked();	// 更新 【点击】
	/*手柄固件更新*/
	void Slots_Page3_Pane2_ChooseFile_Btn_Clicked();	// 选择文件 【点击】
	void Slots_Page3_Pane2_Update_Btn_Clicked();	// 更新 【点击】
	/*其他*/
	void Slots_Page3_ClearDisplay_Btn_Clicked();	// 清空显示 【点击】
public:
	Ui::MainwindowClass* MainPage3_ui;	// ui指针

	// 固件包升级
	QByteArray PTZ_firawareArray;   //云台固件包缓存 字节数组
	int PTZ_firawareLen;               //云台固件包长度(总字节数)

	QByteArray Handle_firawareArray;   //手柄固件包缓存 字节数组
	int Handle_firawareLen;               //手柄固件包长度(总字节数)

signals:
	// 发送提示信息信号
	void MainPage3_Signals_PromptMsg(MessageType type, QString content);
};

#endif
