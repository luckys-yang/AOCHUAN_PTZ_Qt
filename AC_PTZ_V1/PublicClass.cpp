#include "PublicClass.h"
#include <QWidget>
#include<QRegularexpression>	// 正则表达式


PublicClass::PublicClass()
{

}

PublicClass::~PublicClass()
{

}

bool PublicClass::Letter_Number_isValid(const std::string& str)
{
#if 1
    // 将输入的std::string转换为QString
    QString qstr = QString::fromStdString(str);

    // 获取字符串的字符数量
    int nCount = qstr.count();

    // 遍历字符串中的每个字符
    for (int i = 0; i < nCount; i++)
    {
        // 获取字符
        QChar cha = qstr.at(i);

        // 获取字符的Unicode值
        ushort uni = cha.unicode();

        // 检查是否为中文字符的Unicode范围
        if (uni >= 0x4E00 && uni <= 0x9FA5)
        {
            // 这个字符是中文，返回false
            return false;
        }
    }

    // 如果没有中文字符，返回true
    return true;
#elif 0

#endif
}

QRegularExpression PublicClass::getQRegExp(RegExpType type)
{
    switch (int(type))
    {
    case Re_IPv4:
        return QRegularExpression("((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})(\\.((2(5[0-5]|[0-4]\\d))|[0-1]?\\d{1,2})){3}");
    case Re_Port:
        return QRegularExpression("(([1-9]\\d{0,3})|([1-5]\\d{4})|(6([0-4]\\d{0,3}|5([0-4]\\d{0,2}|5([0-2]\\d|3[0-5])))))");
    case Re_LettersAndNumbers:
        return QRegularExpression("[0-9a-zA-Z]+");
    case Re_Number:
        return QRegularExpression("\\d+");
    case Re_PhoneNumber:
        return QRegularExpression("(13[0-9]|14[5|7]|15[0|1|2|3|4|5|6|7|8|9]|18[0|1|2|3|5|6|7|8|9])\\d{8}");
    case Re_TwoBitHex:
        return QRegularExpression("^([0-9a-fA-F]{4})$");
    case Re_0To10:
        return QRegularExpression("(\\d|10)");
    case Re_0To32:
        return QRegularExpression("(\\d|[0-2]\\d|3[0-2])");
    case Re_0To100:
        return QRegularExpression("\\d{1,2}|100");
    case Re_0To255:
    case Re_0To1000:
        return QRegularExpression("\\d{1,3}|1000");
    case Re_0To65535:
        return QRegularExpression("([1-5]?\\d{1,4})|(6([0-4]\\d{0,3}|5([0-4]\\d{0,2}|5([0-2]\\d|3[0-5]))))");
    case Re_1To255:
        return QRegularExpression("(1?[1-9]\\d{0,1}|2([0-4]\\d|5[0-5]))");
    case Re_1To1000:
        return QRegularExpression("([1-9]|[1-9]\\d{1,2}|1000)");
    case Re_1To65535:
        return QRegularExpression("(([1-9]\\d{0,3})|([1-5]\\d{4})|(6([0-4]\\d{0,3}|5([0-4]\\d{0,2}|5([0-2]\\d|3[0-5])))))");
    case Re_0P000To10:
        return QRegularExpression("([0-9]|[0-9]\\.[0-9]{1,3}|10)");
    case Re_0P000To100:
        return QRegularExpression("([0-9]|[0-9]\\.[0-9]{1,3}|[1-9][0-9]|[1-9][0-9]\\.[0-9]{1,3}|100)");
    case Re_0P000To65535:
        return QRegularExpression("([0-9]|[0-9]\\.[0-9]{1,3}|[1-9][0-9]|[1-9][0-9]\\.[0-9]{1,3}|[1-9]\\d{2}|[1-9]\\d{2}\\.[0-9]{1,3}|[1-9]\\d{3}|[1-9]\\d{3}\\.[0-9]{1,3}|[1-5]\\d{4}|[1-5]\\d{4}\\.[0-9]{1,3}|[6][0-4]\\d{3}|[6][0-4]\\d{3}\\.[0-9]{1,3}|[6][5][0-4]\\d{2}|[6][5][0-4]\\d{2}\\.[0-9]{1,3}|[6][5][5][0-2][0-9]|[6][5][5][0-2][0-9]\\.[0-9]{1,3}|[6][5][5][3][0-4]|[6][5][5][3][0-4]\\.[0-9]{1,3}|65535)");
    case Re_10P000To65535:
        return QRegularExpression("([1-9][0-9]|[1-9][0-9]\\.[0-9]{1,3}|[1-9]\\d{2}|[1-9]\\d{2}\\.[0-9]{1,3}|[1-9]\\d{3}|[1-9]\\d{3}\\.[0-9]{1,3}|[1-5]\\d{4}|[1-5]\\d{4}\\.[0-9]{1,3}|[6][0-4]\\d{3}|[6][0-4]\\d{3}\\.[0-9]{1,3}|[6][5][0-4]\\d{2}|[6][5][0-4]\\d{2}\\.[0-9]{1,3}|[6][5][5][0-2][0-9]|[6][5][5][0-2][0-9]\\.[0-9]{1,3}|[6][5][5][3][0-4]|[6][5][5][3][0-4]\\.[0-9]{1,3}|65535)");
    case Re_Burden9999To9999:
        return QRegularExpression("^(-?([1-9]\\d{0,3}|0|2048))$");
    case Re_Burden9999P00To9999:
        return QRegularExpression("^(-?\\d{1,4}(\\.\\d{1,2})?)$");
    case Re_Burden100P00To100:
        return QRegularExpression("^(-?\\d{1,2}(\\.\\d{1,2})?)$|^-100(\\.0{1,2})?$|^100(\\.0{1,2})?$");
    case Re_Burden30P00To30:
        return QRegularExpression("^(-?(30(\\.00)?|[0-2]?\\d(\\.\\d{1,2})?))$");
    case Re_Burden99999To99999:
        return QRegularExpression("^(-?[1-9]\\d{0,4}|0)(\\.\\d{1,2})?$");
    case Re_ThreeNumRanggeBurden99999To99999:
        return QRegularExpression("^(-?[1-9]\\d{0,4}|0),(-?[1-9]\\d{0,4}|0),(-?[1-9]\\d{0,4}|0)$");
    case Re_ValidCharactersRegex:
        return QRegularExpression("^[\\d,-;]+$");
    case Re_Burden9999P0000To9999:
        return QRegularExpression("^(-?\\d{1,4}(\\.\\d{1,4})?)$");

    case Re_All_MaxLen100:
        return QRegularExpression("^(.{1,100})$");
    case Re_user:
        return QRegularExpression("(^[a-zA-Z0-9-\u4e00-\u9fa5_ ]+$)");
    case Re_easypwd:
        return QRegularExpression("([0-9A-Za-z]{8,16})");
    case Re_pwd:
        return QRegularExpression("([^@#%:?/]*)");
    case Re_title:
        return QRegularExpression("(^[a-zA-Z0-9-\u4e00-\u9fa5_ ]+$)");
    }
    return QRegularExpression();
}

QRegularExpressionValidator* PublicClass::getValidator(RegExpType type)
{
    return new QRegularExpressionValidator(getQRegExp(type));
}

