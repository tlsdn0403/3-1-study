//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 20�� �����      (3�� 2���� ����) 
//-------------------------------------------------------------------------------------------
//   ���� ���� �ڷḦ ó���ϱ� - Dog�� �а� ���� , read/wirte
// 
//  �̶� Dog ��ü�� �޸� ����
// 
//  1.STACK
//	2.DATA
//  3.free-store
// 
// 1,2 ���� 3���� ���� -  ũ�Ⱑ ���� ������ �� �ִ� ��?
// 1���� 2���� ����.   -  �޸� ũ�Ⱑ �󸶳� ū��?
// 
//  ���� �ð� �̰� ���� �� �����ϰ� smart pointer�� ���� - �� RAII?
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



class Dog {
private:
	string name;
	int id{};


	friend ostream& operator<<(ostream& os, const Dog& dog) { //friend�� Ŭ�������� ���� �عٴڿ� �־�� �Ѵ�.
		return os << "�� �̸�: " << dog.name << ",�� ID: " << dog.id;
	}

	friend ifstream& operator>>(ifstream& in,  Dog& dog) {
		in.read((char*)&dog, sizeof(Dog));
		return in;
	}
};

array<Dog, 10'0000> dogs;
//----------
int main()
//----------
{
	ifstream in{ "Dog 10������", ios::binary };
	if (not in)
		return 1231412;
	// [����] ���� �ڵ尡 �������� ����ǵ��� �ʿ��� �ڵ带 class Dog�� �߰��϶�.
	for (Dog& dog : dogs) {
		in >> dog;  
		cout << dog << endl;
	}

	save("����.cpp");	
}