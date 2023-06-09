#include "Parser.h"
#include "Stack.h"
#include "Queue.h"
#include <string>
#include <sstream>


std::string Parser::infixToPostfix(const std::string& expression) //����������� ��������� � ��������� ������� � ��������� � ����������� �������.

{
    for (char c : expression) //������ ���� for �������� �� �������� ��������� � ��������� �������. 
    {
        if (std::isspace(c))  //���� ������� ������ - ������, �� ������� token ����������� � ������� ������
            //���� ��������� �������, ����� ���������� ������ �������� ���������. ������� token ���������, � �������������� ��������� ������.
        {
            if (!token.empty())
            {
                if (expectOperand) 
                {
                    if (std::isdigit(token[0]))
                    {
                        outputQueue.enqueue(token); 
                        expectOperand = false;
                    }
                    else
                    {
                        throw std::runtime_error("Invalid token in the expression: " + token);
                    }
                }
                else
                {
                    throw std::runtime_error("Invalid token in the expression: " + token);
                }
                token.clear(); 
            }
            continue;
        }

        if (std::isdigit(c)) //���� ������� ������ - �����, �� �� ����������� � �������� token.
        {
            token += c; 
        }
        else if (isOperator(c)) //���� ������� ������ - �������� (+, -, *, /), �� ������� token ����������� � ������� ������,
            //���� ��������� �������, ����� ���������� ������ �������� ���������. 

        {
            if (!token.empty())
            {
                if (expectOperand)
                {
                    if (std::isdigit(token[0]))
                    {
                        outputQueue.enqueue(token); 
                        expectOperand = false;
                    }
                    else
                    {
                        throw std::runtime_error("Invalid token in the expression: " + token);
                    }
                }
                else
                {
                    throw std::runtime_error("Invalid token in the expression: " + token);
                }
                token.clear(); 
            }

            while (!operatorStack.empty() && operatorStack.top() != '(' && getPrecedence(operatorStack.top()) >= getPrecedence(c)) 
                //���� ������� ����� �� �������� ����������� ������� ��� ���� ��������� ��������� �� ������� ����� �� ������ ������ ����������
                //�������� ���������, ������� �������� ����������� � ���� ����������, � ����� �� ����� ���������� ����������� � ����������� � ������� ������.
            {
                outputQueue.enqueue(std::string(1, operatorStack.top())); 
                operatorStack.pop();
            }

            operatorStack.push(c); 
            expectOperand = true;
        }
        else if (c == '(') //���� ������� ������ �������� '(' (����������� �������), �� ���������� � ����. 
        {
            if (!token.empty())
            {
                throw std::runtime_error("Invalid token in the expression: " + token);
            }
            operatorStack.push(c);
            expectOperand = true;
        }
        else if (c == ')') //���� ������� ������ - ')' (����������� ������), ������� token ����������� � ������� ������, ���� ��������� �������, ����� ���������� ������.
        {
            if (!token.empty())
            {
                if (expectOperand)
                {
                    if (std::isdigit(token[0]))
                    {
                        outputQueue.enqueue(token); 
                        expectOperand = false;
                    }
                    else
                    {
                        throw std::runtime_error("Invalid token in the expression: " + token);
                    }
                }
                else
                {
                    throw std::runtime_error("Invalid token in the expression: " + token);
                }
                token.clear(); 
            }

            while (!operatorStack.empty() && operatorStack.top() != '(') //�����, �� ����� ����������� ��� ��������� � ����������� � �������, 
                //���� �� ����� ���������� ����������� ������.
            {
                outputQueue.enqueue(std::string(1, operatorStack.top())); 
                operatorStack.pop();
            }

            if (operatorStack.empty()) 
            {
                throw std::runtime_error("Mismatched parentheses"); //���� ��������������� ����������� ������ ���, �������������� ������. 

            }

            operatorStack.pop(); 
            expectOperand = false;
        }
        else
        {
            throw std::runtime_error("Invalid character in the expression: " + std::string(1, c)); //���� ������� ������ �� �������� �� ������, �� ����������, �� �������, ���������� ������. 
        }
    }

    if (!token.empty()) //���������, ��� ��������� ����� �� �������� ������ �������
    {
        if (expectOperand)
        {
            if (std::isdigit(token[0])) //����� ���������, ��� ��������� ������� (�����), � ���� ��� ���, �� ��������� ����� � �������� �������, ���� ����� ���������� � �����
            {
                outputQueue.enqueue(token); 
            }
            else
            {
                throw std::runtime_error("Invalid token in the expression: " + token); //����� ����������� ���������� � ������������ ������ � ���������
            }
        }
        else
        {
            throw std::runtime_error("Invalid token in the expression: " + token); //���� ��������� ��������, ������������� ���������� � ������������ ������.
        }
        token.clear(); 
    }

    while (!operatorStack.empty()) //����� � ����� �� ����� ���������� ����������� ��������� � ����������� � �������� �������,
        //���� �� ���������� ����������� ������ ��� ���� �� ������ ������
    {
        if (operatorStack.top() == '(')
        {
            throw std::runtime_error("Mismatched parentheses"); //���� ����������� ����������� ������, ������������� ���������� � �������������� ������.
        }

        outputQueue.enqueue(std::string(1, operatorStack.top())); //����� �����������, ��� ����� ��������� ���� ������� ��������� ������� � ��� � �������� ������� ������ ������ ��������
        operatorStack.pop();
    }

    if (expectOperand && !outputQueue.empty() && outputQueue.size() < 2) 
    {
        throw std::runtime_error("Incomplete expression: " + expression); //������������� ���������� � �������� ���������.
    }

    while (!outputQueue.empty()) // �� ������� ����������� ������ � ����������� � ���������� ���� stringstream � ���� ������ � �������� � �����.
    {
        postfix << outputQueue.dequeue() << " "; 
    }

    
    return postfix.str(); //������������ ��������� ������������� ����������� ������.
}

bool Parser::isOperator(char c) const //����� isOperator ���������, �������� �� �������� ������ �������������� ����������
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int Parser::getPrecedence(char c) const //����� getPrecedence ���������� ��������� ���������.
{
    if (c == '+' || c == '-')
    {
        return 1;
    }
    else if (c == '*' || c == '/')
    {
        return 2;
    }
    return 0;
}