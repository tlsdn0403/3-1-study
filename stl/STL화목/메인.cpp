//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 29�� ȭ����      (9�� 1���� ����) 
// 5�� 6��(ȭ) -> 6�� 19(����)
//-------------------------------------------------------------------------------------------
// STL Container -Containers are objects that store other objects -> �ٸ� ��ü�� ���� �� �ִ� ��ü 
// 1.Sequence Containers
//      arrat<T,N>
//      vector<T> /dynamic(runtime)  array
//      deque<T> - vector ���� �� ���� ���Ҹ� ���� �� �ִ�.
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
#include<ranges>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool ����; // �����Ϸ��� true��

//----------
int main()
//------------------------------------------------------------
{
    ���� = true;
    list<STRING> cont { "1","333", "55555","4444","22" };

    ranges::sort(cont.begin(), cont.end());
    for (const STRING& s : cont) {
        cout << s << endl;
    }

    ���� = false;
    save("����.cpp");
}