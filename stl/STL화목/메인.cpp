//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 20�� �����      (7�� 1���� ����) 
// 4�� 24�� �߰����(30) 8���� 2�� E�� 320ȣ
// 5�� 6��(ȭ) -> 6�� 19(����)
//-------------------------------------------------------------------------------------------
// STL Container -Containers are objects that store other objects -> �ٸ� ��ü�� ���� �� �ִ� ��ü 
// 1.Sequence Containers
//      arrat<T,N>
//      vector<T> /dynamic(runtime)  array
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<vector>
#include<algorithm>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool ����; // �����Ϸ��� true��

//----------
int main()
//------------------------------------------------------------
{       
    vector<int> v{ 1,2,3,4,5 };
    //[����] v���� 3�� �����϶�.
    remove(v.begin(), v.end(), 3);
    for (int n : v)
        cout << n << " ";
    save("����.cpp");
}