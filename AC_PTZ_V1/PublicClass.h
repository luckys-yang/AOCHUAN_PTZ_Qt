#pragma once
#ifndef PUBLICCALSS
#define PUBLICCLASS

#include <iostream>
#include<QRegularexpression>	// 正则表达式
#include <qvalidator.h>

class PublicClass 
{
public:
    enum RegExpType
    {
        Re_IPv4,    // 匹配IPv4地址
        Re_Port,    // 匹配端口号
        Re_LettersAndNumbers,   // 匹配数字和字母
        Re_PhoneNumber, // 匹配数字
        Re_Number,  // 匹配手机号
        Re_TwoBitHex,   // 匹配两位16进制数
        Re_0To10,   // 匹配0-10之间的数字
        Re_0To32,   // 匹配0-32之间的数字
        Re_0To100,  // 匹配0-100之间的数字
        Re_0To255,  // 匹配0-255之间的数字，或者0-1000之间的数字
        Re_0To1000, // 匹配0 - 1000之间的数字
        Re_0To65535,    // 匹配0-65535之间的数字
        Re_1To255,  // 匹配1-255之间的数字
        Re_1To1000, // 匹配1-1000之间的数字
        Re_1To65535,    // 匹配1-65535之间的数字
        Re_0P000To10,   // 匹配0到10之间小数点后三位的数字
        Re_0P000To100,  // 匹配0到100之间小数点后三位的数字，或者1到100之间的整数
        Re_0P000To65535,    // 匹配0到65535之间小数点后三位的数字，或者0到65535之间的整数
        Re_10P000To65535,   // 匹配10到65535之间小数点后三位的数字，或者10到65535之间的整数

        Re_Burden9999To9999,    // 匹配-9999~9999的数字
        Re_Burden9999P00To9999, // 匹配-9999.99 ~ 9999.99 的数字
        Re_Burden100P00To100,   // 匹配-100 ~ 100 的数字 小数2位
        Re_Burden30P00To30, // 匹配-30 ~ 30 的数字 小数2位
        Re_Burden99999To99999,    // 匹配-99999~99999的数字
        Re_ThreeNumRanggeBurden99999To99999,    // 匹配3个数，用,分隔每一个数范围是-99999~99999
        Re_ValidCharactersRegex,  // 匹配数字，分号，逗号，负号
        Re_Burden9999P0000To9999, // 匹配-9999.9999 ~ 9999.9999 的数字

        Re_All_MaxLen100,

        Re_user,    // 匹配用户名，可以包含数字、字母、汉字、下划线和空格
        Re_easypwd,     // 匹配简单密码，只能包含数字和字母，长度在8到16位之间
        Re_pwd, // 匹配密码，不能包含特殊字符（@#%:?/），可以包含任何其他字符
        Re_title    // 匹配标题，可以包含数字、字母、汉字、下划线和空格
    };
	
	~PublicClass();

	/*
	* @brief: 字母和数字有效，其他字符无效
	* @param: 字符串
	* @retval: 只有字母和数字返回true  否则返回false
	*/
	static bool Letter_Number_isValid(const std::string& str);
    static QRegularExpression getQRegExp(RegExpType type);
    static QRegularExpressionValidator* getValidator(RegExpType type);
private:
    PublicClass();
};

#endif
