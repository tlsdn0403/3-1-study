//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 29일 화요일      (9주 1일차 강의) 
// 5월 6일(화) -> 6월 19(예정)
//-------------------------------------------------------------------------------------------
// STL Container -Containers are objects that store other objects -> 다른 객체를 담을 수 있는 객체 
// 1.Sequence Containers
//      arrat<T,N>
//      vector<T> /dynamic(runtime)  array
//      deque<T> - vector 보다 더 많은 원소를 담을 수 있다.
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<ranges>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool 관찰; // 관찰하려면 true로

//----------
int main()
//------------------------------------------------------------
{
    관찰 = true;
    list<STRING> cont { "1","333", "55555","4444","22" };

    ranges::sort(cont.begin(), cont.end());
    for (const STRING& s : cont) {
        cout << s << endl;
    }

    관찰 = false;
    save("메인.cpp");
}