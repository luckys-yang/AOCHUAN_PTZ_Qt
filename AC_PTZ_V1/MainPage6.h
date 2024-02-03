#pragma once
#ifndef MAINPAGE6_H
#define MAINPAGE6_H
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

#define QT_MainPage6_Debug 1

class MainPage6 : public QWidget
{
	Q_OBJECT

public:
	MainPage6(QWidget* parent = nullptr);
	~MainPage6();
	// 页面初始化
	void MainPage6_Init();
	// 页面连接
	void MainPage6_Connect_Handler();

private slots:
	/*调试区*/

public:
	Ui::MainwindowClass* MainPage6_ui;	// ui指针

signals:
	// 发送提示信息信号
	void MainPage6_Signals_PromptMsg(MessageType type, QString content);
};

#endif

