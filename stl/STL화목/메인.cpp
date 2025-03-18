//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 13일 목요일      (2주 2일차 강의) 
//-------------------------------------------------------------------------------------------
//   많은 수의 자료를 처리하기 -binary I/O
//          ->파일을 binary 모드로 열어야 변환이 일어나지 않는다.
//-------------------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<random>
#include"save.h"

using namespace std;

//파일 "int 10만개에를 바이너리모드 wirte 함수로 기록" 에 10만개의 random int 값을 기록하자.
//이 int값은 메모리 크기 그대로 기록하겠다.
//파일은 binary mode로 열자.


default_random_engine dre;


//----------
int main()
//----------
{
	ofstream out{ "int 10만개에를 바이너리모드 wirte 함수로 기록", ios::binary };

	uniform_int_distribution uid{ numeric_limits<int>::min(),numeric_limits<int>::max() }; //int의 최소부터 최댓값까지

	int num; //이게 훨씬 좋은 방법
	for (int i = 0; i < 10'0000; ++i) {
		num = uid(dre);
		out.write((char *)&num, sizeof(int)); //바이트 단위만 다룸으로 바이트 주소임을 알려줌
	}
	save("메인.cpp");	
}