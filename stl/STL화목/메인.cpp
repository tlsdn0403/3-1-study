//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 20�� �����      (3�� 2���� ����) 
//-------------------------------------------------------------------------------------------
// �����Ҵ�� smart pointer - RAII Ŭ������ �ڿ��� �����ϴ� ��
//  - C++ stack-unwinding�� �����Ѵ�
//-------------------------------------------------------------------------------------------
// ���� ���� �ڷ� - FILE
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

// int ���Ĺ�� (const void*,const void*);
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