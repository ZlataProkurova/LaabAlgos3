#include "InfixCalculator.h"

int InfixCalculator::calculate(const std::string& expression) //��������� �������� expression ��� ������ �� ����������� ������,
//����� �������� ����������� ������ ��� �������� � �����
{
    std::string postfix = parser.infixToPostfix(expression); //���������� ������ parser ��� �������������� ���������� ��������� � ����������� �������. ��������� ����������� � ���������� postfix
    result = postfixCalculator.calculate(postfix); //����� ���������� ������ postfixCalculator ��� ���������� ���������� 
    //�� ������ ���������� ����������� �������. ��������� ���������� ����������� � ���������� result.
    return result; 
}
