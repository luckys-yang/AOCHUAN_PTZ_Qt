#pragma once
#ifndef MAINPAGE7_H
#define MAINPAGE7_H

#include <QWidget>
#include "ui_Mainwindow.h"
#include "Mainwindow.h"
#include "FlatUI.h"
#include "AppSettings.h"
#include <QTimer>
#include "NavBar.h"

#define QT_MainPage7_Debug 1

/*链表 -- 插入图片*/
struct ImageItem
{
    QString imagePath;  // 图片路径
    QString imageName; // 图片名称
    ImageItem* next;    // 下一个图片节点指针

    ImageItem(const QString& path, const QString& name) : imagePath(path), imageName(name), next(nullptr) {}  // 构造函数，初始化图片路径和指针
};

class ImageList
{
public:
    ImageList() : head(nullptr), current(nullptr) {}    // 构造函数，初始化链表头指针和当前图片节点指针

    ~ImageList()
    {
        while (head)
        {
            ImageItem* item = head;
            head = item->next;
            delete item;
        }
    }

    void addItem(const QString& path, const QString& name)
    {
        ImageItem* item = new ImageItem(path, name);  // 创建新的图片节点
        if (!head)
        {
            head = item;    // 若链表为空，则将新节点设为头节点
            current = item; // 并将当前节点指针指向新节点
        }
        else
        {
            current->next = item;   // 若链表非空，则将新节点接在当前节点之后
            current = item; // 并将当前节点指针指向新节点
        }
    }
    // 返回当前节点的图片路径
    QString getCurrentImagePath() const
    {
        if (current)
        {
            return current->imagePath;  // 返回当前节点的图片路径
        }
        return "";
    }
    // 返回当前节点的图片名称
    QString getCurrentImageName() const
    {
        if (current)
        {
            return current->imageName; // 返回当前节点的图片名称
        }
        return "";
    }
    // 将当前节点指针指向下一个节点
    QString getNextImagePath()
    {
        if (current && current->next)   
        {
            current = current->next;    // 将当前节点指针指向下一个节点
        }
        else
        {
            current = head; // 若已到达尾节点，则将当前节点指针重新指向头节点
        }
        return getCurrentImagePath();   // 返回当前节点的图片路径
    }

private:
    ImageItem* head;    // 链表头指针
    ImageItem* current; // 当前图片节点指针
};  



class MainPage7 : public QWidget
{
    Q_OBJECT
public:
    MainPage7(QWidget* parent);
    ~MainPage7();

    // 页面初始化
    void MainPage7_Init();
    // 页面连接
    void MainPage7_Connect_Handler();

public slots:
    // 图片被点击处理
    void MainPage7_Image_Clicked_Hanndler();

public:
    ImageList imageList;
    Ui::MainwindowClass* MainPage7_ui;	// ui指针
};

#endif