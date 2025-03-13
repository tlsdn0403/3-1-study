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
#include"save.h"

using namespace std;

default_random_engine dre{  }; //엔진의 시드를 설정할 수 있다. 
uniform_int_distribution uid{ 0,999'9999 }; 


//[문제] 랜덤 int 값 1000개를 파일"int 1000개.txt" 에 텍스트 모드로 저장하라
// 파일을 열었을 때 사람이 읽을 수 있어야 한다.
// 파일을 읽어서 원래 int값을 가져올 수 있어야 한다.


//----------
int main()
//----------
{
    ofstream out{ "int 1000개.txt"}; //RAII 하면 굳이 out.close()를 해줄 필요가 없다
    int cnt{};
    for (int i = 0; i < 1000; ++i) {
        print(out, "{:8} , ", uid(dre)); //구분자 ,delimeter
        if (not( ++cnt % 10))
            out << endl;
    }

    ifstream in;

	save("메인.cpp");	

}