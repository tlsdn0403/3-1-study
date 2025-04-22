//-----------------------------------------------------------------------------
// 2024 STL 중간시험
// 
// Visual Studio 버전 17.9.0 이상 
// Release / x64
// 프로젝트 속성 - C++ 언어 표준 - 최신 C++ 초안의 기능(/std:c++latest)
//-----------------------------------------------------------------------------
// 답지 작성 방법
// - 각 문제를 해결하는 데 필요한 코드만 적는다.
// - 화면 출력을 요구하는 문제는 출력된 내용을 답지에 적는다.
// - 헤더 파일을 적을 필요는 없다.
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <deque>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <list>
#include <memory>
#include <numeric>
#include <print>
#include <random>
#include <string>
#include <vector>
using namespace std;

default_random_engine dre;
uniform_int_distribution uid{ 1, 111 };
uniform_int_distribution uidNum{ 1, 999 };


//---------------------------------------------------------------------------
// class Bird는 num개의 int값을 free store에 저장한다.
//--------------------------------------------------------------------------- 
// file "새들"에는 몇 개인지 모르는 Bird 객체가 기록되어 있다.
// file은 binary mode로 열어 write 멤버함수를 사용하여 기록하였다.
//---------------------------------------------------------------------------

//-----------
// class Bird
//-----------

class Bird {
private:
	int num{};							// [1, 1000] random 값
	int* p{};							// 문제의 난이도를 낮추려고 raw pointer를 사용하였다

public:
	Bird() = default;

	Bird(int n) : num{ n } {			// [문제 1]을 풀지 못한 경우 사용할 생성자
		p = new int[num];
		for (int i = 0; i < num; ++i)
			p[i] = uidNum(dre);
	}

	Bird(const Bird& other) : num{ other.num } {
		p = new int[num];
		memcpy(p, other.p, sizeof(int) * num);
	}

	Bird& operator=(const Bird& rhs) {
		if (this == &rhs)
			return *this;
		delete[] p;
		num = rhs.num;
		p = new int[num];
		memcpy(p, rhs.p, sizeof(int) * num);

		return *this;
	}

	int getNum() const {
		return num;
	}

	int* getData() const {
		return p;
	}

	void show() const {
		cout << "저장하고 있는 int 개수 - " << num << endl;
		for (int i = 0; i < num; ++i)
			print("{:8}", p[i]);
		cout << endl;
	}

	istream& read(istream& is) {
		delete[] p;		// 만일 nullptr라면 아무일도 없다.
		is.read((char*)(this), sizeof(*this));
		p = new int[num];
		is.read((char*)(p), sizeof(int) * num);
		return is;
	}

	void write(ostream& os) {
		os.write((const char*)(this), sizeof(*this));
		os.write((const char*)p, sizeof(int) * num);
	}

	friend ostream& operator>>(ostream& os, Bird& b) {
		return os;
	}

};

//---------
int main()
//---------
{
	string inFileName{ "새들" };
	ifstream in{ inFileName, ios::binary };

	if (not in) {
		cout << "파일 \"" << inFileName << "\"을 열 수 없습니다" << endl;
		return 0;
	}

	{
		// 실행 확인용 코드
		//Bird bird{ 24 };
		//bird.show( );

		// 화면 출력(예)
		// 저장하고 있는 int 개수 - 24
		//		814     136     905     835     127     968     913     221     632     308
		//		 98     547     279     189     547     992     957     996     964     967
		//		158     726     970     981
	}



	//--------------------------------------------------------------------------
	// [문제 1] 파일에 있는 Bird 객체를 컨테이너에 저장하라.                  
	// 모두 몇 객체인가를 화면에 출력하라.                          		(40) 
	//--------------------------------------------------------------------------
	// 컨테이너에 저장하기 위한 코드와 관련 코드를 답지에 적는다.
	// class Bird에 read 멤버를 추가하여 문제를 해결할 수 있다.
	// (물론 다른 방식으로 읽을 수도 있다)
	// 화면에 출력된 읽은 객체 수를 답지에 쓴다.
	//--------------------------------------------------------------------------

	/*vector<Bird> v;

	int cnt{0};
	Bird bird;
	while (!in.eof()) {
		bird.read(in);
		v.push_back(bird);
		++cnt;
	}

	cout << "객체의 수: " << cnt << endl << endl;*/

	vector<Bird> v;
	v.reserve(1'0000);

	Bird b;
	while (b.read(in))
		v.push_back(b);

	cout << "읽은 Bird의 수 - " << v.size() << endl;

	// ******************************************************
	// * 파일을 읽지 못한 학생은 아래 주석을 풀자.          *
	// * 답지에 파일을 읽지 못했다고 적고,                  *	
	// * 코드를 실행 한 후 [문제 2]부터 해결해 나가면 된다. *
	// ******************************************************

	// [문제 1]을 해결하지 못한 경우 주석을 제거하자

	/*vector<Bird> v;
	v.reserve( 1'000 );
	for ( int i = 0; i < 1'000; ++i )
		v.emplace_back( uid( dre ) );*/



		//--------------------------------------------------------------------------
		// [문제 2] 컨테이너에 있는 Bird 객체 중에서 num 값이 100이하인 객체는 
		// 모두 몇 개인지 화면에 출력하라.										(20)
		//--------------------------------------------------------------------------
		// 문제를 해결하는 코드를 답지에 적어라.
		// 화면에 출력한 개수를 답지에 적어라.
		//--------------------------------------------------------------------------

		/*int num = count_if(v.begin(), v.end(), [](Bird& b) {
			return b.getNum() <= 100;
			});

		cout << "num 값이 100이하인 객체 수: " << num << endl << endl;*/

	size_t birdNum = count_if(v.begin(), v.end(), [](const Bird& b) {
		return b.getNum() <= 100;
		});

	cout << "100 이하인 Bird - " << birdNum << endl;

	//--------------------------------------------------------------------------
	// [문제 3] 컨테이너에 있는 Bird 객체를 num 기준 오름차순으로 정렬하라.
	// 제일 마지막 객체의 정보를 출력하라.									(10)
	//--------------------------------------------------------------------------
	// 문제를 해결하는 코드를 답지에 적어라.
	// 화면에 출력한 마지막 객체의 num을 답지에 적어라.
	//--------------------------------------------------------------------------

	/*sort(v.begin(), v.end(), [](Bird& a, Bird& b) {
		return a.getNum() < b.getNum();
		});

	cout << "제일 마지막 객체의 정보: num-" << v.back().getNum() << ", data-" << v.back().getData() << endl << endl;*/

	sort(v.begin(), v.end(), [](const Bird& a, const Bird& b) {
		return a.getNum() < b.getNum();
		});

	cout << "정렬 후 마지막 객체 - " << v.back().getNum() << endl;
	cout << v[v.size() - 1].getNum() << endl;
	cout << v.rbegin()->getNum() << endl;
	cout << (*v.rbegin()).getNum() << endl;

	//--------------------------------------------------------------------------
	// [문제 4] [문제 3]의 정렬을 더 효율적으로 실행하고 싶다. 
	// 해결방안을 간단하게 적어라.										   (10)	
	//--------------------------------------------------------------------------

	// 자원을 관리하는 이 클래스가 이동문법을 지원하면 효율적이다.

	//--------------------------------------------------------------------------
	// [문제 5] class Bird에서 잘못된 부분을 지적하고 해결방법을 적어라.   (10)	
	//--------------------------------------------------------------------------

	// free store에 확보한 메모리를 해제하지 않고 있다.
	// 소멸자에서 자원을 반환하도록 한다.

	//--------------------------------------------------------------------------
	// [문제 6] 다음 블럭의 코드는 반복자 p를 사용하여 v의 모든 원소를 출력한다.
	// 원소 한개를 추가 후 다시 v의 모든 원소를 출력하면 제대로 출력되지 않는다.
	// 왜 그런지 설명하라.												   (20)
	//--------------------------------------------------------------------------
	// (주의) 이 문제는 앞의 문제들과 관련이 없다.
	// 앞의 문제를 모두 해결한 후 주석을 풀고, 단독으로 실행한 후 답하라.
	//--------------------------------------------------------------------------

	/*
	{ // 블럭 코드 시작
		vector<int> v( 100 );
		iota( v.begin( ), v.end( ), 1 );

		auto p = v.begin( );

		cout << endl;
		cout << "v의 원소를 모두 출력" << endl;

		for (auto i = p; i != v.end( ); ++i)
			print( "{:8}", *i );


		cout << endl;
		cout << "원소를 하나 추가한 후 다시 v를 출력" << endl;

		v.push_back( 101 );

		for (auto i = p; i != v.end( ); ++i)
			print( "{:8}", *i );
	}
	*/

	// 이사를 가서 반복자가 무효화됐기 때문이다.
}