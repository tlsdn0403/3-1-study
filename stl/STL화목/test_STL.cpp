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

// 배웠으나 관련 문제가 없는 것
void UniquePtr(void);

// 지금까지 나왔던 문제
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
	// 배웠으나 관련 문제가 없는 것
	//UniquePtr();

	// 지금까지 나왔던 문제
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

// 배웠으나 관련 문제가 없는 것
//---------------------------------------------------------------------------------------
class Dog
{
public:
	Dog() { std::cout << "생성" << '\n'; }
	~Dog() { std::cout << "소멸" << '\n'; }
};

void UniquePtr(void)
{
	// 생성된 객체를 가리키며, 유일한 소유권을 갖는 스마트 포인터
	// 자동으로 메모리를 해제
	std::unique_ptr<Dog> p;
	// 객체를 생성해 스마트 포인터에 할당
	p = std::make_unique<Dog>();

	// 객체 한 개 생성
	std::unique_ptr<Dog> a = std::make_unique<Dog>();
	// 객체 여러 개 생성
	std::unique_ptr<Dog[]> b = std::make_unique<Dog[]>(10);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제1] Problem1()을 손대지 말고 의도대로 실행되도록 change()를 선언하고 정의하라.
class Dog1
{
private:
	int num;
public:
	Dog1(int num) : num(num) {};
	// 직접 정의한 객체는 객체별 연산 시 연산자 오버로딩이 필요함
	friend std::ostream& operator<<(std::ostream& os, Dog1& dog) {
		return os << dog.num;
	}
};

// template을 사용하여 자료형과 상관 없이 작동하도록 만듦
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
// [문제2] int 100개를 저장할 공간을 만들어라.
// [0, 9'9999] 범위의 값을 갖는 int 100개에 할당하라.
// 화면에 값을 출력한다.
void Problem2(void)
{
	// 난수 생성기 <random>
	std::default_random_engine dre;
	// 난수 생성 범위 제한 <random>
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
// [문제3] a의 값 중 가장 큰 값을 찾아 화면에 출력하라.
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

	// [방법1]
	// int 타입의 최솟값을 반환 <algorithm>
	int max = std::numeric_limits<int>::min();
	for (int& num : a)
		if (max < num)
			max = num;
	std::cout << "최댓값: " << max << '\n';

	// [방법2]
	// 지정한 범위에서 최댓값의 위치를 반환 <algorithm>
	auto pos = std::max_element(a.begin(), a.end());
	std::cout << "최댓값: " << *pos << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제4] 파일 "int값들.txt"에 a의 int값을 모두 저장하라.
void Problem4(void)
{
	std::default_random_engine dre;
	std::uniform_int_distribution uid(0, 9'9999);

	std::array<int, 100> a;

	for (int& num : a)
		num = uid(dre);

	// 파일을 쓰기모드로 열기 <fstream>
	std::ofstream out{ "int값들.txt" };
	for (int& num : a)
		// 파일에 쓰기
		std::print(out, "{:8}", num);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제5] "int값들.txt"에는 몇 개인지 모르는 int값이 있다.
// 제일 큰 값을 찾아 화면에 출력하라.
int Problem5(void)
{
	// 파일을 읽기모드로 열기 <fstream>
	std::ifstream in{ "int값들.txt" };
	if (not in)
		return 0;

	// 파일의 지정된 범위에서 최댓값의 위치를 반환
	auto pos = std::max_element(std::istream_iterator<int>{ in }, {});
	std::cout << *pos << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제6] int 100개를 저장할 공간을 확보하라.
// int값을 1부터 시작하는 정수로 채워라.
// 파일에 "int값을.txt"에 기록하라.
void Problem6(void)
{
	std::array<int, 100> a;

	// 지정된 범위만큼 할당된 값부터 1씩 더해 채워넣음 <numueric>
	std::iota(a.begin(), a.end(), 1);

	// [방법1]
	std::ofstream out1{ "int값들.txt" };
	for (int& num : a)
		// {}에 아무것도 넣지 않을 수도 있음
		print(out1, "{}", num);

	// [방법2]
	// binary 형식으로 열기
	std::ofstream out2{ "int값들.txt", std::ios::binary };
	// 파일에 이진 형식으로 쓰기
	out2.write((char*)a.data(), a.size() * sizeof(int));
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제7] int 100개를 "int값들"에 저장하였다.
// 파일은 binary 모드로 열었고
// 값은 메모리 크기 그대로 4'000 바이트를 기록하였다.
// int값 중 제일 큰 값을 찾아 화면에 출력하라.
int Problem7(void)
{
	std::ifstream in{ "int값들.txt", std::ios::binary };
	if (not in)
		return 0;

	std::array<int, 100> a;

	// 이진 형식으로 파일을 읽어 a에 저장
	in.read((char*)a.data(), a.size() * sizeof(int));

	auto pos = std::max_element(a.begin(), a.end());
	std::cout << "최댓값: " << *pos << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제8] "개들"에는 class Dog8 객체 100개가 기록되어 있다.
// 파일은 binary 모드 write 함수로 sizeof(Dog)*100 바이트를 기록하였다.
// 파일을 읽어 가장 num값이 큰 Dog8 정보를 화면에 출력하라.
// class Dog8의 멤버는 다음과 같다.
class Dog8
{
private:
	char c;
	int num;
public:
	void show() const {
		std::cout << "Dog, c-" << c << ", num-" << num << '\n';
	}
	// num값을 얻기 위한 함수 추가
	int getNum() const {
		return num;
	}
};

int Problem8(void)
{
	std::ifstream in{ "개들", std::ios::binary };
	if (not in)
		return 0;

	std::array<Dog8, 100> a;

	in.read((char*)a.data(), a.size() * sizeof(Dog8));

	// lamda를 이용해 최댓값을 찾는 조건 지정
	auto pos = std::max_element(a.begin(), a.end(), [](const Dog8& a, const Dog8& b) {
		return a.getNum() < b.getNum();
		});

	std::cout << "가장 num값이 큰 Dog8" << '\n';
	pos->show();
	std::cout << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제9] "개들"에는 class Dog9 객체 100개가 기록되어 있다.
// 파일은 binary 모드이고 모든 객체를 한 번의 write()로 기록하였다.
// 파일을 읽어 가장 num값이 1'0000미만인 Dog9 객체는 몇 개인지 정보를 화면에 출력하라.
// class Dog9의 멤버는 다음과 같다.
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
	std::ifstream in{ "개들", std::ios::binary };
	if (not in)
		return 0;

	std::array<Dog9, 100> a;

	in.read((char*)a.data(), a.size() * sizeof(Dog9));

	// 지정한 범위에서 지정한 조건에 맞을 때마다 개수를 셈 <algorithm>
	int num = std::count_if(a.begin(), a.end(), [](const Dog9& dog) {
		if (dog.getNum() < 1'0000)
			return true;
		return false;
		});

	std::cout << "1'0000미만 Dog9의 수: " << num << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제10] int num 값을 입력받아라.
// free store에서 int를 num개 할당받아라.
// int 값을 1부터 시작하는 정수로 채워라.
// int 값의 합계를 출력하라.
// 이 과정을 영원히 반복하라.
void Problem10(void)
{
	while (true) {
		int num;

		std::cin >> num;

		int* a = new int[num];

		std::iota(a, a + num, 1);

		// 지정된 범위에서 차례대로 더함 <numeric>
		// 0은 초기값, OLL로 대체 가능 => longlong 0
		int sum = std::accumulate(a, a + num, 0);

		std::cout << "합계: " << sum << '\n';
	}
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제11] "STL.cpp"를 읽어 모든 소문자를 대문자로 변환하여
// "STL대문자.txt"에 저장하라.
int Problem11(void)
{
	std::ifstream in{ "STL.cpp", std::ios::binary };
	if (not in)
		return 0;

	std::ofstream out{ "STL대문자.txt", std::ios::binary };

	// 지정된 범위에서 읽어온 문자를 대문자로 변환 후 파일에 출력 <algorithm>
	std::transform(std::istream_iterator<char>{in}, {},
		std::ostreambuf_iterator<char>{out}, [](char c) {
			return toupper(c);
		});
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제12] int 100개를 저장할 공간을 확보하라.
// int 100개의 값을 [1, 10000] 랜덤값으로 설정하라.
// int값 100개를 std::sort를 사용하여 오름차순으로 정렬하라.
// 정렬결과를 한 줄에 10개씩 화면에 출력하라.
void Problem12(void)
{
	std::default_random_engine dre;
	std::uniform_int_distribution uid(1, 10000);

	std::array<int, 100> a;

	for (int& num : a)
		num = uid(dre);

	// 지정된 범위에서 정렬 <algorithm>
	// default 오름차순
	std::sort(a.begin(), a.end());

	for (int& num : a)
		std::print("{:8}", num);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제13] int 100개를 저장할 공간을 확보하라.
// int 100개의 값을 [1, 10000] 랜덤값으로 설정하라.
// int값 100개를 std::sort를 사용하여 내림차순으로 정렬하라.
// 정렬결과를 한 줄에 10개씩 화면에 출력하라.
void Problem13(void)
{
	std::default_random_engine dre;
	std::uniform_int_distribution uid(1, 10000);

	std::array<int, 100> a;

	for (int& num : a)
		num = uid(dre);

	// lamda를 이용해 정렬 조건 설정
	std::sort(a.begin(), a.end(), [](int a, int b) {
		return a > b;
		});

	for (int& num : a)
		std::print("{:8}", num);
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제14] a의 각 String이 관리하는 글자를 오름차순으로 정렬하라.
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
// [문제15] "STL.cpp"의 단어를 a에 저장하라.
// 길이오름차순으로 a를 정렬하라.
// 화면에 출력하라.
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
// [문제16] v에서 3을 제거하라.
void Problem16(void)
{
	std::vector<int> v{ 1, 2, 3, 4, 5 };

	// vector에서 지정한 숫자 빼기
	//erase(v, 3);

	for (int& num : v)
		std::cout << num << ' ';
	std::cout << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제17] v에서 홀수를 제거하라
void Problem17(void)
{
	std::vector<int> v{ 1, 2, 3, 4, 5 };

	// vector에서 지정한 조건에 맞으면 숫자 빼기 <algorithm>
	std::erase_if(v, [](int num) {
		return num & 1;
		});

	for (int& num : v)
		std::cout << num << ' ';
	std::cout << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제18] "STL.cpp"에 있는 소문자의 출현 횟수를 다음과 같이 출력하라.
// a - 10
// b - 3
// c - 0
// 생략
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
// [문제19] 키보드에서 입력한 단어를 오름차순 정렬 후 출력하라.
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
// [문제20] v에 "333"을 삽입하라.
void Problem20(void)
{
	std::vector<String> v;
	// vector의 사이즈 늘리기
	v.reserve(5);
	v = { "1", "22", "4444", "55555" };

	// 삽입할 위치 조정
	auto p = v.begin();
	++p;
	++p;

	// 333 삽입
	v.insert(p, "333");

	for (String& s : v)
		std::cout << s << '\n';
}
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
// [문제21] 파일 "String.cpp"를 읽어 cont에 저장하라.
// cont를 길이오름차순으로 정렬하라.
int Problem21(void)
{
	// <list>
	std::list<String> cont;

	std::ifstream in{ "String.cpp", std::ios::binary };
	if (not in)
		return 0;

	String s;
	while (in >> s)
		// list 뒤에 요소 추가
		cont.emplace_back(s);

	cont.sort([](const String& a, const String& b) {
		return a.getLen() < b.getLen();
		});

	for (String& s : cont)
		std::cout << s << '\n';
}
//---------------------------------------------------------------------------------------