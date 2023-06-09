#ifndef PARSER_H
#define PARSER_H

#include "Stack.h"
#include "Queue.h"
#include <string>
#include <sstream>

class Parser {
public:
    std::stringstream postfix; // ������������ ����������� ���������
    std::string token; //������������� �������� �������
    bool expectOperand = true; //������������ ���������� ���������� ������
    std::string currentNumber; // �������� ������� �����
    Queue<std::string> outputQueue; // �������� �������������� ������� � ���� ������
    Stack<char> operatorStack; //�������� ������������� ����������.

    std::string infixToPostfix(const std::string& expression); // ������������ �������������� ��������� � ��������� ������� � ��������� � ����������� �������
    // �� ��������, ��������� �������� ������������� �������, ������� ���������� ���� ��� �������� ���������� � ������� ��� �������� ���������.
private:
    bool isOperator(char c) const; //M���� isOperator ����������, �������� �� �������� ������ ����������
    int getPrecedence(char c) const; //getPrecedence ���������� ��������� ��������� ���������
};

#endif // PARSER_H

