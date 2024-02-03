#pragma once
#ifndef APPSETTINGS_H
#define APPSETTINGS_H

#include <QObject>
#include <QDebug>
#include <QMutex>
#include <QSerialport>
#include <QSerialportinfo>
#include "Protocol.h"

#define QT_AppSettings_Debug 1


class AppSettings  : public QObject
{
	Q_OBJECT

public:
	/*Page1--模式*/
	enum PTZ_Mode_et
	{
		PTZ_Mode_Normal = 0,	// 普通模式
		PTZ_Mode_Calibration = 1,	// 校准模式
		PTZ_Mode_MotorLock = 2,	// 电机锁定模式
		PTZ_Mode_StaticCalibration = 3,	// 静态校准模式
	};
	/*Page2--机型*/
	enum Model_et
	{
		Model_V5OldKeyBoard = 0,	// V5 +旧按键板
		Model_V5NewKeyBoard = 1,	// V5 +新按键板
		Model_D2Direct = 2,	// D2 +直连
		Model_D2NewKeyBoard = 3,	// D2 +新按键板
	}; 

	/*Page2--PC地址*/
		enum PCAddr_et
	{
		PCAddr_1 = PRO1_Pitch,	// 1
		PCAddr_2 = PRO1_Roll,		// 2
		PCAddr_3 = PRO1_Yaw,	// 3
		PCAddr_4 = PRO1_Handle,	// 4
		PCAddr_11 = PRO1_Gate1,	// 11
		PCAddr_12 = PRO1_Gate2,	// 12
		PCAddr_13 = PRO1_Camera,	// 13
		PCAddr_14 = PRO1_RemoteCOntrol,	// 14
	};
	/*全局 波特率*/
	enum SerialBaund_et
	{
		SerialBaund_9600 = 9600,	// 9600
		SerialBaund_14400 = 14400,	// 14400
		SerialBaund_115200 = 115200,	// 115200
	};
	/*全局 校验位*/
	enum SerialCheckBit_et
	{
		SerialCheckBit_None = QSerialPort::NoParity,	// 无校验位
		SerialCheckBit_Odd = QSerialPort::OddParity,	// 奇校验
		SerialCheckBit_Even = QSerialPort::EvenParity,	// 偶校验
	};
	/*全局 停止位*/
	enum SerialStopBit_et
	{
		SerialStopBit_1 = QSerialPort::OneStop,	// 1
		SerialStopBit_1P5 = QSerialPort::OneAndHalfStop,	// 1.5
		SerialStopBit_2 = QSerialPort::TwoStop,	// 2
	};
	/*全局 数据位*/
	enum SerialDataBit_et
	{
		SerialDataBit_5 = QSerialPort::Data5,	// 5
		SerialDataBit_6 = QSerialPort::Data6,	// 6
		SerialDataBit_7 = QSerialPort::Data7,	// 7
		SerialDataBit_8 = QSerialPort::Data8,	// 8
	};
	/*全局 复选框状态*/
	enum StatusCheckBox_et
	{
		Status_Enable = Qt::Checked,	// 选中
		Status_Disable = Qt::Unchecked,	// 未选中
	};
	/*全局 成功或失败*/
	enum RunStatus_et
	{
		Status_PASS = 1,	// 成功
		Status_FAIL = 0,	// 失败
	};

	/*设备参数配置*/
	struct DeviceParameter_st
	{
		Model_et device_model;		// 机型
		PCAddr_et device_pcAddr;		// PC地址
		SerialBaund_et device_baund;	// 波特率
		SerialCheckBit_et device_checkBit;		// 校验位
		SerialStopBit_et device_stopBit;		// 停止位
		SerialDataBit_et device_dataBit;		// 数据位
		StatusCheckBox_et device_waitIdleFrame;		// 等待空闲帧
	};
	/*串口通信参数配置*/
	struct SerialCommunicationParameter_st
	{
		StatusCheckBox_et HexDisplay_Status;	// 十六进制显示 勾选状态
		StatusCheckBox_et RecAutoNewLine_Status;	// 接收区自动换行 勾选状态
		bool RecStopStart_Flag;	// 停止接收/继续接收 标志位(trtue 继续接收 false 停止接收)
		StatusCheckBox_et TxAutoNewLine_Status;	// 发送区自动换行 勾选状态
		StatusCheckBox_et HexSend_Status;	// 十六进制发送 勾选状态
		StatusCheckBox_et TimingSend_Status;	// 定时发送 勾选状态
		qsizetype RxDataCount;	// 接收数据计数
		qsizetype TxDataCount;	// 接发送数据计数
	};
	
public:
	~AppSettings();
	static AppSettings* Instance();	// 获取静态实例
	// 初始化
	void AppSettings_Init();

public:
	// 设置当前模式
	void setPTZMode(PTZ_Mode_et mode);

	// 设置设备机型
	void setDeviceModel(Model_et model);	
	// 设置PC地址
	void setDevicePCAddr(PCAddr_et addr);	
	// 设置波特率
	void setDeviceBaund(SerialBaund_et baund);	
	// 设置校验位
	void setDeviceCheckBit(SerialCheckBit_et check_bit);
	// 停止位
	void setDeviceStopBit(SerialStopBit_et stop_bit);	
	// 数据位
	void setDeviceDataBit(SerialDataBit_et data_bit);	
	// 设置等待空闲帧
	void setDeviceWaitIdleFrame(StatusCheckBox_et status);
	// 设置设备缺省值
	void setDeviceDefault(Model_et model);

	// 设置串口是否打开状态
	void setSerial_isOpen(bool status);

	// 获取设备机型
	Model_et getDeviceModel();	
	// 获取PC地址
	PCAddr_et getDevicePCAddr();
	// 获取波特率
	SerialBaund_et getDeviceBaund();
	// 获取校验位
	SerialCheckBit_et getDeviceCheckBit();
	// 获取停止位
	SerialStopBit_et getDeviceStopBit();
	// 获取数据位
	SerialDataBit_et getDeviceDataBit();	
	// 获取等待空闲帧
	StatusCheckBox_et getDeviceWaitIdleFrame();

	// 获取参数配置结构体指针
	DeviceParameter_st* get_pDeviceParameter();
	// 获取串口通信参数配置结构体指针
	SerialCommunicationParameter_st* get_pSerialCommunicationParameter();
	
	// 获取当前模式
	PTZ_Mode_et getPTZMode();

	// 获取串口是否打开状态
	bool getSerial_isOpen();

private:
	AppSettings(QObject *parent = nullptr);
private:
	bool deviceID_isPass_Flag;	// 设备ID是否正确
	bool Serial_isOpen_FLag;	// 串口是否打开标志位
	PTZ_Mode_et PTZ_Mode;	// 当前的模式
	DeviceParameter_st* DeviceParamnter;	// 参数配置结构体指针
	SerialCommunicationParameter_st* SerialCommunicationParameter;
	static QScopedPointer<AppSettings> self; // 静态指针，用于保存 的单例实例
public:
	qint64 RecPack_Count;	// 收包数
	qint64 ParsePack_Count;	// 解析包数
};

#endif