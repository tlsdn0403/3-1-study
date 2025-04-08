//-------------------------------------------------------------------------
// STRING.cpp - std::string과 유사한 클래스이다
//            STL의 container로 동작할 수 있게 코딩해 나간다
//
//                                                        2025.4.8 시작
//-------------------------------------------------------------------------
#include<memory>
#include<iostream>
#include<print>
#include"STRING.h"

//관찰을 제어하기 위한 변수 추가
bool 관찰{ false };                            //2025 04 08 동작을 관찰


// 문제는 std::println이 C++ 표준 라이브러리에 존재하지 않는 함수라는 점입니다.  
// 대신 std::cout을 사용하여 출력하도록 수정해야 합니다.  

STRING::STRING()                             //2025 04 08 동작을 관찰을 위해 코딩  
   : id{ ++gid }  
{  
   
   if (관찰) {
       std::println("[{:8}] {:16} 자원수:{:<10} 메모리:{:<12}, 자원메모리:{:<12}",
           id, "디폴트생성자", len, static_cast<void*>(this), (void*)p.get());
   }
}
STRING::~STRING()                                          //관찰을 위해 어쩔 수 없이...
{
    if (관찰) {
        std::println("[{:8}] {:16} 자원수:{:<10} 메모리:{:<12}, 자원메모리:{:<12}",
            id, "소멸자", len, (void*)this,(void*)p.get());
    }
}

STRING::STRING(const char* s) : id{ ++gid }, len{strlen(s)}
{   //[] -> *로 collapsing 된다.
    p.reset();
    p = std::make_unique<char[]>(len); //p에 주소를 저장하도록
    memcpy(p.get(), s, len);  //p에다가 s의 내용을 len만큼 DMA 다이렉트 메모리 어섹스  이거보다 빠른 메모리끼리의 전송은 없다.

    if (관찰) {
        std::println("[{:8}] {:16} 자원수:{:<10} 메모리:{:<12}, 자원메모리:{:<12}",
            id, "생성자(char*)", len, (void*)this, (void* )p.get());
    }
}

//복사 생성자
STRING::STRING(const STRING& other)
    :id{ ++gid },len {  other.len}  //여기다 ,를 놓고 하면 순서가 보장되지 않는다.
{
    p = std::make_unique<char[]>(len); //생성시에 디폴트 동작을 써뒀기 때문에 그냥 써도 문제가 없을거야
    memcpy(p.get(), other.p.get(), len);

    if (관찰) {
        std::println("[{:8}] {:16} 자원수:{:<10} 메모리:{:<12}, 자원메모리:{:<12}",
            id, "복사생성자", len, (void*)this, (void* )p.get());
    }
}


STRING& STRING::operator=(const STRING& other)     //2025.04.08
{
    if (this == &other)
        return *this;  //*붙어야 자기자신이 된다.

    len = other.len;
    p.release();   // p.reset()과 뭐가 다르냐?? 공부하자
    p = std::make_unique<char[]>(len);
    memcpy(p.get(), other.p.get(), len); //독점소유했던 자원을 반환하고 새로운 자원 얻는다.

    if (관찰) {
        std::println("[{:8}] {:16} 자원수:{:<10} 메모리:{:<12}, 자원메모리:{:<12}",
            id, "복사할당연산자", len, (void*)this, (void* )p.get());
    }
    return *this;
}


size_t STRING::size()const
{
     return len;
}

std::ostream& operator<<(std::ostream& os, const STRING& str) {
     for (int i = 0; i < str.len; ++i) {
         os << str.p[i];
     }
     return os;
}

size_t STRING::gid{};                               //2025.04.08