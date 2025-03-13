//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 13일 목요일      (2주 2일차 강의) 
//-------------------------------------------------------------------------------------------
//   많은 수의 자료를 처리하기
//
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<random>
#include<print>
#include<fstream>
#include<array>
#include<algorithm>
#include"save.h"

using namespace std;

default_random_engine dre{  }; //엔진의 시드를 설정할 수 있다. 
uniform_int_distribution uid{ 0,999'9999 }; 


//[문제] 파일 "int 100개.txt"에는 int 1000개가 text로 기록되어 있다.
// 이 데이터를 메모리에 저장하라.
// 메모리에 있는 데이터를 화면에 출력하시오.



//----------
int main()
//----------
{
   
    ifstream in{ "int 1000개.txt" };
    if (not in)
        return 20250313;
    
    array<int, 1000> arr;
    for (int i = 0; i < 1000; ++i) {
        in >> arr[i];
    }
    for (auto num : arr) {
        print("{:8}", num);
    }
    cout << endl;
	save("메인.cpp");	

}