#include <iostream>
#include <vector>
using namespace std;
// 12 16    n1 * n2 / 最大公因数 = 最小公倍数
int getGCF(int num1, int num2)
{
    //使num1是较大的
    if(num1 < num2) swap(num1, num2);
    int tmp;
    while(num1 % num2 != 0)
    {
        tmp = num1 % num2;
        num1 = num2;
        num2 = tmp;        
    }
    return num2;
}

// int main()
// {
//     int ret = getGCF(16, 18);
//     cout << ret << endl;
//     return 0;
// }

int main() 
{
    int n = 0;
    int power = 0;
    while(1)
    {
    cin >> n >> power;
    vector<int> def(n);
    for(auto& num : def)
    {
        cin >> num;
    }
    for(auto& num : def)
    {
        if(power > num)
        {
            power += num;
        }
        else
        {
            power += getGCF(power, num);
        }
    }
    cout << power << endl;
    }
}
//64 位输出请用 printf("%lld")