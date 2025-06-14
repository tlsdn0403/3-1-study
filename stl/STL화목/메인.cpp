//-------------------------------------------------------------------------------------------
// 2025 STL ȭ56 ��78  6�� 5�� �����      (13�� 2���� ����) 
//  6�� 19�� �� 15�� 2�� - �⸻���� , E320 ���� ....
//-------------------------------------------------------------------------------------------
// ���İ��� algorithms�� �˾ƺ��� - ���⵵ ������
// 
// aaaaaaaaaaaaaabbbbbbcccccccccccccccccdddeeeeeeeeeeeeee------zzzzz 
// a������ 10�����? �׷��� a�� 9���� �ڸ��� �����ϸ� O(1) �˰��� �����ϴ�
// ī��Ʈ�� ���İ� ���þ��� ������ ����.
// 1. partition             O(N)
// 2. nth_element           
// 3. partial_sort
// 4. sort
// 5. stavle_sort
//-----------------------------------------------------
#include<iostream>
#include<vector>
#include<list>
#include<concepts>
#include"save.h"
#include"STRING.h"
using namespace std;



extern bool ����; // �����Ϸ��� true��

template<class iter>
typename iterator_traits<iter>::difference_type  my_distance(iter b, iter e)
{
    //���� iter�� random_access_iterator_tag��� 
    // C++17���Ŀ� ���
    if constexpr (random_access_iterator<iter>) {  //�����Ͻÿ� �Ǵ��ϴ� ���Ǿ�
        return e - b;
    }
    else {
        typename iterator_traits<iter>::difference_type d{};
        while (b != e) {
            ++b;
            ++d;
        }
        return d;
    }
}

//----------
int main()
//------------------------------------------------------------
{  
    // �ݺ��ڰ��� �Ÿ��� ��� idstance �Լ�
    vector<int> v{ 1,2,3,4,5 };
    list<int> c{ 1,2,3,4,5 };

    cout << "vector�� distance - " << my_distance(v.end(), v.begin()) << endl;
    cout << "list�� distance - " << my_distance(c.end(), c.begin()) << endl;
    save("����.cpp");
}