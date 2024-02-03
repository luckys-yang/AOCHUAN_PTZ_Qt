#pragma once
#ifndef SAVELOG_H
#define SAVELOG_H

#include <QObject>
class QFile;

class SaveLog : public QObject
{
    Q_OBJECT
public:
    static SaveLog* Instance(); // 获取SaveLog的单例实例
    explicit SaveLog(QObject* parent = 0);
    ~SaveLog();

private:
    static QScopedPointer<SaveLog> self;    // 静态指针，用于保存单例实例

    //文件对象
    QFile* file;
    //日志文件路径
    QString path;
    //日志文件名称
    QString name;
    //日志文件完整名称
    QString fileName;
    // 日志文件名称(xxx.txt)
    QString TxTfileName;
signals:
    void send(const QString& content);  // 信号，用于发送日志内容
    void UI_Signals_SendDebugMsg_DebugArea(const QString& msg);
public slots:
    //启动日志服务
    void start();
    //暂停日志服务
    void stop();
    //保存日志
    void save(const QString& content);

    //设置日志文件存放路径
    void setPath(const QString& path);
    //设置日志文件名称
    void setName(const QString& name);
    // 获取文件名称
    QString getFileName() const;
    // 获取日志文件存放路径
    QString getFilePath() const;
    /*
    * @brief: 发送调试信息到Debug区
    * @param: 待发送的信息颜色(十六进制或者颜色名)
    * @retval: 待发送的信息
    */
   void UI_SendDebugMsg_DebugArea(const QString& msg_color, const QString& msg);
public:
    bool SaveLogFile_Flag = false;
};

#endif