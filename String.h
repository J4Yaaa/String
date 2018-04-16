#pragma once
#include <stddef.h>

class String 
{ 
public: 
    String(const char* str); 
    void Swap(String& s); 
    String(const String& s); 
//    String& operator=(const String& s);
    String& operator=(String s);
    ~String() ;
    const char* c_str(); 
    void Expand(size_t n); 
    void PushBack(char ch); 
    void PushBack(const char* str); 
    void PushFront(char ch);
    void PushFront(const char* str);
    void PopBack(); 
    void PopFront();
    void Insert(size_t pos, char ch); 
    void Insert(size_t pos, const char* str); 
    void Erase(size_t pos, size_t n = 1); 
    size_t Find(char ch,size_t pos = 0); 
    size_t Find(const char* str,size_t pos = 0); 
    String operator+(char ch); 
    String& operator+=(char ch); 
    String operator+(const char* str); 
    String& operator+=(const char* str); 
    bool operator>(const String& s) const; 
    bool operator>=(const String& s); 
    bool operator<(const String& s); 
    bool operator<=(const String& s); 
    bool operator==(const String& s); 
    bool operator!=(const String& s); 
    char& operator[](int n);
    char operator[](int n) const;
    void Show();
private: 
    char* _str; 
    size_t _size; 
    size_t _capacity; 
}; 
