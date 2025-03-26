//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (3주 2일차 강의) 
//-------------------------------------------------------------------------------------------
// 동적할당과 smart pointer - RAII 클래스로 자원을 관리하는 것
//  - C++ stack-unwinding을 보장한다
//-------------------------------------------------------------------------------------------
// 많은 수의 자료 - FILE
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<array>
#include<random>
#include<print>
#include"save.h"
using namespace std;

uniform_int_distribution<int> uid{ 1, 99999 };
default_random_engine dre;

array<int, 100> arr;

// int 정렬방법 (const void*,const void*);
int cmp(const void* a, const void* b)
{
	
	int x = *static_cast<const int*>(a);
	int y = *static_cast<const int*>(b);
	if (x < y)
		return -1;
	else if (x > y)
		return 1;
	return 0;
}


int main()
{
	for (int& num : arr)
		num = uid(dre);


	qsort(arr.data(), arr.size(), sizeof(int), cmp);

	for (int num : arr) {
		print("{:8}", num);
	}
   
   return 0;  
}