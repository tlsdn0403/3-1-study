//-------------------------------------------------------------------------
// STRING.h - std::string과 유사한 클래스이다
//            STL의 container로 동작할 수 있게 코딩해 나간다
//
//                                                        2025.4.8 시작
//-------------------------------------------------------------------------
#pragma once
#include<memory>
#include<iostream>

class STRING {
public:
    STRING(const char* s);
    STRING();
    STRING(const STRING& other);
    size_t size()const;

    STRING& operator=(const STRING& other);
private:
    size_t len{}; //null char를 쓰지 않겠다는 소리
    std::unique_ptr<char[]> p{};

    friend std::ostream& operator<<(std::ostream& os, const STRING& str);

};