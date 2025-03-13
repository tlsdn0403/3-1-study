//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 13일 목요일      (2주 2일차 강의) 
//-------------------------------------------------------------------------------------------
//   많은 수의 자료를 처리하기
//
//-------------------------------------------------------------------------------------------
#include<iostream>
#include <random>
#include<print>
#include<fstream>
#include<array>
#include<algorithm>
#include"save.h"

using namespace std;

default_random_engine dre{  }; //엔진의 시드를 설정할 수 있다. 
uniform_int_distribution uid{ 0,999'9999 }; 


//[문제] 파일 "int 100개.txt"에는 intㄱ밧 100개가 text로 기록되어 있다.
// 가장 큰 값을 찾아 화면에 출력하라. 출력된 값이 무엇인지 적어라



//----------
int main()
//----------
{
   
    ifstream in{ "int 1000개.txt" };
    array<int, 1000> arr;
    for (int i = 0; i < 1000; ++i) {
        in >> arr[i];
    }
    cout << "가장 큰 값은 :" << *max_element(arr.begin(), arr.end()) << endl;
    for (auto num : arr) {
        print("{:8}", num);
    }

	save("메인.cpp");	

}