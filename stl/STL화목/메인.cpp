//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 13�� �����      (2�� 2���� ����) 
//-------------------------------------------------------------------------------------------
//   ���� ���� �ڷḦ ó���ϱ�
//
//-------------------------------------------------------------------------------------------
#include<iostream>
#include <random>
#include<print>
#include"save.h"

using namespace std;

default_random_engine dre; //�������� �� ������ bit�� �����Ѵ�
uniform_int_distribution uid{ 1,999'9999 };
//[����] ���� int 1000���� �޸𸮿� �����϶�
// ���� ū ���� ã�� ȭ�鿡 ����϶�
void find_max_num(int num[]);

//----------
int main()
//----------
{
	int p[1000];
	for (int i = 0; i < 1000; ++i) {
		p[i] = uid(dre);
		print("{:8}", p[i]);  //���� 8 ���ڿ� ���߾� ����
	}
	cout << endl;
	find_max_num(p);

	save("����.cpp");	
}
void find_max_num(int num[]) {
	int maxNum = 0;
	for (int i = 0; i < 1000; ++i) {
		maxNum = max(maxNum, num[i]);
	}
	cout << " ���� ū ���� :" << maxNum << endl;
}





