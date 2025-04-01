//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 20�� �����      (3�� 2���� ����) 
// 4�� 24�� �߰����(30) 8���� 2��
// ����    (30) - 4�� 10�� ����
//-------------------------------------------------------------------------------------------
// Callable type 
// 
//-------------------------------------------------------------------------------------------
// 
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<array>
#include<algorithm>
#include<string>
#include<print>
#include<ranges>
#include"save.h"
using namespace std;



class Dog {
public:
    bool operator()(Dog a, Dog b) const {
        if (a.name.length() == b.name.length()) {
            return a.id < b.id;
        }
        else
            return a.name.length() < b.name.length();
    }
private:
    string name;
    int id;

    friend ostream& operator<<(ostream& os, const Dog& dog) {
        return os <<dog.id<<" "<<dog.name<< " ";
    }
    friend istream& operator>>(istream& is, Dog& dog) {
        return is >> dog.id >> dog.name;
    }
};
//[����] Dog 10�������� ������ ���� ���� "Dog �ʸ�����"�� �����Ͽ���.
// ������ ���� �ڵ�� ������
//ofstream out("Dog �ʸ�����");
// 
// Dog ��ü�� class Dog�� friend operator<< �� ����Ͽ� �����Ͽ���.
// 
//[����] �� ���Ͽ��� ��Ȯ�ϰ� 10������ Dog ��ü�� ����Ǿ� �ִ�.
// ���Ͽ� ����� Dog ��ü�� ��� �о� �޸𸮿� �����϶�.
// ���� ������ ��ü�� ������ ȭ�鿡 ����ϰ� �������� ��� ������ �����.
// �޸𸮿� ����� Dog ��ü�� ���  name , ���� ���� ������������ �����϶�.
// ���ĵ� Dog ��ü�� �տ������� 100���� ȭ�鿡 ����϶�.
 
array<Dog, 10'0000> da;
//----------
int main()
//----------
{
    
    ifstream in("Dog �ʸ�����");
    for (Dog& dogs : da) {
        in >> dogs;
    }

    cout << "���� �ڿ� �ִ� Dog :" << da.back() << endl;
    sort(da.begin(), da.end(), Dog{});
    for (Dog& dogs : da |views::take(100))
        cout << dogs << endl;

    save("����.cpp");
}