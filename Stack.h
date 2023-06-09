#ifndef STACK_H //позволяет избежать повторного включения заголовочных файлов
#define STACK_H //определяет макрос STACK_H для исключения повторного включения заголовочного файла
#include "LinkedList.h"

template <typename T> //начало шаблона класса Stack, который параметризуется типом T.
class Stack {
public:
    Stack(); //конструктор класса Stack без параметров.
    ~Stack();//деструктор класса Stack.
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
Stack<T>::Stack() = default; //реализация конструктора класса Stack.

template <typename T>
Stack<T>::~Stack() = default; //реализация деструктора класса Stack.

template <typename T>
void Stack<T>::push(const T& data) { //добавления элемента в стек.

    list.push_front(data);
}

template <typename T>
T Stack<T>::pop() { //извлечение элемента из стека и возвращение его значения.
    T data = list[0]; 
    list.pop_front(); 
    return data;
}

template <typename T>
T Stack<T>::top() const { //возвращение значения верхнего элемента стека, не удаляя его.

    return list[0];
}

template <typename T>
bool Stack<T>::empty() const { //проверяем пуст ли стек.
    return list.get_size() == 0;
}

template <typename T>
int Stack<T>::size() const { //возвращение размера стека.

    return list.get_size();
}

template<typename T>
void Stack<T>::clear() //удаление всех элементов из стека.
{
    list.clear();
}

#endif // STACK_H ///закрывает директиву #ifndef и указывает на конец содержимого заголовочного файла.
