#include <iostream>
#include <string>
#include "PostfixCalculator.h"

PostfixCalculator::PostfixCalculator() = default;

int PostfixCalculator::calculate(std::string expression) //Метод calculate получает на вход выражение в виде строки, после чего выполняет последовательные операции с помощью стека
{
    int number = 0; 

    for (char& c : expression) //Он содержит цикл, который проходит по каждому символу строки и выполняет соответствующие действия.
    {
        if (std::isdigit(c)) //Если текущий символ является цифрой, то он добавляется к текущему числу, 
            //которое представляет собой последнюю часть выражения после последнего пробела
        {
            number = number * 10 + (c - '0'); 
        }
        else if (c == ' ') //Если текущий символ - пробел, а number не равен 0, то число помещается в стек
        {
            if (number != 0) 
            {
                stack.push(number);
                number = 0; 
            }
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/') //Если же текущий символ - один из операторов (+, -, *, /),
            //то из стека извлекаются два последних операнда (operand_1 и operand_2), и выполняется соответствующая операция. 
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
            stack.push(result); //Результат затем помещается в стек.
        }
        else if (c == ' ')  //сли текущий символ - пробел, то он просто игнорируется
        {

        }
        else //Если текущий символ не является ни цифрой, ни пробелом, ни оператором, то возникает исключение с сообщением об ошибке.
        {
            throw std::runtime_error("Invalid expression. Try again.");
        }
    }
    //После того, как цикл пройдет по всем символам строки, выполняется проверка размера стека stack
   
    if (stack.size() != 1) //Если он не равен 1, то возникает исключение с сообщением об ошибке.
    {
        throw std::runtime_error("Invalid expression. Try again.");
    }

    return stack.top(); //В конце метода возвращается верхний элемент стека, который является результатом вычислений.
}