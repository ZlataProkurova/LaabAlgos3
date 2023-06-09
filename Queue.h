#ifndef QUEUE_H ////позволяет избежать повторного включения заголовочных файлов
#define QUEUE_H //проверяет, определен ли макрос QUEUE_H. Если макрос не определен, то код до #endif будет выполнен, иначе он будет проигнорирован.

#include "LinkedList.h"

template <typename T>
class Queue {
public:
    Queue(); //конструктор Queue(), который инициализирует объект класса List<T>, используемый для хранения элементов очереди.
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
void Queue<T>::enqueue(T data) { //добавление элемента в конец очереди 
    list.push_back(data);
}



template <typename T>
T Queue<T>::dequeue() { //извлечение элемента из начала очереди
    T data = list[0]; 
    list.removeAt(0);  
    return data;
}


template <typename T>
T Queue<T>::front() const { //получение элемента, находящегося в начале очереди, без его удаления 
    return list[0];
}


template <typename T>
int Queue<T>::size() const { //получение размера очереди
    return list.get_size();
}



template <typename T>
bool Queue<T>::empty() const { //проверка на пустоту
    return list.get_size() == 0;
}

template<typename T>
void Queue<T>::clear() //очистка очереди
{
    list.clear();
}

#endif // QUEUE_H //закрывает директиву препроцессора #ifndef