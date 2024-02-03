#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QWidget>
#include "ui_Mainwindow.h"  // ui
#include "Loginview.h"  // 登陆界面
#include "Progresswait.h"	// 进度条
#include "HoverFillButton.h"    // 波形按钮
#include "QtTest.h" // 测试
#include <QThread>
#include <QMutexLocker>
#include <QPoint>
#include <QSystemtrayicon>	// 托盘

#include "MainPage1.h"
#include "MainPage2.h"
#include "AppSettings.h"
#include "MainPage3.h"
#include "MainPage4.h"
#include "MainPage5.h"
#include "MainPage6.h"
#include "MainPage7.h"
#include "MainTopBottom.h"
#include "SerialThread.h"

class MainPage1;		// 页面1
class MainPage2;		// 页面2
class MainPage3;		// 页面3
class MainPage4;		// 页面4
class MainPage5;		// 页面5
class MainPage6;		// 页面6
class MainPage7;		// 页面7
class MainTopBottom;		// TopBottom
class SerialThread;	// 线程

// 调试打印
//#define QT_Mainwindow_DEBUG

struct MainwindowParameter_t {
	QString qss;	// 存储样式表
	QVector<QPoint> position;	// 坐标
	QPoint m_click;        // 当前鼠标点击坐标
	QString System_Font_Id;	// 系统字体ID
	bool MouseFlag;	// 鼠标标志位
};

class Mainwindow : public QWidget
{
	Q_OBJECT

public:
	enum MainStyle
	{
		// 日本腮红
		MainStyle_JapanBlush = 0,
		// 强力棒
		MainStyle_Strong_Stick = 1,
		// 自信云
		MainStyle_Confident_Cloud = 2,
		// 柠檬飞翔
		MainStyle_Flying_Lemon = 3,
		// 森林伊内
		MainStyle_Forest_Inei = 4,
		// 富金属
		MainStyle_Rich_Metal = 5
	};

	Mainwindow(QWidget* parent = nullptr);
	~Mainwindow();

protected:
	// 初始化
	void Mainwindow_Init();
	// 画背景
	void Mainwindow_Bg_Draw(QPainter* ev);
	// 连接处理函数
	void Mainwindow_Connect_Handler();
	// 设置背景样式
	void Mainwindow_Set_Bg_Style(const MainStyle& mainStyle, QLinearGradient* gradient);
	// 重写窗口显示事件(override)
	void showEvent(QShowEvent* even) override;
	// 重写 paintEvent 事件，进行绘制操作
	void paintEvent(QPaintEvent* even) override;
	// 重写鼠标按下事件(override)
	void mousePressEvent(QMouseEvent* event) override;
	// 重写鼠标松开事件(override)
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	// 重写窗口关闭事件
	void closeEvent(QCloseEvent* event) override;
	// 样式表读取
	void Mainwindow_Get_CSS();
	// 全局配置
	void Mainwindow_Config();
	// 线程初始化
	void Mainwindow_Thread_Init();
public:
	// 初始化测试区
	void UI_Test_Init();

public:
	/*串口多线程*/
	// 串口多线程初始化
	void Mainwindow_Thread_Connect_Handler();
	// 串口打开/关闭 UI使能/失能
	void SerialThread_OnOffPort_UiControl(AppSettings::RunStatus_et status);
	// 串口列表发生变化 UI更新
	void SerialThread_PortCheckStatus_UiContorl();
	// 串口接收完成  UI更新
	void SerialThread_SerialDataDisplay_UiControl(QByteArray disBuff);
	// 串口发送完成 UI更新
	void SerialThread_SerialDataDisplayTx_UiControl(QByteArray disBuff);

	/*旧协议1*/
	void Pro1_Status_To_Ui_Update();	// 根据状态改变Ui
	void Pro1_ShowVersion(QByteArray src, const QByteArray& array, int data_len);	// 版本信息显示
	void Pro1_Page1_ShowPostureQueryMsg(const QByteArray& array, int data_len);	// 姿态信息查询显示
	void Pro1_ShowSystemStatusQuery(const QByteArray& array, int data_len);	// 系统状态查询显示
	void Pro1_VerifyHandler(const QByteArray& array, int data_len);		// 确认命令处理
	void Pro1_DenyHandler(const QByteArray& array, int data_len);		// 否认命令处理
	void Pro1_DebugCmdHandler(const QByteArray& array, int data_len);	// 调试命令处理
	void Pro1_ReadHallHandler(const QByteArray& array, int data_len);		// 读取霍尔处理
	void Pro1_AttitudeFineTuningGetHandler(const QByteArray& array, int data_len);	// 姿态微调 - 获取
	void Pro1_UniformMotionQueryHandler(const QByteArray& array, int data_len);		// 匀速运动速度 - 获取
	void Pro1_MotorZeroPositionQueryHandler(const QByteArray& array, int data_len);	// 电机零位置微调 - 获取
	void Pro1_AttitudeCalibrationHandler(const QByteArray& array, int data_len);	// 姿态校准
	void Pro1_SixCalibrationNextStepHandler(const QByteArray& array, int data_len);	// 六面校准下一步
	void Pro1_SixCalibrationHandler(const QByteArray& array, int data_len);	// 六面校准
	void Pro1_RunControlHandler(const QByteArray& array, int data_len);	// 盗梦 dm1
	void Pro1_UserDataReadHandler(const QByteArray& array, int data_len);	// UD读
	void Pro1_ControlPIDQueryHandler(const QByteArray& array, int data_len);	// 控制PID 获取
	void Pro1_ControlParameterGetHandler(const QByteArray& array, int data_len);	// 控制参数 获取
	void Pro1_FollowParameterGetHandler(const QByteArray& array, int data_len);	// 跟随参数 获取
	void Pro1_PTZTestNoiseHandler(const QByteArray& array, int data_len);	// 噪声测试

public slots:
	/*Page1*/
	void Page1_Pane6_AttitudeCalibration_Btn_Handler();	// 姿态校准
	void Page1_Pane6_GyroCalibration_Btn_Handler();	// GYRO校准
	void Page1_Pane6_SixNextStep_Btn_Handler();	// 六面下一步
	void Page1_Pane6_SixCalibration_Btn_Handler();	// 六面校准
	void Page1_Pane6_IdentifySamples_Btn_Handler();	// 辨识采样
	void Page1_Pane6_ReadRecognition_Btn_Handler();	// 读取识别
	void Page1_Pane6_Inception_Btn_Handler();	// 盗梦空间
	void Page1_Pane6_TrackStart_Btn_Handler();	// 轨迹开始
	void Page1_Pane6_TrackExecute_Btn_Handler();	// 轨迹执行
	void Page1_Pane6_TrackExit_Btn_Handler();	// 轨迹退出
	void Page1_Pane6_DM1Start_Btn_Handler();	// DM1启
	void Page1_Pane6_DM1Execute_Btn_Handler();	// DM1执行
	void Page1_Pane6_DM1Exit_Btn_Handler();	// DM1退
	void Page1_Pane6_ReadUD_Btn_Handler();	// 读UD
	void Page1_Pane6_WriteUD_Btn_Handler();	// 写UD

	void Page1_Pane6_Sound_Btn_Handler();	// 声音按键按下处理
	void Page1_Pane6_MotorCalibration_Btn_Handler();	// 电机校准按键按下处理

	void Page1_Page1_Pane12_Restart_Btn_Handler();	// 重启按下处理
	void Page1_Pane12_ShutDown_Btn_Handler();	// 关机
	void Page1_Pane12_Selfie_Btn_Handler();	// 自拍
	void Page1_Pane12_ReturnCenter_Btn_Handler();	// 回中
	void Page1_Pane12_HVSwitch_Btn_Handler();	// HV切换
	void Page1_Pane12_LeftControl_Btn_Handler();	// 左控
	void Page1_Pane12_NotControl_Btn_Handler();	// 无控
	void Page1_Pane12_RightControl_Btn_Handler();	// 右控
	void Page1_Pane12_QuickFollow_Btn_Handler();	// 快速跟随
	void Page1_Pane12_QuickFollowExit_Btn_Handler();	// 退出快速跟随
	void Page1_Pane12_RollLedOn_Btn_Handler();	// 横滚灯亮
	void Page1_Pane12_RollLedOff_Btn_Handler();	// 横滚灯灭
	void Page1_Pane12_CalibrationClear_Btn_Handler();	// 校准清除
	void Page1_Pane12_ReadHall_Btn_Handler();	// 读霍尔
	void Page1_Pane12_ReadHandlePlate_Btn_Handler();	// 读手柄
	void Page1_Pane12_StartPanorama_Btn_Handler();	// 开始全景
	void Page1_Pane12_ExecutePanorama_Btn_Handler();	// 执行全景
	void Page1_Pane12_ExitPanorama_Btn_Handler();	// 退出全景
	void Page1_Pane7_SetValue_Btn_Handler(qint16 pitch, qint16 roll, qint16 yaw);	// 电机测试-力矩
	void Page1_Pane8_SetValue_Btn_Handler(float pitch, float roll, float yaw);		// 电机测试-姿态
	void Page1_Pane11_GetValue_Btn_Handler();		// 姿态微调 - 获取
	void Page1_Pane11_SetValue_Btn_Handler(float pitch, float roll);	// 姿态微调 - 设置
	void Page1_Pane9_GetValue_Btn_Handler();		// 匀速运动速度 - 获取
	void Page1_Pane9_SetValue_Btn_Handler(qint16 pitch, qint16 yaw);	// 匀速运动速度 - 设置
	void Page1_Pane10_GetValue_Btn_Handler();		// 电机零位置微调 - 获取
	void Page1_Pane10_SetValue_Btn_Handler(float pitch, float yaw);	// 电机零位置微调 - 设置

	/*Page2*/
	void Page2_Pane2_GetValue_Btn_Handler();	// 控制PID 获取
	void Page2_Pane2_SetValue_Btn_Handler();	// 控制PID 设置
	void Page2_Pane3_DefaultValue_Btn_Handler();	// 控制参数 - 缺省
	void Page2_Pane3_SetValue_Btn_Handler();	// 控制参数 - 设置
	void Page2_Pane3_GetValue_Btn_Handler();	// 控制参数 - 获取
	void Page2_Pane4_DefaultValue_Btn_Handler();	// 跟随参数 - 缺省
	void Page2_Pane4_SetValue_Btn_Handler();	// 跟随参数 - 设置
	void Page2_Pane4_GetValue_Btn_Handler();	// 跟随参数 - 获取

	/*Page4*/
	void Page2_Page4_Pane1_IMU_NoiseTest_Btn_Handler();	// IMU噪声测试
	void Page2_Page4_Pane2_IMUZeroOffset_Btn_Handler();	// IMU零偏测试
	void Page2_Page4_Experience_Btn_Handler();	// 一键体检
	void Page4_Pane3_YawDriftSpeedTest_Btn_Handler();	// 航向漂移速度测试

	/*托盘*/
	//void onTrayMenuActivated(QSystemTrayIcon::ActivationReason reason);	// 托盘点击处理

signals:
	// 发送提示信息信号
	void Main_Signals_PromptMsg(MessageType type, QString content);
	// 发送命令包信号
	void Main_Signals_SendPack(Protocol1_FrameHeader_rt head, Protocol1_Addr_et dest, Protocol1_Addr_et src, Protocol1_FunctionCode_et func, quint16 data_len1, quint16 data_len2, QByteArray data);
	// 发送重启信号
	void Main_Signals_SendReboot();
private:
	Ui::MainwindowClass* ui;
	HoverFillButton* btn1;
	MainStyle style;
	QFrame* line;           //水平分割线
	MainPage1* mainpage1;	// 页面1指针
	MainPage2* mainpage2;	// 页面2指针
	MainPage3* mainpage3;	// 页面3指针
	MainPage4* mainpage4;	// 页面4指针
	MainPage5* mainpage5;	// 页面5指针
	MainPage6* mainpage6;	// 页面6指针
	MainPage7* mainpage7;	// 页面7指针
	MainTopBottom* maintopbottom;	// TopBottom指针
	HintMessage* Main_Msg;	// 提示消息 对象指针
	QThread* threadOfSerial;     //进程对象
	SerialThread* serialThread;		// 子线程类
public:
	QSystemTrayIcon* m_trayIcon{};		// 托盘
};

extern MainwindowParameter_t MainwindowParameter;

#endif // !MAINWINDOW_H