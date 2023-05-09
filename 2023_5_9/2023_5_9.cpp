#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

//class Solution {
//public:
//    string addStrings(string num1, string num2)
//    {
//        long long n1 = 0;
//        long long n2 = 0;
//        for (auto& e : num1)
//        {
//            n1 = n1 * 10 + (e - '0');
//        }
//        for (auto& e : num2)
//        {
//            n2 = n2 * 10 + (e - '0');
//        }
//        long long ans = n1 + n2;
//        string ret;
//        while (ans > 0)
//        {
//            ret += ans % 10 + '0';
//            ans /= 10;
//        }
//        reverse(ret.begin(), ret.end());
//        return ret;
//    }
//};

class Solution {
public:
    bool isPalindrome(string s)
    {
        string s2;
        for (auto& e : s)
        {
            if (isalpha(e) || isdigit(e))
            {
                s2 += tolower(e);
            }
        }
        string s3(s2);
        reverse(s3.begin(), s3.end());
        return strcmp(s3.c_str(), s2.c_str()) == 0;
    }
};

int main()
{
    Solution s;
    string ss("A man, a plan, a canal: Panama");
    bool ret = s.isPalindrome(ss);
    cout << ret << endl;
    return 0;
}