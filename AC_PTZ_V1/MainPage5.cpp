#include "MainPage5.h"

MainPage5::MainPage5(QObject* parent)
	: QObject(parent)
{
	MainPage5_ui = nullptr;
	MainPage5_serialPort = nullptr;
}

MainPage5::~MainPage5()
{
#if QT_MainPage5_Debug
	qDebug() << "delete MainPage5";
#endif
}

void MainPage5::MainPage5_Init()
{
	QValidator* validator_1 = PublicClass::getValidator(PublicClass::Re_1To65535);    // 限制

	/*顶部串口设置*/
	// 下拉框
	MainPage5_ui->Top_SerialPort_comboBox->setItemHeight(15);
	MainPage5_ui->Top_SerialPort_comboBox->setAutoWidth(true);
	MainPage5_ui->Top_SerialPort_comboBox->setTextFont(QFont(MainwindowParameter.System_Font_Id, 11));

	MainPage5_ui->Top_SerialBaund_comboBox->setItemHeight(15);
	MainPage5_ui->Top_SerialBaund_comboBox->setAutoWidth(true);
	MainPage5_ui->Top_SerialBaund_comboBox->setTextFont(QFont(MainwindowParameter.System_Font_Id, 11));
	MainPage5_ui->Top_SerialBaund_comboBox->addItem("9600", AppSettings::SerialBaund_9600);
	MainPage5_ui->Top_SerialBaund_comboBox->addItem("14400", AppSettings::SerialBaund_14400);
	MainPage5_ui->Top_SerialBaund_comboBox->addItem("115200", AppSettings::SerialBaund_115200);
	// 标签
	FlatUI::Instance()->setLabelQss(MainPage5_ui->Top_label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#5d6a73");	// 串口端口
	FlatUI::Instance()->setLabelQss(MainPage5_ui->Top_label2, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#5d6a73");	// 串口波特率
	// 串口开关
	MainPage5_ui->Serial_Switch_Btn->setTextOn(QString("串口打开"));	// 按钮使能显示的文本
	MainPage5_ui->Serial_Switch_Btn->setTextOff(QString("串口关闭"));	// 按钮失能显示的文本
	MainPage5_ui->Serial_Switch_Btn->setTextFont(QFont(MainwindowParameter.System_Font_Id, 9));	// 设置字体
	MainPage5_ui->Serial_Switch_Btn->setAnimation(false);	// 使能动画效果
	MainPage5_ui->Serial_Switch_Btn->setBgColorOn(QColor(109, 226, 76));	// 打开状态下的背景颜色

	// 【文本框】
	MainPage5_ui->Page5_SerialDebug_textEdit->setFont(QFont(MainwindowParameter.System_Font_Id, 11));	// 串口Debug区文本框
	MainPage5_ui->Page5_SerialDebug_textEdit->setVerticalScrollBar(MainPage5_ui->Page5_SerialDebugTextEdit_scrollBar);	// 重新指定滚动条
	MainPage5_ui->Page5_SerialSend_textEdit->setFont(QFont(MainwindowParameter.System_Font_Id, 11));	// 串口发送文本框
	MainPage5_ui->Page5_SerialSend_textEdit->setVerticalScrollBar(MainPage5_ui->Page5_SerialSendTextEdit_scrollBar);	// 重新指定滚动条

	// 【标签】
	FlatUI::Instance()->setLabelQss(MainPage5_ui->Page5_label3, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#5d6a73");	// 数据位
	FlatUI::Instance()->setLabelQss(MainPage5_ui->Page5_label4, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#5d6a73");	// 停止位
	FlatUI::Instance()->setLabelQss(MainPage5_ui->Page5_label5, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#5d6a73");	// 校验位
	FlatUI::Instance()->setLabelQss(MainPage5_ui->Page5_label6, QFont(MainwindowParameter.System_Font_Id, 11));	// 周期
	FlatUI::Instance()->setLabelQss(MainPage5_ui->Page5_label8, QFont(MainwindowParameter.System_Font_Id, 11));	// Rx
	FlatUI::Instance()->setLabelQss(MainPage5_ui->Page5_label9, QFont(MainwindowParameter.System_Font_Id, 11));	// Tx
	// 【下拉框】
	// 数据位
	MainPage5_ui->Page5_SerialDataBit_comboBox->setItemHeight(25);
	MainPage5_ui->Page5_SerialDataBit_comboBox->setAutoWidth(true);
	MainPage5_ui->Page5_SerialDataBit_comboBox->setTextFont(QFont(MainwindowParameter.System_Font_Id, 15));
	MainPage5_ui->Page5_SerialDataBit_comboBox->addItem("8", AppSettings::SerialDataBit_8);
	MainPage5_ui->Page5_SerialDataBit_comboBox->addItem("5", AppSettings::SerialDataBit_5);
	MainPage5_ui->Page5_SerialDataBit_comboBox->addItem("6", AppSettings::SerialDataBit_6);
	MainPage5_ui->Page5_SerialDataBit_comboBox->addItem("7", AppSettings::SerialDataBit_7);
	// 停止位
	MainPage5_ui->Page5_SerialStopBit_comboBox->setItemHeight(25);
	MainPage5_ui->Page5_SerialStopBit_comboBox->setAutoWidth(true);
	MainPage5_ui->Page5_SerialStopBit_comboBox->setTextFont(QFont(MainwindowParameter.System_Font_Id, 15));
	MainPage5_ui->Page5_SerialStopBit_comboBox->addItem("1", AppSettings::SerialStopBit_1);
	MainPage5_ui->Page5_SerialStopBit_comboBox->addItem("1.5", AppSettings::SerialStopBit_1P5);
	MainPage5_ui->Page5_SerialStopBit_comboBox->addItem("2", AppSettings::SerialStopBit_2);
	// 校验位
	MainPage5_ui->Page5_SerialCheckBit_comboBox->setItemHeight(25);
	MainPage5_ui->Page5_SerialCheckBit_comboBox->setAutoWidth(true);
	MainPage5_ui->Page5_SerialCheckBit_comboBox->setTextFont(QFont(MainwindowParameter.System_Font_Id, 15));
	MainPage5_ui->Page5_SerialCheckBit_comboBox->addItem("无", AppSettings::SerialCheckBit_None);
	MainPage5_ui->Page5_SerialCheckBit_comboBox->addItem("奇校验", AppSettings::SerialCheckBit_Odd);
	MainPage5_ui->Page5_SerialCheckBit_comboBox->addItem("偶校验", AppSettings::SerialCheckBit_Even);
	// 【按键】
	MainPage5_ui->Page5_ClearReceive_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 清空接收
	MainPage5_ui->Page5_StopReceive_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 停止接收
	MainPage5_ui->Page5_DataSend_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 发送
	MainPage5_ui->Page5_DataClearSend_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 清除发送
	// 【复选框】
	FlatUI::Instance()->setCheckBoxQss(MainPage5_ui->Page5_HexDisplay_checkBox, QFont(MainwindowParameter.System_Font_Id, 11));	// 16进制显示
	FlatUI::Instance()->setCheckBoxQss(MainPage5_ui->Page5_RxWordWrap_checkBox, QFont(MainwindowParameter.System_Font_Id, 11));	// 接收自动换行
	FlatUI::Instance()->setCheckBoxQss(MainPage5_ui->Page5_TxWordWrap_checkBox, QFont(MainwindowParameter.System_Font_Id, 11));	// 发送自动换行
	FlatUI::Instance()->setCheckBoxQss(MainPage5_ui->Page5_HexSend_checkBox, QFont(MainwindowParameter.System_Font_Id, 11));	// 16进制发送
	FlatUI::Instance()->setCheckBoxQss(MainPage5_ui->Page5_TimingSend_checkBox, QFont(MainwindowParameter.System_Font_Id, 11));	// 定时发送
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage5_ui->Page5_Cycle_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 周期
	FlatUI::Instance()->setLineEditQss(MainPage5_ui->Page5_RxCount_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// Rx计数
	FlatUI::Instance()->setLineEditQss(MainPage5_ui->Page5_TxCount_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// Tx计数

	this->MainPage5_ui->Page5_Cycle_lineEdit->setValidator(validator_1);	// 限制

	// 获取串口且添加到下拉框
	Serial_getAvailablePort();
	this->portName = MainPage5_ui->Top_SerialPort_comboBox->currentData().toString();	// 获取下拉框当前所选项的对应数据
}

void MainPage5::MainPage5_Connect_Handler()
{
	connect(MainPage5_ui->Serial_Switch_Btn, &SwitchButton::checkedChanged, this, &MainPage5::Slots_Serial_Switch_Btn_Clicked);
	connect(MainPage5_ui->Top_SerialPort_comboBox, &QComboBox::currentTextChanged, this, &MainPage5::Slots_Top_SerialPort_comboBox_currentTextChanged);
	connect(MainPage5_ui->Top_SerialBaund_comboBox, &QComboBox::currentIndexChanged, this, &MainPage5::Slots_Top_SerialBaund_comboBox_currentIndexChanged);
	connect(MainPage5_ui->Page5_SerialDataBit_comboBox, &QComboBox::currentIndexChanged, this, &MainPage5::Slots_Page5_SerialDataBit_comboBox_currentIndexChanged);
	connect(MainPage5_ui->Page5_SerialStopBit_comboBox, &QComboBox::currentIndexChanged, this, &MainPage5::Slots_Page5_SerialStopBit_comboBox_currentIndexChanged);
	connect(MainPage5_ui->Page5_SerialCheckBit_comboBox, &QComboBox::currentIndexChanged, this, &MainPage5::Slots_Page5_SerialCheckBit_comboBox_currentIndexChanged);

	connect(MainPage5_ui->Page5_HexDisplay_checkBox, &QCheckBox::stateChanged, this, &MainPage5::Slots_Page5_HexDisplay_checkBox_StateChanged);
	connect(MainPage5_ui->Page5_RxWordWrap_checkBox, &QCheckBox::stateChanged, this, &MainPage5::Slots_Page5_RxWordWrap_checkBox_StateChanged);
	connect(MainPage5_ui->Page5_TxWordWrap_checkBox, &QCheckBox::stateChanged, this, &MainPage5::Slots_Page5_TxWordWrap_checkBox_StateChanged);
	connect(MainPage5_ui->Page5_HexSend_checkBox, &QCheckBox::stateChanged, this, &MainPage5::Slots_Page5_HexSend_checkBox_StateChanged);
	connect(MainPage5_ui->Page5_TimingSend_checkBox, &QCheckBox::stateChanged, this, &MainPage5::Slots_Page5_TimingSend_checkBox_StateChanged);
	connect(MainPage5_ui->Page5_StopReceive_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage5::Slots_Page5_StopReceive_Btn_Clicked);
	connect(MainPage5_ui->Page5_ClearReceive_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage5::Slots_Page5_ClearReceive_Btn_Clicked);
	connect(MainPage5_ui->Page5_DataSend_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage5::Slots_Page5_DataSend_Btn_Clicked);
	connect(MainPage5_ui->Page5_SerialSend_textEdit, &QTextEdit::textChanged, this, &MainPage5::Slots_Page5_SerialSend_textEdit_TextChanged);
	connect(MainPage5_ui->Page5_DataClearSend_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage5::Slots_Page5_DataClearSend_Btn_Clicked);
}

void MainPage5::Serial_getAvailablePort()
{
	//获取所有的可用的串口
	auto portsInfo = QSerialPortInfo::availablePorts();
	for (auto& info : portsInfo)
	{
		MainPage5_ui->Top_SerialPort_comboBox->addItem(info.portName().append(": ").append(info.description()), info.portName());	// 添加可用的串口端口号和描述信息
	}
	MainPage5_ui->Top_SerialPort_comboBox->update();
}


/*===================================== 槽函数实现 ==================================*/

void MainPage5::Slots_Serial_Switch_Btn_Clicked(bool status)
{
	if (AppSettings::Instance()->getSerial_isOpen())	// 串口打开状态
	{
		// 发送串口关闭信号
		emit MainPage5_Signals_Serial_Close();
	}
	else	// 串口关闭状态
	{
		// 发送串口初始化信号
		emit MainPage5_Signals_Serial_Init(this->portName, AppSettings::Instance()->getDeviceBaund(), AppSettings::Instance()->getDeviceDataBit(), AppSettings::Instance()->getDeviceCheckBit(), AppSettings::Instance()->getDeviceStopBit());
	}
}

void MainPage5::Slots_Top_SerialPort_comboBox_currentTextChanged(QString text)
{
	this->portName = MainPage5_ui->Top_SerialPort_comboBox->currentData().toString();	// 获取对应数据
#if QT_MainPage5_Debug
	qDebug() << this->portName;
#endif
}

void MainPage5::Slots_Top_SerialBaund_comboBox_currentIndexChanged(int index)
{
	auto baud_current_data = MainPage5_ui->Top_SerialBaund_comboBox->currentData().value<AppSettings::SerialBaund_et>();// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDeviceBaund(baud_current_data);
#if QT_MainPage5_Debug
	qDebug() << AppSettings::Instance()->getDeviceBaund();
#endif
}

void MainPage5::Slots_Page5_SerialDataBit_comboBox_currentIndexChanged(int index)
{
	auto dataBit_current_data = MainPage5_ui->Page5_SerialDataBit_comboBox->currentData().value<AppSettings::SerialDataBit_et>();// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDeviceDataBit(dataBit_current_data);
#if QT_MainPage5_Debug
	qDebug() << AppSettings::Instance()->getDeviceDataBit();
#endif
}

void MainPage5::Slots_Page5_SerialStopBit_comboBox_currentIndexChanged(int index)
{
	auto stopBit_current_data = MainPage5_ui->Page5_SerialStopBit_comboBox->currentData().value<AppSettings::SerialStopBit_et>();// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDeviceStopBit(stopBit_current_data);
#if QT_MainPage5_Debug
	qDebug() << AppSettings::Instance()->getDeviceStopBit();
#endif
}

void MainPage5::Slots_Page5_SerialCheckBit_comboBox_currentIndexChanged(int index)
{
	auto checkBit_current_data = MainPage5_ui->Page5_SerialCheckBit_comboBox->currentData().value<AppSettings::SerialCheckBit_et>();// 获取当前下标对应的绑定数据(需要类型转换)
	AppSettings::Instance()->setDeviceCheckBit(checkBit_current_data);
#if QT_MainPage5_Debug
	qDebug() << AppSettings::Instance()->getDeviceCheckBit();
#endif
}

void MainPage5::Slots_Page5_HexDisplay_checkBox_StateChanged(int status)
{
	AppSettings::Instance()->get_pSerialCommunicationParameter()->HexDisplay_Status = static_cast<AppSettings::StatusCheckBox_et>(status);
#if QT_MainPage5_Debug
	qDebug() << AppSettings::Instance()->get_pSerialCommunicationParameter()->HexDisplay_Status;
#endif
}

void MainPage5::Slots_Page5_RxWordWrap_checkBox_StateChanged(int status)
{
	AppSettings::Instance()->get_pSerialCommunicationParameter()->RecAutoNewLine_Status = static_cast<AppSettings::StatusCheckBox_et>(status);
#if QT_MainPage5_Debug
	qDebug() << AppSettings::Instance()->get_pSerialCommunicationParameter()->RecAutoNewLine_Status;
#endif
}

void MainPage5::Slots_Page5_TxWordWrap_checkBox_StateChanged(int status)
{
	AppSettings::Instance()->get_pSerialCommunicationParameter()->TxAutoNewLine_Status = static_cast<AppSettings::StatusCheckBox_et>(status);
#if QT_MainPage5_Debug
	qDebug() << AppSettings::Instance()->get_pSerialCommunicationParameter()->TxAutoNewLine_Status;
#endif
}

void MainPage5::Slots_Page5_HexSend_checkBox_StateChanged(int status)
{
	AppSettings::Instance()->get_pSerialCommunicationParameter()->HexSend_Status = static_cast<AppSettings::StatusCheckBox_et>(status);

	QByteArray array;
	QString strData = MainPage5_ui->Page5_SerialSend_textEdit->toPlainText();	// 获取文本框想要发送的内容
	QByteArray arr1 = strData.toUtf8().toHex().toUpper();	// UTF-8编码 -> 十六进制

	// 勾选了十六进制发送
	if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->HexSend_Status)
	{
		MainPage5_ui->Page5_SerialSend_textEdit->setPlaceholderText("十六进制不足2位的请前面补0");

		for (int i = 0; i < arr1.length(); i += 2)
		{
			array += arr1.mid(i, 2);
			array += " ";
		}
		MainPage5_ui->Page5_SerialSend_textEdit->clear();	// 清除显示
		MainPage5_ui->Page5_SerialSend_textEdit->setText(array);	// 重新显示
	}
	else
	{
		MainPage5_ui->Page5_SerialSend_textEdit->setPlaceholderText("");
		QByteArray byteArray = QByteArray::fromHex(strData.toUtf8());

		MainPage5_ui->Page5_SerialSend_textEdit->clear();	// 清除显示
		MainPage5_ui->Page5_SerialSend_textEdit->setText(byteArray);	// 重新显示
	}

#if QT_MainPage5_Debug
	qDebug() << array;
	qDebug() << AppSettings::Instance()->get_pSerialCommunicationParameter()->HexSend_Status;
#endif
}

void MainPage5::Slots_Page5_TimingSend_checkBox_StateChanged(int status)
{
	auto time = MainPage5_ui->Page5_Cycle_lineEdit->text().toUInt();	// 获取定时时间
	if (time <= 0)
	{
		MainPage5_ui->Page5_TimingSend_checkBox->setCheckState(Qt::CheckState::Unchecked);	// 取消勾选
		return;
	}
	// 如果发送区为空且换行没有勾则不执行后面，不判断的话会一直弹出发送错误！
	if (("" == MainPage5_ui->Page5_SerialSend_textEdit->toPlainText()) && (AppSettings::Status_Disable == AppSettings::Instance()->get_pSerialCommunicationParameter() ->TxAutoNewLine_Status))
	{
		MainPage5_ui->Page5_TimingSend_checkBox->setCheckState(Qt::CheckState::Unchecked);	// 取消勾选
		emit MainPage5_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("发送内容不能为空!"));
		return;
	}

	AppSettings::Instance()->get_pSerialCommunicationParameter()->TimingSend_Status = static_cast<AppSettings::StatusCheckBox_et>(status);

	if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->TimingSend_Status)
	{
		// 开了串口才能进行勾选或者不勾选，没打开串口的话只能取消勾选
		if (AppSettings::Instance()->getSerial_isOpen())
		{
			// 发送信号进行启动或者停止定时器
			emit MainPage5_Signals_StartStopTimer(time);
		}
		else
		{
			MainPage5_ui->Page5_TimingSend_checkBox->setCheckState(Qt::CheckState::Unchecked);	// 取消勾选
			AppSettings::Instance()->get_pSerialCommunicationParameter()->TimingSend_Status = AppSettings::Status_Disable;
			emit MainPage5_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("请先打开串口!"));
		}
	}

	if (AppSettings::Status_Disable == AppSettings::Instance()->get_pSerialCommunicationParameter()->TimingSend_Status)
	{
		// 发送信号进行启动或者停止定时器
		emit MainPage5_Signals_StartStopTimer(time);
	}

#if QT_MainPage5_Debug
	qDebug() << AppSettings::Instance()->get_pSerialCommunicationParameter()->TimingSend_Status;
#endif
}

void MainPage5::Slots_Page5_StopReceive_Btn_Clicked()
{
	// 标志位取反
	AppSettings::Instance()->get_pSerialCommunicationParameter()->RecStopStart_Flag = !AppSettings::Instance()->get_pSerialCommunicationParameter()->RecStopStart_Flag;

	if (true == AppSettings::Instance()->get_pSerialCommunicationParameter()->RecStopStart_Flag)	// 当前显示是【停止接收】状态，即正在接收
	{
		MainPage5_ui->Page5_StopReceive_Btn->setText("停止接收");
	}
	else // 当前显示的是【继续接收】状态，即停止接收
	{
		MainPage5_ui->Page5_StopReceive_Btn->setText("继续接收");
	}
#if QT_MainPage5_Debug
	qDebug() << AppSettings::Instance()->get_pSerialCommunicationParameter()->RecStopStart_Flag;
#endif
	MainPage5_ui->Page5_StopReceive_Btn->update();
}

void MainPage5::Slots_Page5_ClearReceive_Btn_Clicked()
{
	MainPage5_ui->Page5_SerialDebug_textEdit->clear();	// 清除文本框
	AppSettings::Instance()->get_pSerialCommunicationParameter()->RxDataCount = 0;	// 接收计数清0
	MainPage5_ui->Page5_RxCount_lineEdit->setText(QString::number(0));	// 清零显示
}

void MainPage5::Slots_Page5_DataSend_Btn_Clicked()
{
	if (AppSettings::Instance()->getSerial_isOpen())	// 串口打开状态
	{
		QString strData = MainPage5_ui->Page5_SerialSend_textEdit->toPlainText();	// 获取文本框想要发送的内容
		QByteArray array;

		// 十六进制发送
		if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->HexSend_Status)
		{
#if 0	// 此处暂时无用
			// 将十六进制数据转换为 ASCII 码并发送
			// 虽然是16进制发送， 但还是将16进制转成ascii来发送，显示框再变为16进制
			QByteArray arr1 = strData.toUtf8().toHex().toUpper();	// UTF-8编码
			for (int i = 0; i < arr1.length(); i += 2)
			{
				array += arr1.mid(i, 2);
				array += " ";
			}

			array = QByteArray::fromHex(array);	// 将 array 中的十六进制字符串转换为原始的字节数组  不加的会发送错误
			// 勾选发送新行
			if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->TxAutoNewLine_Status)
			{
				array.append("\r\n");	// 加换行
			}
#endif
			array = QByteArray::fromHex(strData.toUtf8());	// 将十六进制字符串 strData 转换为原始的字节数组 array
			// 勾选发送新行
			if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->TxAutoNewLine_Status)
			{
				array.append("\r\n");	// 加换行
			}
		}
		else // 字符串发送
		{
			// 勾选发送新行
			if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->TxAutoNewLine_Status)
			{
				array = QString(strData + "\r\n").toLocal8Bit();	// 将Qstring转QByteArray
			}
			else
			{
				array = strData.toLocal8Bit();	// 将Qstring转QByteArray
			}
		}
#if QT_MainPage5_Debug
		qDebug() << array;
#endif
		// 发送信号传输数据
		emit MainPage5_Signals_SendArea_Send(array);
		array.clear();
	}
	else
	{
		emit MainPage5_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("请打开串口！"));
	}
}

void MainPage5::Slots_Page5_SerialSend_textEdit_TextChanged()
{
	// 勾选了十六进制发送
	if (AppSettings::Status_Enable == AppSettings::Instance()->get_pSerialCommunicationParameter()->HexSend_Status)
	{
		QString strData = MainPage5_ui->Page5_SerialSend_textEdit->toPlainText();
		// 使用正则表达式匹配十六进制数和空格
		QRegularExpression hexRegex("^[0-9A-Fa-f ]+$");
		if (!hexRegex.match(strData).hasMatch())
		{
			// 获取光标位置
			int cursorPosition = MainPage5_ui->Page5_SerialSend_textEdit->textCursor().position();
			if (cursorPosition != 0)
			{
				emit MainPage5_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("只能输入十六进制或空格!"));
				MainPage5_ui->Page5_SerialSend_textEdit->blockSignals(true);	// 阻塞信号
				MainPage5_ui->Page5_SerialSend_textEdit->setText("");	// 清除输入框
				MainPage5_ui->Page5_SerialSend_textEdit->blockSignals(false);	// 取消阻塞信号
			}
		}
	}
}

void MainPage5::Slots_Page5_DataClearSend_Btn_Clicked()
{
	MainPage5_ui->Page5_SerialSend_textEdit->clear();	// 清除发送文本框
	AppSettings::Instance()->get_pSerialCommunicationParameter()->TxDataCount = 0;	// 发送计数清0
	MainPage5_ui->Page5_TxCount_lineEdit->setText(QString::number(0));	// 清零显示
}

void MainPage5::Slots_Page5_TxDataCnt_UiControl()
{
	MainPage5_ui->Page5_TxCount_lineEdit->setText(QString::number(AppSettings::Instance()->get_pSerialCommunicationParameter()->TxDataCount));	// 发送
}