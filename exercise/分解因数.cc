#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

// 分解因数的做法: 从2开始找到一个因数, 然后用num尝试整除这个因数, 直到不能整除
//  然后再从2向后寻找其他的因数
//  如果num中包含素数,需要在最后手动添加一下
// 例如 14 = 2 * 7, 7不会在循环中被添加, 只能手动添加

void get_factor(int num, vector<int> &factor)
{
    int i;
    for (i = 2; i <= sqrt(num); ++i)
    {
        if (num <= 1) // 找完了
            break;
        while (num % i == 0)
        {
            factor.push_back(i);
            num /= i;
        }
    }
    // 如果最后一个数是质数, 没法被整除
    if (num > 1)
        factor.push_back(num);
}

int main()
{
    int num = 0;
    while (cin >> num)
    {
        vector<int> factor;
        get_factor(num, factor);
        string ret;
        ret += to_string(num) + " = ";
        for (auto &n : factor)
        {
            ret += to_string(n);
            ret += " * ";
        }
        ret.resize(ret.size() - 3);
        cout << ret << endl;
    }
    return 0;
}
// 64 位输出请用 printf("%lld")