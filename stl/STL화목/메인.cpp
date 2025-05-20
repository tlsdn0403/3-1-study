//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  5�� 13�� ȭ����      (11�� 1���� ����) 
//  6�� 19�� �� 15�� 2�� - �⸻����
//-------------------------------------------------------------------------------------------
//  �ݺ��ڿ� �˰���
// 
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<algorithm>
#include<vector>
#include"save.h"
#include"STRING.h"
using namespace std;

extern bool ����; // �����Ϸ��� true��

template<class �ݺ��� , class ��>
�ݺ��� myfind(�ݺ��� b, �ݺ��� e, �� v)
{
    while (b != e) {
        if (*b == v)
            return b;
        ++b;
    }
    return e;
}

template<class �ݺ���, class Pred>
�ݺ��� myfind_if(�ݺ��� b, �ݺ��� e, Pred f)
{
    for (; b != e; ++b) {
        if (f(*b))
            return b;
    }
    return e;
}
template<class �ݺ��� , class �������ݺ���>
void my_copy(�ݺ��� b, �ݺ��� e, �������ݺ��� d)
{
    while (b != e) {
        *d = *b;
        ++b;
        ++d;
    }
}
//----------
int main()
//------------------------------------------------------------
{  
    STRING s{ "�ݺ��ڸ� ����� �˰����� ���� ��" };
    vector<char> v{};
    my_copy(s.begin(), s.end(), back_inserter(v));

    for (const char& c : v) {
        cout << c;
    }
    cout << endl;

    save("����.cpp");
}