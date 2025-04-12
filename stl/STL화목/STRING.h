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
    STRING();                                           //2025. 04 . 08
    ~STRING();                                          //관찰을 위해 어쩔 수 없이...
    
    STRING(const char* s);

    //복사생성과 복사할당

    //자기 자신을 리턴해야 한다. 그래서 앞에 STRING
    STRING(const STRING& other);                        //2025.04.08
    STRING& operator=(const STRING& other);             //2025.04.08

    //이동생성과 이동할당연산자                               //2025. 4. 10
    STRING(STRING&&);                                   //&& ->rvalue reference   여기 넘겨진 인자는 이동달할 것이다.
    STRING& operator=(STRING&&);

    
    //인터 페이스 함수들
    size_t size()const;

    
private:
    size_t len{}; //null char를 쓰지 않겠다는 소리

    //유니크 포인터는 복사가 금지되어있다.
    // 디폴트로 딜리트 되어있다.
    std::unique_ptr<char[]> p{};

    size_t id;                                //2025.04.08

    friend std::ostream& operator<<(std::ostream& os, const STRING& str);

    static size_t gid;     //글로벌 한 id                           //2025.04.08

    
};