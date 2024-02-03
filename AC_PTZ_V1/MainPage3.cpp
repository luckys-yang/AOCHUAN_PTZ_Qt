#include "MainPage3.h"


MainPage3::MainPage3(QWidget *parent)
	: QWidget(parent)
{
	MainPage3_ui = nullptr;
}

MainPage3::~MainPage3()
{
#if QT_MainPage3_Debug
	qDebug() << "delete MainPage3";
#endif
}

void MainPage3::MainPage3_Init()
{
	QValidator* validator_1 = PublicClass::getValidator(PublicClass::Re_All_MaxLen100);    // 限制

	/*云台固件更新*/
	// 【标题框】
	MainPage3_ui->Page3_Pane1->setTitleHeight(15);
	MainPage3_ui->Page3_Pane1->setTitleText("云台固件更新");
	MainPage3_ui->Page3_Pane1->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	//【标签】
	FlatUI::Instance()->setLabelQss(MainPage3_ui->Page3_Pane1_label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#BCEE68");	// 321文件
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage3_ui->Page3_Pane1_321File_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 321文件
	this->MainPage3_ui->Page3_Pane1_321File_lineEdit->setValidator(validator_1);

	// 【按键】
	MainPage3_ui->Page3_Pane1_ChooseFile_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 选择文件
	MainPage3_ui->Page3_Pane1_Update_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 更新

	/*手柄固件更新*/
	// 【标题框】
	MainPage3_ui->Page3_Pane2->setTitleHeight(15);
	MainPage3_ui->Page3_Pane2->setTitleText("手柄固件更新");
	MainPage3_ui->Page3_Pane2->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	//【标签】
	FlatUI::Instance()->setLabelQss(MainPage3_ui->Page3_Pane2_label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#BCEE68");	// BIN文件
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage3_ui->Page3_Pane2_BinFile_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// BIN文件
	this->MainPage3_ui->Page3_Pane2_BinFile_lineEdit->setValidator(validator_1);
	// 【按键】
	MainPage3_ui->Page3_Pane2_ChooseFile_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 选择文件
	MainPage3_ui->Page3_Pane2_Update_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 更新

	/*当前固件版本*/
	// 【标题框】
	MainPage3_ui->Page3_Pane3->setTitleHeight(15);
	MainPage3_ui->Page3_Pane3->setTitleText("当前固件版本");
	MainPage3_ui->Page3_Pane3->setTitleFont(QFont(MainwindowParameter.System_Font_Id, 10));
	//【标签】
	FlatUI::Instance()->setLabelQss(MainPage3_ui->Page3_Pane3_label1, QFont(MainwindowParameter.System_Font_Id, 11));	// 云台
	FlatUI::Instance()->setLabelQss(MainPage3_ui->Page3_Pane3_label2, QFont(MainwindowParameter.System_Font_Id, 11));	// 手柄
	// 【单行输入框】
	FlatUI::Instance()->setLineEditQss(MainPage3_ui->Page3_Pane3_PTZ_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 云台
	FlatUI::Instance()->setLineEditQss(MainPage3_ui->Page3_Pane3_Handle_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 手柄

	/*其他*/
	// 【文本框】
	MainPage3_ui->Page3_BinFile_textEdit->setFont(QFont(MainwindowParameter.System_Font_Id, 11));	// Bin文件区文本框
	MainPage3_ui->Page3_BinFile_textEdit->setVerticalScrollBar(MainPage3_ui->Page3_BinFileTextEdit_scrollBar);	// 重新指定滚动条
	//【标签】
	FlatUI::Instance()->setLabelQss(MainPage3_ui->Page3_label1, QFont(MainwindowParameter.System_Font_Id, 11), 3, "#EE4000");	// Bin文件内容区
	FlatUI::Instance()->setLabelQss(MainPage3_ui->Page3_label2, QFont(MainwindowParameter.System_Font_Id, 10));	// 行数
	FlatUI::Instance()->setLabelQss(MainPage3_ui->Page3_label3, QFont(MainwindowParameter.System_Font_Id, 10));	// 总字节数
	// 按键
	MainPage3_ui->Page3_ClearDisplay_Btn->setButtonStyle(QFont(MainwindowParameter.System_Font_Id, 10), 15);	// 清空显示
	// 单行输入框
	FlatUI::Instance()->setLineEditQss(MainPage3_ui->Page3_LineNumber_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 行数
	FlatUI::Instance()->setLineEditQss(MainPage3_ui->Page3_ByteSum_lineEdit, QFont(MainwindowParameter.System_Font_Id, 10));	// 总字节数
	// 进度条
	MainPage3_ui->Page3_Update_progressBar->setTextFont(MainwindowParameter.System_Font_Id);	// 设置字体
	MainPage3_ui->Page3_Update_progressBar->setTextColor(QColor(233, 222, 250));
	MainPage3_ui->Page3_Update_progressBar->setBarBgColor(QColor(80, 80, 80));
	MainPage3_ui->Page3_Update_progressBar->setBarColor(QColor(255, 107, 107));
	MainPage3_ui->Page3_Update_progressBar->setPrecision(1);
	MainPage3_ui->Page3_Update_progressBar->setStep(5);
	MainPage3_ui->Page3_Update_progressBar->setRange(0, 100);	// 最小值最大值
	// 更新进度方框
	MainPage3_ui->Page3_UpdateSchedule_label->setArrowPosition(NavLabel::ArrowPosition_Right);
	MainPage3_ui->Page3_UpdateSchedule_label->setBackground(QColor("#92fe9d"), QColor("#00c9ff"));
	MainPage3_ui->Page3_UpdateSchedule_label->setTextFont(QFont(MainwindowParameter.System_Font_Id, 11));
}

void MainPage3::MainPage3_Connect_Handler()
{
	/*云台固件更新*/
	connect(MainPage3_ui->Page3_Pane1_ChooseFile_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage3::Slots_Page3_Pane1_ChooseFile_Btn_Clicked);
	connect(MainPage3_ui->Page3_Pane1_Update_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage3::Slots_Page3_Pane1_Update_Btn_Clicked);
	/*手柄固件更新*/
	connect(MainPage3_ui->Page3_Pane2_ChooseFile_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage3::Slots_Page3_Pane2_ChooseFile_Btn_Clicked);
	connect(MainPage3_ui->Page3_Pane2_Update_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage3::Slots_Page3_Pane2_Update_Btn_Clicked);
	/*其他*/
	connect(MainPage3_ui->Page3_ClearDisplay_Btn, &HoverFillButton::HoverFillButton_Signals_mose_isRelease, this, &MainPage3::Slots_Page3_ClearDisplay_Btn_Clicked);
}

void MainPage3::Slots_Page3_Pane1_ChooseFile_Btn_Clicked()
{
	// 弹出文件选择对话框，获取选中的文件名
	// 当前类的对象指针  获取程序路径作为默认打开路径  文件过滤器指定只显示扩展名为bin的文件
	auto filename = QFileDialog::getOpenFileName(this, "打开固件", qApp->applicationDirPath(), QString::fromLocal8Bit("bin File(*.bin)"));
	
	// 判断文件为空则
	if (filename.isEmpty())
	{
		emit MainPage3_Signals_PromptMsg(MessageType::MESSAGE_TYPE_INFORMATION, QString("取消打开!"));
		return;
	}
	QFile file(filename);
	// 判断读取文件失败则
	if (!file.open(QFile::ReadOnly))
	{
		emit MainPage3_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("读取失败 %1: \n%2").arg(filename).arg(file.errorString()));
		MainPage3_ui->Page3_Pane1_321File_lineEdit->clear();	// 清除输入框
		return;
	}
	// 文本框显示文件全路径
	MainPage3_ui->Page3_Pane1_321File_lineEdit->setText(filename);	

	PTZ_firawareArray.clear();	// 清空字节数组
	PTZ_firawareArray = file.readAll();	// 读取全部内容
	PTZ_firawareLen = PTZ_firawareArray.size();	// 数据包长度
	QApplication::setOverrideCursor(Qt::WaitCursor); // 鼠标指针变为等待状态
	QString hexString = PTZ_firawareArray.toHex().toUpper(); // 转换为十六进制字符串并转为大写
	// 以十六进制数显示在文本框
	QString formattedString;
	int lineCount = 0;		// 行数
	for (int i = 0; i < hexString.length(); i += 2)
	{
		QString hexValue = hexString.mid(i, 2); // 获取两个字符，即一个十六进制数

		if (hexValue == "00")		// 高亮 00
		{
			formattedString += "<span style=\"color:red\">" + hexValue + "</span>";
		}
		else
		{
			formattedString += hexValue;
		}
		if ((i + 2) % 32 == 0)
		{
			formattedString += "<br>"; // 每16个十六进制数添加换行
			lineCount++;
		}
		else
		{
			formattedString += " "; // 十六进制数之间用一个空格分隔
		}
	}
	emit MainPage3_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("打开且读取成功!"));
	MainPage3_ui->Page3_BinFile_textEdit->setHtml(formattedString);	// 含html样式显示在文本框
	MainPage3_ui->Page3_LineNumber_lineEdit->setText(QString::number(lineCount));	// 显示行数
	MainPage3_ui->Page3_ByteSum_lineEdit->setText(QString::number(PTZ_firawareLen));	// 显示总字节数
	QApplication::restoreOverrideCursor(); // 鼠标指针恢复为原来状态
	file.close();	// 关闭文件
}

void MainPage3::Slots_Page3_Pane1_Update_Btn_Clicked()
{
	if (false == AppSettings::Instance()->getSerial_isOpen())
	{
		emit MainPage3_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("请先打开串口!"));
		return;
	}
	if (PTZ_firawareLen <= 0)
	{
		emit MainPage3_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("文本为空!"));
		return;
	}
}

void MainPage3::Slots_Page3_Pane2_ChooseFile_Btn_Clicked()
{
	// 弹出文件选择对话框，获取选中的文件名
	// 当前类的对象指针  获取程序路径作为默认打开路径  文件过滤器指定只显示扩展名为bin的文件
	auto filename = QFileDialog::getOpenFileName(this, "打开固件", qApp->applicationDirPath(), QString::fromLocal8Bit("bin File(*.bin)"));

	// 判断文件为空则
	if (filename.isEmpty())
	{
		emit MainPage3_Signals_PromptMsg(MessageType::MESSAGE_TYPE_INFORMATION, QString("取消打开!"));
		return;
	}
	QFile file(filename);
	// 判断读取文件失败则
	if (!file.open(QFile::ReadOnly))
	{
		emit MainPage3_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("读取失败 %1: \n%2").arg(filename).arg(file.errorString()));
		MainPage3_ui->Page3_Pane2_BinFile_lineEdit->clear();	// 清除输入框
		return;
	}
	// 文本框显示文件全路径
	MainPage3_ui->Page3_Pane2_BinFile_lineEdit->setText(filename);

	Handle_firawareArray.clear();	// 清空字节数组
	Handle_firawareArray = file.readAll();	// 读取全部内容
	Handle_firawareLen = Handle_firawareArray.size();	// 数据包长度
	QApplication::setOverrideCursor(Qt::WaitCursor); // 鼠标指针变为等待状态
	QString hexString = Handle_firawareArray.toHex().toUpper(); // 转换为十六进制字符串并转为大写
	// 以十六进制数显示在文本框
	QString formattedString;
	int lineCount = 0;		// 行数
	for (int i = 0; i < hexString.length(); i += 2)
	{
		QString hexValue = hexString.mid(i, 2); // 获取两个字符，即一个十六进制数

		if (hexValue == "00")		// 高亮 00
		{
			formattedString += "<span style=\"color:red\">" + hexValue + "</span>";
		}
		else
		{
			formattedString += hexValue;
		}
		if ((i + 2) % 32 == 0)
		{
			formattedString += "<br>"; // 每16个十六进制数添加换行
			lineCount++;
		}
		else
		{
			formattedString += " "; // 十六进制数之间用一个空格分隔
		}
	}
	emit MainPage3_Signals_PromptMsg(MessageType::MESSAGE_TYPE_SUCCESS, QString("打开且读取成功!"));
	MainPage3_ui->Page3_BinFile_textEdit->setHtml(formattedString);	// 含html样式显示在文本框
	MainPage3_ui->Page3_LineNumber_lineEdit->setText(QString::number(lineCount));	// 显示行数
	MainPage3_ui->Page3_ByteSum_lineEdit->setText(QString::number(PTZ_firawareLen));	// 显示总字节数
	QApplication::restoreOverrideCursor(); // 鼠标指针恢复为原来状态
	file.close();	// 关闭文件
}

void MainPage3::Slots_Page3_Pane2_Update_Btn_Clicked()
{
	if (false == AppSettings::Instance()->getSerial_isOpen())
	{
		emit MainPage3_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("请先打开串口!"));
		return;
	}
	if (Handle_firawareLen <= 0)
	{
		emit MainPage3_Signals_PromptMsg(MessageType::MESSAGE_TYPE_ERROR, QString("文本为空!"));
		return;
	}
}

void MainPage3::Slots_Page3_ClearDisplay_Btn_Clicked()
{
	MainPage3_ui->Page3_BinFile_textEdit->clear();	// 清空显示
	MainPage3_ui->Page3_LineNumber_lineEdit->clear();	// 清空显示
	MainPage3_ui->Page3_ByteSum_lineEdit->clear();	// 清空显示
}
