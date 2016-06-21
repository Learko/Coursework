#include <iostream>
#include <windows.h>
#include "test.h"

using namespace std;


/**********************************************************
 *** Главное Меню программы для Тестирования алгоритмов ***
 **********************************************************
 *                 *        ***        *                  *
 * Тестируемые алгоритмы были разбиты на категории:       *
 * - Алгоритмы сортировки:                                *
 * - - Сортировка пузырьком                               *
 * - - Сортировка Шелла                                   *
 * - - Быстрая Сортировка                                 *
 * - - Поразраядная Сортировка                            *
 * - - Пирамидальная Сортировка                           *
 * - Алгоритмы поика подстроки в строке:                  *
 * - - Алгоритм Книта-Морриса-Пратта                      *
 * - - Алгоритм Бойера-Мура                               *
 * - - Алгоритм Рабина-Карпа                              *
 * - Структуры данных                                     *
 * - - Стек                                               *
 * - - Очередь                                            *
 * - - Дек (двойная/двусторонняя очередь)                 *
 * - - АВЛ-Дерево (бинарное сбалансированное)             *
 * - Польская нотация                                     *
 *                 *        ***        *                  *
 * Выбор пунктов осуществляется вводом номера пункта,     *
 * Для выхода из программы или выхода в предыдущее меню,  *
 * введите "q". Для каждого подпункта реализовано         *
 * сообщение с допустимыми командами, если команда "h"    *
 * или "help" отсутствует, для получения сообщения        *
 * достаточно ввести любую некорректную команду.          *
 *                 *        ***        *                  *
 * В программе реализована обработка исключений,          *
 * сообщения об ошибке начинаются с "Error: ",            *
 * но в случае возникновения непредвиденной ситуации:     *
 * Для экстренного выхода из программы нажмите Ctrl+C     *
 *                 *        ***        *                  *
 **********************************************************/
int main()
{
	// Сообщение с подсказкой
	const char *helpMsg = "Help message:\n\
	0 - Test sorting algorithms\n\
	1 - Test string search alrorithms\n\
	2 - Test data structures\n\
	3 - Test Polish notation\n\
	q - Quit";


	char action = NULL; // Действие

	while (action != 'q') // Индикатор выхода
	{
		switch (action)
		{
		case '0': // Тестирование алгоритмов сортировки
			testSort();
			break;
		case '1': // Тестирование алгоритмов поиска подстроки в строке
			testStringSearch();
			break;
		case '2': // Тестирование структур данных
			testDataStruct();
			break;
		case '3': // Тестирование польской нотации
			testPN();
		}

		SetConsoleTitle("TEST: Main menu"); // Заголовок консоли
		system("cls"); // Очистка консоли
		cout << helpMsg << endl << endl; // Вывод сообщения с подсказкой

		cout << "Select: ";
		cin >> action; // Действие
	}

	return 0;
}
