#include "SaveLog.h"
#include <QMutex>
#include <QFile>
#include <QDatetime>
#include <QApplication>
#include <QTimer>
#include <QStringlist>

// 获取当前日期的字符串表示形式

QString QDATE = QDate::currentDate().toString("yyyy-MM-dd");

void Log(QtMsgType type, const QMessageLogContext&, const QString& msg)
{
    //加锁,防止多线程中qdebug太频繁导致崩溃
    QMutex mutex;
    QMutexLocker locker(&mutex);
    QString content;

    //这里可以根据不同的类型加上不同的头部用于区分
    switch (type)
    {
    case QtDebugMsg:    // 对于调试消息，可以加上特定的标识
        content = QString("【调试】%1").arg(msg);
        break; 

    case QtWarningMsg:  // 对于警告消息，可以加上特定的标识
        content = QString("【警告】%1").arg(msg);
        break;

    case QtCriticalMsg: // 对于严重错误消息，可以加上特定的标识
        content = QString("【严重错误】%1").arg(msg);
        break;

    case QtFatalMsg:    // 对于致命错误消息，可以加上特定的标识
        content = QString("【致命错误】%1").arg(msg);
        break;
    }

    // 将日志内容保存
    SaveLog::Instance()->save(content);
}

// 使用QScopedPointer定义的一个类的静态成员变量
QScopedPointer<SaveLog> SaveLog::self;

SaveLog* SaveLog::Instance()
{
    if (self.isNull())  // 如果单例实例尚未创建
    {
        static QMutex mutex;    // 使用静态局部变量来确保线程安全的初始化
        QMutexLocker locker(&mutex);
        if (self.isNull())  // 双重检查锁定，确保在多线程环境下仅创建一个实例
        {
            self.reset(new SaveLog);
        }
    }

    return self.data(); // 返回单例实例的指针
}

SaveLog::SaveLog(QObject* parent) : QObject(parent)
{
    file = new QFile(this); // 创建文件对象
    //默认取应用程序根目录
    path = qApp->applicationDirPath();
    //默认取应用程序可执行文件名称
    QString str = qApp->applicationFilePath();
    QStringList list = str.split("/");
    name = list.at(list.count() - 1).split(".").at(0);
    fileName = "";
    save("");
}

SaveLog::~SaveLog()
{
    file->close();  // 关闭文件
    qDebug() << "delete SaveLog";
}

void SaveLog::start()
{
    qInstallMessageHandler(Log);    // 安装日志钩子,输出调试信息到文件,便于调试
}

void SaveLog::stop()
{
    qInstallMessageHandler(0);  // 卸载日志钩子
}

void SaveLog::save(const QString& content)
{
        // 方法改进: 之前每次输出日志都打开文件，改成只有当日期改变时才新建和打开文件
        // 构建日志文件名，包含路径、应用程序名称、日期
        QString fileName = QString("%1/%2_log_%3.txt").arg(path).arg(name).arg(QDATE);
        TxTfileName = QString("%1_log_%2.txt").arg(name).arg(QDATE);
        // 如果文件名与当前文件名不同，说明日期已经改变，需要重新打开文件
        if (this->fileName != fileName)
        {
            this->fileName = fileName;
            // 如果文件已经打开，先关闭
            if (file->isOpen())
            {
                file->close();
            }
            // 设置新的文件名，并以追加写入的方式打开文件
            file->setFileName(fileName);
            file->open(QIODevice::WriteOnly | QIODevice::Append | QFile::Text);
        }
        // 使用QTextStream写入日志内容到文件
        QTextStream logStream(file);
        logStream << content << "\n";
}

void SaveLog::setPath(const QString& path)
{
    this->path = path;  // 设置日志文件存放路径
}

void SaveLog::setName(const QString& name)
{
    this->name = name;  // 设置日志文件名称
}

QString SaveLog::getFileName() const
{
    return this->TxTfileName;
}

QString SaveLog::getFilePath() const
{
    return this->path;
}

void SaveLog::UI_SendDebugMsg_DebugArea(const QString& msg_color, const QString& msg)
{
    // 📢
    QString Msg = QString("[%1] <font color=\"%2\">%3</font>").arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss").append("➜")).arg(msg_color).arg(msg);
    // 发送信号给Debug区控件
    emit UI_Signals_SendDebugMsg_DebugArea(Msg);

    // 判断保存调试到文件标志位是否置1，是则输出调试信息
    if (true == SaveLog::Instance()->SaveLogFile_Flag)
    {
        qDebug() << QDateTime::currentDateTime().toString("[yyyy-MM-dd HH:mm:ss]").append("➜").append(msg);	// 日志保存则不要html相关的样式所以直接发送源字串符
    }
}