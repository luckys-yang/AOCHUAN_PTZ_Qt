#include "Loginview.h"
#include "PublicClass.h"	// 公共函数
#include "Progresswait.h"	// 进度条
#include <QPainter>                   // QPainter 类提供了用于在各种设备上绘制图形的方法
#include <QStyleOption>               // QStyleOption 类用于描述 Qt 绘图元素的各种选项
#include <QScreen>                    // QScreen 类提供了有关计算机屏幕的信息，如分辨率和大小
#include <QApplication>               // QApplication 类是 Qt 应用程序的核心类，用于处理应用程序的控制流和主要设置
#include <QGraphicsDropShadowEffect>  // QGraphicsDropShadowEffect 类为 QGraphicsItem 添加了一个简单的阴影效果
#include <QPropertyAnimation>         // QPropertyAnimation 类提供了属性动画的支持，用于在动画过程中更改属性值
#include <QSequentialAnimationGroup>  // QSequentialAnimationGroup 类提供了一种按顺序播放动画组的方法
#include <QPainterPath>               // QPainterPath 类提供了一种描述和绘制 2D 图形路径的方式
#include <QFile>	
#include <QMouseEvent>
#include <QPoint>
#include <QEvent>
#include<QRegularexpression>

#ifdef QT_Loginview_DEBUG
#include <QDebug>
#endif

/*全局变量定义--------------------------------------------------------------------------------------------------------------------------------------*/

// LoginView 和 LoginCard 的窗口大小
#define Login_WINDOW_W 800
#define Login_WINDOW_H 700

// SignInView 和 SignUpView 的窗口大小
#define VICE_WINDOW_W (Login_WINDOW_W / 2)
#define VICE_WINDOW_H 700

// 工具栏窗口大小(一个图标大小是42x42)
#define TOOL_WINDOW_W (42*2)
#define TOOL_WINDOW_H 42

// 加载圈的大小
#define Loading_W 80
#define Loading_H 80

// 用于展开宏，获得宏对应的数值
#define STR(x) #x
#define STRINGIFY(x) STR(x)

// 注册昵称最大长度
#define SignUp_Name_MAX_LEN 8
// 注册登陆账号最大长度
#define SignUpIn_User_MAX_LEN 5
// 注册登陆密码最大长度
#define SignUpIn_Pwd_MAX_LEN 5

// 测试用户名
#define Test_User "admin"
// 测试密码
#define Test_Passed "88888"

struct LoginviewParameter_t {
	int duration;   // 动画时间
	QString qss;	// 存储样式表
};

static LoginviewParameter_t LoginviewParameter =
{
	200,
	""
};

/*装载 LoginCard 的主窗口-----------------------------------------------------------------------------------------------------------------------*/

LoginView::LoginView(QWidget* parent)
	: QWidget(parent)
{
	LoginView::LoginView_Get_CSS();
	LoginView::Init();
}

LoginView::~LoginView()
{
#ifdef QT_Loginview_DEBUG
	qDebug() << "delete LoginView";
#endif
	//// 断开与父窗口的信号槽连接
	//LoginView::disconnect(this, nullptr, parent(), nullptr);
	//// 断开与所有子部件的信号槽连接
	//LoginView::disconnect(m_pLoginCard->Get_progresswait(), nullptr, this, nullptr);
	//LoginView::disconnect(m_pLoginCard->GetWindowButton(), nullptr, this, nullptr);
}

void LoginView::LoginView_Get_CSS()
{
	// 读取css样式
	QFile file(":/Loginview/Resource/CSS/Loginview.css");
	if (true == file.open(QFile::ReadOnly))
	{
		LoginviewParameter.qss = file.readAll();
		file.close();	// 关闭文件
#ifdef QT_Loginview_DEBUG
		qDebug() << LoginviewParameter.qss << Qt::endl;
#endif
	}
	else
	{
#ifdef QT_Loginview_DEBUG
		qDebug() << "open file error";
#endif
	}
}

void LoginView::Init()
{
	/*LoginView 基本设置*/
	this->setFixedSize(Login_WINDOW_W, Login_WINDOW_H);    // 固定窗口大小为屏幕大小
	this->setObjectName(QStringLiteral("login_view"));	// 给窗口设置对象名
	this->setStyleSheet(LoginviewParameter.qss);	// 设置窗口样式
	this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);  // 去掉窗口边框
	this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
	//this->setMouseTracking(true);	// 鼠标跟踪
	/*设置exe*/
	this->setWindowTitle("AOCHAUN_V24.2.3");
	this->setWindowIcon(QIcon(":/Mainwindow/Resource/AC_logo1.ico"));

	// 安装事件过滤器
	installEventFilter(this);

	/*创建 LoginCard 窗口*/
	m_pLoginCard = new LoginCard(this);

	/*连接事件处理*/
	LoginView::LoginView_Connect_Hadnler();
}

void LoginView::paintEvent(QPaintEvent* event)
{
	// QStyleOption ---- Qt 绘图元素的各种选项的类
	QStyleOption opt;
	// 初始化(Qt5是用init函数)
	opt.initFrom(this);

	QPainter p(this);
	QWidget::paintEvent(event);	// 调用基类 QWidget 的 paintEvent 函数
}

void LoginView::LoginView_Connect_Hadnler()
{
	/*【连接1】最小化窗口*/
	connect(m_pLoginCard->GetWindowButton(), &WindowButton::WindowButton_minimize_btn_Click, this, [=]()
		{
			showMinimized();    // 最小化
		});

	/*【连接1】关闭窗口*/
	connect(m_pLoginCard->GetWindowButton(), &WindowButton::WindowButton_close_btn_Click, this, [=]()
		{
			close();    // 关闭
		});

}

LoginCard* LoginView::Get_pLoginCard()
{
	return m_pLoginCard;
}

bool LoginView::eventFilter(QObject* watched, QEvent* event)
{
	QWidget* w = dynamic_cast<QWidget*>(watched);		// 转换
	// 如果窗口没有边框，才能让他点击窗口客户区移动窗口
	if (w->windowFlags() & Qt::FramelessWindowHint)
	{
		QMouseEvent* ev = dynamic_cast<QMouseEvent*>(event);

		// 鼠标点击触发+左键
		if (event->type() == QEvent::MouseButtonPress && ev->button() == Qt::MouseButton::LeftButton)
		{
			m_pos = ev->pos();
		}
		// 鼠标松开触发+左键  MouseButton::可省略
		else if (event->type() == QEvent::MouseButtonRelease && ev->button() == Qt::LeftButton)
		{
			m_pos = { 0, 0 };
		}
		// 鼠标移动触发+左键同时
		else if (event->type() == QEvent::MouseMove && ev->buttons() == Qt::LeftButton)
		{
			w->move(ev->globalPos() - m_pos);	// 全局坐标减去当前位置坐标
			this->update();	// 手动刷新
		}
	}
	return false;
}

/*装载 LoginOverlay + SignInView + SignUpView 的卡片-------------------------------------------------------------------------------*/

LoginCard::LoginCard(QWidget* parent)
	: QWidget(parent)
{
	// 初始化
	LoginCard::Init();
}

LoginCard::~LoginCard()
{
#ifdef QT_Loginview_DEBUG
	qDebug() << "delete LoginCard";
#endif
	//LoginCard::disconnect(m_pOverlay, nullptr, this, nullptr);
	//LoginCard::disconnect(GetSignInView(), nullptr, this, nullptr);
	//LoginCard::disconnect(GetSignUpView(), nullptr, this, nullptr);
	if (progressTimer->isActive())
	{
		progressTimer->stop();
	}
}

const SignInView* LoginCard::GetSignInView() const
{
	return m_pSignInView;  // 返回 SignInView
}

const SignUpView* LoginCard::GetSignUpView() const
{
	return m_pSignUpView;  // 返回 SignUpView
}

LoginOverlay* LoginCard::GetOverlay() const
{
	return m_pOverlay;  // 返回 Overlay
}

const WindowButton* LoginCard::GetWindowButton() const
{
	return m_windowbutton;
}

ProgressPercent* LoginCard::Get_progresspercent()
{
	return m_progresspercent;
}

void LoginCard::LoginCard_Connect_Hadnler()
{
	/*【连接1】动画*/
	connect(m_pOverlay, &LoginOverlay::StatusChanged, this, [&](LoginStatus status)
		{
			QPropertyAnimation* an = nullptr;
			m_pSignInView->Clear();
			m_pSignUpView->Clear();
			if (status == LoginStatus::SignIn)
			{
				// 此时应该显示登录窗口，登录窗口在右边
				// 登录窗口从左往右移动
				m_pSignInView->move(width() / 2, 0);
				m_pSignUpView->move(0, 0);
				m_pSignInView->hide();
				an = new QPropertyAnimation(m_pSignUpView, "geometry");  // 创建一个属性动画对象，控制 SignUpView 的位置变化
				connect(an, &QPropertyAnimation::finished, this, [&, an]
					{
						delete an;
						m_pSignUpView->hide();  // 隐藏 SignUpView
						m_pSignInView->show();  // 显示 SignInView
					});
				an->setDuration(LoginviewParameter.duration);  // 设置动画时间
				an->setStartValue(QRect(m_pSignUpView->pos().x(), m_pSignUpView->pos().y(), m_pSignUpView->width(), m_pSignUpView->height()));  // 设置起始位置
				an->setEndValue(QRect(m_pSignUpView->width(), m_pSignUpView->pos().y(), m_pSignUpView->width(), m_pSignUpView->height()));  // 设置结束位置
			}
			else
			{
				// 此时应该显示注册窗口，注册窗口在左边
				m_pSignInView->move(width() / 2, 0);
				m_pSignUpView->move(0, 0);
				m_pSignUpView->hide();  // 隐藏 SignUpView
				an = new QPropertyAnimation(m_pSignInView, "geometry");  // 创建一个属性动画对象，控制 SignInView 的位置变化
				connect(an, &QPropertyAnimation::finished, this, [&, an]
					{
						delete an;
						m_pSignInView->hide();  // 隐藏 SignInView
						m_pSignUpView->show();  // 显示 SignUpView
					});
				an->setDuration(LoginviewParameter.duration);  // 设置动画时间
				an->setStartValue(QRect(m_pSignInView->pos().x(), m_pSignInView->pos().y(), m_pSignInView->width(), m_pSignInView->height()));  // 设置起始位置
				an->setEndValue(QRect(0, m_pSignInView->pos().y(), m_pSignInView->width(), m_pSignInView->height()));  // 设置结束位置
			}

			an->start();  // 开始动画
		});

	/*【连接2】登陆处理*/
	// 连接 SignInView 的 Submitted 信号和 LoginView 的 SignIn 槽函数
	connect(GetSignInView(), &SignInView::Submitted, this, &LoginCard::SignIn);

	/*【连接3】注册处理*/
	// 连接 SignUpView 的 Submitted 信号和 LoginView 的 SignUp 槽函数
	connect(GetSignUpView(), &SignUpView::Submitted, this, &LoginCard::SignUp);

	/*【连接3】*/
}

void LoginCard::Init()
{
	/*LoginCard 基本配置*/
	setFixedSize(Login_WINDOW_W, Login_WINDOW_H);	// 固定窗口大小
	setObjectName(QStringLiteral("login_card"));	// 给窗口设置对象名
	setStyleSheet(LoginviewParameter.qss);	// 设置窗口样式
	m_backgroundPixmap.load(":/Loginview/Resource/Images/AC_logo.png");	// 加载LOGO
	m_backgroundPixmap = m_backgroundPixmap.scaled(Login_WINDOW_W, Login_WINDOW_H, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);	// 缩放背景图片以适应屏幕
	this->move((width() - this->width()) / 2, (height() - this->height()) / 2);	// 将 LoginCard 窗口移动到屏幕中央

	/*创建登陆窗口*/
	m_pSignInView = new SignInView(this);  // 创建 SignInView 窗口
	m_pSignInView->move(Login_WINDOW_W / 2, 0);  // 将 SignInView 窗口移动到窗口顶部中央位置

	/*创建注册窗口*/
	m_pSignUpView = new SignUpView(this);  // 创建 SignUpView 窗口
	m_pSignUpView->move(Login_WINDOW_W / 2, 0);  // 将 SignUpView 窗口移动到窗口顶部中央位置
	m_pSignUpView->hide();  // 初始化时先隐藏 SignUpView

	/*创建Overlay窗口*/
	m_pOverlay = new LoginOverlay(this);  // 创建 Overlay
	m_pOverlay->move(0, 0);  // 将 Overlay 移动到窗口左上角位置

	/*创建工具栏窗口*/
	m_windowbutton = new WindowButton(this);
	m_windowbutton->move(Login_WINDOW_W - TOOL_WINDOW_W, 0);	// 移动到右上角

	/*创建消息控件*/
	login_Msg = new HintMessage(this);
	login_Msg->SetDuration(500);

	/*加载控件 初始化*/
#if 0
	m_progresswait = new ProgressWait(this);
	m_progresswait->setShowPercent(true);
	m_progresswait->setBarStyle(ProgressWait::BarStyle_RoundCircle);
	m_progresswait->setFixedSize(Loading_W, Loading_H);
	m_progresswait->move(width() - m_progresswait->width(), height() - m_progresswait->height());
	m_progresswait->setCurrentValue(0);
	m_progresswait->setInterval(300);
	m_progresswait->hide();	// 隐藏
#endif
	m_progresspercent = new ProgressPercent(this);
	m_progresspercent->setFixedSize(Loading_W, Loading_H);
	m_progresspercent->move(width() - m_progresspercent->width(), height() - m_progresspercent->height());
	m_progresspercent->hide();	// 隐藏

	// 进度条更新
	progressTimer = new QTimer(this);
	connect(progressTimer, &QTimer::timeout, [=]() 
		{
			static quint8 value = 0;

			if (value > 100)
			{
				value = 100;
				progressTimer->stop();
			}
			if (value < 0)
			{
				value = 0;
			}

			m_progresspercent->setValue(value);

			value += 2;
		});

	LoginCard::LoginCard_Connect_Hadnler();	// 连接处理函数
}

void LoginCard::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.initFrom(this);

	QPainter p(this);
	// 设置渲染提示 --- 开启反锯齿  开启平滑像素变换
	p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	// 使用当前样式（QStyle）绘制一个窗口小部件(widget)
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	// 绘制背景图片
	p.drawPixmap(0, 0, m_backgroundPixmap);

	QWidget::paintEvent(event);
}


void LoginCard::SignIn(const QString user, const QString pwd)
{
	bool count = true;

#ifdef QT_Loginview_DEBUG
	qDebug() << "登陆用户名:" + user + "登陆密码:" + pwd;
#endif

	/*------------------信息校验---------------------------*/

		// 不操作直接点击登陆的
	if (("" == user) || ("" == pwd))
	{
		login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("请填完整账号与密码!"));
		return;
	}

	// 账号为空 或 账号长度超出最大长度 或 含有非字母数字外的字符
	if ((" " == user) || (user.length() > SignUpIn_User_MAX_LEN) || (false == PublicClass::Letter_Number_isValid(user.toStdString())))
	{
		count = false;
		login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("账号错误!"));
	}

	// 密码为空 或 密码长度超出最大长度 或 含有非字母数字外的字符
	if ((" " == pwd) || (pwd.length() > SignUpIn_Pwd_MAX_LEN) || (false == PublicClass::Letter_Number_isValid(pwd.toStdString())))
	{
		count = false;
		login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("密码错误!"));
	}

	// 判断数据库中用户名与密码是否一致(待写)
	QString input_user = m_pSignInView->Get_pEditUser_Object()->text();	// 获取输入用户名
	QString input_passed = m_pSignInView->Get_pEditPwd_Object()->text();	// 获取输入密码

	if (Test_User != input_user)
	{
		count = false;
		login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("用户名不存在!"));
	}

	if (Test_Passed != input_passed)
	{
		count = false;
		login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("密码错误!"));
	}

	// 上面步骤有一个不行则退出
	if (count != true)
	{
		return;
	}

	/*弹出登陆成功框*/
	login_Msg->Push(MessageType::MESSAGE_TYPE_SUCCESS, QString("登陆成功"));

	/*禁用控件*/
	m_pSignInView->Get_pBtnSignIn_Object()->setDisabled(true);
	m_pSignInView->Get_pEditUser_Object()->setDisabled(true);
	m_pSignInView->Get_pEditPwd_Object()->setDisabled(true);
	m_pOverlay->Get_pButton()->setDisabled(true);

	/*显示加载控件，使能加载*/
#if 0
	m_progresswait->show();	// 显示
	m_progresswait->Progresswait_Start_Timer();
#endif
	m_progresspercent->show();	// 显示
	progressTimer->start(110);	// 启动定时器
}

void LoginCard::SignUp(const QString nickName, const QString user, const QString pwd)
{
	bool count = true;

#ifdef QT_Loginview_DEBUG
	qDebug() << "昵称:" << nickName << "注册用户名:" + user + "注册密码:" + pwd;
#endif

	// 不操作直接点击注册的
	if (("" == nickName) || ("" == user) || ("" == pwd))
	{
		login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("请输入信息!"));
		return;
	}
	// 昵称为空 或 昵称长度超出最大长度
	if ((" " == nickName) || (nickName.length() > SignUp_Name_MAX_LEN))
	{
		count = false;
		// append-拼接字符串
		login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("昵称不能为空,且长度不能大于").append(STRINGIFY(SignUp_Name_MAX_LEN)).append("!"));
	}
	// 账号为空 或 账号长度超出最大长度
	if ((" " == user) || (user.length() > SignUpIn_User_MAX_LEN))
	{
		count = false;
		login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("账号不能为空,且长度不能大于").append(STRINGIFY(SignUpIn_User_MAX_LEN)).append("!"));
	}
	else
	{
		// 判断是否只有字母和数字
		if (false == PublicClass::Letter_Number_isValid(user.toStdString()))
		{
			count = false;
			login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("账号只能是英文或数字!"));
		}
	}

	// 密码为空 或 密码长度超出最大长度
	if ((" " == pwd) || (pwd.length() > SignUpIn_Pwd_MAX_LEN))
	{
		count = false;
		login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("密码不能为空,且长度不能大于").append(STRINGIFY(SignUpIn_Pwd_MAX_LEN)).append("!"));
	}
	else
	{
		// 判断是否只有字母和数字
		if (false == PublicClass::Letter_Number_isValid(pwd.toStdString()))
		{
			count = false;
			login_Msg->Push(MessageType::MESSAGE_TYPE_ERROR, QString("密码只能是英文或数字!"));
		}
	}

	// 上面步骤有一个不行则退出
	if (count != true)
	{
		return;
	}

	// 判断数据库是否已存在相同用户名(待写)

	// 注册成功保存账号密码到数据库(待写)

	// 清空注册页面输入的内容，弹出注册成功框
	m_pSignUpView->Clear();
	//login_Msg->Push(MessageType::MESSAGE_TYPE_SUCCESS, QString("注册成功"));
	login_Msg->Push(MessageType::MESSAGE_TYPE_SUCCESS, QString("功能暂未开放"));
}



/*图层--------------------------------------------------------------------------------------------------------------------------------------------*/

LoginOverlay::LoginOverlay(QWidget* parent)
	: QWidget(parent)
	, m_bAni(false)
{
	// 注册了一个名为 LoginStatus 的元类型（Meta Type）
	qRegisterMetaType<LoginStatus>("LoginStatus");
	// 设置 Overlay 的大小为父窗口的一半宽度，高度为父窗口的高度
	setFixedSize(parentWidget()->width() / 2, parentWidget()->height());

	LoginOverlay::Init();	// 初始化
}

LoginOverlay::~LoginOverlay()
{
#ifdef QT_Loginview_DEBUG
	qDebug() << "delete LoginOverlay";
#endif
	LoginOverlay::disconnect(m_pButton, nullptr, this, nullptr);
}


void LoginOverlay::Init()
{
	/*LoginOverlay 窗口基本设置*/
	setObjectName(QStringLiteral("login_overlay"));  // 给窗口设置对象名
	setStyleSheet(LoginviewParameter.qss);	// 设置窗口样式

	/*创建按钮(切换登陆与注册)*/
	m_pButton = new QPushButton(this);
	m_pButton->setObjectName(QStringLiteral("m_pButton"));
	// 设置鼠标样式为手形
	m_pButton->setCursor(Qt::PointingHandCursor);
	// 设置按钮大小
	m_pButton->setFixedSize(width() * 0.36, 60);
	if (m_enStatus == LoginStatus::SignIn)
	{
		m_pButton->setText(QStringLiteral("注册"));  // 设置按钮文本为"注册"
	}
	else
	{
		m_pButton->setText(QStringLiteral("登陆"));  // 设置按钮文本为"登录"
	}
	// 将按钮移动到窗口中央位置
	m_pButton->move((width() - m_pButton->width()) / 2, (height() - m_pButton->height()) / 2);
	// 将 Overlay 窗口置于父窗口之上
	raise();

	/*连接处理*/
	LoginOverlay::LoginOverlay_Connect_Handler();
}

void LoginOverlay::LoginOverlay_Connect_Handler()
{
	// 连接按钮的点击事件和 ChangeStatus 槽函数
	connect(m_pButton, &QPushButton::clicked, this, &LoginOverlay::ChangeStatus);
}

void LoginOverlay::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.initFrom(this);

	QPainter p(this);
	// 设置抗锯齿和平滑绘图
	p.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);  // 绘制 Overlay 的背景

	QWidget::paintEvent(event);
}

void LoginOverlay::ChangeStatus()
{
	// 检查是否动画正在进行
	if (m_bAni)
		return;

	// 将动画进行中标志设置为 true
	m_bAni = true;

	// 创建一个顺序动画组以协调动画
	QSequentialAnimationGroup* pOpacityGroup = new QSequentialAnimationGroup(this);

	// 创建用于叠加和按钮的属性动画
	QPropertyAnimation* an = new QPropertyAnimation(this, "geometry");
	QPropertyAnimation* an2 = new QPropertyAnimation(m_pButton, "geometry");
	QPropertyAnimation* an3 = new QPropertyAnimation(m_pButton, "geometry");

	// 连接槽，当第一个动画完成时调用
	connect(an, &QPropertyAnimation::finished, this, [&, an]()mutable
		{
			delete an;
			an = nullptr;
			// 将动画进行中标志设置为 false
			m_bAni = false;

			// 进行判断
			if (m_enStatus == LoginStatus::SignIn)
			{
				m_pButton->setText(QStringLiteral("注册"));  // 设置按钮文本为"注册"
			}
			else
			{
				m_pButton->setText(QStringLiteral("登陆"));  // 设置按钮文本为"登录"
			}
		});

	// ...

	// 检查当前状态并相应配置动画
	if (m_enStatus == LoginStatus::SignIn)
	{
		// 从左到右的移动动画（注册）
		m_enStatus = LoginStatus::SignUp;
		// 设置叠加和按钮动画的结束值
		an->setEndValue(QRect(width(), 0, width(), height()));
		an2->setEndValue(QRect(-m_pButton->width(), m_pButton->pos().y(), m_pButton->width(), m_pButton->height()));
		an3->setStartValue(QRect(width() + m_pButton->width(), m_pButton->pos().y(), m_pButton->width(), m_pButton->height()));
	}
	else
	{
		// 从右到左的移动动画
		m_enStatus = LoginStatus::SignIn;
		an->setEndValue(QRect(0, 0, width(), height()));
		an2->setEndValue(QRect(width() + m_pButton->width(), m_pButton->pos().y(), m_pButton->width(), m_pButton->height()));
		an3->setStartValue(QRect(-m_pButton->width(), m_pButton->pos().y(), m_pButton->width(), m_pButton->height()));
	}

	an3->setEndValue(QRect(m_pButton->pos().x(), m_pButton->pos().y(), m_pButton->width(), m_pButton->height()));

#ifdef QT_Loginview_DEBUG
	qDebug() << "枚举类型:" << static_cast<int>(m_enStatus);
#endif

	// 发送状态改变信号
	emit StatusChanged(m_enStatus);
	pOpacityGroup->addAnimation(an2);
	pOpacityGroup->addAnimation(an3);
	an->start();
	pOpacityGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

QPushButton* LoginOverlay::Get_pButton()
{
	return m_pButton;
}





/*登录界面--------------------------------------------------------------------------------------------------------------------------------------------*/

SignInView::SignInView(QWidget* parent)
	: QWidget(parent)
{
	SignInView::Init();
}

SignInView::~SignInView()
{
#ifdef QT_Loginview_DEBUG
	qDebug() << "delete SignInView";
#endif
	SignInView::disconnect(m_pBtnSignIn, nullptr, this, nullptr);
}

void SignInView::Clear()
{
	// 清空编辑框内容
	m_pEditPwd->clear();
	m_pEditUser->clear();
}

void SignInView::Init()
{
	// 设置固定大小
	setFixedSize(VICE_WINDOW_W, VICE_WINDOW_H);
	setObjectName(QStringLiteral("sign_in_view"));
	setStyleSheet(LoginviewParameter.qss);	// 设置窗口样式

	/*【垂直布局】*/

	m_pVMainLayout = new QVBoxLayout(this);
	m_pVMainLayout->setObjectName(QStringLiteral("m_pVMainLayout"));

	m_pLabelTitle = new QLabel(QStringLiteral("登录"));	// 创建标签控件
	m_pLabelTitle->setObjectName(QStringLiteral("m_pLabelTitle"));

	m_pEditUser = new QLineEdit(this);	// 创建文本框控件
	m_pEditUser->setObjectName(QStringLiteral("m_pEditUser"));
	m_pEditUser->setPlaceholderText(QStringLiteral("账号"));
	m_pEditUser->setPlaceholderText("测试账号: admin");

	m_pEditUser->setFixedSize(width() * 0.6, 65);

	m_pEditPwd = new QLineEdit(this);
	m_pEditPwd->setObjectName(QStringLiteral("m_pEditPwd"));
	m_pEditPwd->setEchoMode(QLineEdit::EchoMode::Password);
	m_pEditPwd->setPlaceholderText(QStringLiteral("密码"));
	m_pEditPwd->setPlaceholderText("测试密码: 88888");

	m_pEditPwd->setFixedSize(width() * 0.6, 65);

	m_pBtnSignIn = new QPushButton(QStringLiteral("登录"), this);
	m_pBtnSignIn->setObjectName(QStringLiteral("m_pBtnSignIn"));
	m_pBtnSignIn->setCursor(Qt::PointingHandCursor);
	m_pBtnSignIn->setFixedSize(m_pEditUser->width() * 0.6, 60);

	// 设置编辑框的焦点策略
	for (auto& edit : findChildren<QLineEdit*>())
	{
		edit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	}

	m_pLabelTitle->adjustSize(); // 调整标题标签的大小以适应内容
	m_pVMainLayout->addStretch(); // 在垂直布局中添加一个可伸缩的空间，使得下面的控件垂直居中
	m_pVMainLayout->addSpacing(40); // 在垂直布局中添加一个40像素的垂直间距
	m_pVMainLayout->addWidget(m_pLabelTitle, 0, Qt::AlignCenter); // 在垂直布局中添加标题标签，居中对齐
	m_pVMainLayout->addSpacing(40); // 在垂直布局中添加一个40像素的垂直间距
	m_pVMainLayout->addWidget(m_pEditUser, 0, Qt::AlignCenter); // 在垂直布局中添加账号编辑框，居中对齐
	m_pVMainLayout->addSpacing(40); // 在垂直布局中添加一个40像素的垂直间距
	m_pVMainLayout->addWidget(m_pEditPwd, 0, Qt::AlignCenter); // 在垂直布局中添加密码编辑框，居中对齐
	m_pVMainLayout->addSpacing(40); // 在垂直布局中添加一个40像素的垂直间距
	m_pVMainLayout->addWidget(m_pBtnSignIn, 0, Qt::AlignCenter); // 在垂直布局中添加登录按钮，居中对齐
	m_pVMainLayout->addStretch(); // 在垂直布局中再添加一个可伸缩的空间，使得下面的内容垂直居中

	SignInView::SignInView_ValidateControl();
	SignInView::SignInView_Connect_Handler();
}

void SignInView::SignInView_Connect_Handler()
{
	/*【连接1】连接登录按钮的点击信号到相应槽函数*/
	connect(m_pBtnSignIn, &QPushButton::clicked, this, &SignInView::ButtonSignInClicked);
}

void SignInView::SignInView_ValidateControl()
{
	this->m_pEditUser->setValidator(new QRegularExpressionValidator(QRegularExpression(R"(^[A-Za-z0-9]{0,5}$)"), m_pEditUser));	// 只能输入英文和数字长度范围0-5
	this->m_pEditPwd->setValidator(new QRegularExpressionValidator(QRegularExpression(R"(^[A-Za-z0-9]{0,5}$)"), m_pEditPwd));	// 只能输入英文和数字长度范围0-5
}

void SignInView::paintEvent(QPaintEvent* event)
{
	// 创建 QStyleOption 对象并初始化
	QStyleOption opt;
	opt.initFrom(this);

	QPainter p(this);
	// 使用当前样式绘制基本控件
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	// 调用基类的 paintEvent 函数
	QWidget::paintEvent(event);
}

void SignInView::ButtonSignInClicked()
{
	// 发送带有账号和密码信息的 Submitted 信号
	emit Submitted(m_pEditUser->text(), m_pEditPwd->text());
}

QLineEdit* SignInView::Get_pEditUser_Object()
{
	return m_pEditUser;
}

QLineEdit* SignInView::Get_pEditPwd_Object()
{
	return m_pEditPwd;
}

QPushButton* SignInView::Get_pBtnSignIn_Object()
{
	return m_pBtnSignIn;
}


/*注册界面--------------------------------------------------------------------------------------------------------------------------------------------*/

SignUpView::SignUpView(QWidget* parent)
	: QWidget(parent)
{
	SignUpView::Init();
}

SignUpView::~SignUpView()
{
#ifdef QT_Loginview_DEBUG
	qDebug() << "delete SignUpView";
#endif
	SignUpView::disconnect(m_pBtnSignUp, nullptr, this, nullptr);
}

void SignUpView::Clear()
{
	// 清空编辑框内容
	m_pEditNickName->clear();
	m_pEditPwd->clear();
	m_pEditUser->clear();
}

void SignUpView::Init()
{
	// 设置固定大小
	setFixedSize(VICE_WINDOW_W, VICE_WINDOW_H);
	setObjectName(QStringLiteral("sign_up_view"));
	setStyleSheet(LoginviewParameter.qss);	// 设置窗口样式

	/*【垂直布局】*/

	m_pVMainLayout = new QVBoxLayout(this);

	m_pLabelTitle = new QLabel(QStringLiteral("注册"));
	m_pLabelTitle->setObjectName(QStringLiteral("m_pLabelTitle"));

	m_pEditNickName = new QLineEdit(this);
	m_pEditNickName->setObjectName(QStringLiteral("m_pEditNickName"));
	m_pEditNickName->setPlaceholderText(QStringLiteral("昵称"));
	m_pEditNickName->setFixedSize(width() * 0.6, 65);

	m_pEditUser = new QLineEdit(this);
	m_pEditUser->setObjectName(QStringLiteral("m_pEditUser"));
	m_pEditUser->setPlaceholderText(QStringLiteral("账号"));
	m_pEditUser->setFixedSize(width() * 0.6, 65);

	m_pEditPwd = new QLineEdit(this);
	m_pEditPwd->setObjectName(QStringLiteral("m_pEditPwd"));
	m_pEditPwd->setEchoMode(QLineEdit::EchoMode::Password);
	m_pEditPwd->setPlaceholderText(QStringLiteral("密码"));
	m_pEditPwd->setFixedSize(width() * 0.6, 65);

	m_pBtnSignUp = new QPushButton(QStringLiteral("注册"), this);
	m_pBtnSignUp->setObjectName(QStringLiteral("m_pBtnSignUp"));
	m_pBtnSignUp->setCursor(Qt::PointingHandCursor);
	m_pBtnSignUp->setFixedSize(m_pEditUser->width() * 0.6, 60);

	// 设置编辑框的焦点策略
	for (auto& edit : findChildren<QLineEdit*>())
	{
		edit->setFocusPolicy(Qt::FocusPolicy::ClickFocus);
	}

	m_pLabelTitle->adjustSize();	// 调整标题标签的大小以适应内容
	m_pVMainLayout->addStretch();	// 在垂直布局中添加一个可伸缩的空间，使得下面的控件垂直居中
	m_pVMainLayout->addSpacing(40);	// 在垂直布局中添加一个40像素的垂直间距
	m_pVMainLayout->addWidget(m_pLabelTitle, 0, Qt::AlignCenter);	// 在垂直布局中添加标题标签，居中对齐
	m_pVMainLayout->addSpacing(40);	// 在垂直布局中添加一个40像素的垂直间距
	m_pVMainLayout->addWidget(m_pEditNickName, 0, Qt::AlignCenter);
	m_pVMainLayout->addSpacing(40);	// 在垂直布局中添加一个40像素的垂直间距
	m_pVMainLayout->addWidget(m_pEditUser, 0, Qt::AlignCenter);		// 在垂直布局中添加账号编辑框，居中对齐
	m_pVMainLayout->addSpacing(40);	// 在垂直布局中添加一个40像素的垂直间距
	m_pVMainLayout->addWidget(m_pEditPwd, 0, Qt::AlignCenter);	 // 在垂直布局中添加密码编辑框，居中对齐
	m_pVMainLayout->addSpacing(40);	// 在垂直布局中添加一个40像素的垂直间距
	m_pVMainLayout->addWidget(m_pBtnSignUp, 0, Qt::AlignCenter);	// 在垂直布局中添加注册按钮，居中对齐
	m_pVMainLayout->addStretch();	// 在垂直布局中再添加一个可伸缩的空间，使得下面的内容垂直居中

	SignUpView::SignUpView_ValidateControl();
	SignUpView::SignUpView_Connect_Handler();
}

void SignUpView::SignUpView_Connect_Handler()
{
	/*【连接1】连接注册按钮的点击信号到相应槽函数*/
	connect(m_pBtnSignUp, &QPushButton::clicked, this, &SignUpView::ButtonSignUpClicked);
}

void SignUpView::SignUpView_ValidateControl()
{
	this->m_pEditNickName->setValidator(new QRegularExpressionValidator(QRegularExpression(R"(^[一-龥A-Za-z0-9]{0,8}$)"), m_pEditNickName));	// 允许输入0-8位中文英文数字，其他的不能输入
	this->m_pEditUser->setValidator(new QRegularExpressionValidator(QRegularExpression(R"(^[A-Za-z0-9]{0,5}$)"), m_pEditUser));	// 只能输入英文和数字长度范围0-5
	this->m_pEditPwd->setValidator(new QRegularExpressionValidator(QRegularExpression(R"(^[A-Za-z0-9]{0,5}$)"), m_pEditPwd));	// 只能输入英文和数字长度范围0-5
}

void SignUpView::paintEvent(QPaintEvent* event)
{
	// 创建 QStyleOption 对象并初始化
	QStyleOption opt;
	opt.initFrom(this);

	QPainter p(this);
	// 使用当前样式绘制基本控件
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	// 调用基类的 paintEvent 函数
	QWidget::paintEvent(event);
}

void SignUpView::ButtonSignUpClicked()
{
	// 发送带有昵称、账号和密码信息的 Submitted 信号
	emit Submitted(m_pEditNickName->text(), m_pEditUser->text(), m_pEditPwd->text());
}


/*工具栏-------------------------------------------------------------------------------*/

WindowButton::WindowButton(QWidget* parent)
	:QWidget(parent)
{
	WindowButton::Init();	// 初始化
}

WindowButton::~WindowButton()
{
#ifdef QT_Loginview_DEBUG
	qDebug() << "delete WindowButton";
#endif
	WindowButton::disconnect(close_btn, nullptr, this, nullptr);
	WindowButton::disconnect(minimize_btn, nullptr, this, nullptr);
}

void WindowButton::Init()
{
	// 设置固定大小
	this->setFixedSize(TOOL_WINDOW_W, TOOL_WINDOW_H);
	setObjectName(QStringLiteral("windowbutton"));
	setStyleSheet(LoginviewParameter.qss);	// 设置窗口样式

	minimize_btn = new QPushButton("━", this);
	minimize_btn->setObjectName("minimize_btn");
	minimize_btn->setFixedSize(42, 42);

	close_btn = new QPushButton("✖", this);
	close_btn->setObjectName("close_btn");
	close_btn->setFixedSize(42, 42);

	// 右上角
	close_btn->move(width() - close_btn->width(), 0);	// width()是指当前widget对象的宽度就是WindowButton
	minimize_btn->move(width() - close_btn->width() * 2, 0);

#ifdef QT_Loginview_DEBUG
	qDebug() << "WindowButton宽度:" << width() << "WindowButton高度:" << height();
#endif

	WindowButton::WindowButton_Connect_Handler();
}

void WindowButton::WindowButton_Connect_Handler()
{
	// 关闭
	connect(close_btn, &QPushButton::clicked, [=]()
		{
			emit WindowButton_close_btn_Click();
		});
	// 最小化
	connect(minimize_btn, &QPushButton::clicked, [=]()
		{
			emit WindowButton_minimize_btn_Click();
		});
}

void WindowButton::paintEvent(QPaintEvent* event)
{
	// 创建 QStyleOption 对象并初始化
	QStyleOption opt;
	opt.initFrom(this);

	QPainter p(this);
	// 使用当前样式绘制基本控件
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	// 调用基类的 paintEvent 函数
	QWidget::paintEvent(event);
}