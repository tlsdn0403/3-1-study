//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 13일 목요일      (2주 2일차 강의) 
//-------------------------------------------------------------------------------------------
//   많은 수의 자료를 처리하기
//
//-------------------------------------------------------------------------------------------
#include<iostream>
#include <random>
#include<print>
#include<vector>
#include<array>
#include<algorithm>
#include"save.h"

using namespace std;

default_random_engine dre{  }; //엔진의 시드를 설정할 수 있다. 
uniform_int_distribution uid{ 0,999'9999 }; 


//[문제] 랜덤 int 1000개를 메모리에 저장하라
// 저장된 값 중에서 가장 큰 값을 찾아 화면에 출력하라 

void find_max_num(int num[]);

//----------
int main()
//----------
{
	array<int, 1000> arr; //일관된 표현식으로 바뀐다.

	for (int& num : arr) { //지역에서 지역밖에 있는거 못함 
		num = uid(dre);
	}

	//end는 iterator 가 마지막 원소 뒤에 값을 가리킨다.

	cout << " 가장 큰 수는 :" << *max_element(arr.begin(), arr.end()) << endl;
	

	save("메인.cpp");	
}
void find_max_num(int num[]) {
	int maxNum{ numeric_limits<int>::min() }; //공부 좀 한 학생은 이렇게 쓴다.

	for (int i = 0; i < 1000; ++i) {
		maxNum = max(maxNum, num[i]);
	}
	cout << " 가장 큰 수는 :" << maxNum << endl;
}





