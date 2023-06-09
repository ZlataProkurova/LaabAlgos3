#include <iostream>
#include "InfixCalculator.h"

int main()
{ 
    setlocale(LC_ALL, "Russian");

    InfixCalculator infixCalculator;
    std::string expression;
    int result;

    std::cout << "������� ��������� � ��������� ����� ��� ����������: " << std::endl;
    std::getline(std::cin, expression); 
    while (expression != "�����")
    {
        try {
            result = infixCalculator.calculate(expression);
            std::cout << "���������: " << result << std::endl;
        }
        catch (std::runtime_error& e)
        {
            std::cout << "������: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "������, ������������ ������ ������" << std::endl;
        }
        std::cout << "����� ����� �� ���������, ������� '�����' ��� ������� ������ ��������� : " << std::endl;
        std::getline(std::cin, expression);

        return 0;
    }
}