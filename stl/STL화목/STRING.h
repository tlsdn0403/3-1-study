//-------------------------------------------------------------------------
// STRING.h - std::string과 유사한 클래스이다
//            STL의 container로 동작할 수 있게 코딩해 나간다
//
//                                                        2025.4.8 시작
//  >> 연산자                                             2025.05.01 
//  >  연산자                                             2025. 5. 8
//  begin() , end()                                       2025. 5.13
//  역방향 반복자는 반드시 클래스로 제공                  2025. 5.13
//  반복자도 당연히 클래스로 코딩해야 함                  2025. 5.15
//-------------------------------------------------------------------------
#pragma once
#include<memory>
#include<iostream>

class STRING_Iterator {
    //표준 반복자는 다음 다섯가지 물음에 대답할 수 있어야 한다.
public:
    using difference_type = ptrdiff_t;
    using value_type = char;
    using pointer = char*;
    using reference = char&;
    using iterator_category = std::random_access_iterator_tag;
public:
    STRING_Iterator(char* p): p{p}{}

    //반복자라면 최소한 다음 기능을 제공해야 함
    char& operator*()const {
        return *p;
    }
    STRING_Iterator& operator++() {
        ++p;
        return *this;
    }
    
    //관계 연산자들
    bool operator==(const STRING_Iterator& rhs)const {
        return p == rhs.p;
    }
    bool operator<(const STRING_Iterator& rhs) const {
        return p < rhs.p; 
    }
    bool operator>(const STRING_Iterator& rhs) const {
        return p > rhs.p; 
    }

    STRING_Iterator& operator--() {
        --p;
        return *this;
    }
    STRING_Iterator operator--(int) {
        STRING_Iterator temp = *this;
        --p;
        return temp;
    }
    STRING_Iterator operator++(int) {
        STRING_Iterator temp = *this;
        ++p;
        return temp;
    }
    STRING_Iterator operator+(difference_type n) const { return STRING_Iterator(p + n); }
    STRING_Iterator operator-(difference_type n) const { return STRING_Iterator(p - n); }

    difference_type operator-(const STRING_Iterator& rhs) const {
        return p - rhs.p;
    }

private:
    char* p;
};







// 반복자 어댑터 ( 반복자인척 하지만 속에서 딴짓 하는 놈)
class STRING_Reverse_Iterator {
public:
    STRING_Reverse_Iterator(char* p) : p{ p } {}

    char operator*() {
        return *(p - 1);
    }
    void operator++() {
        --p;
    }
    bool operator==(const STRING_Reverse_Iterator& rhs)const { //end 위치인지 비교할 수 있어야 한다.
        return p == rhs.p;
    }
private:
    char* p;
};




class STRING {
public:
    STRING();                                           //2025. 04 . 08
    ~STRING();                                          //관찰을 위해 어쩔 수 없이...
    
    STRING(const char* s);

    //복사생성과 복사할당

    //자기 자신을 리턴해야 한다. 그래서 앞에 STRING
    STRING(const STRING& other);                        //2025.04.08
    STRING& operator=(const STRING& other);             //2025.04.08

 


    //이동생성과 이동할당연산자                         //2025. 4. 10
    STRING(STRING&&);                                   //&& ->rvalue reference   여기 넘겨진 인자는 이동달할 것이다.
    STRING& operator=(STRING&&);

    
    //2025. 04. 22 관계 연산자들
    bool operator==(const STRING& rhs) const;
    bool operator<(const STRING& rhs)  const;           //2025. 5. 8

    //인터 페이스 함수들

    size_t size()const;

    //  begin() , end()                                       2025. 5.13
    STRING_Iterator begin() const;
    STRING_Iterator end() const;

    STRING_Reverse_Iterator rbegin() const;
    STRING_Reverse_Iterator rend() const;

private:
    size_t len{}; //null char를 쓰지 않겠다는 소리

    //유니크 포인터는 복사가 금지되어있다.
    // 디폴트로 딜리트 되어있다.
    std::unique_ptr<char[]> p{};

    size_t id;                                //2025.04.08

    friend std::ostream& operator<<(std::ostream& os, const STRING& str);
    // 2025. 5. 1 추가
    friend std::istream& operator>>(std::istream& is, STRING& str);


    static size_t gid;     //글로벌 한 id                           //2025.04.08

    
};
