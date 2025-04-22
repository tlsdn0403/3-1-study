//-------------------------------------------------------------------------
// STRING.cpp - std::string�� ������ Ŭ�����̴�
//            STL�� container�� ������ �� �ְ� �ڵ��� ������
//
//                                                        2025.4.8 ����
// 2025. 4. 10    �̵������� �̵��Ҵ翬���� �ڵ�
//-------------------------------------------------------------------------
#include<memory>
#include<iostream>
#include<print>
#include<algorithm>
#include"STRING.h"

//������ �����ϱ� ���� ���� �߰�
bool ����{ false };                            //2025 04 08 ������ ����


// ������ std::println�� C++ ǥ�� ���̺귯���� �������� �ʴ� �Լ���� ���Դϴ�.  
// ��� std::cout�� ����Ͽ� ����ϵ��� �����ؾ� �մϴ�.  

STRING::STRING()                             //2025 04 08 ������ ������ ���� �ڵ�  
   : id{ ++gid }  
{  
   
   if (����) {
       std::println("[{:8}] {:16} �ڿ���:{:<10} �޸�:{:<12}, �ڿ��޸�:{:<12}",
           id, "����Ʈ������", len, static_cast<void*>(this), (void*)p.get());
   }
}
STRING::~STRING()                                          //������ ���� ��¿ �� ����...
{
    if (����) {
        std::println("[{:8}] {:16} �ڿ���:{:<10} �޸�:{:<12}, �ڿ��޸�:{:<12}",
            id, "�Ҹ���", len, (void*)this,(void*)p.get());
    }
}

STRING::STRING(const char* s) : id{ ++gid }, len{strlen(s)}
{   //[] -> *�� collapsing �ȴ�.
    p.reset();
    p = std::make_unique<char[]>(len); //p�� �ּҸ� �����ϵ���
    memcpy(p.get(), s, len);  //p���ٰ� s�� ������ len��ŭ DMA ���̷�Ʈ �޸� ���  �̰ź��� ���� �޸𸮳����� ������ ����.

    if (����) {
        std::println("[{:8}] {:16} �ڿ���:{:<10} �޸�:{:<12}, �ڿ��޸�:{:<12}",
            id, "������(char*)", len, (void*)this, (void* )p.get());
    }
}

//���� ������
STRING::STRING(const STRING& other)
    :id{ ++gid },len {  other.len}  //����� ,�� ���� �ϸ� ������ ������� �ʴ´�.
{
    //������� �ʾƾ� �� �ڵ��̴�. ������ ���� ���� �������� �ý��� ���̴�.
    p = std::make_unique<char[]>(len); //�����ÿ� ����Ʈ ������ ��ױ� ������ �׳� �ᵵ ������ �����ž�
    memcpy(p.get(), other.p.get(), len);

    if (����) {
        std::println("[{:8}] {:16} �ڿ���:{:<10} �޸�:{:<12}, �ڿ��޸�:{:<12}",
            id, "���������", len, (void*)this, (void* )p.get());
    }
}


STRING& STRING::operator=(const STRING& other)     //2025.04.08
{
    if (this == &other)
        return *this;  //*�پ�� �ڱ��ڽ��� �ȴ�.

    len = other.len;
    p.release();   // p.reset()�� ���� �ٸ���?? �������� 
    p = std::make_unique<char[]>(len);
    memcpy(p.get(), other.p.get(), len); //���������ߴ� �ڿ��� ��ȯ�ϰ� ���ο� �ڿ� ��´�.

    if (����) {
        std::println("[{:8}] {:16} �ڿ���:{:<10} �޸�:{:<12}, �ڿ��޸�:{:<12}",
            id, "�����Ҵ翬����", len, (void*)this, (void* )p.get());
    }
    return *this;
}



//�̵������� �̵��Ҵ翬����                               //2025. 4. 10
STRING::STRING(STRING&& other)
    :id{ ++gid }, len{ other.len }
{
    p.reset(other.p.release());  
    other.len = 0;

    if (����) {
        std::println("[{:8}] {:16} �ڿ���:{:<10} �޸�:{:<12}, �ڿ��޸�:{:<12}",
            id, "�̵� ������", len, (void*)this, (void*)p.get());
    }
}

//�� �� �Ȱ��� �ڵ� �� �ʿ�� ����.
STRING& STRING::operator=(STRING&& other)
{
    if (this == &other) //adress of other
        return *this;

    len = other.len;
    p.release(); //���� �ִ� �޸� �ý��ۿ� ��ȯ�ϰ� �ٽ� ����
    p.reset(other.p.release());
    other.p.release();

    //�̷��� ��°����ϴ�.
    other.len = 0;
    if (����) {
        std::println("[{:8}] {:16} �ڿ���:{:<10} �޸�:{:<12}, �ڿ��޸�:{:<12}",
            id, "�̵� �Ҵ� ������", len, (void*)this, (void*)p.get());
    }
    return *this; //�Ҵ繮�� �ǵڿ� �߰��� ����� �Ѵ�.
}



bool STRING::operator==(const STRING& rhs) const
{
    return std::equal(&p[0], &p[len], &rhs.p[0]);
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

size_t STRING::gid{};                               //2025.04.08