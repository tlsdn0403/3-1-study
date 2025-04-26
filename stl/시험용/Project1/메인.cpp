//-----------------------------------------------------------------------------
// STL 중간시험
//-----------------------------------------------------------------------------
// 환경 - VS 17.12.4 이상, C++언어 표준 - /std:c++latest, 미리보기Release x64
// 헤더 파일을 추가할 필요는 없다.
// 각 문제에서 요구하는 답을 구분하여 적어라.	
//-----------------------------------------------------------------------------

#include <iostream>
#include <memory>
#include <numeric>
#include <fstream>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

//-----------------------------------------------------------------------------
// Test는 num개의 int를 free-store에 확보한 contiguous 메모리에 저장한다.
//-----------------------------------------------------------------------------

class Test {
public:
	Test( ) = default;

	// 저장된 int의 값을 앞에서 부터 7개만 출력
	void show( ) const {						
		cout << num << " - ";
		for ( int i = 0; i < 7; ++i )
			cout << p[ i ] << " ";
		cout << endl;
	}
	int returnNum() {
		return num;
	}


private:
	size_t num {};				// free-store에 저장한 int의 개수	
	unique_ptr<int[]> p {};		// num개의 int가 저장되어 있는 contiguous 메모리를 관리하는 포인터

public:
	friend istream& operator>>(istream& is, Test& t) {
		is.read((char*)&t.num, sizeof(int));
		t.p = make_unique<int[]>(t.num);
		is.read((char*)t.p.get(), sizeof(int) * t.num);
		return is;
	}

	friend ostream& operator<<( ostream& os, const Test& t ) {
		os.write( (char*)&t.num, sizeof(int) );
		os.write( (char*)t.p.get(), sizeof( int ) * t.num );
		return os;
	}
	bool operator<(const Test& other) const {
		return num < other.num;
	}
	// 평균값 계산 함수
	double average() const {
		if (num == 0) return 0.0;
		return accumulate(p.get(), p.get() + num, 0.0) / num;
	}
};

//-----------------------------------------------------------------------------
// main에 있는 문제를 순서대로 해결하며 요구하는 답을 답지에 적어 제출한다.
//-----------------------------------------------------------------------------

//---------
int main( )
//---------
{
	//-----------------------------------------------------------------------------------
	// [문제 1] 다음 코드를 실행시키면 폴더에 "숫자들" 파일이 생성될 것이다. 
	// 파일의 크기를 살펴보고 왜 그런지 이유를 정확하게 설명하라.		(20)
	//-----------------------------------------------------------------------------------
	{
		array<int, 100> numbers;
		iota( numbers.begin( ), numbers.end( ), 1 );

		// array numbers 가 크기가 100인 배열이고 4byte짜리 int자료형을 담는다

		/*
		for ( int num : numbers )
			cout << num << " ";
		cout << endl;
		*/

		ofstream out { "숫자들" };
		out.write( (char*)numbers.data( ), sizeof( int ) * numbers.size( ) );
	}


	ifstream in { "시험.dat", ios::binary };
	if ( not in ) {
		cout << "파일을 열 수 없습니다" << endl;
		return 20250424;
	}


	//-------------------------------------------------------------------------
        // Test 클래스에 추가된 멤버 함수 및 관련 함수
       


         
       
	// [문제 2] 다운받은 "시험.dat"에는 Test 객체 2'000개가 저장되어 있다.
        // 파일이 제대로 열리지 않는 문제를 해결하기 위해 파일 경로와 열기 모드를 확인하고, 예외 처리를 추가합니다.
	// 파일은 binary mode로 열었다.
	// Test 객체는 << 연산자를 사용하여 기록하였다.
	// "시험.dat"에 저장된 Test 객체를 읽어 컨테이너에 저장하라.
	// 마지막 객체의 show()를 호출하라.
	//-------------------------------------------------------------------------
	// 답지에는 다음 내용을 적으면 된다.
	// - 읽기 위해 추가한 Test의 멤버함수와 관련 함수	 				(20)
	// - 코딩에 사용한 컨테이너를 선택한 이유							(5)
	// - 실제 읽어서 저장하는 코드										(10)
	// - show() 호출로 화면에 출력된 값 중에서 num의 값만 적어라.		(5)
	//-------------------------------------------------------------------------


    array<Test, 2'000> tests; // Test 객체를 저장할 컨테이너
    for (size_t i = 0; i < tests.size(); ++i) {
					in >> tests[i]; 
    }
	tests.back().show();
	tests[1999].show();
   




	//-------------------------------------------------------------------------
	// [문제 3] 컨테이너에 저장된 Test 객체를 오름차순으로 정렬한다.
	// 앞에서 만든 컨테이너의 이름을 x라고 하자.
	//	
	//		sort( x.begin(), x.end() );
	// 
	// 이렇게 sort를 호출하여 x에 저장된 Test 객체가 num 기준 오름차순으로
	// 정렬되게 하라.
	// 정렬 후 제일 마지막 객체의 show()를 호출하라.
	//-------------------------------------------------------------------------
	// 답지에는 다음 내용을 적으면 된다.
	// - 정렬하기 위해 추가한 관련 Test의 멤버들	 					(10)
	// - 마지막 객체를 화면에 출력하는 코드와 출력된 num 값				(10)
	//-------------------------------------------------------------------------
// Test 클래스에 num 값을 비교하는 연산자 추가를 람다로 처리
	sort(tests.begin(), tests.end());
	tests.back().show();




	//-------------------------------------------------------------------------
	// [문제 4] Test 객체가 free-store에 저장한 int 값의 평균값을 계산하는
	// 멤버 함수 average()를 작성하라.
    // 컨테이너에 저장된 모든 Test 객체가 저장한 int의 평균값을 화면에 출력하라.
 
	//-------------------------------------------------------------------------
	// 답지에는 다음 내용을 적으면 된다.
	// average의 정의													(10)
	// 모든 객체의 평균값을 화면에 출력하는 코드와 
	// 화면에 출력된 마지막 객체의 평균값								(10)
	//-------------------------------------------------------------------------
	
	double totalAverage = 0.0;
	for (const Test& t : tests) {
		totalAverage += t.average();
	}
	cout << "모든 Test 객체의 평균값: " << totalAverage /(double) tests.size() << endl;



	//-------------------------------------------------------------------------
	// [문제 5] 여기에서는 int 값을 메모리 크기 그대로 파일에 기록하였다.
	// 만일 int 값을 글자로 기록한다면 한 개의 int를 기록하기 위해 필요한 
	// 메모리는 평균 몇 바이트인지 알고 싶다.
	// 
	// 예시)  int값         글자로 저장할때 바이트       메모리크기로 저장 
	//		   -12345				6                           4
	//         -100					4                           4
	//          0					1							4
	//		    123					3							4
	//			123456				6							4
	//			2140000000			10							4
	// 
	// 우리 컴파일 환경에서 int가 표현할 수 있는 모든 값을 글자로 저장한다면
	// 평균 몇 바이트가 필요한 지 소수점 2자리 까지 출력하라.			   (30)
	//-------------------------------------------------------------------------
	// 문제를 해결하는 코드를 답지에 적는다
	// 출력된 평균값도 답지에 적는다
	// (도움) 전역함수 to_string()은 int를 string으로 변환한다.
	//-------------------------------------------------------------------------




	// int의 최소값과 최대값
	int minValue = numeric_limits<int>::min();
	int maxValue = numeric_limits<int>::max();

	// int 범위의 모든 값을 순회하며 글자로 변환한 길이를 누적
	long long totalLength = 0;
	long long count = 0;

	for (int i = minValue; i < maxValue; ++i) {
		totalLength += to_string(i).length();
		++count;

		// maxValue를 포함하기 위해 마지막 루프 처리
		if (i == maxValue - 1) {
			totalLength += to_string(maxValue).length();
			++count;
			break;
		}
	}

	// 평균 계산
	double averageLength = static_cast<double>(totalLength) / count;

	// 소수점 2자리까지 출력
	cout << "평균 글자 수: "<< averageLength << endl;

	return 0;


	
}
