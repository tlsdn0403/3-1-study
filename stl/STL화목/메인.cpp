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
#include<fstream>
#include<ranges>
#include<array>
#include<algorithm>
#include<set>
#include<vector>
#include<map>
#include<format>
#include<print>
#include"save.h"
#include"STRING.h"
using namespace std;

extern bool 관찰; // 관찰하려면 true로


// 강의자료 "이상한 나라의 앨리스.txt" 를 다운
// 여기에 있는 모든 단어를 multiset<STRING>에 저장하라.
// 단어의 개수를 출력하라 26626
// [3] 단어와 사용횟수를 화면에 출력하라.

bool cmp(pair<string, int>& a, pair<string, int>& b);
void Sort(map<string, int>& M);

//----------
int main()
//------------------------------------------------------------
{  
   

    ifstream in("이상한 나라의 앨리스.txt");
   
    if (not in)
        return 1234;

     

    map<STRING, size_t> wordNum;
    STRING 단어;
    while (in >> 단어)
        wordNum[단어]++;



    for (auto [word, count] : wordNum) {
        cout << word << " - " << count << endl;
       /* println("{:20} - {:}",(char*)(word) , count);*/
    }
  
    

         
    save("메인.cpp");
}