//-------------------------------------------------------------------------
// STRING.cpp - std::string�� ������ Ŭ�����̴�
//            STL�� container�� ������ �� �ְ� �ڵ��� ������
//
//                                                        2025.4.8 ����
//-------------------------------------------------------------------------
#include<memory>
#include<iostream>
#include"STRING.h"

STRING::STRING() = default;


STRING::STRING(const char* s) : len{ strlen(s) }
{   //[] -> *�� collapsing �ȴ�.
    p.reset();
    p = std::make_unique<char[]>(len); //p�� �ּҸ� �����ϵ���
    memcpy(p.get(), s, len);  //p���ٰ� s�� ������ len��ŭ DMA ���̷�Ʈ �޸� ���  �̰ź��� ���� �޸𸮳����� ������ ����.
}

//���� ������
STRING::STRING(const STRING& other)
    :len{other.len}  //����� ,�� ���� �ϸ� ������ ������� �ʴ´�.
{
    p = std::make_unique<char[]>(len); //�����ÿ� ����Ʈ ������ ��ױ� ������ �׳� �ᵵ ������ �����ž�
    memcpy(p.get(), other.p.get(), len);
}


STRING& STRING::operator=(const STRING& other)     //2025.04.08
{
    if (this == &other)
        return *this;  //*�پ�� �ڱ��ڽ��� �ȴ�.

    len = other.len;
    p.release();   // p.reset()�� ���� �ٸ���?? ��������
    p = std::make_unique<char[]>(len);
    memcpy(p.get(), other.p.get(), len); //���������ߴ� �ڿ��� ��ȯ�ϰ� ���ο� �ڿ� ��´�.
    return *this;
}


size_t STRING::size()const
{
     return len;
}

std::ostream& operator<<(std::ostream& os, const STRING& str) {
     for (int i = 0; i < str.len; ++i) {
         os << str.p[i];
     }
     return os;
}

