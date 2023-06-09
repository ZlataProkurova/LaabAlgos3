#include "Parser.h"
#include "Stack.h"
#include "Queue.h"
#include <string>
#include <sstream>


std::string Parser::infixToPostfix(const std::string& expression) //преобразует выражение в инфиксной нотации в выражение в постфиксной нотации.

{
    for (char c : expression) //Первый цикл for проходит по символам выражения в инфиксной нотации. 
    {
        if (std::isspace(c))  //Если текущий символ - пробел, то текущий token добавляется в очередь вывода
            //если ожидается операнд, иначе происходит ошибка парсинга выражения. Текущий token очищается, и обрабатывается следующий символ.
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

        if (std::isdigit(c)) //Если текущий символ - цифра, то он добавляется к текущему token.
        {
            token += c; 
        }
        else if (isOperator(c)) //Если текущий символ - оператор (+, -, *, /), то текущий token добавляется к очереди вывода,
            //если ожидается операнд, иначе происходит ошибка парсинга выражения. 

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
                //пока вершина стека не является открывающей скобкой или пока приоритет оператора на вершине стека не станет меньше приоритета
                //текущего оператора, текущий оператор добавляется в стек операторов, а также из стека операторов извлекаются и добавляются в очередь вывода.
            {
                outputQueue.enqueue(std::string(1, operatorStack.top())); 
                operatorStack.pop();
            }

            operatorStack.push(c); 
            expectOperand = true;
        }
        else if (c == '(') //Если текущий символ является '(' (открывающей скобкой), он помещается в стек. 
        {
            if (!token.empty())
            {
                throw std::runtime_error("Invalid token in the expression: " + token);
            }
            operatorStack.push(c);
            expectOperand = true;
        }
        else if (c == ')') //Если текущий символ - ')' (закрывающая скобка), текущий token добавляется в очередь вывода, если ожидается операнд, иначе происходит ошибка.
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

            while (!operatorStack.empty() && operatorStack.top() != '(') //Далее, из стека извлекаются все операторы и добавляются в очередь, 
                //пока не будет достигнута открывающая скобка.
            {
                outputQueue.enqueue(std::string(1, operatorStack.top())); 
                operatorStack.pop();
            }

            if (operatorStack.empty()) 
            {
                throw std::runtime_error("Mismatched parentheses"); //Если соответствующей открывающей скобки нет, обрабатывается ошибка. 

            }

            operatorStack.pop(); 
            expectOperand = false;
        }
        else
        {
            throw std::runtime_error("Invalid character in the expression: " + std::string(1, c)); //Если текущий символ не является ни цифрой, ни оператором, ни скобкой, происходит ошибка. 
        }
    }

    if (!token.empty()) //проверяет, что очередное токен не является пустой строкой
    {
        if (expectOperand)
        {
            if (std::isdigit(token[0])) //Затем проверяет, что ожидается операнд (число), и если это так, то добавляет токен в выходную очередь, если токен начинается с цифры
            {
                outputQueue.enqueue(token); 
            }
            else
            {
                throw std::runtime_error("Invalid token in the expression: " + token); //иначе выбрасывает исключение о некорректном токене в выражении
            }
        }
        else
        {
            throw std::runtime_error("Invalid token in the expression: " + token); //если ожидается оператор, выбрасывается исключение о некорректном токене.
        }
        token.clear(); 
    }

    while (!operatorStack.empty()) //Далее в цикле из стека операторов извлекаются операторы и добавляются в выходную очередь,
        //пока не встретится открывающая скобка или стек не станет пустым
    {
        if (operatorStack.top() == '(')
        {
            throw std::runtime_error("Mismatched parentheses"); //Если встречается открывающая скобка, выбрасывается исключение о несоответствии скобок.
        }

        outputQueue.enqueue(std::string(1, operatorStack.top())); //Далее проверяется, что после обработки всех токенов ожидается операнд и что в выходной очереди больше одного элемента
        operatorStack.pop();
    }

    if (expectOperand && !outputQueue.empty() && outputQueue.size() < 2) 
    {
        throw std::runtime_error("Incomplete expression: " + expression); //выбрасывается исключение о неполном выражении.
    }

    while (!outputQueue.empty()) // из очереди извлекаются токены и добавляются в переменную типа stringstream в виде строки с пробелом в конце.
    {
        postfix << outputQueue.dequeue() << " "; 
    }

    
    return postfix.str(); //Возвращается строковое представление постфиксной записи.
}

bool Parser::isOperator(char c) const //Метод isOperator проверяет, является ли заданный символ математическим оператором
{
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int Parser::getPrecedence(char c) const //метод getPrecedence возвращает приоритет оператора.
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