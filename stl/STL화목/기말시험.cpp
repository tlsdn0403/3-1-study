//-----------------------------------------------------------------------------
// 2024 STL 기말시험
// 
// Visual Studio 버전 17.9.0 이상 
// Release / x64
// 프로젝트 속성 - C++ 언어 표준 - 최신 C++ 초안의 기능(/std:c++latest)
//-----------------------------------------------------------------------------
// 답지 작성 방법
// - 각 문제를 해결하는 데 필요한 코드만 적는다.
// - 화면에 출력을 요구하는 문제는 출력된 내용을 답지에 적는다.
// - 헤더 파일을 적을 필요는 없다.
//-----------------------------------------------------------------------------

#include <algorithm>
#include <array>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <string>
#include <vector>
#include <numeric>
#include <set>
#include <cctype>
using namespace std;


//-------------------------------------------------------------------------------------------
// 몇 개인지 모르는 단어를 "기말시험.txt" 파일에 저장하였다.
// 
// [이 시험에서 단어의 정의] 
// 단어는 영문자와 숫자로만 이루어진 문자집합이다.
// 
// (다음 3줄은 이 문제에서 사용한 단어의 예시이다)
//	Z2ioEzzzszcuhAc6wnujf6kt
//	mkehuiWdzvdtmrdfbaklmuxuS
//	uowvavVyklpeTFVzIha2xwYuzbupt6Rkofnkj
//
// 파일에는 단어를 공백으로 분리하여 기록하였다.
//-------------------------------------------------------------------------------------------



//---------
int main( )
//---------
{

	ifstream in{ "기말시험.txt" };

	if (not in) {
		cout << "기말시험.txt - 파일을 열 수 없습니다" << endl;
		return -1;
	}


	//---------------------------------------------------------------------------------
	// [문제 1] 파일 "기말시험.txt"에 저장된 모든 단어를 읽어 STL Container에 저장하라.	
	// 모두 몇 개의 단어를 읽었는 지 화면에 출력하고 답지에도 적어라.              (10)
	//---------------------------------------------------------------------------------
	// "기말시험.txt"에 있는 단어를 읽어 컨테이너에 저장하기 위한 코드를 답지에 적는다.
	// 사용한 컨테이너 / 읽고 저장하는 코드 / 단어 수 출력 코드  / 출력된 값
	//
	// (주의) 파일을 모두 읽기 전에는 몇 개의 단어가 있는 지 알 수 없다.
	//---------------------------------------------------------------------------------

	multiset<string> s{ istream_iterator<string>{in}, {} };

	/*for (const string& s : s)
		std::cout << s << endl;*/

	cout << "단어 수 - " << s.size() << endl;


	// [참고] 읽은 단어를 앞에서 부터 10개만 출력한 결과는 다음과 같다
	/*
	Z2ioEzzzszcuhAc6wnujf6kt
	mkehuiWdzvdtmrdfbaklmuxuS
	uowvavVyklpeTFVzIha2xwYuzbupt6Rkofnkj
	pj9EkkskylwqdmInszsxn
	molwpMzazjrjwBrt1zCHUcqaRnlfdjtbGnvzv30go
	x3aEwfhmfM9qtlobikxvgdmjs
	vikivrj4hxmtckwj
	xodfyz2akumoaxfxldgumc6qp7jrS
	lBuevIRkuczEtg2cihzfpfek
	kehqduwy0ptIdhWfNaahc3js
	*/


	//-----------------------------------------------------------------------------
	// [문제 2] 컨테이너에 저장한 단어의 평균 길이를 출력하고 답지에도 적어라. (20)
	//-----------------------------------------------------------------------------
	// 컨테이너에 있는 모든 단어의 길이를 합한 후 단어개수로 나눈 값을 구한다.
	// 평균 길이를 구하는 코드 / 값을 출력하는 코드 / 출력된 값
	//
	// (주의) 알고리즘을 사용하지 않고 합계를 계산 한 경우 0점
	//-----------------------------------------------------------------------------

	int total = accumulate(s.begin(), s.end(), 0, [](int sum, const string& s) {
		return sum + s.length();
		});

	cout << "평균 길이 - " << total / s.size() << endl;



	//---------------------------------------------------------------------------
	// [문제 3] 컨테이너에 저장된 단어 중에서 숫자가 한 개 이상 들어간 단어는 
	// 모두 몇 개인지 세고, 숫자는 '*'로 변환하라.							 (30)
	//---------------------------------------------------------------------------
	// 개수를 세는 도중에 숫자를 '*'로 변환할 수 있다.
	// 개수를 세고 변환하는 코드 / 개수를 출력하는 코드 / 출력된 개수
	// 
	// (주의) 알고리즘을 사용하지 않고 loop로 해결한 경우 0점
	//---------------------------------------------------------------------------

	int cnt{};

	for (const string& s : s) {
		auto p = find_if(s.begin(), s.end(), [](char c) {
			if (isdigit(c)) {
				c = '*';
				return true;
			}
			return false;
			});

		if (p != s.end()) 
			cnt++;
	}
	
	cout << "숫자가 한 개 이상 들어간 단어 수 - " << cnt << endl;


	// [참고] [문제 3]의 결과를 앞에서부터 10개만 출력한 결과
	/*
	Z*ioEzzzszcuhAc*wnujf*kt
	mkehuiWdzvdtmrdfbaklmuxuS
	uowvavVyklpeTFVzIha*xwYuzbupt*Rkofnkj
	pj*EkkskylwqdmInszsxn
	molwpMzazjrjwBrt*zCHUcqaRnlfdjtbGnvzv**go
	x*aEwfhmfM*qtlobikxvgdmjs
	vikivrj*hxmtckwj
	xodfyz*akumoaxfxldgumc*qp*jrS
	lBuevIRkuczEtg*cihzfpfek
	kehqduwy*ptIdhWfNaahc*js
	*/





	//---------------------
	// [문제 4]를 위한 준비
	//---------------------
	ifstream in2{ "기말시험2.txt" };

	if (not in2) {
		cout << "기말시험2.txt - 파일을 열 수 없습니다" << endl;
		return -1;
	}

	//---------------------------------------------------------------------------
	// [문제 4] "기말시험2.txt"에도 단어들이 저장되어 있다.
	// "기말시험.txt" 파일과 "기말시험2.txt" 파일에 저장되어 있는 단어 중에서
	// 동일한 단어를 골라내어 화면에 출력하라.								 (30)
	//---------------------------------------------------------------------------
	// "기말시험2.txt"를 컨테이너에 저장하는 코드 / 
	// 동일한 단어를 골라 화면 출력하기  위한 코드 / 화면에 출력된 동일한 단어
	//
	// (참고) 동일함은 operator==으로 판단함을 의미한다.
	// (주의) 알고리즘을 사용하지 않고 loop로 해결한 경우 0점
	//---------------------------------------------------------------------------

	multiset<string> s2{ istream_iterator<string>{in2}, {} };
	set<string> same;

	for (const string& str1 : s) {
		for (const string& str2 : s2) {
			bool e = std::equal(str1.begin(), str1.end(), str2.begin());
			if (e)
				same.insert(str2);
		}
	}

	for (const string& s : same)
		cout << s << endl;




	//---------------------------------------------------------------------------------
	// [문제 5] [문제 1]에서 사용한 컨테이너의 이름을 con 이라고 하자.
	// 주석으로 표시한 것과 같이 코딩하였는데,
	// con 에 저장한 단어의 문자 중에서 '*'이 '-' 로 바뀌었다.
	// 필요한 코딩을 추가하라.                                                     (30)
	//---------------------------------------------------------------------------------
	// 문제를 해결하기 위해 추가한 코드를 답지에 적는다.
	// 	
	// (주의) std::find_if로 이렇게 해선 안되지만 당신은 이렇게 할 수 있는 실력이 있다.
	//---------------------------------------------------------------------------------

	// 다음 주석문을 제거하고 실행할 것
	// std::find_if( con.begin( ), con.end( ),  STAR );





	// [참고] [문제 5]의 결과를 앞에서부터 10개만 출력한 결과
	/*
	----dnpeq-aourspgnhjxpq
	---TudzglkcTzclHwmbjsdscBlic
	---VduvqsjstxozulXpeT-sux
	---efkbTqdii-m
	---efqvacakrmwqeqzTNvh
	---eyadmwvytzwiclnTxf
	---fvvbbgxPaqmxuejneqavfsk
	---ghyjhxsa-xilnrqrdngbnZqh-ay
	---gpvqjrbwjekkvu-lc
	---if-tqetxkbddrdbnqgsotms-oaCtbt	
	*/
}