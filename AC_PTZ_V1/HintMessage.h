#pragma once
#ifndef HINTMESSAGE_H
#define HINTMESSAGE_H

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>
#include <mutex>

// 调试打印
//#define QT_HintMessage_DEBUG

// 定义消息类型枚举
enum MessageType
{
	MESSAGE_TYPE_SUCCESS = 0x20,    // 成功
	MESSAGE_TYPE_ERROR, // 错误
	MESSAGE_TYPE_WARNING,   // 警告
	MESSAGE_TYPE_INFORMATION    // 信息
};

/*声明区-------------------------------------------------------------------------------*/

class HintMessageItem;  // 消息项类声明

/*主类HintMessage----------------------------------------------------------*/

class HintMessage : public QObject
{
	Q_OBJECT

public:
	HintMessage(QObject* parent);
	~HintMessage();
	
	/*
	* @brief: 初始化
	* @param: None
	* @retval: None
	*/
	void Init();
	/*
	* @brief: 推入消息
	* @param: 消息类型
	* @param: 消息内容
	* @retval: None
	*/
	void Push(MessageType type, QString content);

	/*
	* @brief: 设置消息显示的时间
	* @param: 显示时间，必须大于等于0，若等于0则不消失
	* @retval: None
	*/
	void SetDuration(int nDuration);

private:
	std::vector<HintMessageItem*> m_vecMessage; // 消息项容器(该向量存储的元素类型是指向 HintMessageItem 类的指针)
	std::mutex m_qMtx; // 互斥锁，用于线程安全操作
	int m_nWidth;   // 消息项宽度
	int m_nDuration;     // 消息显示时间

private slots:
	// 调整消息项位置的槽函数
	void adjustItemPos(HintMessageItem* pItem);
	// 移除消息项的槽函数
	void removeItem(HintMessageItem* pItem);
};

/*消息项类声明，继承自QWidget-------------------------------------------------*/

class HintMessageItem : public QWidget
{
	Q_OBJECT
public:
	// 构造函数
	explicit HintMessageItem(QWidget* parent = nullptr,
		MessageType type = MessageType::MESSAGE_TYPE_INFORMATION,
		QString content = "");
	// 析构函数
	~HintMessageItem() override;

	/*
	* @brief: 显示消息项
	* @param: None
	* @retval: None
	*/
	void Show();

	/*
	* @brief: 关闭消息项
	* @param: None
	* @retval: None
	*/
	void Close();

	/*
	* @brief: 设置消息显示时间
	* @param: 显示的时间
	* @retval: None
	*/
	void SetDuration(int nDuration);

protected:
	// 重写绘制事件(override)
	void paintEvent(QPaintEvent* event) override;

private:
	// 消息项出现动画
	void AppearAnimation();
	// 消息项消失动画
	void DisappearAnimation();

private:
	const int nIconMargin = 12; // 图标边距
	const int nLeftMargin = 64; // 左边距
	const int nTopMargin = 10;  // 顶部边距
	const int nMinWidth = 400;  // 最小宽度
	const int nMinHeight = 70;  // 最小高度
	QLabel* m_pLabelIcon;   // 图标标签指针
	QLabel* m_pLabelContent;    // 内容标签指针
	QTimer m_lifeTimer; // 生命周期定时器
	int m_nWidth;   // 消息项宽度
	int m_nHeight;  // 消息项高度
	int m_nDuration;    // 消息显示时间

signals:
	// 消息项准备移除的信号
	void itemReadyRemoved(HintMessageItem* pItem);
	// 消息项移除的信号
	void itemRemoved(HintMessageItem* pItem);
};

#endif
