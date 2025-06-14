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
#include <thread>
#include <vector>
using namespace std;

default_random_engine dre;
uniform_int_distribution uid{ 1, 1234 };
uniform_int_distribution uidMon;

//---------------------------------------------------------------------------
// class Monster는 num 밀리초만큼 CPU를 정지시킨다. 
// 멤버 s에는 숫자로만 이루어진 문자열이 저장되어 있다.
// file "몬스터들"에는 몇 개인지 모르는 Monster 객체가 기록되어 있다.
// file은 binary mode로 열어 write 멤버함수를 사용하여 기록하였다.
//---------------------------------------------------------------------------

//--------------
// class Monster
//--------------

class Monster {
private:
	int num{};							// [1, 1000] random 값
	string s;							// [0, 9] digit로만 이루어진 문자열

public:
	Monster() = default;

	Monster(int n) : num{ n } {		// 파일에서 읽지 못한 경우 사용
		s = to_string(uidMon(dre));
	}

	int getNum() const {
		return num;
	}

	string& getS() {
		return s;
	}

	void attack() const {
		print("{:8} 밀리초 정지\n", num);
		this_thread::sleep_for(std::chrono::milliseconds(num));
	}

	void show() const {
		print("sleep 시간 {:8}, 문자열 - {}\n", num, s);
	}

	void write(ostream& os) {
		os.write((const char*)(this), sizeof(*this));
	}

	friend istream& operator>>(istream& is, Monster& monster)
	{
		is.read(reinterpret_cast<char*>(&monster), sizeof(Monster));
		return is;
	}

};

void erase(vector<Monster>& v, const Monster& mon) {
	v.erase(remove_if(v.begin(), v.end(), [&mon](const Monster& m) {
		return m.getNum() == mon.getNum();
		}), v.end());
}

//---------
int main()
//---------
{
	

	{
		// 실행 확인용 코드
		//Monster mon{ 25 };
		//mon.attack( );
		//mon.show( );
	}



	//--------------------------------------------------------------------------
    // [문제 1] 파일에 있는 Monster 객체를 아래 주석에 있는 코드와 같이 
    // vector<Monster> v에 저장하고 싶다.     
    // 주석을 제거한 후 문제없이 실행되도록 하라.             
    // 모두 몇 객체를 저장했나 화면에 출력하라.                        		(30) 


    ifstream in("몬스터들", ios::binary);
    if (not in) {
		cerr << "파일을 열 수 없습니다.\n";
		return 1;
    }

    vector<Monster> v = { istream_iterator<Monster>{in}, {} };
    cout << "[문제 1] - 저장된 Monster 객체 수: " << v.size() << endl;
	//--------------------------------------------------------------------------
	// 컨테이너에 저장하기 위한 코드와 필요한 관련 코드를 답지에 적는다.
	// 화면에 출력된 객체 수를 답지에 쓴다.
	//--------------------------------------------------------------------------

	// 아래 주석으로 감싼 문장이 문제없이 실행되어야 한다.
	/*vector<Monster> v = { istream_iterator<Monster>{in}, {} };*/





	// ******************************************************
	// * 파일을 읽지 못한 학생은 아래 주석을 풀자.          *
	// * 코드를 실행 한 후 [문제 2]부터 해결해 나가면 된다. *
	// ******************************************************

	// [문제 1]을 해결하지 못한 경우 주석을 제거하자

	/*
	vector<Monster> v;
	v.reserve( 12345 );
	for ( int i = 0; i < 12345; ++i )
		v.emplace_back( uid( dre ) );
	*/


	//--------------------------------------------------------------------------
    // [문제 2] v에 있는 Monster 객체를 num 기준 오름차순으로 정렬하라.
    // 제일 마지막 객체의 show()를 호출하라.								(10)

    sort(v.begin(), v.end(), [](const Monster& a, const Monster& b) {
    return a.getNum() < b.getNum();
    });

    v.back().show();
	//--------------------------------------------------------------------------
	// 문제를 해결하는 코드를 답지에 적어라.
	// 화면에 출력된 결과를 답지에 적어라.
	//--------------------------------------------------------------------------
	


	//--------------------------------------------------------------------------
    // [문제 3] v에 있는 모든 Monster 객체의 멤버 s를 오름차순으로 정렬하라. 
    // 제일 마지막 객체의 show()를 호출하라.								(10)

	for (Monster& monster : v) {
		sort(monster.getS().begin(), monster.getS().end());
	}

    v.back().show();
	//--------------------------------------------------------------------------
	// 문제를 해결하는 코드를 답지에 적어라.
	// 화면에 출력된 결과를 답지에 적어라.
	//--------------------------------------------------------------------------


	



	//--------------------------------------------------------------------------
    // [문제 4] 모든 Monster 객체의 멤버 s에 있는 문자에서 '0'을 제거하라.
    // 제일 마지막 객체의 show()를 호출하라.								(10)

    
	//--------------------------------------------------------------------------
	// 문제를 해결하는 코드를 답지에 적어라.
	// 화면에 출력된 결과를 답지에 적어라.
	//--------------------------------------------------------------------------
	for (Monster &monster : v) {
		monster.getS().erase(remove(monster.getS().begin(), monster.getS().end(), '0'), monster.getS().end());
	}

	v.back().show();



	//--------------------------------------------------------------------------
    // [문제 5] 컨테이너에 있는 Monster 객체 중에서, 멤버 s가 [1, 9] 숫자를 모두
        // [문제 5] 컨테이너에 있는 Monster 객체 중에서, 멤버 s가 [1, 9] 숫자를 모두  
        // 갖고 있는 객체는 몇 개인지 출력하라.  
    //int count{};  
    //for (Monster& m : v) {  
    //   string s = m.getS();  
    //   sort(s.begin(), s.end()); // 문자열 정렬  
    //   s.erase(unique(s.begin(), s.end()), s.end()); // 중복 제거  
    //   if (s.size() == 9) {  
		  // ++count;
    //   }  
    //}

	int count = count_if(v.begin(), v.end(), [](Monster& m) {
	string s = m.getS();
	sort(s.begin(), s.end());
	s.erase(unique(s.begin(), s.end()), s.end());
	return s.size() == 9;
});


    cout << "[문제 5] - [1, 9] 숫자를 모두 갖고 있는 Monster 객체 수: " << count << endl;
	

    // 갖고 있는 객체는 몇 개인지 출력하라.								    (30)
	
	


	//--------------------------------------------------------------------------
	// [문제 3]과 [문제 4]를 제대로 해결한 상태라고 가정한다.
	// 문제를 해결하는 코드를 답지에 적어라.
	// 화면에 출력된 결과를 답지에 적어라.
	// 
	// 예) 다음 5개의 Monster 객체에서 해당 객체는 3번째 객체이다
	// 
	// 	sleep 시간     1228, 문자열 - 1112699
	//	sleep 시간     1221, 문자열 - 1224789
	//	sleep 시간      497, 문자열 - 1234567789	-> 1부터 9까지 모두 있음
	//	sleep 시간      624, 문자열 - 1233455889
	//	sleep 시간      625, 문자열 - 1224457889
	//--------------------------------------------------------------------------
	





	//--------------------------------------------------------------------------
	// [문제 6] 컨테이너 v에서 num이 123 객체를 모두 지우려 한다.
        
	// 주석으로 감싼 문장이 문제없이 실행되도록 코딩하라.
	// num이 123인 객체를 모두 지운 후 남은 객체의 개수를 출력하라.         (20)
	//--------------------------------------------------------------------------
	// 문제를 해결하는 코드를 답지에 적어라.
	// 화면에 출력된 결과를 답지에 적어라.
	// 
	// 예) 다음은 num이 123인 Monster 객체들이다.
	//		sleep 시간      123, 문자열 - 903417324
	//		sleep 시간      123, 문자열 - 58633046
	//		sleep 시간      123, 문자열 - 1916090906	 
	//--------------------------------------------------------------------------

	cout << "[문제 6] - num이 123인 Monter 객체" << endl;

	Monster mon{ 123 };
	mon.show();
	int numc{};
	for (auto& m : v) {
		if (m.getNum() == 123) {
			++numc;
		}
	}
	cout << "num이 123인 Monter 객체수 -" << numc << endl;
    // main 함수 내에서 사용
    erase(v,mon);
	cout << "[문제 6] - num이 123인 Monster 객체를 모두 지운 후 남은 객체 수: " << v.size() << endl;


}
