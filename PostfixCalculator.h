#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include <string>
#include "Stack.h"

class PostfixCalculator
{
public:
    PostfixCalculator(); //инициализирует объект класса Stack<int>, используемый для хранения операндов выражения.

    int calculate(std::string expression); //принимает строку expression с постфиксным выражением и возвращает результат его вычисления.

private:
    Stack<int> stack;
};

#endif // POSTFIXCALCULATOR_H
