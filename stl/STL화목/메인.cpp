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
#include<unordered_set>
#include <cctype>
#include<print>
#include<map>
#include<random>
#include"STRING.h"
using namespace std;

// 1. "시험.txt" 파일을 연다.
// 2. 파일에서 id와 name을 읽어 Test 객체를 생성한다.
// 3. id 기준 오름차순으로 정렬된 컨테이너(예: std::set)로 저장한다.
// 4. 컨테이너의 크기를 출력한다.
extern bool 관찰; // 관찰하려면 true로
class Test {
public:
    size_t id;
    STRING name;
    Test(size_t i, const STRING& n) : id(i), name(n) {}
    bool operator<(const Test& other) const { return id < other.id; }
    friend std::ostream& operator<<(std::ostream& os, const Test& test) {
        os << test.id << " " << test.name << " ";
        return os;
    }
    friend std::istream& operator>>(std::istream& is, Test& test) {
        is >> test.id >> test.name;
        return is;
    }
    void read(std::istream& is) {
        is >> id >> name;
    }
};

template<>
struct std::hash<STRING> { //스페셜라이제이션 한다
    size_t operator()(const STRING& s)const {
        std::string str(s.begin(), s.end());
        return hash<std::string>{}(string{ s.begin(),s.end() }); //템플릿 스트럭쳐이기에 템플릿 스트럭쳐를 타입을 주지 않고 생성할 방법은 없다.
    }
};
//---------
int main()
//---------
{
    std::ifstream in("시험.txt");
    if (not in) {
        cout << "2025 06 19" << endl;
        return 0;
    }

    std::set<Test> tests;
    Test t(0, "");
    while (in >> t) {
        tests.insert(t);
    }
    cout << tests.size() << endl;

    /*관찰 = true;
    Test k = *tests.rbegin();
    관찰 = false;
    cout << k << endl;*/

    // "비교.txt" 파일을 연다.
    std::ifstream fin("비교.txt");
    std::vector<STRING> v;
    STRING s;
    while (fin >> s) {
        v.push_back(s);    
    }
    //관찰 = true;
    //STRING S = *v.rbegin();
    //관찰 = false;
    //// vector<STRING>에 저장한 STRING의 개수 출력
    //cout << v.size() << endl;

    
    std::set<STRING> vset(v.begin(), v.end());

    for (const auto& test : tests) {
        if (vset.contains(test.name)) {
            cout << test.name << endl;
        }
    }
    //for (const auto& test : tests) {
    //    auto p = find(v.begin(), v.end(), test.name);
    //    if (p != v.end()) {
    //        // test.name이 v에 존재함
    //        cout << *p << endl;
    //    }
    //}
    
}
 
