#pragma once
#ifndef SERIALTHREAD_H
#define SERIALTHREAD_H

#include <QObject>
#include "MainPage5.h"
#include "AppSettings.h"
#include <QRunnable>
#include <QSerialPort>
#include <QTimer>
#include<QStandardpaths>
#include "Protocol.h"
#include <QQueue>
#include <QtEndian>
#define QT_SerialThread_Debug 0

// 保存端口名字与描述列表
struct SerialPortInfo_st
{
	QString portName;
	QString description;
};

class SerialThread : public QObject
{
	Q_OBJECT

public:
	SerialThread(QObject* parent);
	~SerialThread();
	// 初始化
	void SerialThread_Init();

	// 串口初始化(串口名 波特率 数据位 校验位 停止位)
	void Serial_Init(QString portname, AppSettings::SerialBaund_et baud, AppSettings::SerialDataBit_et data_bit, AppSettings::SerialCheckBit_et check_bit, AppSettings::SerialStopBit_et stop_bit);
	// 串口关闭
	void Serial_Close();
	// 获取端口列表
	void Serial_GetPortList();

	// 返回当前端口列表
	const QList<SerialPortInfo_st>& get_SerialPortList();
	// 返回当前串口指针
	QSerialPort* get_pSerialPort() const;

	// 串口线程接收数据
	void Serial_Thread_Data_Receive();
	// 串口线程发送数据
	void Serial_Thread_SendData(QByteArray data);
	// 定时发送 定时器启动停止控制(time--定时时间)
	void Serial_Thread_TimingSend_Control(int time);
	// 定时器超时处理
	void Serial_Thread_Timeout_Data_Handler();


	/*旧协议部分1*/
	/*状态机枚举*/
	enum OldProtocol1_Status_et
	{
		HeaderState = 0,	// 帧头状态
		SourceAddressState = 1,	// 目的地址状态
		DestinationAddressStatus = 2,	// 源地址状态
		FunctionCodeStatus = 3,	// 功能码状态
		DataLen1Status = 4,		// 数据长度1
		DataLen2Status = 5,		// 数据长度2
		ReceiveDataBlockState = 6,	// 接收数据块状态
		LastReceiveDataBlockState = 7,	// 最后接收数据块状态
		ChecksumState = 8	// 校验和状态
	};
	/*打开串口后需要定时发送的命令*/
	enum OldProtocol1_TimingSendOrder_et
	{
		Timing_NoneSend = 0,	// 无命令发送
		Timing_FUNC_VersionQuery = 1,		// 版本查询
		Timing_FUNC_PostureQuery = 2,	// 姿态查询
		Timing_FUNC_StatusQuery = 3,	// 状态查询
	};
	struct OldProtocol1_Parameter_st
	{
		Protocol1_InsideStatus_st Pro1_InsideStatus;	// 内部状态位域结构体变量
		Protocol1_ExtendedStatus_st Pro1_ExtendedStatus;	// 扩展状态位域结构体变量
		Protocol1_SystemStatus_st Pro1_SystemStatus;	// 系统状态位域结构体变量
		bool dataCheck_Flag;	// 接收数据校验结果标志位(true正确false错误)
		OldProtocol1_Status_et state_machine;	// 协议解析状态机
		int dataLen;	// 接收的协议里 接收数据长度
		int dataLen_Cnt;	// 接收的协议里 接收数据计数器
		bool ConnectDevice_Flag;	// 连接到下位机标志位(通过判断版本查询)
		QByteArray valid_data;	// 有效数据(用于数据解析)
		QByteArray check_data;	// 校验数据(用于校验)
		QByteArray func_code;	// 功能码
		QByteArray src_addr;	// 来源地址
	}*OldProtocol1_Parameter;
	// 旧协议接收处理函数
	void Serial_Thread_OldProtocol1_Rec_Handler(QByteArray& recvBuff);
	// 串口数据获取与校验(QByteArray& 引用类型直接修改原始数据)
	void Serial_Thread_OldProtocol1_DataGetCheck(QByteArray& recvBuff);
	// 串口数据解析(参数1：功能码 参数2：数据的个数从0下标开始)
	void Serial_Thread_OldProtocol1_Data_Analyze(QByteArray src, QByteArray code, const QByteArray& array, int data_len);
	// 串口定时发送命令
	void Serial_Thread_OldProtocol1_TimingSendOrder();
	// 串口发送命令包(帧头，目的地地址，源地址，功能码，数据长度1，数据长度2，数据(可空))
	void Serial_Thread_OldProtool1_SendPack(Protocol1_FrameHeader_rt head, Protocol1_Addr_et dest, Protocol1_Addr_et src, Protocol1_FunctionCode_et func, quint16 data_len1, quint16 data_len2, QByteArray data);
	// 串口数据CRC校验
	QByteArray Serial_Thread_OldProtocol1_CRC(const QByteArray& array);
signals:
	void Pro1_Signals_PostureQuery(const QByteArray& array, int data_len);	// 姿态查询
	void Pro1_Signals_VersionQuery(QByteArray src, const QByteArray& array, int data_len);	// 版本查询
	void Pro1_Signals_SystemStatusQuery(const QByteArray& array, int data_len);	// 系统状态查询
	void Pro1_Signals_Verify(const QByteArray& array, int data_len);		// 确认命令
	void Pro1_Signals_Deny(const QByteArray& array, int data_len);	// 否认命令
	void Pro1_Signals_DebugCmd(const QByteArray& array, int data_len);	// 调试命令
	void Pro1_Signals_ReadHall(const QByteArray& array, int data_len);		// 读取霍尔命令
	void Pro1_Signals_AttitudeFineTuningGet(const QByteArray& array, int data_len);		// 姿态微调 - 获取
	void Pro1_Signals_UniformMotionQuery(const QByteArray& array, int data_len);		// 匀速运动速度 获取
	void Pro1_Signals_MotorZeroPositionQuery(const QByteArray& array, int data_len);	// 电机零位置微调 - 获取
	void Pro1_Signals_AttitudeCalibration(const QByteArray& array, int data_len);	// 姿态校准
	void Pro1_Signals_SixCalibrationNextStep(const QByteArray& array, int data_len);	// 六面下一步
	void Pro1_Signals_SixCalibration(const QByteArray& array, int data_len);	// 六面校准
	void Pro1_Signals_RunControl(const QByteArray& array, int data_len);	// 盗梦 dm1
	void Pro1_Signals_UserDataRead(const QByteArray& array, int data_len);	// UD读
	void Pro1_Signals_ControlPIDQuery(const QByteArray& array, int data_len);	// 控制PID 获取
	void Pro1_Signals_ControlParameterGet(const QByteArray& array, int data_len);	// 控制参数 获取
	void Pro1_Signals_FollowParameterGet(const QByteArray& array, int data_len);	// 跟随参数 获取
	void Pro1_Signals_PTZTestNoise(const QByteArray& array, int data_len);	// IMU噪声测试

signals:
	// 发送显示数据在接收区信号
	void MainPage5_Signals_OldProtocol1_Serial_DataToUi(QByteArray disBuff);
	// 发送提示信息
	void SerialThread_Signals_PromptMsg(MessageType type, QString content);
	// 打开串口成功/失败 则发送(成功则是：AppSettings::Status_PASS  失败则是：AppSettings::Status_FAIL)
	void SerialThread_Signals_OpenPort(AppSettings::RunStatus_et status);
	// 关闭串口成功 发送使能UI信号
	void SerialThread_Signals_PortClose(AppSettings::RunStatus_et status);
	// 获取端口列表发送数据信号
	void SerialThread_Signals_SendPortList();
	// 发送数据成功 更新接收区信号
	void SerialThread_Signals_SerialTxDataToUi(QByteArray disBuff);
	// 定时器已启动信号，开始发送数据
	void SerialThread_Signals_StartSendData();
	// 发送Pack包更新发送计数信号
	void SerialThread_Signals_TxDataCntToUi();
	// 收包/解包计数更新
	void SerialThread_Signals_PackCountToUi();
private:
	QSerialPort* _serialPort;		//串口

	QTimer* CheckPort_timer;	// 端口列表检测定时器
	QTimer* TimingSend_timer;	// 定时发送定时器
	QTimer* timingSendOrderTimer;	// 定时发送命令定时器
	QTimer* serialRxTimer;	// 串口定时解析数据定时器

	QString CurrentComName;		// 当前端口名字
	QList<SerialPortInfo_st> CurrentComInfo;	// 存储当前端口列表
	QQueue<QByteArray> dataQueue;
	OldProtocol1_TimingSendOrder_et OldProtocol1_TimingSendOrder;	// 定时发送命令状态
};

#endif