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
    //����� calculate() ��������� ��������� ��������� � ���� ������ � ���������� ��� ��������� � ���� ������ �����
    //�� ������� ���������� ������ parser ��� ������� ��������� � ��������� ����������� �������
    //����� �� ���������� ������ postfixCalculator ��� ���������� ���������� �� ������ ���������� ����������� �������.
    int result{};

private:
    Parser parser; //������ ���������
    PostfixCalculator postfixCalculator; //���������� ���������
};

#endif // INFIXCALCULATOR_H#pragma once
