#ifndef STACK_H //��������� �������� ���������� ��������� ������������ ������
#define STACK_H //���������� ������ STACK_H ��� ���������� ���������� ��������� ������������� �����
#include "LinkedList.h"

template <typename T> //������ ������� ������ Stack, ������� ��������������� ����� T.
class Stack {
public:
    Stack(); //����������� ������ Stack ��� ����������.
    ~Stack();//���������� ������ Stack.
    void push(const T& data); 
    T pop();
    T top() const;
    bool empty() const;
    int size() const;
    void clear();

private:
    List<T> list;
};

template <typename T>
Stack<T>::Stack() = default; //���������� ������������ ������ Stack.

template <typename T>
Stack<T>::~Stack() = default; //���������� ����������� ������ Stack.

template <typename T>
void Stack<T>::push(const T& data) { //���������� �������� � ����.

    list.push_front(data);
}

template <typename T>
T Stack<T>::pop() { //���������� �������� �� ����� � ����������� ��� ��������.
    T data = list[0]; 
    list.pop_front(); 
    return data;
}

template <typename T>
T Stack<T>::top() const { //����������� �������� �������� �������� �����, �� ������ ���.

    return list[0];
}

template <typename T>
bool Stack<T>::empty() const { //��������� ���� �� ����.
    return list.get_size() == 0;
}

template <typename T>
int Stack<T>::size() const { //����������� ������� �����.

    return list.get_size();
}

template<typename T>
void Stack<T>::clear() //�������� ���� ��������� �� �����.
{
    list.clear();
}

#endif // STACK_H ///��������� ��������� #ifndef � ��������� �� ����� ����������� ������������� �����.
