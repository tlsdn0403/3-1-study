//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 6�� �����      (1�� 2���� ����) 
//-------------------------------------------------------------------------------------------
//������ȯ�� Ȯ��/ ���б� ���Ǹ� ���� �� save ���� �����
// ���� -save.cpp�� �и��ϼ���
//-------------------------------------------------------------------------------------------
// VS ���� - 17.13 �̻�
// Release ����� x64  / C++ ��� ǥ�� - /std:: c++ latest, sdl �˻� - �ƴϿ�
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<fstream>
#include<filesystem>
#include<vector>
#include<algorithm>
#include<chrono>

//[����] �������� ������ ����ǵ��� �ض�  
void save(const std::string& fileName); //������ �̸��� �ȹٲ� �Ű� ������ ũ�Ⱑ �ִٺ��� �����ؼ� �������� ���� ���� const string&�� ����
//----------
int main()
//----------
{
	std::cout << "2025 STL" << std::endl; //end of line �� �� ���̴�

	save("����.cpp");
}
//--------------------------------
void save(const std::string& fileName)
//--------------------------------
{
	//fileName�� �б���� ����
	std::ifstream in{ fileName.data() }; //RAII
	// ! ��� not ��� ����
	if (not in) {
		std::cerr << "������ �� ���� �����ϴ�" << std::endl;
		exit(20250306);
	}

	//���� ���� ������ ������ ����
	std::string nameToSave{ "2025 1�б� STL ���� ���� ȭ56 ��78 ��������.txt" };
	std::ofstream out{ nameToSave, std::ios::app }; //ios::app �� �ؾ� �̻ڰ� ���ٿ���

	//�����ߴٰ� ȭ�鿡 ����Ѵ�.`
	auto size = std::filesystem::file_size(fileName);
	std::cout << nameToSave << "���Ͽ� " << fileName << "�� ���ٿ����ϴ� " << size << "����Ʈ" << std::endl;

	// ������ �ð��� ���Ͽ� �������
	auto now = std::chrono::system_clock::now(); //time_point�� ��´� , epoch�� ���� �����
	using namespace std::chrono_literals;
	auto utc = std::chrono::system_clock::to_time_t(now); //UTC �ð����� �ٲ۴�
	auto lt = std::localtime(&utc); //�ʹ� ������ �Լ��� &�� �Ѱ�����Ѵ� �����޷½ð����� ����
	auto old = out.imbue(std::locale("ko_KR"));

	out << '\n' << '\n';
	out << "==============================================" << '\n';
	out << "������ �ð� :" << std::put_time(lt, "%c %A ") << '\n';
	out << "==============================================" << '\n';
	out << "\n";

	out.imbue(old); //���� loacle�� ����

	//���� ���Ͽ� �ִ� ��� ������ �о� �� ���Ͽ� ���ٿ�����
	std::copy(std::istreambuf_iterator<char>{ in }, {}, std::ostreambuf_iterator<char>{ out });
}

