//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 20�� �����      (7�� 1���� ����) 
// 4�� 24�� �߰����(30) 8���� 2�� E�� 320ȣ
// 5�� 6��(ȭ) -> 6�� 19(����)
//-------------------------------------------------------------------------------------------
// STL Container -Containers are objects that store other objects -> �ٸ� ��ü�� ���� �� �ִ� ��ü 
// 1.Sequence Containers
//      arrat<T,N>
//      vector<T> /dynamic(runtime)  array
//      deque<T> - vector ���� �� ���� ���Ҹ� ���� �� �ִ�.
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<deque>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool ����; // �����Ϸ��� true��

//----------
int main()
//------------------------------------------------------------
{     
   
    deque<STRING> d{ "1","22","333","4444","55555" };
    
    ���� = true;
    d.push_front("0");
    d.push_front("-1");
    ���� = false;
    for (const STRING& s : d)
        cout << s << endl;
    save("����.cpp");
}