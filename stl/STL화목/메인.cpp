//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 20�� �����      (3�� 2���� ����) 
//-------------------------------------------------------------------------------------------
// �����Ҵ�� smart pointer - RAII Ŭ������ �ڿ��� �����ϴ� ��
//  - C++ stack-unwinding�� �����Ѵ�
//-------------------------------------------------------------------------------------------
// Callable
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<random>
#include<array>
#include<print>
#include"save.h"
using namespace std;

uniform_int_distribution uid{ 0, 999'9999 };
default_random_engine dre;

//[����] ���� int 1000������ �޸𸮿� ��������.
// ���� int ���� [0, 1'000'0000 ) == 0���� 999'9999 ���� ���� ������ 
// qsort�� ����ؼ� ������������ �����϶�
//������ ����� �տ������� 1000���� ȭ�鿡 ����϶�

array<int, 1'000'0000> arr;

int cmp(const void* a, const void* b) {
	if (*(int*)a > *(int*)b) {
		return 1;
	}
	else if (*(int*)a < *(int*)b) {
		return -1;
	}
	else {
		return 0;
	}
}
//----------
int main()
//----------
{
	for (int& num : arr)
		num = uid(dre);
	qsort(arr.data(), arr.size(), sizeof(int), cmp);

	for (int i = 0; i < 1000; ++i) {
		print("{:5}", arr[i]);
	}
	cout << endl;
	
	save("����.cpp");
}