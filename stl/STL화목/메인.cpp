//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  5�� 22�� �����      (12�� 2���� ����) 
//  6�� 19�� �� 15�� 2�� - �⸻����
//-------------------------------------------------------------------------------------------
//  Associative Container - key�� ������ value�� �׻� ���Ļ��·� �����ϴ� �����̳�
//                          ������ key���� �������� �Ѵ�.
//  set / multiset - key == value
//  map / multimap - pair(key, value>
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<algorithm>
#include<set>
#include<ranges>
#include"save.h"
#include"STRING.h"
using namespace std;

extern bool ����; // �����Ϸ��� true��
template<>
struct less<STRING>
{
public:
    bool operator()(const STRING & a, const STRING  & b) const //�̰� ����Լ��� �ٲ��ִ� ���� ���� const�� �ٿ���� �� const �ϰ���
    {
        return a.size() < b.size();
    }
};

//----------
int main()
//------------------------------------------------------------
{  
    

    //[����] s�� �⺻���� ������ less�� ����Ͽ� ����Ʈ �� �������� ���ĵǰ� ����
    set<STRING > s{ "333","2222","11111","44","5" }; 

    for (const STRING& str : s) {
        cout << str << endl;
    }
    cout<<endl;



    save("����.cpp");
}