#include <iostream>
#include <random>
#include <array>
#include <print>
#include <algorithm>
#include <fstream>
#include <numeric>
#include <vector>
#include <list>
#include "String.h"

// ������� ���� ������ ���� ��
void UniquePtr(void);

// ���ݱ��� ���Դ� ����
void Problem1(void);
void Problem2(void);
void Problem3(void);
void Problem4(void);
int Problem5(void);
void Problem6(void);
int Problem7(void);
int Problem8(void);
int Problem9(void);
void Problem10(void);
int Problem11(void);
void Problem12(void);
void Problem13(void);
void Problem14(void);
int Problem15(void);
void Problem16(void);
void Problem17(void);
int Problem18(void);
void Problem19(void);
void Problem20(void);
int Problem21(void);

int main(void)
{
	// ������� ���� ������ ���� ��
	//UniquePtr();

	// ���ݱ��� ���Դ� ����
	//Problem1();
	//Problem2();
	//Problem3();
	//Problem4();
	//Problem5();
	//Problem6();
	//Problem7();
	Problem8();
	//Problem9();
	//Problem10();
	//Problem11();
	//Problem12();
	//Problem13();
	//Problem14();
	//Problem15();
	//Problem16();
	//Problem17();
	//Problem18();
	//Problem19();
	//Problem20();
	//Problem21();
}

// ������� ���� ������ ���� ��
//---------------------------------------------------------------------------------------
class Dog
{
public:
	Dog() { std::cout << "����" << '\n'; }
	~Dog() { std::cout << "�Ҹ�" << '\n'; }
};

void UniquePtr(void)
{
	// ������ ��ü�� ����Ű��, ������ �������� ���� ����Ʈ ������
	// �ڵ����� �޸𸮸� ����
	std::unique_ptr<Dog> p;
	// ��ü�� ������ ����Ʈ �����Ϳ� �Ҵ�
	p = std::make_unique<Dog>();

	// ��ü �� �� ����
	std::unique_ptr<Dog> a = std::make_unique<Dog>();
	// ��ü ���� �� ����
	std::unique_ptr<Dog[]> b = std::make_unique<Dog[]>(10);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����1] Problem1()�� �մ��� ���� �ǵ���� ����ǵ��� change()�� �����ϰ� �����϶�.
class Dog1
{
private:
	int num;
public:
	Dog1(int num) : num(num) {};
	// ���� ������ ��ü�� ��ü�� ���� �� ������ �����ε��� �ʿ���
	friend std::ostream& operator<<(std::ostream& os, Dog1& dog) {
		return os << dog.num;
	}
};

// template�� ����Ͽ� �ڷ����� ��� ���� �۵��ϵ��� ����
template <typename T>
void change(T& a, T& b)
{
	T temp{ a };
	a = b;
	b = temp;
}

void Problem1(void)
{
	Dog1 a{ 1 }, b{ 2 };

	change(a, b);

	std::cout << a << ", " << b << '\n';	// 2, 1
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����2] int 100���� ������ ������ ������.
// [0, 9'9999] ������ ���� ���� int 100���� �Ҵ��϶�.
// ȭ�鿡 ���� ����Ѵ�.
void Problem2(void)
{
	// ���� ������ <random>
	std::default_random_engine dre;
	// ���� ���� ���� ���� <random>
	std::uniform_int_distribution uid(0, 9'9999);

	// <array>
	std::array<int, 100> a;

	for (int& num : a)
		num = uid(dre);

	for (int& num : a)
		// <print>
		std::print("{:8}", num);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����3] a�� �� �� ���� ū ���� ã�� ȭ�鿡 ����϶�.
void Problem3(void)
{
	std::default_random_engine dre;
	std::uniform_int_distribution uid(0, 9'9999);

	std::array<int, 100> a;

	for (int& num : a)
		num = uid(dre);

	for (int& num : a)
		std::print("{:8}", num);
	std::cout << '\n';

	// [���1]
	// int Ÿ���� �ּڰ��� ��ȯ <algorithm>
	int max = std::numeric_limits<int>::min();
	for (int& num : a)
		if (max < num)
			max = num;
	std::cout << "�ִ�: " << max << '\n';

	// [���2]
	// ������ �������� �ִ��� ��ġ�� ��ȯ <algorithm>
	auto pos = std::max_element(a.begin(), a.end());
	std::cout << "�ִ�: " << *pos << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����4] ���� "int����.txt"�� a�� int���� ��� �����϶�.
void Problem4(void)
{
	std::default_random_engine dre;
	std::uniform_int_distribution uid(0, 9'9999);

	std::array<int, 100> a;

	for (int& num : a)
		num = uid(dre);

	// ������ ������� ���� <fstream>
	std::ofstream out{ "int����.txt" };
	for (int& num : a)
		// ���Ͽ� ����
		std::print(out, "{:8}", num);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����5] "int����.txt"���� �� ������ �𸣴� int���� �ִ�.
// ���� ū ���� ã�� ȭ�鿡 ����϶�.
int Problem5(void)
{
	// ������ �б���� ���� <fstream>
	std::ifstream in{ "int����.txt" };
	if (not in)
		return 0;

	// ������ ������ �������� �ִ��� ��ġ�� ��ȯ
	auto pos = std::max_element(std::istream_iterator<int>{ in }, {});
	std::cout << *pos << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����6] int 100���� ������ ������ Ȯ���϶�.
// int���� 1���� �����ϴ� ������ ä����.
// ���Ͽ� "int����.txt"�� ����϶�.
void Problem6(void)
{
	std::array<int, 100> a;

	// ������ ������ŭ �Ҵ�� ������ 1�� ���� ä������ <numueric>
	std::iota(a.begin(), a.end(), 1);

	// [���1]
	std::ofstream out1{ "int����.txt" };
	for (int& num : a)
		// {}�� �ƹ��͵� ���� ���� ���� ����
		print(out1, "{}", num);

	// [���2]
	// binary �������� ����
	std::ofstream out2{ "int����.txt", std::ios::binary };
	// ���Ͽ� ���� �������� ����
	out2.write((char*)a.data(), a.size() * sizeof(int));
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����7] int 100���� "int����"�� �����Ͽ���.
// ������ binary ���� ������
// ���� �޸� ũ�� �״�� 4'000 ����Ʈ�� ����Ͽ���.
// int�� �� ���� ū ���� ã�� ȭ�鿡 ����϶�.
int Problem7(void)
{
	std::ifstream in{ "int����.txt", std::ios::binary };
	if (not in)
		return 0;

	std::array<int, 100> a;

	// ���� �������� ������ �о� a�� ����
	in.read((char*)a.data(), a.size() * sizeof(int));

	auto pos = std::max_element(a.begin(), a.end());
	std::cout << "�ִ�: " << *pos << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����8] "����"���� class Dog8 ��ü 100���� ��ϵǾ� �ִ�.
// ������ binary ��� write �Լ��� sizeof(Dog)*100 ����Ʈ�� ����Ͽ���.
// ������ �о� ���� num���� ū Dog8 ������ ȭ�鿡 ����϶�.
// class Dog8�� ����� ������ ����.
class Dog8
{
private:
	char c;
	int num;
public:
	void show() const {
		std::cout << "Dog, c-" << c << ", num-" << num << '\n';
	}
	// num���� ��� ���� �Լ� �߰�
	int getNum() const {
		return num;
	}
};

int Problem8(void)
{
	std::ifstream in{ "����", std::ios::binary };
	if (not in)
		return 0;

	std::array<Dog8, 100> a;

	in.read((char*)a.data(), a.size() * sizeof(Dog8));

	// lamda�� �̿��� �ִ��� ã�� ���� ����
	auto pos = std::max_element(a.begin(), a.end(), [](const Dog8& a, const Dog8& b) {
		return a.getNum() < b.getNum();
		});

	std::cout << "���� num���� ū Dog8" << '\n';
	pos->show();
	std::cout << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����9] "����"���� class Dog9 ��ü 100���� ��ϵǾ� �ִ�.
// ������ binary ����̰� ��� ��ü�� �� ���� write()�� ����Ͽ���.
// ������ �о� ���� num���� 1'0000�̸��� Dog9 ��ü�� �� ������ ������ ȭ�鿡 ����϶�.
// class Dog9�� ����� ������ ����.
class Dog9
{
private:
	char c;
	int num;
public:
	void show() const {
		std::cout << "Dog, c-" << c << ", num-" << num << '\n';
	}
	int getNum() const {
		return num;
	}
};

int Problem9(void)
{
	std::ifstream in{ "����", std::ios::binary };
	if (not in)
		return 0;

	std::array<Dog9, 100> a;

	in.read((char*)a.data(), a.size() * sizeof(Dog9));

	// ������ �������� ������ ���ǿ� ���� ������ ������ �� <algorithm>
	int num = std::count_if(a.begin(), a.end(), [](const Dog9& dog) {
		if (dog.getNum() < 1'0000)
			return true;
		return false;
		});

	std::cout << "1'0000�̸� Dog9�� ��: " << num << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����10] int num ���� �Է¹޾ƶ�.
// free store���� int�� num�� �Ҵ�޾ƶ�.
// int ���� 1���� �����ϴ� ������ ä����.
// int ���� �հ踦 ����϶�.
// �� ������ ������ �ݺ��϶�.
void Problem10(void)
{
	while (true) {
		int num;

		std::cin >> num;

		int* a = new int[num];

		std::iota(a, a + num, 1);

		// ������ �������� ���ʴ�� ���� <numeric>
		// 0�� �ʱⰪ, OLL�� ��ü ���� => longlong 0
		int sum = std::accumulate(a, a + num, 0);

		std::cout << "�հ�: " << sum << '\n';
	}
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����11] "STL.cpp"�� �о� ��� �ҹ��ڸ� �빮�ڷ� ��ȯ�Ͽ�
// "STL�빮��.txt"�� �����϶�.
int Problem11(void)
{
	std::ifstream in{ "STL.cpp", std::ios::binary };
	if (not in)
		return 0;

	std::ofstream out{ "STL�빮��.txt", std::ios::binary };

	// ������ �������� �о�� ���ڸ� �빮�ڷ� ��ȯ �� ���Ͽ� ��� <algorithm>
	std::transform(std::istream_iterator<char>{in}, {},
		std::ostreambuf_iterator<char>{out}, [](char c) {
			return toupper(c);
		});
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����12] int 100���� ������ ������ Ȯ���϶�.
// int 100���� ���� [1, 10000] ���������� �����϶�.
// int�� 100���� std::sort�� ����Ͽ� ������������ �����϶�.
// ���İ���� �� �ٿ� 10���� ȭ�鿡 ����϶�.
void Problem12(void)
{
	std::default_random_engine dre;
	std::uniform_int_distribution uid(1, 10000);

	std::array<int, 100> a;

	for (int& num : a)
		num = uid(dre);

	// ������ �������� ���� <algorithm>
	// default ��������
	std::sort(a.begin(), a.end());

	for (int& num : a)
		std::print("{:8}", num);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����13] int 100���� ������ ������ Ȯ���϶�.
// int 100���� ���� [1, 10000] ���������� �����϶�.
// int�� 100���� std::sort�� ����Ͽ� ������������ �����϶�.
// ���İ���� �� �ٿ� 10���� ȭ�鿡 ����϶�.
void Problem13(void)
{
	std::default_random_engine dre;
	std::uniform_int_distribution uid(1, 10000);

	std::array<int, 100> a;

	for (int& num : a)
		num = uid(dre);

	// lamda�� �̿��� ���� ���� ����
	std::sort(a.begin(), a.end(), [](int a, int b) {
		return a > b;
		});

	for (int& num : a)
		std::print("{:8}", num);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����14] a�� �� String�� �����ϴ� ���ڸ� ������������ �����϶�.
void Problem14(void)
{
	std::array<String, 5> a{
		"12341232312312312312312314123999999999",
		"23313143423123213243245324567463214567463213`3243565333",
		"213333333333333424121",
		"777777713231232312323123",
		"555551323213123213"
	};

	for (String& s : a)
		std::sort(s.getData(), s.getData() + s.getLen());

	for (String& s : a)
		std::cout << s << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����15] "STL.cpp"�� �ܾ a�� �����϶�.
// ���̿����������� a�� �����϶�.
// ȭ�鿡 ����϶�.
int Problem15(void)
{
	std::ifstream in{ "STL.cpp" };
	if (not in)
		return 0;

	std::array<String, 50> a;

	for (int i = 0; i < 50; ++i)
		in >> a[i];

	std::sort(a.begin(), a.end(), [](const String& a, const String& b) {
		return a.getLen() < b.getLen();
		});

	for (String& s : a)
		std::cout << s << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����16] v���� 3�� �����϶�.
void Problem16(void)
{
	std::vector<int> v{ 1, 2, 3, 4, 5 };

	// vector���� ������ ���� ����
	//erase(v, 3);

	for (int& num : v)
		std::cout << num << ' ';
	std::cout << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����17] v���� Ȧ���� �����϶�
void Problem17(void)
{
	std::vector<int> v{ 1, 2, 3, 4, 5 };

	// vector���� ������ ���ǿ� ������ ���� ���� <algorithm>
	std::erase_if(v, [](int num) {
		return num & 1;
		});

	for (int& num : v)
		std::cout << num << ' ';
	std::cout << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����18] "STL.cpp"�� �ִ� �ҹ����� ���� Ƚ���� ������ ���� ����϶�.
// a - 10
// b - 3
// c - 0
// ����
// z - 2
int Problem18(void)
{
	std::ifstream in{ "STL.cpp" };
	if (not in)
		return 0;

	std::array<int, 26> alphaNum{};

	char c;
	while (in >> c)
		if (islower(c))
			alphaNum[c - 'a']++;

	for (int i = 0; i < 26; ++i)
		std::cout << static_cast <char>('a' + i) << " - " << alphaNum[i] << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����19] Ű���忡�� �Է��� �ܾ �������� ���� �� ����϶�.
void Problem19(void)
{
	std::vector<String> v{ std::istream_iterator<String>{std::cin}, {} };

	std::sort(v.begin(), v.end(), [](const String& a, const String& b) {
		return a.getLen() < b.getLen();
		});

	for (String& s : v)
		std::cout << s << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����20] v�� "333"�� �����϶�.
void Problem20(void)
{
	std::vector<String> v;
	// vector�� ������ �ø���
	v.reserve(5);
	v = { "1", "22", "4444", "55555" };

	// ������ ��ġ ����
	auto p = v.begin();
	++p;
	++p;

	// 333 ����
	v.insert(p, "333");

	for (String& s : v)
		std::cout << s << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [����21] ���� "String.cpp"�� �о� cont�� �����϶�.
// cont�� ���̿����������� �����϶�.
int Problem21(void)
{
	// <list>
	std::list<String> cont;

	std::ifstream in{ "String.cpp", std::ios::binary };
	if (not in)
		return 0;

	String s;
	while (in >> s)
		// list �ڿ� ��� �߰�
		cont.emplace_back(s);

	cont.sort([](const String& a, const String& b) {
		return a.getLen() < b.getLen();
		});

	for (String& s : cont)
		std::cout << s << '\n';
}
//---------------------------------------------------------------------------------------