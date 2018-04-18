#include "String.h"
#include <iostream>
using namespace std;
#include <string.h>
#include <string>

//释放时如果引用计数为1,可以直接释放
void String::Releace()
{
    if(--(*_pCount) == 0)
    {
        delete[] _str;
        delete _pCount;
        _str = NULL;
        _pCount = NULL;
    }
}

//扩容
void String::Expand(size_t n)
{
    char* new_str = new char[n + 1];
    strcpy(new_str,_str);
    delete[] _str;
    _str = new_str;
    _capacity = n;
}

//写时拷贝
void String::CopyOnWrite()
{
    if((*_pCount) > 1)
    {
        --(*_pCount);
        int len = strlen(_str);
        char* new_str = new char[len + 1];
        strcpy(new_str,_str);
        _str = new_str;
        _pCount = new size_t(1);
        _size = len;
        _capacity = len;
    }
}

String::String(const char* str):_str(new char[strlen(str)+1]),_pCount(new size_t(1))
{
    strcpy(_str,str);
    int len = strlen(str);
    _size = len;
    _capacity = len;
}

String::String(const String& s):_str(s._str),_pCount(s._pCount),_size(s._size),_capacity(s._capacity)
{
    ++(*_pCount);
}

String::~String()
{
    Releace();
}

String& String::operator=(const String& s) 
{
    if(_str != s._str)
    {
        Releace();
        ++(*_pCount);
    }
    return *this;
}

char& String::operator[](size_t pos)
{
    CopyOnWrite();
    return _str[pos];
}

void String::PushBack(char ch)
{
    CopyOnWrite();
    if(_size + 1 > _capacity)
    {
        Expand(2 * _size);
    }
    _str[_size++] = ch;
    _str[_size] = '\0';
}

void String::PushBack(const char* str)
{
    CopyOnWrite();
    int len = strlen(str);
    if(_size + len >= _capacity)
    {
        Expand(_size + len);
    }
    strcat(_str,str);
    _size += len;
}

void String::PopBack()
{
    CopyOnWrite();
    _str[--_size] = '\0';
}

void String::Show()
{
    cout<<_str<<endl;
    cout<<"pCount = "<<*_pCount<<endl;
    cout<<"_size = "<<_size<<endl;
    cout<<"_capa = "<<_capacity<<endl;
}

////////////////////////////////////////////////

int main()
{
    String s1("hello");
    String s2(s1);
    s1.Show();
    s2.PopBack();
    s1.Show();
    s2.Show();
    return 0;
}
