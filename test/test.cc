#include <iostream>
using namespace std;

int main()
{
    int a = 0x12345678;
    int* pa = &a;
    if(*((char*)pa) == 0x78)
    {
        cout << "大端" << endl;
    }
    else
    {
        cout << "小端" << endl;
    }
    return 0;
}