//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 29�� ȭ����      (9�� 1���� ����) 
// 5�� 6��(ȭ) -> 6�� 19(����)
//-------------------------------------------------------------------------------------------
// STL Container -Containers are objects that store other objects -> �ٸ� ��ü�� ���� �� �ִ� ��ü 
// 1.Sequence Containers
//      arrat<T,N>
//      vector<T> - pish_back() ������ O(1)�ð�
//      deque<T> - push_front()/push_back() O(1)
//      list<T> -  node ��� ������ ��ġ�� ������ O(1)
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<list>
#include<algorithm>
#include"save.h"
#include"STRING.h"
using namespace std;

class Test {
    char x[1'000'000];
};

extern bool ����; // �����Ϸ��� true��

//----------
int main()
//------------------------------------------------------------
{
    //[����] "����.cpp"�� �ܾ list�� �����϶�.
    //ã�� �ܾ ������� ������ ���� , ������ list�� �� ��° �ܾ����� ����� ����.

    
    ifstream in("����.cpp");
    if (not in) {
        return 123123;
    }
    list<STRING> �ܾ��{ istream_iterator<STRING>{in} , {} };   //�� �ڵ尡 �� ����ɱ�??? �ʰ� ���̾� ��ǲ���Ϸκ��� �о�� �� �ִ� ���۷����͸� �������� ������ �����ϴ�
   
    while (true) {
        cout << "ã���� �ܾ�?? ";
        STRING �ܾ�;
        cin >> �ܾ�;

        auto res = find(�ܾ��.begin(), �ܾ��.end(), �ܾ�);
        if (res == �ܾ��.end())
            cout << �ܾ� << "-  ���� �ܾ��Դϴ�" << endl;
        else
            cout << "ã�ҽ��ϴ�" << endl;
    }
    save("����.cpp");
}