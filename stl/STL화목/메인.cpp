//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 13�� �����      (2�� 2���� ����) 
//-------------------------------------------------------------------------------------------
//   ���� ���� �ڷḦ ó���ϱ�
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

default_random_engine dre{  }; //������ �õ带 ������ �� �ִ�. 
uniform_int_distribution uid{ 0,999'9999 }; 


//[����] ���� int 1000���� �޸𸮿� �����϶�
// ����� �� �߿��� ���� ū ���� ã�� ȭ�鿡 ����϶� 

void find_max_num(int num[]);

//----------
int main()
//----------
{
	array<int, 1000> arr; //�ϰ��� ǥ�������� �ٲ��.

	for (int& num : arr) { //�������� �����ۿ� �ִ°� ���� 
		num = uid(dre);
	}

	//end�� iterator �� ������ ���� �ڿ� ���� ����Ų��.

	cout << " ���� ū ���� :" << *max_element(arr.begin(), arr.end()) << endl;
	

	save("����.cpp");	
}
void find_max_num(int num[]) {
	int maxNum{ numeric_limits<int>::min() }; //���� �� �� �л��� �̷��� ����.

	for (int i = 0; i < 1000; ++i) {
		maxNum = max(maxNum, num[i]);
	}
	cout << " ���� ū ���� :" << maxNum << endl;
}





