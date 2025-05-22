//-------------------------------------------------------------------------
// STRING.h - std::string�� ������ Ŭ�����̴�
//            STL�� container�� ������ �� �ְ� �ڵ��� ������
//
//                                                        2025.4.8 ����
//  >> ������                                             2025.05.01 
//  <  ������                                             2025. 5. 8
//  begin() , end()                                       2025. 5.13
//  ������ �ݺ��ڴ� �ݵ�� Ŭ������ ����                  2025. 5.13
//  �ݺ��ڵ� �翬�� Ŭ������ �ڵ��ؾ� ��                  2025. 5.15
//  �����ݺ��ڰ� �Ƿ��� �̷� ������� ����                2025. 5.20
//  <=> ������                                            2025. 5.22
//  std::less�� Ư��ȭ                                    2025. 5.22
//-------------------------------------------------------------------------
#pragma once
#include<memory>
#include<iostream>

class STRING_Iterator {
    //ǥ�� �ݺ��ڴ� ���� �ټ����� ������ ����� �� �־�� �Ѵ�.
public:
    using difference_type = ptrdiff_t;
    using value_type = char;
    using pointer = char*;
    using reference = char&;
    using iterator_category = std::random_access_iterator_tag;
public:
    STRING_Iterator() = default;
    STRING_Iterator(char* p): p{p}{}

    //�ݺ��ڶ�� �ּ��� ���� ����� �����ؾ� ��

    char& operator*()const { //����ֵ��� location ���� ������� char&
        return *p;
    }
    STRING_Iterator& operator++() {
        ++p;
        return *this;
    }
    
    

    //���� �����ڵ�
    bool operator==(const STRING_Iterator& rhs)const {
        return p == rhs.p;
    }
    bool operator<(const STRING_Iterator& rhs) const {
        return p < rhs.p; 
    }
    bool operator>(const STRING_Iterator& rhs) const {
        return p > rhs.p; 
    }

    
    
    
    

    //�����ݺ��ڰ� �ǰ� �ʹ�. - 2025. 5. 20
    difference_type operator-(const STRING_Iterator& rhs) const {
        return p - rhs.p;
    }
    STRING_Iterator operator--() {
        return --p;
    }
    STRING_Iterator operator+(difference_type n) const {
        return p + n; 
    }
    STRING_Iterator operator-(difference_type n) const {
        return p - n; 
    }
    auto operator<=>(const STRING_Iterator& rhs)const {
        return p <=> rhs.p;
    }

private:
    char* p{}; //�̷��� �ϸ� ����Ʈ �����ÿ� ����Ʈ ���� �����ȴ�.
};







// �ݺ��� ����� ( �ݺ�����ô ������ �ӿ��� ���� �ϴ� ��)
class STRING_Reverse_Iterator {
public:
    STRING_Reverse_Iterator(char* p) : p{ p } {}

    char operator*() {
        return *(p - 1);
    }
    void operator++() {
        --p;
    }
    bool operator==(const STRING_Reverse_Iterator& rhs)const { //end ��ġ���� ���� �� �־�� �Ѵ�.
        return p == rhs.p;
    }
private:
    char* p;
};




class STRING {
public:
    STRING();                                           //2025. 04 . 08
    ~STRING();                                          //������ ���� ��¿ �� ����...
    
    STRING(const char* s);

    //��������� �����Ҵ�

    //�ڱ� �ڽ��� �����ؾ� �Ѵ�. �׷��� �տ� STRING
    STRING(const STRING& other);                        //2025.04.08
    STRING& operator=(const STRING& other);             //2025.04.08

 


    //�̵������� �̵��Ҵ翬����                         //2025. 4. 10
    STRING(STRING&&);                                   //&& ->rvalue reference   ���� �Ѱ��� ���ڴ� �̵����� ���̴�.
    STRING& operator=(STRING&&);

    
    //2025. 04. 22 ���� �����ڵ�
    //bool operator==(const STRING& rhs) const;
    bool operator<(const STRING& rhs)  const;          //2025. 5. 8

    //2025. 05. 22
    // ��� ���迬���ڸ� ��ü�ϴ� three-way comparison operator
    auto operator<=> (const STRING& rhs)  const {
        return std::lexicographical_compare(p.get(), p.get() + len,
            rhs.p.get(), rhs.p.get() + rhs.len); //lexicographical_compare�� �̿��ؼ� ������ ������ ����.
    };



    //���� ���̽� �Լ���

    size_t size()const;

    //  begin() , end()                                       2025. 5.13
    STRING_Iterator begin() const;
    STRING_Iterator end() const;

    STRING_Reverse_Iterator rbegin() const;
    STRING_Reverse_Iterator rend() const;

private:
    size_t len{}; //null char�� ���� �ʰڴٴ� �Ҹ�

    //����ũ �����ʹ� ���簡 �����Ǿ��ִ�.
    // ����Ʈ�� ����Ʈ �Ǿ��ִ�.
    std::unique_ptr<char[]> p{};

    size_t id;                                //2025.04.08

    friend std::ostream& operator<<(std::ostream& os, const STRING& str);
    // 2025. 5. 1 �߰�
    friend std::istream& operator>>(std::istream& is, STRING& str);


    static size_t gid;     //�۷ι� �� id                           //2025.04.08

    
};
