#include <iostream>
#include <exception>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "..\dataStructures\stack.h"

using namespace std;


/**************************************************************************************************
 * Перевод выражения в нормальную Польскую нотацию                                                *
 *                                                                                                *
 * Описание алгоритма:                                                                            *
 * Проходим по строке от начала до конца, разбивая на лексемы,                                    *
 * и добавляем их в стек выражений(лексем) (exprStack)                                            *
 * т.о. на вершине стека окажется последняя в строке лексема.                                     *
 * В это же время, функции(все слова после которых идет скобка)                                   *
 * добавляем в множество функций, а переменные(скобки нет)                                        *
 * в множество переменных.                                                                        *
 *                                                                                                *
 * Записываем все функции к операторам, с приоритетом 3                                           *
 * (сразу до операторов - скобок)                                                                 *
 *                                                                                                *
 * Далее работаем со стеком выражений, т.е. начиная с конца строки.                               *
 * Если вытащили число или переменную - сразу записываем на результирующий стек,                  *
 * Если встретили оператор, проверяем не является ли он унарным минусом,                          *
 * если является - преобразуем его в вид  0 - N (достаточно добавить в результируюший стек 0)     *
 * Затем вытаскиваем все(или до 1-й скобки) операторы с бОльшим приоритетом                       *
 * Если при этом встретили открывющую скобку(закрывющая просто складывается на стек операторов)   *
 * Вытаскиваем все операторы до закрывающей скобки.                                               *
 * т.о. в стеке операторов могут лежать закрывающиеся скобки, но открывающиеся - никогда          *
 *                                                                                                *
 * Когда стек выражений стал пуст, вытаскиваем оставшиеся операторы в результирующий стек.        *
 * Стек используется для того чтобы не дописывать в начало строки                                 *
 * (в стеке выражений, выражениея(лексемы) идут в обратном порядке)                               *
 *                                                                                                *
 * Переводим стек(разворачиваем его) в строку и возвращаем ее                                     *
 *************************************************************************************************/
char *toPN(string expr)
{
	// Приоритеты операций
	unordered_map<string, uint8_t> operators = {
		{ "+" , 0 },  { "-" , 0 },
		{ "*" , 1 },  { "/" , 1 },
		{ "^" , 2 },
		{ "(" , 4 },  { ")" , 4 }
	};
	
	unordered_set<string> functions; // Множество функций
	unordered_set<string> variables; // Множество переменных


	// Стек выражений
	// Разбираем переданное выражение на составляющие
	Stack<string> exprStack;

	string tmp; // Вспомогательная строка
	for (size_t i = 0; i < expr.length(); i++)
	{
		// Допустимы только ASCII символы
		if (expr[i] < 0 || expr[i] > 255)
			throw exception("Only ASCII symbols accepted");
		// Если встречена цифра
		if (isdigit(expr[i]))
		{
			// Считываем все цифры
			while (isdigit(expr[i]))
				tmp += expr[i++];

			i--; // Уменьшаем счетчик т.к. в цикле сдвинулись лишний раз
			exprStack.push(tmp); // Складывем полученое число на стек выражений
 			tmp.clear(); // Очищаем строку содержащую число
		}
		/* Если встречен один из операторов.
		 * expr[i] - символ, но в operators хранятся строки
		 * запись вида { expr[i] } вынужденная необходимость для поиска совпадений */
		else if (operators.find({ expr[i] }) != operators.end())
		{
			tmp = expr[i]; // Записываем оператор в строку
			exprStack.push(tmp); // Добавляем оператор на стек
			tmp.clear(); // Очищаем строку
		}
		// Если встречена буква
		else if (isalpha(expr[i]))
		{
			while (isalpha(expr[i])) // Считываем все слово целиком
				tmp += expr[i++];
			
			while (isspace(expr[i])) // Пропускаем все пробелы
				i++;
			if (expr[i] == '(') // Если след. символ - скобка
				functions.insert(tmp); // Значит встречена функция
			else
				variables.insert(tmp); // Иначе переменная

			i--; // Отходим на символ назад(до этого был лишний переход)
			exprStack.push(tmp); // Добавляем операнд в стек выражений
			tmp.clear(); // Очищаем строку
		}
		else if (!isspace(expr[i])) // Если встречен другой символ и не пробел
		{
			throw exception("Syntax Error!"); // Синтаксическая ошибка
		}
	}

	
	for (auto func : functions) // Задаем приоритет функций (наибольший, но до скобок)
		operators[func] = 3;

	Stack<string> resultStack; // Результируюший стек
	Stack<string> opStack;     // Стек операций

	tmp.clear(); // Очищаем строку, для дальнейшего использования
	while (exprStack.len()) // Пока стек не пуст
	{
		tmp = exprStack.pop(); // Вытаскиваем операнд или оператор из стека

		if (isdigit(tmp[0])) // Если первый символ - цифра => это число
			resultStack.push(tmp); // Можно сразу записывать в результирующий стек
		else if (variables.find(tmp) != variables.end()) // Аналогично, если переменная
			resultStack.push(tmp);
		else if (operators.find(tmp) != operators.end()) // Если это оператор
		{
			// Унарный минус
			// Если встречен минус, а до него ничего нет или скобка
			if (tmp == "-" && (!exprStack.len() || exprStack.peek() == "("))
				resultStack.push("0"); // Добавить 0 в результирующий стек


			int opPriority = operators[tmp]; // Приоритет операции

			// Пока стек не пуст и след. эл-т не закрывающаяся скобка и приоритет в стеке больше текущего
			while (opStack.len() && opStack.peek() != ")" && operators[opStack.peek()] > opPriority)
				resultStack.push(opStack.pop()); // Вытаскиваем эл-ты в результирующий стек

			if (tmp != "(") // Если встречена открывающая скобка
				opStack.push(tmp); // Добавляем оператор на стек операций
			else
			{
				while (opStack.peek() != ")") // Пока не встретили закрывающую скобку
					resultStack.push(opStack.pop()); // Переносим все эл-ты в результирующий стек
				opStack.pop(); // Вытаскиваем закрывающую скобку
			}
		}
	}
	
	// Стек выражений закончился, Вытаскиваем все операторы в результирующий стек
	while (opStack.len())
		resultStack.push(opStack.pop());

	// Записываем результат в строку через пробел
	string result;
	while (resultStack.len())
		result += resultStack.pop() + ' ';

	// Возвращаем строку преобразованную в char *
	return _strdup(result.c_str());
}