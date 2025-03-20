//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (3주 2일차 강의) 
//-------------------------------------------------------------------------------------------
//   많은 수의 자료를 처리하기 - Dog를 읽고 쓴다 , read/wirte
// 
//  이때 Dog 객체는 메모리 영역
// 
//  1.STACK
//	2.DATA
//  3.free-store
// 
// 1,2 번과 3번의 차이 -  크기가 언제 결정할 수 있는 가?
// 1번과 2번의 차이.   -  메모리 크기가 얼마나 큰가?
// 
//  다음 시간 이거 조금 더 설명하고 smart pointer로 직행 - 왜 RAII?
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



class Dog {
private:
	string name;
	int id{};


	friend ostream& operator<<(ostream& os, const Dog& dog) { //friend는 클래스에서 제일 밑바닥에 있어야 한다.
		return os << "개 이름: " << dog.name << ",개 ID: " << dog.id;
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
	ifstream in{ "Dog 10만마리", ios::binary };
	if (not in)
		return 1231412;
	// [문제] 다음 코드가 수정없이 실행되도록 필요한 코드를 class Dog에 추가하라.
	for (Dog& dog : dogs) {
		in >> dog;  
		cout << dog << endl;
	}

	save("메인.cpp");	
}