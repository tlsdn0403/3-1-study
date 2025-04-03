//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  3�� 20�� �����      (5�� 2���� ����) 
// 4�� 24�� �߰����(30) 8���� 2��
// ����    (30) - 4�� 10�� ����
//-------------------------------------------------------------------------------------------
// STRING - std::stromg�� ������ Ŭ����, STL ǥ�� container�� �ǵ��� �������ѳ�������
//-------------------------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<memory>
#include"save.h"
using namespace std;
class STRING {
public:
    STRING(const char* s) : len{ strlen(s) } {   //[] -> *�� collapsing �ȴ�.
        p.reset();
        p= make_unique<char[]>(len); //p�� �ּҸ� �����ϵ���
        memcpy(p.get(), s, len);  //p���ٰ� s�� ������ len��ŭ DMA ���̷�Ʈ �޸� ���  �̰ź��� ���� �޸𸮳����� ������ ����.
    }


    size_t size( )const {
        return len;
    }


private:
    size_t len{}; //null char�� ���� �ʰڴٴ� �Ҹ�
    unique_ptr<char[]> p{};



    friend ostream& operator<<(ostream& os, const STRING& str) {
        for (int i = 0; i < str.len; ++i) {
            os << str.p[i];
        }
        return os;
    }
};

//----------
int main()
//------------------------------------------------------------
{
    STRING s{ "std::string�� ������ Ŭ����" };
    cout << s.size() << endl; //s�� Ȯ���� �ڿ��� ����Ʈ ��
    cout << s << endl;
    save("����.cpp");
}