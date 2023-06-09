#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include <string>
#include "Stack.h"

class PostfixCalculator
{
public:
    PostfixCalculator(); //�������������� ������ ������ Stack<int>, ������������ ��� �������� ��������� ���������.

    int calculate(std::string expression); //��������� ������ expression � ����������� ���������� � ���������� ��������� ��� ����������.

private:
    Stack<int> stack;
};

#endif // POSTFIXCALCULATOR_H
