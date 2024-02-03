#pragma once
#ifndef MAINTOPBOTTOM_H
#define MAINTOPBOTTOM_H
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
#include <QDesktopServices>

#define QT_MainTopBottom_Debug 1

class MainTopBottom : public QWidget
{
	Q_OBJECT

public:
	MainTopBottom(QWidget* parent = nullptr);
	~MainTopBottom();
	// 页面初始化
	void MainTopBottom_Init();
	// 页面连接
	void MainTopBottom_Connect_Handler();

private slots:
	/*调试区*/
	void Slots_MainTopBottom_DebugArea_Display(const QString& msg);	// debug区显示
	void Slots_MainTopBottom_Debug_Clear_Btn_Clicked();	// 清空调试区【点击】
	void Slots_MainTopBottom_Debug_SaveLog_CheckBox_stateChanged(int status);	// 保存日志 【勾选】
	void Slots_MainTopBottom_Bottom_LogPath_Btn_Clicked();	// 日志路径 【点击】
public:
	Ui::MainwindowClass* MainTopBottom_ui;	// ui指针
signals:
	// 发送提示信息信号
	void MainTopBottom_Signals_PromptMsg(MessageType type, QString content);
};

#endif

