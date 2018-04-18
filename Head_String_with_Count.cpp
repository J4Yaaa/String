#include "Head_String.h"
#include <iostream>
using namespace std;
#include <string.h>

//写时拷贝
void String::CopyOnWrite()
{
    if(GetCount() > 1)
    {
        --GetCount();
        size_t len = strlen(_str);
        char* new_str = new char[len + 5];
        strcpy(new_str + 4,_str);
        _str = new_str + 4;
        GetCount() = 1;
        _size = len;
        _capacity = len;
    }
}

//得到当前_str的引用计数
int& String::GetCount()
{
    return *((int*)(_str-4));
}

//析构时,如果引用计数为1,就释放掉空间
void String::Release()
{
    if(--GetCount() == 0)
    {
        delete[] (_str - 4);
        _size = 0;
        _capacity = 0;
    }
}

String::String(const char* str):_str(new char[strlen(str) + 5])
{
    int len = strlen(str);
    _str = _str + 4;
    strcpy(_str,str);
    _size = len;
    _capacity = len;
    GetCount() = 1;
}

// s2(s1)
String::String(const String& s):_str(s._str),_size(s._size),_capacity(s._capacity)
{
    GetCount()++;
}

//s2(this) = s1(s)
String& String::operator=(const String& s)
{
    if(_str != s._str)
    {
        Release();
        _str = s._str;
        _size = s._size;
        _capacity = s._capacity;
        GetCount()++;
    }
    return *this;
}

String::~String()
{
    Release();
}

char& String::operator[](size_t pos)
{
    CopyOnWrite();
    return _str[pos];
}

void String::Expand(int n)
{
    char* new_str = new char[n + 1];
    strcpy(new_str + 4,_str);
    *(int*)new_str = GetCount();
    delete (_str-4);
    _str = new_str + 4;
    _capacity = n;
}

void String::PushBack(char ch)
{
    CopyOnWrite();
    if(_size + 1 > _capacity)
    {
        Expand(2 * _capacity);
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
    memcpy(_str+_size,str,len + 1);
    _size += len;
}

void String::PopBack()
{
    CopyOnWrite();
    --_size;
    _str[_size] = '\0';
}

void String::Erase(size_t pos,size_t len)//从pos开始删除len个元素
{
    CopyOnWrite();
    if(pos >= _size)
    {
        return;
    }
    if(pos + len >= _size)
    {
        _str[pos] = '\0';
        _size = pos;
        return;
    }
    size_t i = pos;
    for(; i <= _size; ++i)
    {
        _str[i] = _str[i + len];
    }
    _size -= len;
}

void String::Insert(size_t pos,char ch)
{
    CopyOnWrite();
    if(pos > _size)
    {
        return;
    }
    if(_size + 1 > _capacity)
    {
        Expand(2 * _capacity);
    }
    ++_size;
    size_t i = _size;
    for(; i > pos; --i)
    {
        _str[i] = _str[i - 1];
    }
    _str[pos] = ch;
}

void String::Insert(size_t pos,const char* str)
{
    CopyOnWrite();
    if(pos > _size)
    {
        return;
    }
    int len = strlen(str);
    if(_size + len >= _capacity)
    {
        Expand(_size + len);
    }
    size_t i = _size;
    for(; (int)i >= (int)pos; --i)
    {
        _str[i+len] = _str[i];
    }
    for(i = pos; i < pos + len; ++i)
    {
        _str[i] = *str++;
    }
    _size += len;
}

void String::Show()
{
    cout<<_str<<endl;
    cout<<"pCount = "<<GetCount()<<endl;
    cout<<"size = "<<_size<<endl;
    cout<<"capa = "<<_capacity<<endl;
}

////////////////////////////////////////////
int main()
{
    String s1("abcdefghijklmn");
    String s2(s1);
    String s3(s1);
    s1.Show();
    cout<<"---------------"<<endl;
    s2.Insert(3,"!!!!!!!");
    s1.Show();
    s2.Show();
    cout<<"---------------"<<endl;
    s3.Insert(0,"##########");
    s1.Show();
    s3.Show();
    return 0;
}

