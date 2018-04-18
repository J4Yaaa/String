#pragma once
#include <stddef.h>

class String 
{ 
public: 
    String(const char* str = ""); 
    String(const String& s); 
    ~String();
    String& operator=(const String& s); 
    char& operator[](size_t pos); 
    void Releace();
    void CopyOnWrite(); 
    void Expand(size_t n);
    void PushBack(char ch);
    void PushBack(const char* str);
    void PopBack();

    void Show();
private: 
    char* _str; 
    size_t* _pCount; 
    size_t _size;
    size_t _capacity;
}; 
