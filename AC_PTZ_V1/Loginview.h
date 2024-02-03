#pragma once
#ifndef LOGINVIEW_H
#define LOGINVIEW_H
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMetaEnum>
#include "HintMessage.h"
#include "Progresswait.h"
#include "ProgressPercent.h"	// 等待进度条
// 调试打印
//#define QT_Loginview_DEBUG

/*声明区-------------------------------------------------------------------------------*/
class LoginCard;
class SignInView;
class SignUpView;
class LoginOverlay;
class WindowButton;

// 登录状态枚举
enum class LoginStatus
{
	// 登录
	SignIn = 0x20,
	// 注册
	SignUp
};

/*装载 LoginCard 的主窗口-------------------------------------------------------------------------------*/

class LoginView : public QWidget
{
	Q_OBJECT
public:
	explicit LoginView(QWidget* parent = nullptr);
	~LoginView();

	// 返回  LoginCard 对象指针
	LoginCard* Get_pLoginCard();
	// 重写事件过滤函数(override)
	bool eventFilter(QObject* watched, QEvent* event) override;
	
protected:
	// 初始化窗口内容
	void Init();
	// 绘制事件(override)
	void paintEvent(QPaintEvent* event) override;
	// 处理连接事件
	void LoginView_Connect_Hadnler();
	// 样式表读取
	void LoginView_Get_CSS();
private:
	LoginCard* m_pLoginCard; // LoginCard 对象指针
	QPoint m_pos;
};


/*装载 LoginOverlay + SignInView + SignUpView 的卡片-------------------------------------------------------------------------------*/
class LoginCard : public QWidget
{
	Q_OBJECT
public:
	explicit LoginCard(QWidget* parent = nullptr);
	~LoginCard();
	// 获取 SignInView 对象指针的常量版本
	const SignInView* GetSignInView() const;
	// 获取 SignUpView 对象指针的常量版本
	const SignUpView* GetSignUpView() const;
	// 获取 LoginOverlay 对象指针的常量版本
	LoginOverlay* GetOverlay() const;
	// 获取 WindowButton 对象指针的常量版本
	 const WindowButton* GetWindowButton() const;
	 // 获取 ProgressPercent 对象指针
	 ProgressPercent* Get_progresspercent();
protected:
	// 初始化函数
	void Init();
	// 绘制事件(override)
	void paintEvent(QPaintEvent* event) override;
	// 登录函数
	void SignIn(const QString user, const QString pwd);
	// 注册函数
	void SignUp(const QString nickName, const QString user, const QString pwd);
	// 处理连接事件
	void LoginCard_Connect_Hadnler();
private:
	QPixmap m_backgroundPixmap; // 背景图像
	SignInView* m_pSignInView; // SignInView 对象指针
	SignUpView* m_pSignUpView; // SignUpView 对象指针
	LoginOverlay* m_pOverlay; // LoginOverlay 对象指针
	WindowButton* m_windowbutton;	// WindowButton 对象指针
	HintMessage* login_Msg;	// 登陆界面的消息 对象指针
	//ProgressWait* m_progresswait;	// 等待条 对象指针
	ProgressPercent* m_progresspercent;		// 等待条 对象指针
	bool SignIn_Success_Flag;	// 验证登陆 成功标志位
	QTimer* progressTimer;	// 等待定时器
};

/*图层-------------------------------------------------------------------------------*/
class LoginOverlay : public QWidget
{
	Q_OBJECT
public:
	explicit LoginOverlay(QWidget* parent = nullptr);
	~LoginOverlay();

	// 返回 按钮对象指针（切换登陆和注册的那个按钮）
	QPushButton* Get_pButton();

protected:
	// 初始化函数
	void Init();
	// 绘制事件(override)
	void paintEvent(QPaintEvent* event) override;
	// 改变状态的函数
	void ChangeStatus();
	// 连接处理函数
	void LoginOverlay_Connect_Handler();

private:
	const int m_nRadius = 8; // 图层边框圆角半径
	bool m_bAni; // 是否正在进行动画状态
	QPushButton* m_pButton; // 按钮对象指针（切换登陆和注册的那个按钮）
	QPixmap m_backgroundPixmap; // 背景图像
	LoginStatus m_enStatus = LoginStatus::SignIn; // 当前登录状态
signals:

	/*
	* status 当前最新的状态
	*/
	void StatusChanged(LoginStatus status); // 状态改变信号
};

/*登录界面-------------------------------------------------------------------------------*/
class SignInView : public QWidget
{
	Q_OBJECT
public:
	explicit SignInView(QWidget* parent = nullptr);
	~SignInView();

	// 清空界面的函数
	void Clear();
	// 返回用户名输入框 对象指针
	QLineEdit* Get_pEditUser_Object();
	// 返回 密码输入框 对象指针
	QLineEdit* Get_pEditPwd_Object();
	// 返回 登录按钮 对象指针
	QPushButton* Get_pBtnSignIn_Object();
protected:
	// 初始化函数
	void Init();
	// 绘制事件(override)
	void paintEvent(QPaintEvent* event) override;
	// 连接处理函数
	void SignInView_Connect_Handler();
	// 验证控制函数
	void SignInView_ValidateControl();
	// 登录按钮被按下的槽函数
	void ButtonSignInClicked();
private:
	QVBoxLayout* m_pVMainLayout; // 主垂直布局
	QLabel* m_pLabelTitle; // 标题标签
	QLineEdit* m_pEditUser; // 用户名输入框
	QLineEdit* m_pEditPwd; // 密码输入框
	QPushButton* m_pBtnSignIn; // 登录按钮
signals:
	/*
	* user 用户名
	* pwd 密码
	*/
	void Submitted(const QString user, const QString pwd);  // 登录信息提交信号
};

/*注册界面-------------------------------------------------------------------------------*/
class SignUpView : public QWidget
{
	Q_OBJECT
public:
	explicit SignUpView(QWidget* parent = nullptr);
	~SignUpView();

	//  清空界面的函数
	void Clear();
protected:
	// 初始化函数
	void Init();
	// 绘制事件(override)
	void paintEvent(QPaintEvent* event) override;
	// 连接处理函数
	void SignUpView_Connect_Handler();
	// 验证控制函数
	void SignUpView_ValidateControl();
	// 注册按钮被按下的槽函数
	void ButtonSignUpClicked();
private:
	QVBoxLayout* m_pVMainLayout; // 主垂直布局
	QLabel* m_pLabelTitle; // 标题标签
	QLineEdit* m_pEditNickName; // 昵称输入框
	QLineEdit* m_pEditUser; // 用户名输入框
	QLineEdit* m_pEditPwd; // 密码输入框
	QPushButton* m_pBtnSignUp; // 注册按钮
signals:
	/*
	* nickName 昵称
	* user 用户名
	* pwd 密码
	*/
	void Submitted(const QString nickName, const QString user, const QString pwd);  // 注册信息提交信号
};

/*工具栏-------------------------------------------------------------------------------*/
class WindowButton : public QWidget
{
	Q_OBJECT
public:
	explicit WindowButton(QWidget* parent = nullptr);
	~WindowButton();

protected:
	// 初始化函数
	void Init();
	// 绘制事件(override)
	void paintEvent(QPaintEvent* event) override;
	// 连接处理函数
	void WindowButton_Connect_Handler();

signals:
	// 发送最小化槽函数
	void WindowButton_minimize_btn_Click();
	// 发送关闭槽函数
	void WindowButton_close_btn_Click();
private:
	QPushButton* minimize_btn;  // 最小化按钮
	QPushButton* close_btn; // 关闭按钮
};


#endif
