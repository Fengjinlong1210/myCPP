#include <iostream>
#include <time.h>
using namespace std;

// 测试传值返回和传引用返回的效率

class A
{
public:
    int arr[100000];
};

A test_val(A a)
{
    return a;
}

A& test_ref(A& a)
{
    return a;
}

int main()
{
    A a;//创建一个对象
    //time_t  long int类型
    //clock_t long int
    clock_t begin1 = clock();
    for(int i = 0; i < 10000; ++i)
    {
        test_val(a);
    }
    clock_t end1 = clock();
    cout << "value use time: " << end1 - begin1 << endl;

    clock_t begin2 = clock();
    for(int i = 0; i < 10000; ++i)
    {
        test_ref(a);
    }
    clock_t end2 = clock();
    cout << "ref use time: " << end2 - begin2 << endl;
    return 0;
}