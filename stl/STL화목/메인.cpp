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
#include<fstream>
#include<array>
#include<vector>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool ����; // �����Ϸ��� true��

//[����]  "����.cpp" ������ �ҹ��� ���ĺ� ��(frequency)�� ������ ���� ����϶�.
// a -> 10
// b -> 3
//.....
// z -> 0�� 
// �̷�������
//----------
int main()
//------------------------------------------------------------
{
    ifstream file("����.cpp");
    if (not file)
    {
        return 12345;
    }

    array<int,26> frequency; // ���ĺ� �ҹ��� �󵵸� ������ ���� �ʱ�ȭ
    char c;
    while (file.get(c))
    {
        if (c >= 'a' && c <= 'z') {
            frequency[c - 'a'] += 1;
        }
    }

    file.close();

    for (int i = 0; i < 26; ++i)
    {
        cout << (char)('a' + i) << " -> " << frequency[i] << "��" << endl;
    }
   
    save("����.cpp");
}