//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (6주 2일차 강의) 
// 4월 24일 중간고사(30) 8주차 2일
// 5월 6일(화) -> 6월 19(예정)
//-------------------------------------------------------------------------------------------
// STRING - std::string과 유사한 클래스, STL 표준 container가 되도록 발전시켜나갈것임
//          내부 동작을 관찰할 수 있게 하자.
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<array>
#include<string>
#include<memory>
#include<algorithm>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool 관찰; // 관찰하려면 true로

//----------
int main()
//------------------------------------------------------------
{
    array<STRING, 5> a{ "1","333","22","55555","4444" };
    관찰 = true;
    std::sort(a.begin(), a.end(), [](const STRING& lhs, STRING& rhs)  //가오 좀 부리자
        {
            return lhs.size() < rhs.size();
        });

    
    for (const STRING& str : a)
        cout << str << endl;
    관찰 = false;
    save("메인.cpp");
}