//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (5주 2일차 강의) 
// 4월 24일 중간고사(30) 8주차 2일
// 과제    (30) - 4월 10일 설명
//-------------------------------------------------------------------------------------------
// STRING - std::stromg과 유사한 클래스, STL 표준 container가 되도록 발전시켜나갈것임
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<memory>
#include"save.h"
using namespace std;
class STRING {
public:
    STRING(const char* s) : len{ strlen(s) } {   //[] -> *로 collapsing 된다.
        p.reset();
        p= make_unique<char[]>(len); //p에 주소를 저장하도록
        memcpy(p.get(), s, len);  //p에다가 s의 내용을 len만큼 DMA 다이렉트 메모리 어섹스  이거보다 빠른 메모리끼리의 전송은 없다.
    }


    size_t size( )const {
        return len;
    }


private:
    size_t len{}; //null char를 쓰지 않겠다는 소리
    unique_ptr<char[]> p{};



    friend ostream& operator<<(ostream& os, const STRING& str) {
        for (int i = 0; i < str.len; ++i) {
            os << str.p[i];
        }
        return os;
    }
};

//----------
int main()
//------------------------------------------------------------
{
    STRING s{ "std::string과 유사한 클래스" };
    cout << s.size() << endl; //s가 확보한 자원의 바이트 수
    cout << s << endl;
    save("메인.cpp");
}