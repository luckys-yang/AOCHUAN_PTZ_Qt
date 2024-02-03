#include "SerialThread.h"

SerialThread::SerialThread(QObject* parent)
	: QObject(parent)
{
	SerialThread_Init();
	CheckPort_timer = new QTimer();
	CheckPort_timer->setInterval(1000);
	connect(CheckPort_timer, &QTimer::timeout, this, &SerialThread::Serial_GetPortList);	// 定时1s检测一次端口
	CheckPort_timer->start();
	TimingSend_timer = nullptr;
	// 定时从队列里拿数据
	serialRxTimer = new QTimer();
	connect(serialRxTimer, &QTimer::timeout, this, &SerialThread::Serial_Thread_Timeout_Data_Handler);
	serialRxTimer->start(5);
	timingSendOrderTimer = nullptr;
}

SerialThread::~SerialThread()
{
#if QT_SerialThread_Debug
	qDebug() << "delete SerialThread";
#endif
	if (CheckPort_timer->isActive())
	{
		CheckPort_timer->stop();
	}
	if (TimingSend_timer->isActive())
	{
		TimingSend_timer->stop();
	}
	if (serialRxTimer->isActive())
	{
		serialRxTimer->stop();
	}
	if (timingSendOrderTimer->isActive())
	{
		timingSendOrderTimer->stop();
	}
}

void SerialThread::SerialThread_Init()
{
	this->OldProtocol1_Parameter = new OldProtocol1_Parameter_st();
	OldProtocol1_Parameter->dataCheck_Flag = false;
	OldProtocol1_Parameter->state_machine = HeaderState;
	OldProtocol1_Parameter->dataLen = 0;
	OldProtocol1_Parameter->dataLen_Cnt = 0;
	OldProtocol1_Parameter->ConnectDevice_Flag = false;
	
	OldProtocol1_Parameter->check_data.clear();	// 清除
	OldProtocol1_Parameter->func_code.clear();
	OldProtocol1_Parameter->valid_data.clear();
	OldProtocol1_TimingSendOrder = Timing_NoneSend;
}


void SerialThread::Serial_Init(QString portname, AppSettings::SerialBaund_et baud, AppSettings::SerialDataBit_et data_bit, AppSettings::SerialCheckBit_et check_bit, AppSettings::SerialStopBit_et stop_bit)
{
	_serialPort = new QSerialPort();

	_serialPort->setPortName(portname);	// 串口名
	_serialPort->setBaudRate(baud);	// 波特率
	_serialPort->setDataBits(static_cast<QSerialPort::DataBits>(data_bit));	// 数据位
	_serialPort->setParity(static_cast<QSerialPort::Parity>(check_bit));	// 校验位
	_serialPort->setStopBits(static_cast<QSerialPort::StopBits>(stop_bit));	// 停止位

	if (!_serialPort->open(QIODevice::ReadWrite))	// 打开串口失败
	{
		emit SerialThread_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("%1 %2").arg(portname).arg(_serialPort->errorString()));
		AppSettings::Instance()->setSerial_isOpen(false);	// 串口打开标志位置0
		emit SerialThread_Signals_OpenPort(AppSettings::Status_FAIL);
	}
	else
	{
		_serialPort->flush();	// 清空缓冲区
		_serialPort->setFlowControl(QSerialPort::NoFlowControl);	// 无流式控制
		_serialPort->setRequestToSend(true);	// 将 RTS 信号置为高电平，表示准备好发送数据
		_serialPort->setDataTerminalReady(true);	// DTR 信号置为高电平，表示数据终端已经准备好进行通信
		emit SerialThread_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("打开串口成功!"));
		CurrentComName = portname;	// 获取当前串口名
		emit SerialThread_Signals_OpenPort(AppSettings::Status_PASS);
		//_serialPort->setReadBufferSize(1);	// 设置缓冲区大小
		/*开始定时发送命令*/
		// 如果之前已经创建了定时器，则先解除定时器与槽函数的连接否则定时器停不下来
		if (timingSendOrderTimer != nullptr)
		{
			disconnect(timingSendOrderTimer, &QTimer::timeout, this, nullptr);
			timingSendOrderTimer->stop();
			timingSendOrderTimer = nullptr;
		}
		timingSendOrderTimer = new QTimer();
		connect(timingSendOrderTimer, &QTimer::timeout, this, &SerialThread::Serial_Thread_OldProtocol1_TimingSendOrder);
		OldProtocol1_TimingSendOrder = Timing_FUNC_VersionQuery;
		timingSendOrderTimer->start(100);	// 启动定时器
		// 进行接收数据函数连接(Qt::UniqueConnection 确保信号和槽的连接是唯一的)
		AppSettings::Instance()->setSerial_isOpen(true);	// 串口打开标志位置1
		connect(_serialPort, &QSerialPort::readyRead, this, &SerialThread::Serial_Thread_Data_Receive, Qt::QueuedConnection);
	}
}

void SerialThread::Serial_Close()
{
	if (_serialPort->isOpen())
	{
		AppSettings::Instance()->setSerial_isOpen(false);	// 串口打开标志位置0
		_serialPort->clear();	// 清除
		_serialPort->close();	// 关闭
		CurrentComName = nullptr;	// 当前串口名置空

		emit SerialThread_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("已关闭串口!"));
		emit SerialThread_Signals_PortClose(AppSettings::Status_FAIL);
		emit SerialThread_Signals_SendPortList();	// 关闭串口则进行更新

		OldProtocol1_Parameter->ConnectDevice_Flag = false;	// 连接设备标志位清除
		// 定时发送命令定时器 停止
		if (timingSendOrderTimer->isActive())
		{
			timingSendOrderTimer->stop();
			OldProtocol1_TimingSendOrder = Timing_NoneSend;
		}

		//AppSettings::Instance()->RecPack_Count = 0;	// 收包数清除
		//AppSettings::Instance()->ParsePack_Count = 0;	// 解包数清除
		//emit SerialThread_Signals_PackCountToUi();	// 发送信号更新显示
	}
}

void SerialThread::Serial_GetPortList()
{
	QList<SerialPortInfo_st> portsInfo;
	bool COMx_Num_flag = true;	// 端口数量标志位
	bool CurrentDevice_Flag = false;	// 当前端口是否还在标志位 --- false则不存在 true则存在

	auto availablePorts = QSerialPortInfo::availablePorts();
	for (const auto& port : availablePorts)
	{
		SerialPortInfo_st info;
		info.portName = port.portName();
		info.description = port.description();
		portsInfo.append(info);
	}
	// 1. 先检测数量是否一样，不一致则进行复制，不能直接步骤2. 有可能造成索引溢出异常！
	if (portsInfo.size() != CurrentComInfo.size())
	{
		CurrentComInfo = portsInfo;	// 更新当前的端口列表
		COMx_Num_flag = false;
	}
	// 2. 数量一致则检测列表数据是否一致
	for (int i = 0; i < portsInfo.size(); ++i)
	{
		if (portsInfo[i].portName != CurrentComInfo[i].portName || portsInfo[i].description != CurrentComInfo[i].description)
		{
			CurrentComInfo = portsInfo;	// 更新当前的端口列表
			COMx_Num_flag = false;
		}
		if ((CurrentComName == portsInfo[i].portName) && (true == AppSettings::Instance()->getSerial_isOpen()))	// 当打开串口的情况下 则表示当前设备已拔出
		{
			CurrentDevice_Flag = true;
		}
	}

	if ((false == CurrentDevice_Flag) && (true == AppSettings::Instance()->getSerial_isOpen()))	// 当前串口打开状态且当前使用的端口发生变化则
	{
		Serial_Close();	// 串口关闭
		emit SerialThread_Signals_PromptMsg(MessageType::MESSAGE_TYPE_WARNING, QString("关闭原因：当前端口发生错误!"));
	}
	if ((false == COMx_Num_flag) && (false == AppSettings::Instance()->getSerial_isOpen()))	// 当前串口列表发生改变且串口是关闭状态则
	{
		// 发送信号，将状态传递给主线程更新UI
		emit SerialThread_Signals_SendPortList();

#if QT_SerialThread_Debug
		qDebug() << "端口发生改变" << CurrentDevice_Flag;
#endif
	}
}

const QList<SerialPortInfo_st>& SerialThread::get_SerialPortList()
{
	return CurrentComInfo;
}

QSerialPort* SerialThread::get_pSerialPort() const
{
	return this->_serialPort;
}

void SerialThread::Serial_Thread_Data_Receive()
{
	if (AppSettings::Instance()->getSerial_isOpen())
	{
#if 0	// 普通方式接收
		QThread::msleep(50);	// 延时
		auto array = _serialPort->readAll();
		Serial_Thread_OldProtocol1_Rec_Handler(array);	// 旧协议1数据处理
#else 1	// 队列方式接收
		auto array = _serialPort->readAll();
		// 将接收到的数据传递给数据处理器
		dataQueue.enqueue(array);
		
		AppSettings::Instance()->RecPack_Count++;	// 收包数++
		emit SerialThread_Signals_PackCountToUi();	// 发送信号更新显示
#endif
	}
}

void SerialThread::Serial_Thread_SendData(QByteArray data)
{
	_serialPort->write(data);
	if (!_serialPort->waitForBytesWritten()) // qt中的串口通信在发送后必须要进行发送是否成功的判断才能够正常工作
	{
		emit SerialThread_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("发送错误!"));
#if QT_SerialThread_Debug
		qDebug() << "serial write error";
#endif
	}
	else
	{
		emit SerialThread_Signals_SerialTxDataToUi(data);	// 发送更新信号
	}
}

void SerialThread::Serial_Thread_TimingSend_Control(int time)
{
	// 如果之前已经创建了定时器，则先解除定时器与槽函数的连接否则定时器停不下来
	if (TimingSend_timer != nullptr)
	{
		disconnect(TimingSend_timer, &QTimer::timeout, this, nullptr);
		TimingSend_timer->stop();
		TimingSend_timer = nullptr;
	}
	TimingSend_timer = new QTimer(this);
	connect(TimingSend_timer, &QTimer::timeout, this, [=]()
		{
			// 发送数据信号
			emit SerialThread_Signals_StartSendData();
		});

	if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->TimingSend_Status)
	{
		// 启动定时器
		TimingSend_timer->start(time);
	}
	else if (AppSettings::Status_Disable == AppSettings::Instance()->get_pSerialCommunicationParameter()->TimingSend_Status)
	{
		TimingSend_timer->stop();
	}
}

void SerialThread::Serial_Thread_Timeout_Data_Handler()
{
	// 定时器触发时处理队列中的数据
	while (!dataQueue.isEmpty())
	{
		QByteArray data = dataQueue.dequeue();
		Serial_Thread_OldProtocol1_Rec_Handler(data);	// 旧协议1数据处理
	}
}

QByteArray SerialThread::Serial_Thread_OldProtocol1_CRC(const QByteArray& array)
{
	quint16 temp = 0;

	for (char byte : array)
	{
		temp += static_cast<quint8>(byte);
	}

	return QByteArray::number(temp & 0xFF, 16).toUpper().rightJustified(2, '0');
}

/*================================== 旧协议1 ==============================*/
void SerialThread::Serial_Thread_OldProtocol1_Rec_Handler(QByteArray& recvBuff)
{
	static int success_Cnt = 0;

	// 处理数据
	Serial_Thread_OldProtocol1_DataGetCheck(recvBuff);
	// 校验成功则显示
//	if (true == OldProtocol1_Parameter->dataCheck_Flag)
//	{
//	}
	// 发送显示信号
	emit MainPage5_Signals_OldProtocol1_Serial_DataToUi(recvBuff);
}

void SerialThread::Serial_Thread_OldProtocol1_DataGetCheck(QByteArray& recvBuff)
{
	QByteArray crc;        // 接收到的CRC
	QByteArray datalen_temp;	// 数据长度

	QDataStream out(&recvBuff, QIODevice::ReadWrite);      // 创建QDataStream对象，用于读取QByteArray

	while (!out.atEnd())    // 如果未读取到QByteArray结尾
	{
		qint8 outChar = 0;  // 定义一个字节类型的变量，初始化为0
		out >> outChar;     // 从QByteArray中读取一个字节，并放入outChar中

		switch (OldProtocol1_Parameter->state_machine)
		{
		case HeaderState:
		{
			// 判断帧头
			if (PRO1_FrameHead == outChar)
			{
				OldProtocol1_Parameter->state_machine = SourceAddressState;
			}
			break;
		}
		case SourceAddressState:
		{
			// 判断目的地
			if (PRO1_Gate2 == outChar)
			{
				OldProtocol1_Parameter->check_data.append(outChar);
				OldProtocol1_Parameter->state_machine = DestinationAddressStatus;
			}
			else
			{
				OldProtocol1_Parameter->check_data.clear();
				OldProtocol1_Parameter->state_machine = HeaderState;
			}
			break; 
		}
		case DestinationAddressStatus:
		{
			// 判断来源地址
			if ((PRO1_Pitch == outChar) || (PRO1_Roll == outChar) || (PRO1_Yaw == outChar) || (PRO1_Handle == outChar) || (PRO1_Gate1 == outChar) || (PRO1_Gate2 == outChar) || (PRO1_Camera == outChar) || (PRO1_RemoteCOntrol == outChar))
			{
				OldProtocol1_Parameter->src_addr.append(outChar);		// 存储来源地址
				OldProtocol1_Parameter->check_data.append(outChar);	
				OldProtocol1_Parameter->state_machine = FunctionCodeStatus;
			}
			else
			{
				OldProtocol1_Parameter->check_data.clear();
				OldProtocol1_Parameter->state_machine = HeaderState;
			}
			break;
		}
		case FunctionCodeStatus:
		{
			// 功能码
			OldProtocol1_Parameter-> func_code.append(outChar);		// 获取功能码
			OldProtocol1_Parameter->check_data.append(outChar);
			OldProtocol1_Parameter->state_machine = DataLen1Status;
			break;
		}
		case DataLen1Status:
		{
			// 数据长度1和2是一样的
			datalen_temp.append(outChar);
			OldProtocol1_Parameter->state_machine = DataLen2Status;
			break;
		}
		case DataLen2Status:
		{
			// 数据长度1和2是一样的，故转换为实际长度只需要拿其中一个即可
			datalen_temp.append(outChar);
			OldProtocol1_Parameter->check_data.append(datalen_temp);
			OldProtocol1_Parameter->dataLen_Cnt = 0;	// 计数清0
			OldProtocol1_Parameter->dataLen = outChar;
			
			quint8 lowByte;
			quint8 highByte;
			quint16 value;

			if (datalen_temp.size() >= 2)
			{
				 lowByte = static_cast<quint8>(datalen_temp.at(0));	// 合并
				 highByte = static_cast<quint8>(datalen_temp.at(1));
				 value = (highByte << 8) | lowByte;
				 // 数据长度为0则直接跳到CRC即可
				 if (0x00 == value)
				 {
					 OldProtocol1_Parameter->state_machine = ChecksumState;
				 }
				 else
				 {
					 OldProtocol1_Parameter->state_machine = ReceiveDataBlockState;
				 }
			}
			else
			{
				OldProtocol1_Parameter->valid_data.clear();
				crc.clear();        // 接收到的CRC
				OldProtocol1_Parameter->check_data.clear();
				datalen_temp.clear();
				OldProtocol1_Parameter->func_code.clear();

				OldProtocol1_Parameter->state_machine = HeaderState;
			}
			break;
		}
		case ReceiveDataBlockState:
		case LastReceiveDataBlockState:
		{
			OldProtocol1_Parameter->valid_data.append(outChar);	// 接收的有效数据
			OldProtocol1_Parameter->check_data.append(outChar);
			if (OldProtocol1_Parameter->dataLen_Cnt == (OldProtocol1_Parameter->dataLen - 1))		// 接收够数据(0~69相当于70个所以dataLen需要-1)
			{
				OldProtocol1_Parameter->state_machine = ChecksumState;
			}
			else	// 未接收完
			{
				OldProtocol1_Parameter->state_machine = LastReceiveDataBlockState;
				++OldProtocol1_Parameter->dataLen_Cnt;	// 计数++
			}
			break;
		}
		case ChecksumState:
		{
			// CRC校验
			crc.append(outChar);
#if 0
			qDebug() << "有效数据个数:" << OldProtocol1_Parameter->dataLen_Cnt << "OldProtocol1_Parameter->dataLen:" << OldProtocol1_Parameter->dataLen << Qt::endl;
#endif
			QByteArray strSum = Serial_Thread_OldProtocol1_CRC(OldProtocol1_Parameter->check_data);
			crc = crc.toHex().toUpper();	// 转为16进制

			if (crc == strSum)
			{
				// 校验成功
				OldProtocol1_Parameter->dataCheck_Flag = true;
				
				// 串口数据解析
				Serial_Thread_OldProtocol1_Data_Analyze(OldProtocol1_Parameter->src_addr, OldProtocol1_Parameter->func_code, OldProtocol1_Parameter->valid_data, OldProtocol1_Parameter->dataLen);
			}
			else
			{
				// 校验失败
				//qDebug() << "校验失败";
				OldProtocol1_Parameter->dataCheck_Flag = false;
			}
			OldProtocol1_Parameter->src_addr.clear();
			OldProtocol1_Parameter->valid_data.clear();
			crc.clear();        // 接收到的CRC
			OldProtocol1_Parameter->check_data.clear();
			datalen_temp.clear();
			OldProtocol1_Parameter->func_code.clear();

			OldProtocol1_Parameter->state_machine = HeaderState;
			break;
		}
		default:break;
		}
	}
}

void SerialThread::Serial_Thread_OldProtocol1_TimingSendOrder()
{
	if (!AppSettings::Instance()->getSerial_isOpen())
	{
		return;
	}
	switch (OldProtocol1_TimingSendOrder)
	{
	case Timing_NoneSend:
	{
		break;
	}
	case Timing_FUNC_VersionQuery:
	{
		if (true == OldProtocol1_Parameter->ConnectDevice_Flag)
		{
			OldProtocol1_TimingSendOrder = Timing_FUNC_PostureQuery;
		}
		Serial_Thread_OldProtool1_SendPack(PRO1_FrameHead, PRO1_Roll, PRO1_Gate2, PRO1_FUNC_VersionQuery, 0x00, 0x00, nullptr);
		//qDebug() << "定时版本查询....";
		break;
	}
	case Timing_FUNC_PostureQuery:
	{
		Serial_Thread_OldProtool1_SendPack(PRO1_FrameHead, PRO1_Roll, PRO1_Gate2, PRO1_FUNC_PostureQuery, 0x00, 0x00, nullptr);
		OldProtocol1_TimingSendOrder = Timing_FUNC_StatusQuery;
		//qDebug() << "定时姿态查询....";
		break;
	}
	case Timing_FUNC_StatusQuery:
	{
		Serial_Thread_OldProtool1_SendPack(PRO1_FrameHead, PRO1_Roll, PRO1_Gate2, PRO1_FUNC_SystemStatusQuery, 00, 00, nullptr);
		OldProtocol1_TimingSendOrder = Timing_FUNC_PostureQuery;
		break;
	}
	default:break;
	}
}

void SerialThread::Serial_Thread_OldProtool1_SendPack(Protocol1_FrameHeader_rt head, Protocol1_Addr_et dest, Protocol1_Addr_et src, Protocol1_FunctionCode_et func, quint16 data_len1, quint16 data_len2, QByteArray data)
{
	QByteArray sendPackArray;

	sendPackArray.append(dest);	// 目的地
	sendPackArray.append(src);	// 源
	sendPackArray.append(func);	// 功能码
	sendPackArray.append(QByteArray::fromHex(QString("%1").arg(data_len1, 2, 16, QChar('0')).toUtf8()));// 数据长度1
	sendPackArray.append(QByteArray::fromHex(QString("%1").arg(data_len2, 2, 16, QChar('0')).toUtf8()));// 数据长度2
	if ((data != nullptr) && (data_len1 != 0) && (data_len2 != 0))
	{
		sendPackArray.append(data);		// 数据
	}
	//qDebug() << QByteArray::number(data_len1).toHex().toUpper();		// 不能这样这样 0 变成ASCII码 30
	QString crc = Serial_Thread_OldProtocol1_CRC(sendPackArray);	// 计算CRC
	sendPackArray.append(QByteArray::fromHex(crc.toUtf8()));	// CRC校验
	sendPackArray.prepend(head);	// 帧头插在头部
	
	if (AppSettings::Instance()->getSerial_isOpen())
	{
		_serialPort->write(sendPackArray);	// 发送
	}
	else
	{
		emit SerialThread_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("串口未打开!"));
		return;
	}


#if 1	// 发送不显示但是计数更新
		AppSettings::Instance()->get_pSerialCommunicationParameter()->TxDataCount += sendPackArray.size();
		emit SerialThread_Signals_TxDataCntToUi();	// 发送计数更新信号
#elif 0	// 发送显示且计数更新
	emit SerialThread_Signals_SerialTxDataToUi(data);	// 发送更新信号
#endif

#if 0
	qDebug() << "thread write:" + sendPackArray.toHex().toUpper() << "CRC:" << crc;
#endif
}

void SerialThread::Serial_Thread_OldProtocol1_Data_Analyze(QByteArray src, QByteArray code, const QByteArray& array, int data_len)
{
	quint8 funccode = static_cast<quint8>(code.at(0));	// 获取功能码
	switch (funccode)
	{
	case PRO1_FUNC_Verify:	// 确认
	{
		emit Pro1_Signals_Verify(array, data_len);
		break;
	}
	case PRO1_FUNC_Deny:	// 否认
	{
		emit Pro1_Signals_Deny(array, data_len);
		break;
	}
	case PRO1_FUNC_DebugCmd:	// 调试命令
	{
		qDebug() << array.toHex().toUpper();
		emit Pro1_Signals_DebugCmd(array, data_len);
		break;
	}
	case PRO1_FUNC_PostureQuery:	// 姿态查询
	{
		emit Pro1_Signals_PostureQuery(array, data_len); 
		break;
	}
	case PRO1_FUNC_VersionQuery:	// 版本查询
	{
		emit Pro1_Signals_VersionQuery(src, array, data_len);
		OldProtocol1_Parameter->ConnectDevice_Flag = true;
		break;
	}
	case PRO1_FUNC_SystemStatusQuery:	// 系统状态查询
	{
		emit Pro1_Signals_SystemStatusQuery(array, data_len);
		break;
	}
	case PRO1_FUNC_ReadHall:	// 读取霍尔
	{
		emit Pro1_Signals_ReadHall(array, data_len);
		break;
	}
	case PRO1_FUNC_AttitudeFineTuningGet:	// 姿态获取
	{
		emit Pro1_Signals_AttitudeFineTuningGet(array, data_len);
		break;
	}
	case PRO1_FUNC_UniformMotionQuery:	// 匀速运动速度 获取
	{
		emit Pro1_Signals_UniformMotionQuery(array, data_len);
		break;
	}
	case PRO1_FUNC_MotorZeroPositionQuery:	// 电机零位置 查询
	{
		emit Pro1_Signals_MotorZeroPositionQuery(array, data_len);
		break;
	}
	case PRO1_FUNC_AttitudeCalibration:		// 姿态校准
	{
		emit Pro1_Signals_AttitudeCalibration(array, data_len);
		break;
	}
	case PRO1_FUNC_SixCalibrationNextStep:	// 六面下一步
	{
		emit Pro1_Signals_SixCalibrationNextStep(array, data_len);
		break;
	}
	case PRO1_FUNC_SixCalibration:	// 六面校准
	{
		emit Pro1_Signals_SixCalibration(array, data_len);
		break;
	}
	case PRO1_FUNC_RunControl:	// 盗梦 dm1
	{
		emit Pro1_Signals_RunControl(array, data_len);
		break;
	}
	case PRO1_FUNC_UserDataRead:	// UD读
	{
		emit Pro1_Signals_UserDataRead(array, data_len);
		break;
	}
	case PRO1_FUNC_ControlPIDQuery:	// 控制PID读取
	{
		emit Pro1_Signals_ControlPIDQuery(array, data_len);
		break;
	}
	case PRO1_FUNC_ControlParameterGet:	// 控制参数 - 获取
	{
		emit Pro1_Signals_ControlParameterGet(array, data_len);
		break;
	}
	case PRO1_FUNC_FollowParameterGet:	// 跟随参数 - 获取
	{
		emit Pro1_Signals_FollowParameterGet(array, data_len);
		break;
	}
	case PRO1_FUNC_PTZTestNoise:	// IMU云台测试
	{
		emit Pro1_Signals_PTZTestNoise(array, data_len);
		break;
	}
	default:
	{
		//qDebug() << "功能码错误";
		//return;
	}
	}
#if 0
	qDebug() << funccode;
#endif
	AppSettings::Instance()->ParsePack_Count++;	// 解包数++
	emit SerialThread_Signals_PackCountToUi();	// 发送信号更新显示
}