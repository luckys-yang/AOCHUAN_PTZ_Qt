﻿#pragma once
#ifndef LCDDATETIME_H
#define LCDDATETIME_H

#include <QLCDNumber>

/**
 * 当前时间LCD控件
 * 1:可设置时间字符串格式
 * 2:可设置中间点分隔符是否闪烁
 * 3:可实时显示当前时间
 */

class LcdDateTime : public QLCDNumber
{
    Q_OBJECT
        Q_PROPERTY(bool dotHide READ getDotHide WRITE setDotHide)
        Q_PROPERTY(QString format READ getFormat WRITE setFormat)
        Q_PROPERTY(int digitCount READ getDigitCount WRITE setDigitCount)

public:
    explicit LcdDateTime(QWidget* parent = 0);
    ~LcdDateTime();

private:
    bool dotHide;
    QString format;
    int digitCount;
    QTimer* timer;

public:
    bool getDotHide()               const;
    QString getFormat()             const;
    int getDigitCount()             const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    void start(int interval = 1000);
    void setDateTime();
    void setDotHide(bool dotHide);
    void setFormat(const QString& format);
};

#endif

