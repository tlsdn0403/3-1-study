//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  6월 5일 목요일      (13주 2일차 강의) 
//  6월 19일 목 15주 2일 - 기말시험 , E320 에서 ....
//-------------------------------------------------------------------------------------------
// 정렬관련 algorithms을 알아본다 - 복잡도 순으로
// 
// aaaaaaaaaaaaaabbbbbbcccccccccccccccccdddeeeeeeeeeeeeee------zzzzz 
// a개수가 10개라고? 그러면 a가 9번쨰 자리에 존재하면 O(1) 알고리즘 가능하다
// 카운트는 정렬과 관련없이 개수를 센다.
// 1. partition             O(N)
// 2. nth_element           
// 3. partial_sort
// 4. sort
// 5. stavle_sort
//-----------------------------------------------------
#include<iostream>
#include<vector>
#include<list>
#include<concepts>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool 관찰; // 관찰하려면 true로

template<class iter>
typename iterator_traits<iter>::difference_type  my_distance(iter b, iter e)
{
    //만일 iter가 random_access_iterator_tag라면 
    // C++17이후에 방식
    if constexpr (random_access_iterator<iter>) {  //컴파일시에 판단하는 조건씩
        return e - b;
    }
    else {
        typename iterator_traits<iter>::difference_type d{};
        while (b != e) {
            ++b;
            ++d;
        }
        return d;
    }
}

//----------
int main()
//------------------------------------------------------------
{  
    // 반보자간의 거리를 재는 idstance 함수
    vector<int> v{ 1,2,3,4,5 };
    list<int> c{ 1,2,3,4,5 };

    cout << "vector의 distance - " << my_distance(v.end(), v.begin()) << endl;
    cout << "list의 distance - " << my_distance(c.end(), c.begin()) << endl;
    save("메인.cpp");
}