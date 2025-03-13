//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 13일 목요일      (2주 2일차 강의) 
//-------------------------------------------------------------------------------------------
//   많은 수의 자료를 처리하기
//
//-------------------------------------------------------------------------------------------
#include<iostream>
#include <random>
#include<print>
#include"save.h"

using namespace std;

default_random_engine dre; //엔전에서 막 임의의 bit를 가공한다
uniform_int_distribution uid{ 1,999'9999 };
//[문제] 랜덤 int 1000개를 메모리에 저장하라
// 가장 큰 값을 찾아 화면에 출력하라
void find_max_num(int num[]);

//----------
int main()
//----------
{
	int p[1000];
	for (int i = 0; i < 1000; ++i) {
		p[i] = uid(dre);
		print("{:8}", p[i]);  //나는 8 글자에 맞추어 볼래
	}
	cout << endl;
	find_max_num(p);

	save("메인.cpp");	
}
void find_max_num(int num[]) {
	int maxNum = 0;
	for (int i = 0; i < 1000; ++i) {
		maxNum = max(maxNum, num[i]);
	}
	cout << " 가장 큰 수는 :" << maxNum << endl;
}





