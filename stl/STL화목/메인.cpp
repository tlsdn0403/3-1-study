//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  5월 13일 화요일      (11주 1일차 강의) 
//  6월 19일 목 15주 2일 - 기말시험
//-------------------------------------------------------------------------------------------
//  반복자와 알고리즘
// 
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<algorithm>
#include<vector>
#include"save.h"
#include"STRING.h"
using namespace std;

extern bool 관찰; // 관찰하려면 true로

template<class 반복자 , class 값>
반복자 myfind(반복자 b, 반복자 e, 값 v)
{
    while (b != e) {
        if (*b == v)
            return b;
        ++b;
    }
    return e;
}

template<class 반복자, class Pred>
반복자 myfind_if(반복자 b, 반복자 e, Pred f)
{
    for (; b != e; ++b) {
        if (f(*b))
            return b;
    }
    return e;
}
template<class 반복자 , class 목적지반복자>
void my_copy(반복자 b, 반복자 e, 목적지반복자 d)
{
    while (b != e) {
        *d = *b;
        ++b;
        ++d;
    }
}
//----------
int main()
//------------------------------------------------------------
{  
    STRING s{ "반복자를 사용한 알고리즘을 연습 중" };
    vector<char> v{};
    my_copy(s.begin(), s.end(), back_inserter(v));

    for (const char& c : v) {
        cout << c;
    }
    cout << endl;

    save("메인.cpp");
}