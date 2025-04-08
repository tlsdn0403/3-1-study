//-------------------------------------------------------------------------
// STRING.h - std::string�� ������ Ŭ�����̴�
//            STL�� container�� ������ �� �ְ� �ڵ��� ������
//
//                                                        2025.4.8 ����
//-------------------------------------------------------------------------
#pragma once
#include<memory>
#include<iostream>

class STRING {
public:
    STRING(const char* s);
    STRING();
    STRING(const STRING& other);
    size_t size()const;

    STRING& operator=(const STRING& other);
private:
    size_t len{}; //null char�� ���� �ʰڴٴ� �Ҹ�
    std::unique_ptr<char[]> p{};

    friend std::ostream& operator<<(std::ostream& os, const STRING& str);

};