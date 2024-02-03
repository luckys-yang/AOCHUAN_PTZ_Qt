#include "Mainwindow.h"
#include <QtWidgets/QApplication>
#include "LoginView.h"

/*声明区-----------------------------------------------------------------------*/
void Main_SwitchWindow(LoginView& loginView, Mainwindow& mainWindow);


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	Mainwindow main;
	LoginView login;

#if 1
	Main_SwitchWindow(login, main);
	login.show();  // 登陆窗口
#elif 0
	main.show();
#endif

	return a.exec();
}

// 切换窗口
void Main_SwitchWindow(LoginView& loginView, Mainwindow& mainWindow)
{
	QObject::connect(loginView.Get_pLoginCard()->Get_progresspercent(), &ProgressPercent::valueChanged, [&](int value)
		{
			if (value >= 100)
			{
				loginView.close();
				mainWindow.show();
			}
		});
	/*托盘连接信号*/
	QObject::connect(mainWindow.m_trayIcon, &QSystemTrayIcon::activated, [&](QSystemTrayIcon::ActivationReason reason)
		{
			switch (reason)
			{
			case QSystemTrayIcon::Unknown:
			{
				qDebug() << "Unknown";
				break;
			}
			case QSystemTrayIcon::Context:			//右键
			{
				qDebug() << "Context";
				break;
			}
			case QSystemTrayIcon::DoubleClick:		//双击
			{
				qDebug() << "DoubleClick";
				break;
			}
			case QSystemTrayIcon::Trigger:			//左键点击
			{
				if (true == loginView.isVisible())	// 登录窗口显示
				{
					if (loginView.isMinimized())
					{
						loginView.showNormal();
						loginView.raise();
					}
					else
					{
						loginView.showMinimized();
					}
				}
				else if (true == mainWindow.isVisible())	// 主页面显示
				{
					if (mainWindow.isMinimized())
					{
						mainWindow.showNormal();
						mainWindow.raise();
					}
					else
					{
						mainWindow.showMinimized();
					}
				}
				qDebug() << "Trigger";
				break;
			}
			case QSystemTrayIcon::MiddleClick:		//中击
			{
				qDebug() << "MiddleClick";
				break;
			}
			default: break;
			}
		});
}