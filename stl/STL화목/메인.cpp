//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  5월 13일 화요일      (11주 1일차 강의) 
//  6월 19일 목 15주 2일 - 기말시험
//-------------------------------------------------------------------------------------------
//  iterator - Iterators are a generalization of pointers that 
// allow a C++ program to work with different data structures in a uniform manner
// 
// 반복자는 클래스로 코딩해야 합니다.
// 
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<algorithm>
#include"save.h"
#include"STRING.h"
using namespace std;

extern bool 관찰; // 관찰하려면 true로


//----------
int main()
//------------------------------------------------------------
{  

    STRING s{ "2025 5 15" };

    // 문제없이 실행되도록
    sort(s.begin(), s.end());

    cout << s << endl;   // "0122555"

    save("메인.cpp");
}