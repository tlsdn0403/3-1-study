//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (7주 1일차 강의) 
// 4월 24일 중간고사(30) 8주차 2일 E동 320호
// 5월 6일(화) -> 6월 19(예정)
//-------------------------------------------------------------------------------------------
// STL Container -Containers are objects that store other objects -> 다른 객체를 담을 수 있는 객체 
// 1.Sequence Containers
//      arrat<T,N>
//      vector<T> /dynamic(runtime)  array
//      deque<T> - vector 보다 더 많은 원소를 담을 수 있다.
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<deque>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool 관찰; // 관찰하려면 true로

//----------
int main()
//------------------------------------------------------------
{     
   
    deque<STRING> d{ "1","22","333","4444","55555" };
    
    관찰 = true;
    d.push_front("0");
    d.push_front("-1");
    관찰 = false;
    for (const STRING& s : d)
        cout << s << endl;
    save("메인.cpp");
}