//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (3주 2일차 강의) 
//-------------------------------------------------------------------------------------------
//   많은 수의 자료를 처리하기 - Dog를 읽고 쓴다 , read/wirte
// 
//-------------------------------------------------------------------------------------------
// constexpr 가 뭘까??? 알아보자
// structured-binding
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<array>
#include"save.h"


using namespace std;

// [문제] eclass에서 다운 받은 파일 "Dog 10만마리" 는 binary mode로 열었고,
// 위에 적은 class Dog를 스트림의 write 함수를 사용하여 메모리 그대로 저장하였다.
// Dog 객체 10만개를 메모리에 저장하라.
// 가장 마지막 객체의 정보를 cout을 사용하여 화면에 출력하라. 


class Dog {
private:
	string name;
	int id{};

	static int sid; // scope - local , life time - global

	friend ostream& operator<<(ostream& os, const Dog& dog) { //friend는 클래스에서 제일 밑바닥에 있어야 한다.
		return os << "개 이름: " << dog.name << ",개 ID: " << dog.id;
	}
};

int Dog::sid{ };
array<Dog, 10'0000> dogs;
//----------
int main()
//----------
{
	ifstream in{ "Dog 10만마리", ios::binary };
	if (not in)
		return 1231412;

	in.read((char*)dogs.data(), sizeof(Dog) * dogs.size());


	cout << dogs.back() << endl;
	save("메인.cpp");	
}