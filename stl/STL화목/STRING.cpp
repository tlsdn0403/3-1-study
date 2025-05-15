//-------------------------------------------------------------------------
// STRING.cpp - std::string과 유사한 클래스이다
//            STL의 container로 동작할 수 있게 코딩해 나간다
//
//                                                        2025.4.8 시작
// 2025. 4. 10    이동생성과 이동할당연산자 코딩
// 2025. 5.  1    >> 연산자  코딩
// 2025. 5.  8    >  연산자  코딩
// 2025. 5. 13    begin , end 코딩
//-------------------------------------------------------------------------
#include<memory>
#include<iostream>
#include<print>
#include<algorithm>
#include<string>
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
    //사용하지 않아야 할 코드이다. 보장할 수가 없다 프레임을 시스템 콜이다.
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



//이동생성과 이동할당연산자                               //2025. 4. 10
STRING::STRING(STRING&& other)
    :id{ ++gid }, len{ other.len }
{
    p.reset(other.p.release());  
    other.len = 0;

    if (관찰) {
        std::println("[{:8}] {:16} 자원수:{:<10} 메모리:{:<12}, 자원메모리:{:<12}",
            id, "이동 생성자", len, (void*)this, (void*)p.get());
    }
}

//둘 다 똑같이 코딩 할 필요는 없다.
STRING& STRING::operator=(STRING&& other)
{
    if (this == &other) //adress of other
        return *this;

    len = other.len;
    p.release(); //갖고 있던 메모리 시스템에 반환하고 다시 세팅
    p.reset(other.p.release());
    other.p.release();

    //이래야 출력가능하다.
    other.len = 0;
    if (관찰) {
        std::println("[{:8}] {:16} 자원수:{:<10} 메모리:{:<12}, 자원메모리:{:<12}",
            id, "이동 할당 연산자", len, (void*)this, (void*)p.get());
    }
    return *this; //할당문의 맨뒤에 추가를 해줘야 한다.
}


bool STRING::operator==(const STRING& rhs) const
{
    return std::equal(&p[0], &p[len], &rhs.p[0], &rhs.p[rhs.len]);
}

bool STRING::operator<(const STRING& rhs) const //2025. 5. 8  
{
    return std::lexicographical_compare(p.get(), p.get() + len,
        rhs.p.get(), rhs.p.get() + rhs.len);
}


size_t STRING::size()const
{
     return len;
}

//반복자는 컨테이너가 제공을 하는 것임 , 자료구조야 너 원소 첫 위치가 어딨어??? 

STRING_Iterator STRING::begin() const
{
    return STRING_Iterator{ p.get() };     //return &p[0]
}
STRING_Iterator STRING::end() const
{
    return STRING_Iterator{ p.get() + len };  //return &p[len] 
}


STRING_Reverse_Iterator STRING::rbegin() const
{
    return STRING_Reverse_Iterator{ p.get() + len };  //이건 그냥 명확하게 쓰기 위해서 한 것이다.
}
STRING_Reverse_Iterator STRING::rend() const
{
    return  p.get();     
}



std::ostream& operator<<(std::ostream& os, const STRING& str)
{
     for (int i = 0; i < str.len; ++i) {
         os << str.p[i];
     }
     return os;
}
std::istream& operator>>(std::istream& is, STRING& str)
{
    std::string s; //얘는 자원이 아니다 , 자원은 영속성이 있어야 한다. 
    is >> s;
    str.len = s.length();
    str.p.release();
    str.p = std::make_unique<char[]>(str.len);


    memcpy(str.p.get(), s.data(), str.len);
    return is;
}

size_t STRING::gid{};                               //2025.04.08