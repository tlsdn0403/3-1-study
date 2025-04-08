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
    STRING();                          //2025. 04 . 08
    STRING(const char* s);

    //��������� �����Ҵ�

    //�ڱ� �ڽ��� �����ؾ� �Ѵ�. �׷��� �տ� STRING
    STRING(const STRING& other);                        //2025.04.08
    STRING& operator=(const STRING& other);             //2025.04.08

    //�̵������� �̵��Ҵ�


    size_t size()const;

    
private:
    size_t len{}; //null char�� ���� �ʰڴٴ� �Ҹ�

    //����ũ �����ʹ� ���簡 �����Ǿ��ִ�.
    // ����Ʈ�� ����Ʈ �Ǿ��ִ�.
    std::unique_ptr<char[]> p{};

    friend std::ostream& operator<<(std::ostream& os, const STRING& str);

};