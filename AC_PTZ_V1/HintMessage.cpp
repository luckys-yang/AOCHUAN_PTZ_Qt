#include "HintMessage.h"
#include <QPainter>
#include <QStyleOption>
#include <QGraphicsOpacityEffect>
#include <QSequentialAnimationGroup>
#include <algorithm>
#include <QFile>

#ifdef QT_HintMessage_DEBUG
#include <QDebug>
#endif

// 控制消息项之间的间距
static int nMessageItemMargin = 20;

struct HintMessageParameter_t {
	QString qss;	// 存储样式表
};

static HintMessageParameter_t HintMessageParameter =
{
	""
};

/*主类HintMessage--------------------------------------------------------------------------*/

// 构造函数，初始化 HintMessage 类
HintMessage::HintMessage(QObject* parent)
	: QObject(parent)
{
	// 检查父对象是否为空，若为空则抛出运行时错误
	if (parent == nullptr)
		throw std::runtime_error("message structure error!");

	// 尝试将父对象转换为 QWidget 指针，若失败则抛出运行时错误
	auto widget = qobject_cast<QWidget*>(parent);
	if (widget == nullptr)
	{
		throw std::runtime_error("message structure error!");
	}

	// 获取父 Widget 的宽度，并初始化消息的宽度和显示时间
	m_nWidth = widget->width();
	m_nDuration = 3000;

	// 预留消息向量的空间，提高性能
	m_vecMessage.reserve(50);

	HintMessage::Init();
}


HintMessage::~HintMessage()
{
#ifdef QT_HintMessage_DEBUG
	qDebug() << "delete HintMessage";
#endif // QT_HintMessage_DEBUG
}

void HintMessage::Init()
{
	// 读取css样式
	QFile file(":/HintMessage/Resource/CSS/HintMessage.css");
	if (true == file.open(QFile::ReadOnly))
	{
		HintMessageParameter.qss = file.readAll();
		file.close();	// 关闭文件
#ifdef QT_HintMessage_DEBUG
		qDebug() << HintMessageParameter.qss << Qt::endl;
#endif
	}
	else
	{
#ifdef QT_HintMessage_DEBUG
		qDebug() << "open file error";
#endif
	}
}

void HintMessage::Push(MessageType type, QString content)
{
	// 使用 unique_lock 来锁定互斥量，确保线程安全
	std::unique_lock<std::mutex> lck(m_qMtx);

	// 初始化消息项的高度
	int height = 0;

	// 计算消息项的高度，以便确定新消息的位置
	for_each(m_vecMessage.begin(), m_vecMessage.end(), [&height](HintMessageItem* pTp) mutable {
		height += (nMessageItemMargin + pTp->height());
		});

	// 创建新的消息项
	HintMessageItem* pItem = new HintMessageItem(qobject_cast<QWidget*>(parent()), type, content);

	// 连接消息项的信号与槽，以便在相应事件发生时执行特定操作
	connect(pItem, &HintMessageItem::itemReadyRemoved, this, &HintMessage::adjustItemPos);
	connect(pItem, &HintMessageItem::itemRemoved, this, &HintMessage::removeItem);

	// 设置消息项显示的持续时间
	pItem->SetDuration(m_nDuration);

	// 计算新消息项的位置
	height += nMessageItemMargin;
	pItem->move(QPoint((m_nWidth - pItem->width()) / 2, height));

	// 将新消息项加入消息向量
	m_vecMessage.emplace_back(pItem);

	// 显示新消息项
	pItem->Show();
}

void HintMessage::SetDuration(int nDuration)
{
	if (nDuration < 0)
	{
		nDuration = 0;
	}
	m_nDuration = nDuration;    // 消息显示时间等于设置的消息时间
}

// 调整消息项位置的槽函数
void HintMessage::adjustItemPos(HintMessageItem* pItem)
{
	pItem->Close();
}

// 从消息提示框中移除指定的消息项
void HintMessage::removeItem(HintMessageItem* pItem)
{
	// 使用 unique_lock 来锁定互斥量，确保线程安全
	std::unique_lock<std::mutex> lck(m_qMtx);

	// 在消息向量中查找并移除指定的消息项
	for (auto itr = m_vecMessage.begin(); itr != m_vecMessage.end();)
	{
		if (*itr == pItem)
		{
			m_vecMessage.erase(itr);
#ifdef QT_HintMessage_DEBUG
			qDebug() << "erased";
#endif
			break;
		}
		else ++itr;
	}

	// 重新计算消息项的高度
	int height = nMessageItemMargin;

	// 遍历消息向量，为每个消息项创建动画
	for_each(m_vecMessage.begin(), m_vecMessage.end(), [&](HintMessageItem* pTp)
		{
			// 创建消息项的位置变化动画
			QPropertyAnimation* pAnimation1 = new QPropertyAnimation(pTp, "geometry", this);
			pAnimation1->setDuration(300);
			pAnimation1->setStartValue(QRect(pTp->pos().x(),
				pTp->pos().y(),
				pTp->width(),
				pTp->height()));
			pAnimation1->setEndValue(QRect(pTp->pos().x(),
				height,
				pTp->width(),
				pTp->height()));

			// 启动动画，设置动画结束后自动删除
			pAnimation1->start(QAbstractAnimation::DeletionPolicy::DeleteWhenStopped);

			// 更新消息项的垂直位置
			height += (nMessageItemMargin + pTp->height());
		});
};



/*消息项类声明，继承自QWidget--------------------------------------------------------------*/

HintMessageItem::HintMessageItem(QWidget* parent, MessageType type, QString content)
	: QWidget(parent)
{
	// 设置消息项的显示时长为 3000 毫秒
	m_nDuration = 3000;

	// 设置消息项的窗口标志，使其为无边框窗口
	this->setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

	// 设置消息项的属性，使其支持透明背景
	this->setAttribute(Qt::WA_TranslucentBackground);

	// 创建消息项的图标标签，并将其作为子组件添加到消息项中
	m_pLabelIcon = new QLabel(this);

	switch (type)
	{
	case MessageType::MESSAGE_TYPE_SUCCESS:
	{
		// 设置消息项的对象名称
		this->setObjectName(QStringLiteral("HintMessage_Success_item"));
		m_pLabelIcon->setObjectName("HintMessage_Success_Lable");
		m_pLabelIcon->setPixmap(QPixmap(":/HintMessage/Resource/Images/type_success.png"));
		break;
	}
	case MessageType::MESSAGE_TYPE_ERROR:
	{
		// 设置消息项的对象名称
		this->setObjectName(QStringLiteral("HintMessage_Error_item"));
		m_pLabelIcon->setObjectName("HintMessage_Error_Lable");
		m_pLabelIcon->setPixmap(QPixmap(":/HintMessage/Resource/Images/type_error.png"));
		break;
	}
	case MessageType::MESSAGE_TYPE_WARNING:
	{
		// 设置消息项的对象名称
		this->setObjectName(QStringLiteral("HintMessage_Warning_item"));
		m_pLabelIcon->setObjectName("HintMessage_Warning_Lable");
		m_pLabelIcon->setPixmap(QPixmap(":/HintMessage/Resource/Images/type_warning.png"));
		break;
	}
	case MessageType::MESSAGE_TYPE_INFORMATION:
	{
		// 设置消息项的对象名称
		this->setObjectName(QStringLiteral("HintMessage_Information_item"));
		m_pLabelIcon->setObjectName("HintMessage_Information_Lable");
		m_pLabelIcon->setPixmap(QPixmap(":/HintMessage/Resource/Images/type_infomation.png"));
		break;
	}
	default:break;
	}
	this->setStyleSheet(HintMessageParameter.qss);	// 设置样式

	// 创建消息项的内容标签，并将其作为子组件添加到消息项中
	m_pLabelContent = new QLabel(this);

	// 设置内容标签的文本内容
	m_pLabelContent->setText(content);

	// 调整内容标签的大小以适应文本内容
	m_pLabelContent->adjustSize();

	// 计算消息项的宽度和高度
	m_nWidth = m_pLabelContent->width() + nLeftMargin * 2;
	m_nHeight = m_pLabelContent->height() + nTopMargin * 2;

	// 如果计算得到的宽度小于最小宽度，设置宽度为最小宽度
	if (m_nWidth < nMinWidth) m_nWidth = nMinWidth;

	// 如果计算得到的高度小于最小高度，设置高度为最小高度
	if (m_nHeight < nMinHeight) m_nHeight = nMinHeight;

	// 调整消息项的大小
	resize(m_nWidth, m_nHeight);

	// 将内容标签移动到指定位置，使其在垂直方向居中显示
	m_pLabelContent->move(nLeftMargin, (m_nHeight - m_pLabelContent->height()) / 2);

	// 将图标标签移动到指定位置，使其在垂直方向居中显示
	m_pLabelIcon->move(nIconMargin, (m_nHeight - m_pLabelIcon->height()) / 2);

	// 连接消息项的生命周期定时器的超时信号到槽函数
	connect(&m_lifeTimer, &QTimer::timeout, this, [&]()
		{
			// 定时器超时时停止定时器，发射消息项准备移除的信号
			m_lifeTimer.stop();
			emit itemReadyRemoved(this);
		});

	// 隐藏消息项
	hide();
}

HintMessageItem::~HintMessageItem()
{
#ifdef QT_HintMessage_DEBUG
	qDebug() << "delete HintMessageItem";
#endif // QT_HintMessage_DEBUG
	if (m_lifeTimer.isActive())
	{
		m_lifeTimer.stop();
	}
}

void HintMessageItem::Show()
{
	show();
	if (m_nDuration > 0)
	{
		m_lifeTimer.start(m_nDuration);
	}
	HintMessageItem::AppearAnimation();
}

void HintMessageItem::Close()
{
	HintMessageItem::DisappearAnimation();
}

void HintMessageItem::SetDuration(int nDuration)
{
	m_nDuration = nDuration;
}

void HintMessageItem::paintEvent(QPaintEvent* event)
{
	QStyleOption opt;
	opt.initFrom(this);

	QPainter p(this);
	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}

void HintMessageItem::AppearAnimation()
{
	// 创建位置变化的属性动画，作用于消息项的 geometry 属性
	QPropertyAnimation* animation = new QPropertyAnimation(this, "geometry");

	// 设置动画持续时间为 20 毫秒
	animation->setDuration(20);

	// 设置动画的起始值，将消息项上移一个消息项的间距
	animation->setStartValue(QRect(pos().x(), pos().y() - nMessageItemMargin, m_nWidth, m_nHeight));

	// 设置动画的结束值，将消息项还原到原始位置
	animation->setEndValue(QRect(pos().x(), pos().y(), m_nWidth, m_nHeight));

	// 启动动画，并设置动画结束后自动删除
	animation->start(QAbstractAnimation::DeletionPolicy::DeleteWhenStopped);

}

void HintMessageItem::DisappearAnimation()
{
	// 创建透明度效果对象，作用于消息项
	QGraphicsOpacityEffect* pOpacity = new QGraphicsOpacityEffect(this);

	// 设置透明度效果的初始透明度为 1（完全不透明）
	pOpacity->setOpacity(1);

	// 将透明度效果应用到消息项上
	setGraphicsEffect(pOpacity);

	// 创建透明度属性动画，作用于透明度效果的 opacity 属性
	QPropertyAnimation* pOpacityAnimation2 = new QPropertyAnimation(pOpacity, "opacity");

	// 设置透明度动画的持续时间为 500 毫秒
	pOpacityAnimation2->setDuration(500);

	// 设置透明度动画的起始值为 1（完全不透明）
	pOpacityAnimation2->setStartValue(1);

	// 设置透明度动画的结束值为 0（完全透明）
	pOpacityAnimation2->setEndValue(0);

	// 启动透明度动画，并设置动画结束后自动删除
	pOpacityAnimation2->start(QAbstractAnimation::DeletionPolicy::DeleteWhenStopped);

	// 连接透明度动画的完成信号到槽函数
	connect(pOpacityAnimation2, &QPropertyAnimation::finished, this, [&]()
		{
			// 发射消息项移除的信号，然后延迟删除消息项本身
			emit itemRemoved(this);
			deleteLater();
		});
}
