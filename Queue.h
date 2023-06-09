#ifndef QUEUE_H ////��������� �������� ���������� ��������� ������������ ������
#define QUEUE_H //���������, ��������� �� ������ QUEUE_H. ���� ������ �� ���������, �� ��� �� #endif ����� ��������, ����� �� ����� ��������������.

#include "LinkedList.h"

template <typename T>
class Queue {
public:
    Queue(); //����������� Queue(), ������� �������������� ������ ������ List<T>, ������������ ��� �������� ��������� �������.
    void enqueue(T data);
    T dequeue();
    T front() const;
    int size() const;
    bool empty() const;
    void clear();

private:
    List<T> list;
};

template <typename T>
Queue<T>::Queue() = default; 


template <typename T>
void Queue<T>::enqueue(T data) { //���������� �������� � ����� ������� 
    list.push_back(data);
}



template <typename T>
T Queue<T>::dequeue() { //���������� �������� �� ������ �������
    T data = list[0]; 
    list.removeAt(0);  
    return data;
}


template <typename T>
T Queue<T>::front() const { //��������� ��������, ������������ � ������ �������, ��� ��� �������� 
    return list[0];
}


template <typename T>
int Queue<T>::size() const { //��������� ������� �������
    return list.get_size();
}



template <typename T>
bool Queue<T>::empty() const { //�������� �� �������
    return list.get_size() == 0;
}

template<typename T>
void Queue<T>::clear() //������� �������
{
    list.clear();
}

#endif // QUEUE_H //��������� ��������� ������������� #ifndef