#include "AppSettings.h"

QScopedPointer<AppSettings> AppSettings::self;    // 声明了FlatUI类中的一个静态成员变量self

AppSettings* AppSettings::Instance()
{
	// 检查 self 是否为空
	if (self.isNull())
	{
		// 使用静态局部变量来确保线程安全的初始化
		static QMutex mutex;
		QMutexLocker locker(&mutex);
		// 再次检查 self 是否为空，防止多线程竞争条件
		if (self.isNull())
		{
			self.reset(new AppSettings); // 创建并初始化  实例
		}
	}

	return self.data(); // 返回  实例的指针
}

void AppSettings::AppSettings_Init()
{
	/*模式*/
	this->PTZ_Mode = AppSettings::PTZ_Mode_Normal;   // 模式默认普通
	/*设备参数初始化*/
	this->DeviceParamnter = new DeviceParameter_st();   // 分配内存
	this->DeviceParamnter->device_baund = AppSettings::SerialBaund_9600;
	this->DeviceParamnter->device_checkBit = AppSettings::SerialCheckBit_None;
	this->DeviceParamnter->device_dataBit = AppSettings::SerialDataBit_8;
	this->DeviceParamnter->device_model = AppSettings::Model_V5OldKeyBoard;
	this->DeviceParamnter->device_pcAddr = AppSettings::PCAddr_12;
	this->DeviceParamnter->device_stopBit = AppSettings::SerialStopBit_1;
	this->DeviceParamnter->device_waitIdleFrame = AppSettings::Status_Disable;
	/*串口打开标志位*/
	this->Serial_isOpen_FLag = false;
	/*设备ID是否正确*/
	this->deviceID_isPass_Flag = false; 
	/*串口通信参数配置初始化*/
	this->SerialCommunicationParameter = new SerialCommunicationParameter_st();
	this->SerialCommunicationParameter->HexDisplay_Status = Status_Disable;
	this->SerialCommunicationParameter->HexSend_Status = Status_Disable;
	this->SerialCommunicationParameter->RecAutoNewLine_Status = Status_Disable;
	this->SerialCommunicationParameter->RecStopStart_Flag = true;	// 默认是在接收
	this->SerialCommunicationParameter->TimingSend_Status = Status_Disable;
	this->SerialCommunicationParameter->TxAutoNewLine_Status = Status_Disable;
	this->SerialCommunicationParameter->RxDataCount = 0;
	this->SerialCommunicationParameter->TxDataCount = 0;

	/*串口相关*/
	this->RecPack_Count = 0;
	this->ParsePack_Count = 0;
}

AppSettings::AppSettings(QObject* parent)
	: QObject(parent)
{
	DeviceParamnter = nullptr;
}

AppSettings::~AppSettings()
{
	delete DeviceParamnter; // 释放内存
#if QT_AppSettings_Debug
	qDebug() << "delete AppSettings";
#endif
}

AppSettings::PTZ_Mode_et AppSettings::getPTZMode()
{
	return this->PTZ_Mode;
}

bool AppSettings::getSerial_isOpen()
{
	return this->Serial_isOpen_FLag;
}

void AppSettings::setPTZMode(PTZ_Mode_et mode)
{
	if (mode != PTZ_Mode)
	{
		this->PTZ_Mode = mode;
	}
}

void AppSettings::setDeviceModel(Model_et model)
{
	if (this->DeviceParamnter->device_model != model)
	{
		this->DeviceParamnter->device_model = model;
	}
}

void AppSettings::setDevicePCAddr(PCAddr_et addr)
{
	if (this->DeviceParamnter->device_pcAddr != addr)
	{
		this->DeviceParamnter->device_pcAddr = addr;
	}
}

void AppSettings::setDeviceBaund(SerialBaund_et baund)
{
	if (this->DeviceParamnter->device_baund != baund)
	{
		this->DeviceParamnter->device_baund = baund;
	}
}

void AppSettings::setDeviceCheckBit(SerialCheckBit_et check_bit)
{
	if (this->DeviceParamnter->device_checkBit != check_bit)
	{
		this->DeviceParamnter->device_checkBit = check_bit;
	}
}

void AppSettings::setDeviceStopBit(SerialStopBit_et stop_bit)
{
	if (this->DeviceParamnter->device_stopBit != stop_bit)
	{
		this->DeviceParamnter->device_stopBit = stop_bit;
	}
}

void AppSettings::setDeviceDataBit(SerialDataBit_et data_bit)
{
	if (this->DeviceParamnter->device_dataBit != data_bit)
	{
		this->DeviceParamnter->device_dataBit = data_bit;
	}
}

void AppSettings::setDeviceWaitIdleFrame(StatusCheckBox_et status)
{
	if (this->DeviceParamnter->device_waitIdleFrame != status)
	{
		this->DeviceParamnter->device_waitIdleFrame = status;
	}
}

void AppSettings::setDeviceDefault(Model_et model)
{
	PCAddr_et addr = PCAddr_2;	// PC地址2
	SerialBaund_et baund = AppSettings::SerialBaund_9600;	// 9600波特率
	SerialCheckBit_et check_bit = AppSettings::SerialCheckBit_None;	// 无校验
	SerialStopBit_et stop_bit = AppSettings::SerialStopBit_1;	// 停止位1
	SerialDataBit_et data_bit = AppSettings::SerialDataBit_8;	// 数据位8
	StatusCheckBox_et status = AppSettings::Status_Enable;	// 不等待空闲帧

	switch (model)
	{
	case AppSettings::Model_V5OldKeyBoard:
	{
		break;
	}
	case AppSettings::Model_V5NewKeyBoard:
	{
		addr = AppSettings::PCAddr_12;
		break;
	}
	case AppSettings::Model_D2Direct:
	{
		break;
	}
	case AppSettings::Model_D2NewKeyBoard:
	{
		break;
	}
	default:break;
	}

	this->setDeviceBaund(baund);
	this->setDeviceCheckBit(check_bit);
	this->setDeviceDataBit(data_bit);
	this->setDeviceModel(model);
	this->setDevicePCAddr(addr);
	this->setDeviceStopBit(stop_bit);
	this->setDeviceWaitIdleFrame(status);
}

void AppSettings::setSerial_isOpen(bool status)
{
	if (this->Serial_isOpen_FLag != status)
	{
		this->Serial_isOpen_FLag = status;
	}
}

AppSettings::Model_et AppSettings::getDeviceModel()
{
	return this->DeviceParamnter->device_model;
}

AppSettings::PCAddr_et AppSettings::getDevicePCAddr()
{
	return this->DeviceParamnter->device_pcAddr;
}

AppSettings::SerialBaund_et AppSettings::getDeviceBaund()
{
	return this->DeviceParamnter->device_baund;
}

AppSettings::SerialCheckBit_et AppSettings::getDeviceCheckBit()
{
	return this->DeviceParamnter->device_checkBit;
}

AppSettings::SerialStopBit_et AppSettings::getDeviceStopBit()
{
	return this->DeviceParamnter->device_stopBit;
}

AppSettings::SerialDataBit_et AppSettings::getDeviceDataBit()
{
	return this->DeviceParamnter->device_dataBit;
}

AppSettings::StatusCheckBox_et AppSettings::getDeviceWaitIdleFrame()
{
	return this->DeviceParamnter->device_waitIdleFrame;
}

AppSettings::DeviceParameter_st* AppSettings::get_pDeviceParameter()
{
	return this->DeviceParamnter;
}

AppSettings::SerialCommunicationParameter_st* AppSettings::get_pSerialCommunicationParameter()
{
	return this->SerialCommunicationParameter;
}


