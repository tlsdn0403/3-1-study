//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  6�� 5�� �����      (13�� 2���� ����) 
//  6�� 19�� �� 15�� 2�� - �⸻����
//-------------------------------------------------------------------------------------------
// Unordered Associatiove Containers - Hash ����
//-----------------------------------------------------
#include<iostream>
#include<unordered_set>
#include<print>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool ����; // �����Ϸ��� true��


template<>
struct std::hash<STRING>  { //����ȶ������̼� �Ѵ�
    size_t operator()(const STRING& s)const {
        std::string str(s.begin(), s.end());
        return hash<std::string>{}(string{ s.begin(),s.end() }); //���ø� ��Ʈ�����̱⿡ ���ø� ��Ʈ���ĸ� Ÿ���� ���� �ʰ� ������ ����� ����.
    }
};



//----------
int main()
//------------------------------------------------------------
{  
    unordered_set<STRING, hash<STRING> > us{ "1","22","333", "4444", "55555" };
    
    for (const STRING& s : us)
        cout << s << endl;
    //������� ���� �޸𸮸� ȭ�鿡 ����Ѵ�
    while (true) {
        for (size_t bc = 0; bc < us.bucket_count(); ++bc) {
            print("[{:>3}]", bc);
            for (auto i = us.begin(bc); i != us.end(bc); ++i) {
                print(" -> {:}", std::string{ i->begin(), i->end() });
            }
            cout << endl;
        }

        cout << "�߰��� STRING -";
        STRING s;
        cin >> s;
        us.insert(s);
    }
    save("����.cpp");
}