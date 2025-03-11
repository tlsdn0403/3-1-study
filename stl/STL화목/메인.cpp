//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 11일 목요일      (1주 2일차 강의) 
//-------------------------------------------------------------------------------------------
//   template 복습
//
//-------------------------------------------------------------------------------------------
#include<iostream>
#include"save.h"
using namespace std;      //우리는 이렇게 하면 안되지만, 공부시간을 줄이기 위해


// C++에서 [문제] change 함수는 몇 번이나 overloading 해야 할까??
// C++ 언어의 자료형은 몇 개인가? 무한개

class Dog {
public:
	
	Dog() = default;
	Dog(int n) :num{ n } { };
	friend ostream& operator<<(ostream& os, const Dog& dog) {
		return os << dog.num;
	}
private:
	int num{ };
};

//템플릿은 선언과 정의를 동시에 한다
template<class T>
void change(T& a, T& b)
{
	T temp{ a };
	a = b;
	b = temp;
}
//----------
int main()
//----------
{
	cout << sizeof(Dog);
	{
		Dog a{ 1 }, b{ 2 };
		change(a, b);
		cout << a << " ," << b << endl;  //의도  -2,1  연산자 오버로딩 하는 줄
	}

	{
		int a{ 1 }, b{ 2 };
		change(a, b);
		cout << a << " ," << b << endl;  //의도  -2,1
	}
	save("메인.cpp");
	
}





