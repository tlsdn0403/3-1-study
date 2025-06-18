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
#include<print>
#include<map>
#include<random>
#include"STRING.h"
using namespace std;

// 강의자료 "이상한 나라의 앨리스.txt" 를 다운
// 여기에 있는 모든 단어를 multiset<STRING>에 저장하라.
// 단어의 개수를 출력하라 26626
// [3] 단어와 사용횟수를 화면에 출력하라.
// [4] 가장많이 사용된 단어부터 단어와 횟수를 모두 출력하라.
//      the - 1xxx
default_random_engine dre{ random_device{}() }; // 리얼 랜덤 디바이스를 생성해서 호출

//---------
int main()
//---------
{
    vector<int> v(100);
    iota(v.begin(), v.end(), 1);
    {
        cout << "홀수와 짝수로 분리" << endl;
        shuffle(v.begin(), v.end(), dre);
        cout << "partion 하기 전:" << endl;
        for (int num : v) {
            print("{:8}", num);
        }
        cout << endl;

        // 1 2 3 4 5 6 7 8 9 0 동그람가 들어간 숫자랑 아닌 숫자로 나눠라  6, 8, 9, 0 들어가 있으면 참
        auto it = partition(v.begin(), v.end(), [](int n) {
            while (n > 0) {
                int d = n % 10;
                if (d == 0 || d == 6 || d == 8 || d == 9) return true;
                n /= 10;
            }
            return false;
            });

        cout << "동그라미가 들어간 숫자:" << endl;
        for (auto i = v.begin(); i != it; ++i) {
            print("{:8}", *i);
        }
        cout << endl;

        cout << "동그라미가 없는 숫자:" << endl;
        for (auto i = it; i != v.end(); ++i) {
            print("{:8}", *i);
        }
        cout << endl;


    }
}
