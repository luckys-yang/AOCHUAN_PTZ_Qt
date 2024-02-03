#pragma once
#ifndef MAINPAGE5_H
#define MAINPAGE5_H
#include <QWidget>
#include "ui_Mainwindow.h"
#include "Mainwindow.h"
#include "FlatUI.h"
#include "AppSettings.h"
#include "SaveLog.h"
#include "HoverFillButton.h"
#include<QRegularexpression>	// 正则表达式
#include <QRunnable>
#include <QSerialPort>
#include <QTimer>
#include<QStandardpaths>
#include "PublicClass.h"
#include "HintMessage.h"

#define QT_MainPage5_Debug 0

class MainPage5 : public QObject
{
	Q_OBJECT

public:
	MainPage5(QObject* parent = nullptr);
	~MainPage5();
	// 页面初始化
	void MainPage5_Init();
	// 页面连接
	void MainPage5_Connect_Handler();

	/*串口相关*/
	// 获取可用串口且添加到下拉框
	void Serial_getAvailablePort();

public slots:
	/*串口*/
	void Slots_Serial_Switch_Btn_Clicked(bool status);	// 顶部串口开关 【点击】
	void Slots_Top_SerialPort_comboBox_currentTextChanged(QString text);	// 端口号 【当前选项文本改变】
	void Slots_Top_SerialBaund_comboBox_currentIndexChanged(int index);	// 波特率 【当前选项下标改变】
	void Slots_Page5_SerialDataBit_comboBox_currentIndexChanged(int index);	// 数据位 【当前选项下标改变】
	void Slots_Page5_SerialStopBit_comboBox_currentIndexChanged(int index);	//  停止位【当前选项下标改变】
	void Slots_Page5_SerialCheckBit_comboBox_currentIndexChanged(int index);	// 校验位 【当前选项下标改变】

	void Slots_Page5_HexDisplay_checkBox_StateChanged(int status);	// 接收区十六进制显示 【勾选】
	void Slots_Page5_RxWordWrap_checkBox_StateChanged(int status);	// 接收区自动换行显示 【勾选】
	void Slots_Page5_TxWordWrap_checkBox_StateChanged(int status);	// 发送区自动换行显示 【勾选】
	void Slots_Page5_HexSend_checkBox_StateChanged(int status);	// 十六进制发送 【勾选】
	void Slots_Page5_TimingSend_checkBox_StateChanged(int status);	// 定时发送 【勾选】
	void Slots_Page5_StopReceive_Btn_Clicked();	// 继续接收/停止接收【点击】
	void Slots_Page5_ClearReceive_Btn_Clicked();	// 清除接收【点击】
	void Slots_Page5_DataSend_Btn_Clicked();	// 发送 【点击】
	void Slots_Page5_SerialSend_textEdit_TextChanged();	// 发送文本框 【发生改变】
	void Slots_Page5_DataClearSend_Btn_Clicked();	// 清除发送【点击】
	void Slots_Page5_TxDataCnt_UiControl();	// Pack包发送 发送计数ui更新
public:
	Ui::MainwindowClass* MainPage5_ui;	// ui指针
	QSerialPort* MainPage5_serialPort;		//串口
	QString portName;	// 端口名称

signals:
	// 发送提示信息信号
	void MainPage5_Signals_PromptMsg(MessageType type, QString content);
	// 发送打开串口则初始化信号
	void MainPage5_Signals_Serial_Init(QString portname, AppSettings::SerialBaund_et baud, AppSettings::SerialDataBit_et data_bit, AppSettings::SerialCheckBit_et check_bit, AppSettings::SerialStopBit_et stop_bit);
	// 发送串口关闭信号
	void MainPage5_Signals_Serial_Close();
	// 发送 串口发送区发送信号
	void MainPage5_Signals_SendArea_Send(QByteArray data);
	// 发送 启动/停止 定时发送定时器
	void MainPage5_Signals_StartStopTimer(int time);
};

#endif

