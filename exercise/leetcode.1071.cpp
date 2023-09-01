#include <iostream>
#include <algorithm>
using namespace std;
class Solution {
public:
    string gcdOfStrings(string str1, string str2) 
    {
        if(str1 + str2 != str2 + str1) return "";
        string str = str1 + str2;
        return str.substr(0, __gcd(str1.size(), str2.size()));
    }
};
//对于字符串 s 和 t，只有在 s = t + ... + t（t 自身连接 1 次或多次）时，我们才认定 “t 能除尽 s”。

//给定两个字符串 str1 和 str2 。返回 最长字符串 x，要求满足 x 能除尽 str1 且 x 能除尽 str2 。

//字符串最大公约数
// 如果两个字符串前后合并不想等, 一定不存在这样的字符串
// 如果存在, 只需找到两个字符串长度的最大公因数, 截取前面的长度