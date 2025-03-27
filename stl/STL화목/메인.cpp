//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (3주 2일차 강의) 
//-------------------------------------------------------------------------------------------
// 동적할당과 smart pointer - RAII 클래스로 자원을 관리하는 것
//  - C++ stack-unwinding을 보장한다
//-------------------------------------------------------------------------------------------
// Callable
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<random>
#include<array>
#include<print>
#include<ranges>
#include<algorithm>
#include"save.h"
using namespace std;


//[문제] 랜덤 int 1000만개를 메모리에 저장하자.
// 랜덤 int 값은 [0, 1'000'0000 ) == 0부터 999'9999 까지 값을 갖도록 
// c++언어의 sort를 사용해서 오름차순으로 정렬하라
//정렬한 결과를 앞에서부터 1000개만 화면에 출력하라

array<int, 1'000'0000> a;

uniform_int_distribution uid{ 0, 999'9999 };
default_random_engine dre;

bool 오름차순(const int a, const int b)
{
	return a < b;
}

//----------
int main()
//----------
{
	for (int& num : a)
		num = uid(dre);

	//정렬
	sort(a.begin(), a.end(),오름차순);  // 디폴트 정렬 operator <
	
	for (int num:a | views::take(1000))
		print("{:8}", num);
	cout << endl;
	
	save("메인.cpp");
}