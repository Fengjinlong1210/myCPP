剑指 Offer 20. 表示数值的字符串
请实现一个函数用来判断字符串是否表示数值（包括整数和小数）。

数值（按顺序）可以分成以下几个部分：

若干空格
一个 小数 或者 整数
（可选）一个 'e' 或 'E' ，后面跟着一个 整数
若干空格
小数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
下述格式之一：
至少一位数字，后面跟着一个点 '.'
至少一位数字，后面跟着一个点 '.' ，后面再跟着至少一位数字
一个点 '.' ，后面跟着至少一位数字
整数（按顺序）可以分成以下几个部分：

（可选）一个符号字符（'+' 或 '-'）
至少一位数字

class Solution {
public:
    bool isNumber(string s) 
    {
        //先去除所有的空格
        int i = 0;
        while(i < s.size() && s[i] == ' ')
        {
            ++i;
        }
        s = s.substr(i);
        if(s.size() == 0) return false;
        while(s.back() == ' ')
        {
            s.pop_back();
        }
        //处理以后就是完整的数字,不包含空格
        bool numFlag = false;
        bool dotFlag = false;
        bool eFlag = false;
        //只有最前面和最后面可以出现空格
        //如果有符号，一定是在一开始出现或在e后面
        //有.时，一定要没有出现过.和e
        for(int i = 0; i < s.size(); ++i)
        {
            if(isdigit(s[i]))
            {
                //有数字出现    
                numFlag = true;
            }
            else if(s[i] == '.' && !dotFlag && !eFlag)
            {
                //.出现时, 必须没有e和点
                dotFlag = true;
            }
            else if((s[i] == 'e' || s[i] == 'E') && !eFlag && numFlag)
            {
                //有e时, 需要没出现过e,并且必须出现过数字,后面必须跟整数
                eFlag = true;
                numFlag = false;//  表示e后面要有整数
            }
            else if((s[i] == '+' || s[i] == '-') && (i == 0 || s[i - 1] == 'e' || s[i - 1] == 'E'))
            {
                //如果是符号, 必须在开始或者e的后面
                //符号不需要处理
            }
            else
            {
                //只要不满足上面的条件, 就是错误
                return false;
            }
        }      
        //返回数字标记位, 如果没有数字或者e后面没有数字都是错误
        return numFlag;
    }
};class Solution {
public:
    bool isNumber(string s) 
    {
        //先去除所有的空格
        int i = 0;
        while(i < s.size() && s[i] == ' ')
        {
            ++i;
        }
        s = s.substr(i);
        if(s.size() == 0) return false;
        while(s.back() == ' ')
        {
            s.pop_back();
        }
        //处理以后就是完整的数字,不包含空格
        bool numFlag = false;
        bool dotFlag = false;
        bool eFlag = false;
        //只有最前面和最后面可以出现空格
        //如果有符号，一定是在一开始出现或在e后面
        //有.时，一定要没有出现过.和e
        for(int i = 0; i < s.size(); ++i)
        {
            if(isdigit(s[i]))
            {
                //有数字出现    
                numFlag = true;
            }
            else if(s[i] == '.' && !dotFlag && !eFlag)
            {
                //.出现时, 必须没有e和点
                dotFlag = true;
            }
            else if((s[i] == 'e' || s[i] == 'E') && !eFlag && numFlag)
            {
                //有e时, 需要没出现过e,并且必须出现过数字,后面必须跟整数
                eFlag = true;
                numFlag = false;//  表示e后面要有整数
            }
            else if((s[i] == '+' || s[i] == '-') && (i == 0 || s[i - 1] == 'e' || s[i - 1] == 'E'))
            {
                //如果是符号, 必须在开始或者e的后面
                //符号不需要处理
            }
            else
            {
                //只要不满足上面的条件, 就是错误
                return false;
            }
        }      
        //返回数字标记位, 如果没有数字或者e后面没有数字都是错误
        return numFlag;
    }
};