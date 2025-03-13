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
// 가장 큰 값을 찾아 화면에 출력하라. 출력된 값이 무엇인지 적어라



//----------
int main()
//----------
{
   
    ifstream in{ "int 1000개.txt" };
    if (not in)
        return 20250313;
    cout<<"최댓값은:"<<*max_element(istream_iterator<int>{in}, {})<<endl; //별 3개를 건너뛰고 이런코딩도 가능하다

	save("메인.cpp");	

}