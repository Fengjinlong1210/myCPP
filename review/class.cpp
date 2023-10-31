#include <iostream>
using namespace std;

class a
{
    int num;
};

class b
{
    int func()
    {

    }

    int num;
};

class c
{

};

int main()
{
    cout << "a = " << sizeof(a) << endl;
    cout << "b = " << sizeof(b) << endl;
    cout << "c = " << sizeof(c) << endl;
    return 0;
}