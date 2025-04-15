//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (7주 1일차 강의) 
// 4월 24일 중간고사(30) 8주차 2일
// 5월 6일(화) -> 6월 19(예정)
//-------------------------------------------------------------------------------------------
// STL Container -Containers are objects that store other objects -> 다른 객체를 담을 수 있는 객체 
// 1.Sequence Containers
//      arrat<T,N>
//      vector<T> /dynamic(runtime)  array
//-------------------------------------------------------------------------------------------
#include<iostream>

#include<vector>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool 관찰; // 관찰하려면 true로

//키보드에서 입력한 정수값의 합계와 평균을 출력하시오.

//----------
int main()
//------------------------------------------------------------
{
    int num
    <int> v{ 1,2,3, };
    //반복자를 사용하여 access

    for (int i = 4; i < 10; ++i) {
        v.push_back(i);
        cout << v.data() << endl;
    }

    for ( auto i= ; i != v.crend(); --i) { //이때는 오토를 사용하는 것을 권장한다.
        cout << *i << endl;
    }

    save("메인.cpp");
}