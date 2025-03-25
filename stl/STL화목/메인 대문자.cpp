//-------------------------------------------------------------------------------------------
// 2025 STL 화56 목78  3월 20일 목요일      (3주 2일차 강의) 
//-------------------------------------------------------------------------------------------
// 동적할당과 SMART POINTER - RAII 클래스로 자원을 관리하는 것
//  - C++ STACK-UNWINDING을 보장한다
//-------------------------------------------------------------------------------------------
// 많은 수의 자료 - FILE
//-------------------------------------------------------------------------------------------
#INCLUDE<IOSTREAM>
#INCLUDE<FSTREAM>
#INCLUDE<ALGORITHM>
#INCLUDE"SAVE.H"
USING NAMESPACE STD;

//[문제] "메인.CPP"의 내용 중에 소문자를 모두 대문자로 바꿔 "메인 대문자.CPP"에 저장하라

INT MAIN()  
//----------  
{  
   IFSTREAM IN{ "메인.CPP" };  
   IF (!IN)  
       RETURN 12345;  
   OFSTREAM OUT{ "메인 대문자.CPP" };  
   
   TRANSFORM(ISTREAMBUF_ITERATOR<CHAR>{IN}, {},
       OSTREAMBUF_ITERATOR<CHAR>{OUT}, [](CHAR C) {RETURN TOUPPER(C); });
   
   RETURN 0;  
}