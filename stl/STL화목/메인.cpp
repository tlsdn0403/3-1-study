//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 11�� �����      (1�� 2���� ����) 
//-------------------------------------------------------------------------------------------
//   template ����
//
//-------------------------------------------------------------------------------------------
#include<iostream>
#include"save.h"
using namespace std;      //�츮�� �̷��� �ϸ� �ȵ�����, ���νð��� ���̱� ����


// C++���� [����] change �Լ��� �� ���̳� overloading �ؾ� �ұ�??
// C++ ����� �ڷ����� �� ���ΰ�? ���Ѱ�

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

//���ø��� ����� ���Ǹ� ���ÿ� �Ѵ�
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
		cout << a << " ," << b << endl;  //�ǵ�  -2,1  ������ �����ε� �ϴ� ��
	}

	{
		int a{ 1 }, b{ 2 };
		change(a, b);
		cout << a << " ," << b << endl;  //�ǵ�  -2,1
	}
	save("����.cpp");
	
}





