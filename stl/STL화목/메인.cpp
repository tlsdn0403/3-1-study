//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 29일 화요일      (9주 1일차 강의) 
// 5월 6일(화) -> 6월 19(예정)
//-------------------------------------------------------------------------------------------
// STL Container -Containers are objects that store other objects -> 다른 객체를 담을 수 있는 객체 
// 1.Sequence Containers
//      arrat<T,N>
//      vector<T> - pish_back() 동작이 O(1)시간
//      deque<T> - push_front()/push_back() O(1)
//      list<T> -  node 기반 임의의 위치에 삽입이 O(1)
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<list>
#include<algorithm>
#include"save.h"
#include"STRING.h"
using namespace std;

class Test {
    char x[1'000'000];
};

extern bool 관찰; // 관찰하려면 true로

//----------
int main()
//------------------------------------------------------------
{
    //[문제] "메인.cpp"의 단어를 list에 저장하라.
    //찾을 단어를 물어봐서 없으면 없다 , 있으면 list의 몇 번째 단어인지 출력해 주자.

    
    ifstream in("메인.cpp");
    if (not in) {
        return 123123;
    }
    list<STRING> 단어들{ istream_iterator<STRING>{in} , {} };   //이 코드가 왜 실행될까??? 너가 말이야 인풋파일로부터 읽어올 수 있는 오퍼레이터를 만들어놨기 때문에 가능하다
   
    while (true) {
        cout << "찾으실 단어?? ";
        STRING 단어;
        cin >> 단어;

        auto res = find(단어들.begin(), 단어들.end(), 단어);
        if (res == 단어들.end())
            cout << 단어 << "-  없는 단어입니다" << endl;
        else
            cout << "찾았습니다" << endl;
    }
    save("메인.cpp");
}