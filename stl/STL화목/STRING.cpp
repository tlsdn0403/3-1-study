//-------------------------------------------------------------------------
// STRING.cpp - std::string과 유사한 클래스이다
//            STL의 container로 동작할 수 있게 코딩해 나간다
//
//                                                        2025.4.8 시작
//-------------------------------------------------------------------------
#include<memory>
#include<iostream>
#include"STRING.h"

STRING::STRING()
{
}
STRING::STRING(const char* s) : len{ strlen(s) }
{   //[] -> *로 collapsing 된다.
    p.reset();
    p = std::make_unique<char[]>(len); //p에 주소를 저장하도록
    memcpy(p.get(), s, len);  //p에다가 s의 내용을 len만큼 DMA 다이렉트 메모리 어섹스  이거보다 빠른 메모리끼리의 전송은 없다.
}

STRING::STRING(const STRING& other)
{
    len = other.len;
    p.reset();
    p = std::make_unique<char[]>(len);
    memcpy(p.get(), other.p.get(), len);
}

size_t STRING::size()const {
     return len;
 }
STRING& STRING::operator=(const STRING& other) {
    
    len = other.len;
    p.reset();
    p = std::make_unique<char[]>(len);
    memcpy(p.get(), other.p.get(), len);
    return *this;
}
std::ostream& operator<<(std::ostream& os, const STRING& str) {
     for (int i = 0; i < str.len; ++i) {
         os << str.p[i];
     }
     return os;
}

