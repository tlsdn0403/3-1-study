//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 20�� �����      (3�� 2���� ����) 
//-------------------------------------------------------------------------------------------
//   ���� ���� �ڷḦ ó���ϱ� - Dog�� �а� ���� , read/wirte
// 
//-------------------------------------------------------------------------------------------
// constexpr �� ����??? �˾ƺ���
// structured-binding
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<array>
#include"save.h"


using namespace std;

// [����] eclass���� �ٿ� ���� ���� "Dog 10������" �� binary mode�� ������,
// ���� ���� class Dog�� ��Ʈ���� write �Լ��� ����Ͽ� �޸� �״�� �����Ͽ���.
// Dog ��ü 10������ �޸𸮿� �����϶�.
// ���� ������ ��ü�� ������ cout�� ����Ͽ� ȭ�鿡 ����϶�. 


class Dog {
private:
	string name;
	int id{};

	static int sid; // scope - local , life time - global
	friend ostream& operator<<(ostream& os, const Dog& dog) {
		os << "�� �̸�: " << dog.name << ",�� ID: " << dog.id;
		return os;
	}
};

int Dog::sid{ };
array<Dog, 10'0000> Da;
//----------
int main()
//----------
{
	ifstream in{ "Dog 10������", ios::binary };
	
	in.read((char*)&Da, sizeof(Dog) * Da.size());

	cout << Da.back() << endl;
	save("����.cpp");	
}