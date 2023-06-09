#include "InfixCalculator.h"

int InfixCalculator::calculate(const std::string& expression) //объявляет параметр expression как ссылку на константную строку,
//чтобы избежать копирования строки при передаче в метод
{
    std::string postfix = parser.infixToPostfix(expression); //использует объект parser для преобразования инфиксного выражения в постфиксную нотацию. Результат сохраняется в переменной postfix
    result = postfixCalculator.calculate(postfix); //метод использует объект postfixCalculator для вычисления результата 
    //на основе полученной постфиксной нотации. Результат вычислений сохраняется в переменной result.
    return result; 
}
