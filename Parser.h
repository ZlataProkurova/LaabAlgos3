#ifndef PARSER_H
#define PARSER_H

#include "Stack.h"
#include "Queue.h"
#include <string>
#include <sstream>

class Parser {
public:
    std::stringstream postfix; // обрабатывает постфиксное выражение
    std::string token; //представление текущего символа
    bool expectOperand = true; //отслеживание ожидаемого очередного токена
    std::string currentNumber; // содержит текущее число
    Queue<std::string> outputQueue; // хранение результирующей очереди в виде строки
    Stack<char> operatorStack; //хранение промежуточных операторов.

    std::string infixToPostfix(const std::string& expression); // осуществляет преобразование выражения в инфиксной нотации в выражение в постфиксной нотации
    // Он работает, используя алгоритм сортировочной станции, который использует стек для хранения операторов и очередь для хранения операндов.
private:
    bool isOperator(char c) const; //Mетод isOperator определяет, является ли заданный символ оператором
    int getPrecedence(char c) const; //getPrecedence возвращает численный приоритет оператора
};

#endif // PARSER_H

