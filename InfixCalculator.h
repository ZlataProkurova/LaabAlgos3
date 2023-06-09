#ifndef INFIXCALCULATOR_H
#define INFIXCALCULATOR_H

#include <iostream>
#include <string>
#include "Parser.h"
#include "PostfixCalculator.h"

class InfixCalculator
{
public:
    int calculate(const std::string& expression); 
    //Метод calculate() принимает инфиксное выражение в виде строки и возвращает его результат в виде целого числа
    //Он сначала использует объект parser для разбора выражения и получения постфиксной нотации
    //Затем он использует объект postfixCalculator для вычисления результата на основе полученной постфиксной нотации.
    int result{};

private:
    Parser parser; //разбор выражения
    PostfixCalculator postfixCalculator; //вычисление выражения
};

#endif // INFIXCALCULATOR_H#pragma once
