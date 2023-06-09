#include <iostream>
#include <string>
#include "PostfixCalculator.h"

PostfixCalculator::PostfixCalculator() = default;

int PostfixCalculator::calculate(std::string expression) //����� calculate �������� �� ���� ��������� � ���� ������, ����� ���� ��������� ���������������� �������� � ������� �����
{
    int number = 0; 

    for (char& c : expression) //�� �������� ����, ������� �������� �� ������� ������� ������ � ��������� ��������������� ��������.
    {
        if (std::isdigit(c)) //���� ������� ������ �������� ������, �� �� ����������� � �������� �����, 
            //������� ������������ ����� ��������� ����� ��������� ����� ���������� �������
        {
            number = number * 10 + (c - '0'); 
        }
        else if (c == ' ') //���� ������� ������ - ������, � number �� ����� 0, �� ����� ���������� � ����
        {
            if (number != 0) 
            {
                stack.push(number);
                number = 0; 
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') //���� �� ������� ������ - ���� �� ���������� (+, -, *, /),
            //�� �� ����� ����������� ��� ��������� �������� (operand_1 � operand_2), � ����������� ��������������� ��������. 
        {
            int operand_2 = stack.pop();
            int operand_1 = stack.pop();
            int result = 0;

            switch (c)
            {
            case '+':
                result = operand_1 + operand_2;
                break;

            case '-':
                result = operand_1 - operand_2;
                break;

            case '*':
                result = operand_1 * operand_2;
                break;

            case '/':
                if (operand_2 == 0)
                {
                    throw std::runtime_error("Division by zero!");
                }
                result = operand_1 / operand_2;
                break;
            }
            stack.push(result); //��������� ����� ���������� � ����.
        }
        else if (c == ' ')  //��� ������� ������ - ������, �� �� ������ ������������
        {

        }
        else //���� ������� ������ �� �������� �� ������, �� ��������, �� ����������, �� ��������� ���������� � ���������� �� ������.
        {
            throw std::runtime_error("Invalid expression. Try again.");
        }
    }
    //����� ����, ��� ���� ������� �� ���� �������� ������, ����������� �������� ������� ����� stack
   
    if (stack.size() != 1) //���� �� �� ����� 1, �� ��������� ���������� � ���������� �� ������.
    {
        throw std::runtime_error("Invalid expression. Try again.");
    }

    return stack.top(); //� ����� ������ ������������ ������� ������� �����, ������� �������� ����������� ����������.
}