//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 27일 목요일      (4주 2일차 강의) 
//-------------------------------------------------------------------------------------------
// 동적할당과 SMART POINTER - RAII 클래스로 자원을 관리하는 것
//  - C++ STACK-UNWINDING을 보장한다
//-------------------------------------------------------------------------------------------
// 4월 24일 중간고사.
//-------------------------------------------------------------------------------------------
#INCLUDE<IOSTREAM>
#INCLUDE<MEMORY>
#INCLUDE<STRING>
#INCLUDE<FSTREAM>
#INCLUDE<ALGORITHM>
#INCLUDE"SAVE.H"
USING NAMESPACE STD;


//----------
INT MAIN()
//----------
{
	IFSTREAM IN{ "메인.CPP" };
	IF (NOT IN) {
		COUT << "파일을 열 수 없어요" << ENDL;
		RETURN 123123;
	}
	OFSTREAM OUT{ "메인 대문자.CPP" };
	TRANSFORM(ISTREAMBUF_ITERATOR<CHAR>{IN}, {},
		OSTREAMBUF_ITERATOR<CHAR>{OUT}, [](CHAR C) {RETURN TOUPPER(C); });
	SAVE("메인.CPP");
}