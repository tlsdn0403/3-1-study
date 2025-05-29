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
#include<fstream>
#include<ranges>
#include<array>
#include<algorithm>
#include<set>
#include<vector>
#include<map>
#include<format>
#include<print>
#include"save.h"
#include"STRING.h"
using namespace std;

extern bool ����; // �����Ϸ��� true��


// �����ڷ� "�̻��� ������ �ٸ���.txt" �� �ٿ�
// ���⿡ �ִ� ��� �ܾ multiset<STRING>�� �����϶�.
// �ܾ��� ������ ����϶� 26626
// [3] �ܾ�� ���Ƚ���� ȭ�鿡 ����϶�.

bool cmp(pair<string, int>& a, pair<string, int>& b);
void Sort(map<string, int>& M);

//----------
int main()
//------------------------------------------------------------
{  
   

    ifstream in("�̻��� ������ �ٸ���.txt");
   
    if (not in)
        return 1234;

     

    map<STRING, size_t> wordNum;
    STRING �ܾ�;
    while (in >> �ܾ�)
        wordNum[�ܾ�]++;



    for (auto [word, count] : wordNum) {
        cout << word << " - " << count << endl;
       /* println("{:20} - {:}",(char*)(word) , count);*/
    }
  
    

         
    save("����.cpp");
}