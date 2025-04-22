//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (7주 1일차 강의) 
// 4월 24일 중간고사(30) 8주차 2일 E동 320호
// 5월 6일(화) -> 6월 19(예정)
//-------------------------------------------------------------------------------------------
// STL Container -Containers are objects that store other objects -> 다른 객체를 담을 수 있는 객체 
// 1.Sequence Containers
//      arrat<T,N>
//      vector<T> /dynamic(runtime)  array
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<vector>
#include<algorithm>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool 관찰; // 관찰하려면 true로

//----------
int main()
//------------------------------------------------------------
{       
    vector<int> v{ 1,2,3,4,5 };
    //[문제] v에서 3을 제거하라.
    remove(v.begin(), v.end(), 3);
    for (int n : v)
        cout << n << " ";
    save("메인.cpp");
}