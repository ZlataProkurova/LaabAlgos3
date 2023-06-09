#include <iostream>
#include "InfixCalculator.h"

int main()
{ 
    setlocale(LC_ALL, "Russian");

    InfixCalculator infixCalculator;
    std::string expression;
    int result;

    std::cout << "Введите выражение в инфиксной форме для вычисления: " << std::endl;
    std::getline(std::cin, expression); 
    while (expression != "выход")
    {
        try {
            result = infixCalculator.calculate(expression);
            std::cout << "Результат: " << result << std::endl;
        }
        catch (std::runtime_error& e)
        {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
        catch (...) {
            std::cout << "Ошибка, неправильный формат записи" << std::endl;
        }
        std::cout << "Чтобы выйти из программы, введите 'выход' или введите другое выражение : " << std::endl;
        std::getline(std::cin, expression);

        return 0;
    }
}