#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T> //������ ������
class List {
public:
    List(); //����������� ������
    ~List(); //���������� ������

    void insert(T data, int index); //������� �������� � ������ �� �������
    void removeAt(int index); // �������� �������� �� ������ �� �������
    void remove(T data); // �������� ������� ��������� �������� �� ������
    void pop_back(); // �������� ���������� �������� �� ������
    void print() const; // ����� ������ �� �����
    void push_front(T data); // ������� �������� � ������ ������
    void push_back(T data); // ������� �������� � ����� ������
    void pop_front(); // �������� ������� �������� �� ������
    void clear();  // ������� ������
    int search(T data) const; // ����� ������� ������� ��������� �������� � ������
    int get_size() const { return size; } // ��������� �������� ������� ������
    T& operator[](int index) const; // ���������� ��������� ���������� ��� �������� ������� � ��������� ������

private:
    class Node {
    public:
        Node* ptrNextNode;  // ��������� �� ��������� ���� ������
        T data; //������, �������� � ����

        Node(T value = T(), Node* nextNode = nullptr) : data(value), ptrNextNode(nextNode) {} // ����������� ���� � �����������
        //�� ���������, ����� �������� �� ���������� � �������
    };

    Node* head;
    int size;
};

template <typename T> //������ ������� ������������
List<T>::List() {  // ����������� ������������ ������
    size = 0;
    head = nullptr;
}

template <typename T> // ������ ������� �����������
List<T>::~List() { //����������� ����������� ������
    clear();
}

template <typename T>
void List<T>::push_back(T data) { /// ������ ������� ���������� �������� � ����� ������
    if (head == nullptr) {
        head = new Node(data);
    }
    else {
        Node* currNode = head; // ���������� ��������� �� ������ ����
        while (currNode->ptrNextNode != nullptr) { // ��������� �� ��������� ����
            currNode = currNode->ptrNextNode;
        }
        currNode->ptrNextNode = new Node(data); // ������� ����� ���� � ����� ������
    }
    size++; // ���������� ���������� ����� � ������
}

template <typename T>  // ������ ������� ������� � ��������� ������ �� �������
T& List<T>::operator[](const int index) const  {
    if (index < size) { // ���� ������ ��������� � �������� ������
        int counter = 0;
        Node* currNode = head;
        while (currNode != nullptr) { // ��������� �� ����� ������
            if (counter == index)
                return currNode->data;
            currNode = currNode->ptrNextNode;
            counter++; // ����������� ������� ���������
        }
    }
    else 
        throw std::out_of_range("Index out of range"); //����������� ���������� � ������ ������� �� ������� ����������
}

template <typename T>
void List<T>::pop_front() { //������� ������ ������� �� ������
    if (head == nullptr) //������ ���� � ������� ������ �� ������
        return;
    Node* temp = head;
    head = head->ptrNextNode; //��������� �� ��������� ������
    delete temp;
    size--;
}

template <typename T>
void List<T>::push_front(T data) { // ������� ����� ������� � ������� `data` � ��������� ��� � ������ ������
    head = new Node(data, head);
    size++;
}

template <typename T>
void List<T>::insert(T data, int index) { //��������� ����� ������� � ������� `data` � ������� � �������� �������� `index`
    try {
        if (index == 0) { //��� `index` ����� 0, �� ���������� ������� `push_front()`, ����� �������� ������� � ������ ������.
            push_front(data);
        }
        else {
            Node* previousNode = head;
            for (int i = 0; i < index - 1; ++i) {
                if (previousNode == nullptr)
                    throw std::out_of_range("Index out of range"); //��� `index` ������ ��� ����� ������� ������, �� ������������� ���������� `std::out_of_range`
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
void List<T>::print() const { //������� ���������� ������ � ����������� ����� ������
    Node* currNode = head;
    std::cout << "List: ";
    while (currNode != nullptr) { // �� ������ �������� �������� �������� �������� ��������� �� �����, � ��������� `currNode` ��������� �� ��������� ������� � ������. 
        std::cout << currNode->data << " ";
        currNode = currNode->ptrNextNode;
    }
    std::cout << std::endl;
}

template <typename T>
void List<T>::removeAt(int index) { // ������� ������� � �������� �������� `index` �� ������.
    try {
        if (index == 0) { //���� ������ �������� ����� ����, �� �������� ����� `pop_front()`, ������� ������� ������ ������� ������. 
            pop_front();
        }
        else { //� ��������� ������ ������� ������� � �������� `(index - 1)` � ������� �������, ������� ��������� �� ��
            Node* previousNode = head; //�������� ����� �������� � �������� `(index - 1)` � ������ ������. 

            for (int i = 0; i < index - 1; ++i) {
                previousNode = previousNode->ptrNextNode;
            }
            Node* toDelete = previousNode->ptrNextNode;
            previousNode->ptrNextNode = toDelete->ptrNextNode; //������������� ����� ����� ������ ������ ���, ����� ���������� ��������� ����
            delete toDelete;
            size--;
        }
    }
    catch (std::exception& e) {
        std::cout << "Error occurred while removing an element at index. Index out of range." << e.what() << std::endl;
    }
}

template <typename T>
void List<T>::remove(T data) { //����� ������� ������� �� ������ �� ��������. 

    Node* currNode = head;
    Node* previousNode = nullptr;
    while (currNode != nullptr) { //���������� ����� �� ��� ���, ���� �� ����� ������ ��������������� �������. 

        if (currNode->data == data) { //���� ������ ������� �� ���������, ������ ��������, �� ��� ����� �������. 

            if (previousNode == nullptr) {
                head = currNode->ptrNextNode;
            }
            else { //������������� ����� ����� ������ ���, ����� ���������� ��������� ����. 

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
void List<T>::pop_back() { //������� ��������� ������� ������, ���� �� ����������.
    if (head == nullptr) ///���� ������ ������ ����� nullptr, �� ����� ������ ���������� ����������
        return;
    removeAt(size - 1); // ����� ����� �������� ����� removeAt() � ���������� size-1, ��� �������� � �������� ���������� ��������.
}

template <typename T>
void List<T>::clear() { //������� ��� �������� ������, ���� ��� ������ �� ������ ������ ����
    while (size)
        pop_front();
}

template <typename T>
int List<T>::search(T data) const { //���� ������� ������, ������� �������� �������� data
    Node* currNode = head; //���� ���������� �� ����� ������, ������� � ������, � ���������� �������� �������� �������� � data
    int index = 0;
    while (currNode != nullptr) {
        if (currNode->data == data) {
            return index; //���� ������� ����� �������, �� ���������� ��� ������. 
        }
        currNode = currNode->ptrNextNode;
        index++;
    }
    return -1; //���� ������� �� ������, �� ���������� -1.
}

#endif // LIST_H