//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  5�� 13�� ȭ����      (11�� 1���� ����) 
//  6�� 19�� �� 15�� 2�� - �⸻����
//-------------------------------------------------------------------------------------------
//  iterator - Iterators are a generalization of pointers that 
// allow a C++ program to work with different data structures in a uniform manner
// 
// �ݺ��ڴ� Ŭ������ �ڵ��ؾ� �մϴ�.
// 
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<algorithm>
#include"save.h"
#include"STRING.h"
using namespace std;

extern bool ����; // �����Ϸ��� true��


//----------
int main()
//------------------------------------------------------------
{  

    STRING s{ "2025 5 15" };

    // �������� ����ǵ���
    sort(s.begin(), s.end());

    cout << s << endl;   // "0122555"

    save("����.cpp");
}