#pragma once
#include <stddef.h>

class String 
{ 
public: 
    String(const char* str = ""); 
    String(const String& s); 
    String& operator=(const String& s); 
    ~String();
    int& GetCount();
    void Release();
    void CopyOnWrite(); 
    char& operator[](size_t pos); 
    void Expand(int n);
    void PushBack(char ch);
    void PushBack(const char* str);
    void PopBack();
    void Erase(size_t pos,size_t len);//从pos开始删除len个元素
    void Insert(size_t pos,char ch);
    void Insert(size_t pos,const char* str);
    void Show();
private: 
    char* _str; // 引用计数在头上 
    size_t _size;
    size_t _capacity;
};
