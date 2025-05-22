//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  5월 22일 목요일      (12주 2일차 강의) 
//  6월 19일 목 15주 2일 - 기말시험
//-------------------------------------------------------------------------------------------
//  Associative Container - key와 연관된 value를 항상 정렬상태로 유지하는 컨테이너
//                          정렬은 key값을 기준으로 한다.
//  set / multiset - key == value
//  map / multimap - pair(key, value>
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<algorithm>
#include<set>
#include<ranges>
#include"save.h"
#include"STRING.h"
using namespace std;

extern bool 관찰; // 관찰하려면 true로
template<>
struct less<STRING>
{
public:
    bool operator()(const STRING & a, const STRING  & b) const //이게 멤버함수로 바꿔주는 순간 후위 const를 붙여줘야 됨 const 일관성
    {
        return a.size() < b.size();
    }
};

//----------
int main()
//------------------------------------------------------------
{  
    

    //[문제] s를 기본정렬 기준인 less를 사용하여 바이트 수 기준으로 정렬되게 하자
    set<STRING > s{ "333","2222","11111","44","5" }; 

    for (const STRING& str : s) {
        cout << str << endl;
    }
    cout<<endl;



    save("메인.cpp");
}