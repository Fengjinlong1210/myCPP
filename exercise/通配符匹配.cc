#include <cctype>
#include <iostream>
#include <string>
using namespace std;

bool isMatch(const char* match, const char* str)
{
    if(*match == 0 && *str == 0) return true;
    if(*match == 0 || *str == 0) return false;

    if(*match == '?')
    {
        if(!isalnum(*str)) return false;
        return isMatch(match + 1, str + 1);
    }
    else if(*match == '*')
    {
        while(*match == '*')
        {
            ++match;
        }
        --match;
        //处理多个*的情况, 只保留一个
        if(!isalnum(*str)) return false;
        return isMatch(match + 1, str) || isMatch(match + 1, str + 1) ||
            isMatch(match, str + 1);
        //返回三种情况, 匹配0个, 匹配1个, 匹配多个
    }
    else if(tolower(*match) == tolower(*str))
    {
        //字符相等, 向下匹配
        return isMatch(match + 1, str + 1);
    }
    return false;
}

int main() 
{
    string str1;
    string str2;
    getline(cin, str1);//包含通配符
    getline(cin, str2);
    bool ret = isMatch(str1.c_str(), str2.c_str());
    if(ret)
    {
        cout << "true";
    }
    else
    {
        cout << "false";
    }   
    return 0;
}
// 64 位输出请用 printf("%lld")