#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T> //Шаблон класса
class List {
public:
    List(); //Конструктор списка
    ~List(); //Деструктор списка

    void insert(T data, int index); //Вставка элемента в список по индексу
    void removeAt(int index); // Удаление элемента из списка по индексу
    void remove(T data); // Удаление первого вхождения элемента из списка
    void pop_back(); // Удаление последнего элемента из списка
    void print() const; // Вывод списка на экран
    void push_front(T data); // Вставка элемента в начало списка
    void push_back(T data); // Вставка элемента в конец списка
    void pop_front(); // Удаление первого элемента из списка
    void clear();  // Очистка списка
    int search(T data) const; // Поиск индекса первого вхождения элемента в списке
    int get_size() const { return size; } // Получение текущего размера списка
    T& operator[](int index) const; // Перегрузка оператора индексации для быстрого доступа к элементам списка

private:
    class Node {
    public:
        Node* ptrNextNode;  // Указатель на следующий узел списка
        T data; //Данные, хранимые в узле

        Node(T value = T(), Node* nextNode = nullptr) : data(value), ptrNextNode(nextNode) {} // Конструктор узла с параметрами
        //по умолчанию, когда значения не передаются в функцию
    };

    Node* head;
    int size;
};

template <typename T> //Шаблон функции конструктора
List<T>::List() {  // Определение конструктора списка
    size = 0;
    head = nullptr;
}

template <typename T> // Шаблон функции деструктора
List<T>::~List() { //Определение деструктора списка
    clear();
}

template <typename T>
void List<T>::push_back(T data) { /// Шаблон функции добавления элемента в конец списка
    if (head == nullptr) {
        head = new Node(data);
    }
    else {
        Node* currNode = head; // Запоминаем указатель на первый узел
        while (currNode->ptrNextNode != nullptr) { // Переходим на последний узел
            currNode = currNode->ptrNextNode;
        }
        currNode->ptrNextNode = new Node(data); // Создаем новый узел в конце списка
    }
    size++; // Обновление количества узлов в списке
}

template <typename T>  // Шаблон функции доступа к элементам списка по индексу
T& List<T>::operator[](const int index) const  {
    if (index < size) { // Если индекс находится в пределах списка
        int counter = 0;
        Node* currNode = head;
        while (currNode != nullptr) { // Переходим по узлам списка
            if (counter == index)
                return currNode->data;
            currNode = currNode->ptrNextNode;
            counter++; // Увеличиваем счетчик переходов
        }
    }
    else 
        throw std::out_of_range("Index out of range"); //Выбрасываем исключение о выходе индекса за границы доступного
}

template <typename T>
void List<T>::pop_front() { //удаляет первый элемент из списка
    if (head == nullptr) //список пуст и функция ничего не делает
        return;
    Node* temp = head;
    head = head->ptrNextNode; //указывает на следующий элемет
    delete temp;
    size--;
}

template <typename T>
void List<T>::push_front(T data) { // создает новый элемент с данными `data` и добавляет его в начало списка
    head = new Node(data, head);
    size++;
}

template <typename T>
void List<T>::insert(T data, int index) { //вставляет новый элемент с данными `data` в позицию с заданным индексом `index`
    try {
        if (index == 0) { //сли `index` равен 0, то вызывается функция `push_front()`, чтобы добавить элемент в начало списка.
            push_front(data);
        }
        else {
            Node* previousNode = head;
            for (int i = 0; i < index - 1; ++i) {
                if (previousNode == nullptr)
                    throw std::out_of_range("Index out of range"); //сли `index` больше или равен размеру списка, то выбрасывается исключение `std::out_of_range`
                previousNode = previousNode->ptrNextNode;
            }
            if (previousNode == nullptr)
                throw std::out_of_range("Index out of range");
            Node* newNode = new Node(data, previousNode->ptrNextNode);
            previousNode->ptrNextNode = newNode;
            size++;
        }
    }
    catch (std::out_of_range& e) {
        std::cout << "Error occurred while inserting an element: " << e.what() << std::endl;
    }
}

template <typename T>
void List<T>::print() const { //выводит содержимое списка в стандартный поток вывода
    Node* currNode = head;
    std::cout << "List: ";
    while (currNode != nullptr) { // На каждой итерации значение текущего элемента выводится на экран, а указатель `currNode` указывает на следующий элемент в списке. 
        std::cout << currNode->data << " ";
        currNode = currNode->ptrNextNode;
    }
    std::cout << std::endl;
}

template <typename T>
void List<T>::removeAt(int index) { // удаляет элемент с заданным индексом `index` из списка.
    try {
        if (index == 0) { //если индекс элемента равен нулю, то вызываем метод `pop_front()`, который удаляет первый элемент списка. 
            pop_front();
        }
        else { //в противном случае находим элемент с индексом `(index - 1)` и удаляем элемент, который находится за ни
            Node* previousNode = head; //начинаем поиск элемента с индексом `(index - 1)` с головы списка. 

            for (int i = 0; i < index - 1; ++i) {
                previousNode = previousNode->ptrNextNode;
            }
            Node* toDelete = previousNode->ptrNextNode;
            previousNode->ptrNextNode = toDelete->ptrNextNode; //перестраиваем связи между узлами списка так, чтобы пропустить удаляемый узел
            delete toDelete;
            size--;
        }
    }
    catch (std::exception& e) {
        std::cout << "Error occurred while removing an element at index. Index out of range." << e.what() << std::endl;
    }
}

template <typename T>
void List<T>::remove(T data) { //метод удаляет элемент из списка по значению. 

    Node* currNode = head;
    Node* previousNode = nullptr;
    while (currNode != nullptr) { //продолжаем поиск до тех пор, пока не будет найден соответствующий элемент. 

        if (currNode->data == data) { //если найден элемент со значением, равным искомому, то его нужно удалить. 

            if (previousNode == nullptr) {
                head = currNode->ptrNextNode;
            }
            else { //перестраиваем связи между узлами так, чтобы пропустить удаляемый узел. 

                previousNode->ptrNextNode = currNode->ptrNextNode;
            }
            delete currNode;
            size--;
            return;
        }
        previousNode = currNode;
        currNode = currNode->ptrNextNode;
    }
}

template <typename T>
void List<T>::pop_back() { //удаляет последний элемент списка, если он существует.
    if (head == nullptr) ///Если голова списка равна nullptr, то метод просто возвращает управление
        return;
    removeAt(size - 1); // Иначе метод вызывает метод removeAt() с параметром size-1, что приводит к удалению последнего элемента.
}

template <typename T>
void List<T>::clear() { //удаляет все элементы списка, пока его размер не станет равным нулю
    while (size)
        pop_front();
}

template <typename T>
int List<T>::search(T data) const { //ищет элемент списка, который содержит значение data
    Node* currNode = head; //етод проходится по всему списку, начиная с головы, и сравнивает значение текущего элемента с data
    int index = 0;
    while (currNode != nullptr) {
        if (currNode->data == data) {
            return index; //Если находит такой элемент, то возвращает его индекс. 
        }
        currNode = currNode->ptrNextNode;
        index++;
    }
    return -1; //Если элемент не найден, то возвращает -1.
}

#endif // LIST_H