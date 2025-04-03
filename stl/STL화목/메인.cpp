//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 20�� �����      (5�� 2���� ����) 
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
    void show() const {
        println("[{:12}] - {}", id, name);
    }

    size_t getNameLen( )const {
        return name.length();
    }

    bool operator<(const Dog& other) const {
        return name.size() < other.name.size();
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
//[����] ���� "Dog �ʸ�����" ���� ��Ȯ�ϰ� 10������ Dog ��ü�� ����Ǿ� �ִ�.
// ���Ͽ� ����� Dog ��ü�� ��� �о� �޸𸮿� �����϶�.
// ���� ������ ��ü�� ������ ȭ�鿡 ����ϰ� �������� ��� ������ �����.
// �޸𸮿� ����� Dog ��ü�� ���  name , ���� ���� ������������ �����϶�.
// ���ĵ� Dog ��ü�� �տ������� 100���� ȭ�鿡 ����϶�.
 
array<Dog, 10'0000> dogs;
//----------
int main()
//----------
{
    
    ifstream in("Dog �ʸ�����"); //�Ȱ��� text ���� ����� �Ѵ�.
    if (not in)
        return 1234;
    for (int i = 0; i < 10'0000; ++i) {
        in >> dogs[i];
    }
    cout << "���� ������ ��ü�� ���� : "<< endl;
    dogs.back().show();

    cout << "Dog name ���̱��� ��������( ascending order) ���� �����մϴ�" << endl;

    sort(dogs.begin(), dogs.end());
    
    for (const Dog& dog : dogs | views::reverse)
        dog.show();
    save("����.cpp");
}