//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (3주 2일차 강의) 
// 4월 24일 중간고사(30) 8주차 2일
// 과제    (30) - 4월 10일 설명
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
//[설명] Dog 10만마리를 다음과 같이 파일 "Dog 십만마리"에 저장하였다.
// 파일은 다음 코드로 열었다
//ofstream out("Dog 십만마리");
// 
// Dog 객체는 class Dog의 friend operator<< 를 사용하여 저장하였다.
// 
//[문제] 이 파일에는 정확하게 10만개의 Dog 객체가 저장되어 있다.
// 파일에 저장된 Dog 객체를 모두 읽어 메모리에 저장하라.
// 제일 마지막 객체의 정보를 화면에 출력하고 답지에도 출력 내용을 적어라.
// 메모리에 저장된 Dog 객체를 멤버  name , 길이 기준 오름차순으로 정렬하라.
// 정렬된 Dog 객체를 앞에서부터 100개를 화면에 출력하라.
 
array<Dog, 10'0000> da;
//----------
int main()
//----------
{
    
    ifstream in("Dog 십만마리");
    for (Dog& dogs : da) {
        in >> dogs;
    }

    cout << "가장 뒤에 있는 Dog :" << da.back() << endl;
    sort(da.begin(), da.end(), Dog{});
    for (Dog& dogs : da |views::take(100))
        cout << dogs << endl;

    save("메인.cpp");
}