//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 13�� �����      (2�� 2���� ����) 
//-------------------------------------------------------------------------------------------
//   ���� ���� �ڷḦ ó���ϱ�
//
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<random>
#include<print>
#include<fstream>
#include<array>
#include<algorithm>
#include"save.h"

using namespace std;

default_random_engine dre{  }; //������ �õ带 ������ �� �ִ�. 
uniform_int_distribution uid{ 0,999'9999 }; 


//[����] ���� "int 100��.txt"���� int 1000���� text�� ��ϵǾ� �ִ�.
// �� �����͸� �޸𸮿� �����϶�.
// �޸𸮿� �ִ� �����͸� ȭ�鿡 ����Ͻÿ�.



//----------
int main()
//----------
{
   
    ifstream in{ "int 1000��.txt" };
    if (not in)
        return 20250313;
    
    array<int, 1000> arr;
    for (int i = 0; i < 1000; ++i) {
        in >> arr[i];
    }
    for (auto num : arr) {
        print("{:8}", num);
    }
    cout << endl;
	save("����.cpp");	

}