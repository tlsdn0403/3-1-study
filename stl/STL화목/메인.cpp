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
#include<fstream>
#include<array>
#include<vector>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool 관찰; // 관찰하려면 true로

//[문제]  "메인.cpp" 파일의 소문자 알파벳 빈도(frequency)를 다음과 같이 출력하라.
// a -> 10
// b -> 3
//.....
// z -> 0개 
// 이런식으로
//----------
int main()
//------------------------------------------------------------
{
    ifstream file("메인.cpp");
    if (not file)
    {
        return 12345;
    }

    array<int,26> frequency; // 알파벳 소문자 빈도를 저장할 벡터 초기화
    char c;
    while (file.get(c))
    {
        if (c >= 'a' && c <= 'z') {
            frequency[c - 'a'] += 1;
        }
    }

    file.close();

    for (int i = 0; i < 26; ++i)
    {
        cout << (char)('a' + i) << " -> " << frequency[i] << "개" << endl;
    }
   
    save("메인.cpp");
}