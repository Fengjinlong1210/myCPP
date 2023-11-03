#include <iostream>
#include <cassert>
#include <cstring>
using namespace std;

class String
{
public:
    String()
    {}

    String(const String& str)
    {
        if(str._str == nullptr)
        {
            assert(false);
        }
        _str = new char[str._capacity];
        memcpy(_str, str._str, sizeof(char) * str._size);
        _capacity = str._capacity;
        _size = str._size;
    }

    String(const char* str = "")
    {
        int n = strlen(str);
        _str = new char[n + 1];
        _size = n + 1;
        _capacity = n + 1;
        memcpy(_str, str, sizeof(char) * (n + 1));
    }

    String& operator+=(const String& str)
    {
        
    }

private:
    char* _str = nullptr;
    size_t _size = 0;
    size_t _capacity = 16;
};

int main()
{
    String str("hello");
    
    return 0;
}