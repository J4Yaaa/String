#include "String.h"
#include <string.h>
#include <iostream>
#include <assert.h>
using namespace std;

String::String(const char* str):_str(new char[strlen(str) + 1])
{
    strcpy(_str,str);
    _size = strlen(str);
    _capacity = _size;
}

String::~String()
{
    delete[] _str;
    _size = 0;
    _capacity = 0;
}

//必须把_str起始置为空
//因为在后续出了这个函数作用于的时候,delete会尝试着去释放一个随机空间
//delete和free是不可以释放随机空间的,但是可以释放NULL
String::String(const String& s):_str(NULL),_size(0),_capacity(0)
{
    String tmp(s._str);
    Swap(tmp);
}

void String::Swap(String& s)
{
    swap(_str,s._str);
    swap(_size,s._size);
    swap(_capacity,s._capacity);
}

//为了支持连等,返回引用
//传值
String& String::operator=(String s)
{
    Swap(s);
    return *this;
}
//传引用
//String& String::operator=(const String& s)
//{
//    if(this != &s)
//    {
//        String tmp(s);
//        Swap(tmp);
//    }
//    return *this;
//}

void String::Expand(size_t n)
{
    char* newstr = new char[n + 1];
    strcpy(newstr,_str);
    delete[] _str;
    _str = newstr;
    _capacity = n;
}

void String::PushBack(char ch)
{
//    if(_size >= _capacity)
//    {
//        Expand(_capacity * 2);
//    }
//    _str[_size++] = ch;
//    _str[_size] = '\0';
    Insert(_size,ch);
}

void String::PushBack(const char* str)
{
//    int len = strlen(str);
//    if(len + _size > _capacity)
//    {
//        Expand(_size + len);
//    }
//    strcpy(_str+_size,str); 
//    _size += len;
    Insert(_size,str);
}

void String::PushFront(char ch)
{
//    if(_size >= _capacity)
//    {
//        Expand(2 * _capacity);
//    }
//    size_t i = _size;
//    for(; i > 0; --i)
//    {
//        _str[i] = _str[i - 1];
//    }
//    _str[0] = ch;
//    ++_size;
    Insert(0,ch);
}

void String:: PushFront(const char* str)
{
//    int len = strlen(str);
//    if(_size + len > _capacity)
//    {
//        Expand(_size+len);
//    }
//    int i = _size;
//    for(; i >= 0; --i)
//    {
//        _str[i + len] = _str[i];
//    }
//
////    char* p = _str;
////
////    while(*str != '\0')
////    {
////        *p++ = *str++;
////    }
//
//    memcpy(_str,str,len);
//    _size += len;
    Insert(0,str);
}

void String::PopBack()
{
//    if(_size == 0)
//    {
//        return;
//    }
//    --_size;
//    _str[_size] = '\0';
    Erase(_size - 1);
}

void String::PopFront()
{
//    assert(_size > 0);
//    size_t i = 0;
//    for(;i < _size; ++i)
//    {
//        _str[i] = _str[i + 1];
//    }
//    --_size;
    Erase(0,1);
}

void String::Insert(size_t pos,char ch)
{
    if(pos > _size + 1)
    {
        return;
    }
    if(_size + 1 >= _capacity)
    {
        Expand(2 * _size);
    }
    int i = _size;
    for(;i >= (int)pos; --i)
    {
        _str[i + 1] = _str[i];
    }
    _str[pos] = ch;
    ++_size;
}

void String::Insert(size_t pos,const char* str)
{
    if(pos > _size + 1)
    {
        return;
    }
    int len = strlen(str);
    if(_size + len > _capacity)
    {
        Expand(_size + len);
    }
     int i = _size;
     for(; i >= (int)pos; --i)
     {
         _str[i+len] = _str[i];
     }
     while(*str)
     {
         _str[pos++] = *(str++);
     }
     _size += len;
}

void String::Erase(size_t pos,size_t len)
{
    if(_size == 0)
    {
        return;
    }
    if(pos > _size)
    {
        return;
    }
    if(pos + len >= _size)
    {//要删除的元素从pos开始一直到_str结束都没有删除完成
     //那就直接让pos位置等于 '\0'并且改变_size
        _str[pos] = '\0';
        _size = pos;
    }
    else
    {
        strcpy(_str+pos,_str+pos+len);
        _size -= len;
    }
}

size_t String::Find(char ch,size_t pos) 
{
    if(_size == 0)
    {
        return (size_t)-1;
    }
    if(pos > _size)
    {
        return (size_t)-1;
    }
    size_t i = pos;
    for(; i < _size; ++i)
    {
        if(_str[i] == ch)
            return i;
    }
    return (size_t)-1;
}

size_t String::Find(const char* str,size_t pos) 
{
    if(_size == 0)
    {
        return (size_t)-1;
    }
    size_t len = strlen(str);
    if(len > _size - pos)
    {
        return (size_t)-1;
    }
    const char* src = _str + pos;
    while(*src != '\0')
    {
        const char* match = str;
        const char* cur = src;

        while(*match != '\0' && *match == *cur)
        {
            ++match;
            ++cur;
        }
        if(*match == '\0')
        {
            return src - _str;
        }
        else
        {
            ++src;
        }
    }
    return -1;
}

String String::operator+(char ch)
{
    String tmp(*this);
    tmp.PushBack(ch);
    return tmp;
}

String& String::operator+=(char ch)
{
    PushBack(ch);
    return *this;
}

String String::operator+(const char* str)
{
    String tmp(*this);
    tmp.PushBack(str);
    return tmp;
}

String& String::operator+=(const char* str)
{
    PushBack(str);
    return *this;
}

bool String::operator>(const String& s) const
{
    char* p = _str;
    const char* q = s._str;
    if(p == NULL && q == NULL)
    {
        return true;
    }
    else if(p == NULL && q != NULL)
    {
        return false;
    }
    else if(p != NULL && q == NULL)
    {
        return true;
    }
    else
    {
        while(*p != '\0' && *q != '\0')
        {
            if(*p > *q)
            {
                return true;
            }
            else if(*p < *q)
            {
                return false;
            }
            else
            {
                ++p;
                ++q;
            }
        }
        if(*p != '\0')
        {
            return true;
        }
        return false;
    }
}

bool String::operator>=(const String& s)
{
    return (*this > s) || (*this == s);
}

bool String::operator<(const String& s)
{
    return !(*this >= s);
}

bool String::operator<=(const String& s)
{
    return (*this < s) || (*this == s);
}

bool String::operator!=(const String& s)
{
    return !(*this == s);
}

bool String::operator==(const String& s)
{
    if(_size != s._size)
    {
        return false;
    }
    char* p = _str;
    const char* q = s._str;
    while(*p == *q && *p != '\0' && *q != '\0')
    {
        ++p;
        ++q;
    }
    if(*p == '\0' && *p == '\0')
    {
        return true;
    }
    return false;
}

char& String::operator[](int n)
{
    assert(n < _size);
    return _str[n];
}
    
char String::operator[](int n) const
{
    return _str[n];
}

void String::Show()
{
    cout<<"str:  "<<_str<<endl;
    cout<<"size: "<<_size<<endl;
    cout<<"capa: "<<_capacity<<endl;
}

//////////////////////TEST CODE/////////////////////

#if 1

void TestString()
{
    String s1("hello world,hello everyday,hello tomorrow!");
    s1.Show();
    s1.Show();
}

int main()
{
    TestString();
    return 0;
}

//C++ 库中的 swap()函数用来交换内置类型
#endif
