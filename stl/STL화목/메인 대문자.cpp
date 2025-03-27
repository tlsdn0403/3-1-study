//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 27�� �����      (4�� 2���� ����) 
//-------------------------------------------------------------------------------------------
// �����Ҵ�� SMART POINTER - RAII Ŭ������ �ڿ��� �����ϴ� ��
//  - C++ STACK-UNWINDING�� �����Ѵ�
//-------------------------------------------------------------------------------------------
// 4�� 24�� �߰����.
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
	IFSTREAM IN{ "����.CPP" };
	IF (NOT IN) {
		COUT << "������ �� �� �����" << ENDL;
		RETURN 123123;
	}
	OFSTREAM OUT{ "���� �빮��.CPP" };
	TRANSFORM(ISTREAMBUF_ITERATOR<CHAR>{IN}, {},
		OSTREAMBUF_ITERATOR<CHAR>{OUT}, [](CHAR C) {RETURN TOUPPER(C); });
	SAVE("����.CPP");
}