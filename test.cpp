#include <iostream>
#include <stdexcept>
#include <windows.h>
#include "io.h"
#include "test.h"

/************ Sorting algorithms ***************/
#include "sortingAlgorithms\bubbleSort.h"
#include "sortingAlgorithms\shellSort.h"
#include "sortingAlgorithms\quickSort.h"
#include "sortingAlgorithms\radixSort.h"
#include "sortingAlgorithms\heapSort.h"

/********** String search algorithms ***********/
#include "stringSearchAlgorithms\boyerMoore.h"
#include "stringSearchAlgorithms\kmp.h"
#include "stringSearchAlgorithms\rabinKarp.h"

/*************** Data structures ***************/
#include "dataStructures\stack.h"
#include "dataStructures\queue.h"
#include "dataStructures\deque.h"
#include "dataStructures\avlTree.h"

/*********** Normal Polish Notation ************/
#include "polishNotation\polishNotation.h"

using namespace std;


// Тестирование алгоритмов сортировки
void testSort()
{
	SetConsoleTitle("TEST: Sorting Algorithms"); // Заголовок окна
	system("cls"); // Очистка экрана

	// Сообщение с подсказкой
	const char *helpMsg = "Help message:\n\
	0 - Bubble Sort\n\
	1 - Shell Sort\n\
	2 - Quick Sort\n\
	3 - Radix Sort\n\
	4 - Heap Sort\n\
	q - Back to Main menu";


	char action = NULL; // Действие

	while (action != 'q') // Пока не ввели q
	{
		switch (action)
		{
		case '0': // Сортировка пузырьком
			sortWrap(bubbleSort); 
			break;
		case '1': // Сортировка Шелла
			sortWrap(shellSort);
			break;
		case '2': // Быстрая сортировка
			sortWrap([](int *arr, int length) { quickSort(arr, length, 0); });
			break;
		case '3': // Поразрядная сортировка
			sortWrap(radixSort);
			break;
		case '4': // Пирамидальная сортировка
			sortWrap(heapSort);
			break;
		default: // Ничего из выше перечисленного
			cout << helpMsg; // Вывести сообщение с подсказкой
		}

		while (cin.get() != '\n'); // Очистка потока ввода
		cout << endl << endl << "Select: ";
		cin >> action; // Считывание действия
	}
}

/* Обертка для функции сортировки (декоратор)
 * Принимает алгоритм (ф-ю сортировки)         */
void sortWrap(void sort(int *, int))
{
	int length; // Кол-во эл-в
	cout << "Number of elements: ";
	cin >> length;

	cout << "Your array: ";
	int *arr = inputArray(length); // Формирование массива

	sort(arr, length); // Сортировка массива переданным методом

	cout << "Sorted array: ";
	printArray(arr, length); // Вывод массива через пробел
}


// Тестирование алгоритмов поиска подстроки в строке
void testStringSearch()
{
	SetConsoleTitle("TEST: String Search algorithms"); // Заголовок консоли
	system("cls"); // Очистка экрана

	// Сообщение с подсказкой
	const char *helpMsg = "Help message:\n\
	0 - Knuth-Morris-Pratt string searching algorithm\n\
	1 - Boyer-Moore string search algorithm\n\
	2 - Rabin-Karp string search algorithm\n\
	q - Back to Main menu";


	char action = NULL; // Действие

	while (action != 'q') // Пока не ввели q
	{
		switch (action)
		{
		case '0': // Алгоритм Кнута-Морриса-Пратта
			stringSearchWrap(kmp);
			break;
		case '1': // Алгоритм Бойера-Мура
			stringSearchWrap(boyerMoore);
			break;
		case '2': // Алгоритм Рабина-Карпа
			stringSearchWrap(rabinKarp);
			break;
		default: // Ничего из выше перечисленного
			cout << helpMsg; // Вывод сообщения с подсказкой
		}

		cout << endl << endl << "Select: ";
		cin >> action; // Считывание действия
		while (cin.get() != '\n'); // Очистка потока ввода
	}
}

/* Обертка для функции поиска подстроки в строке (декоратор)
 * Принимает алгоритм (ф-ю поиска)                            */
void stringSearchWrap(List *searchFunc(char *, char *))
{
	char haystack[255]; // Строка
	char needle[255];   // Шаблон

	cout << "string: ";
	cin.getline(haystack, 255); // Считываем строку
	cout << "template: ";
	cin.getline(needle, 255);   // Считываем шаблон

	// Поиск подстроки в строке переданным алгоритмом
	List *entry = searchFunc(haystack, needle);

	// Индексы всех вхождений через пробел
	cout << "Entry: ";
	if (entry->len() != 0)
		for (const auto &en : *entry)
			cout << *en.data << ' ';
	else
		cout << "Empty";
}


// Тестирование Структур данных
void testDataStruct()
{
	SetConsoleTitle("TEST: Data structures"); // Заголовок консоли
	system("cls"); // Очистка экрана
	
	// Сообщение с подсказкой
	const char *helpMsg = "Help message:\n\
	0 - Stack\n\
	1 - Queue\n\
	2 - Deque\n\
	3 - AVL-Tree\n\
	q - Back to Main menu";


	char action = NULL; // Действие

	while (action != 'q') // Пока не равно q (завершение)
	{
		switch (action)
		{
		case '0': // Тестирование Стека
			SetConsoleTitle("TEST: Data structures: Stack"); // Новый заголовок
			system("cls"); // Очистка консоли

			testStack(); // Тестирование очереди

			SetConsoleTitle("TEST: Data structures"); // Возвращаем заголовок
			system("cls"); // Очистка консоли

			cout << helpMsg; // Сообщение с подсказкой
			break;
		case '1': // Тестирование Очереди
			SetConsoleTitle("TEST: Data structures: Queue"); // Новый заголовок
			system("cls"); // Очистка консоли

			testQueue(); // Тестирование Очереди

			SetConsoleTitle("TEST: Data structures"); // Возвращаем заголовок
			system("cls"); // Очистка консоли

			cout << helpMsg; // Сообщение с подсказкой
			break;
		case '2': // Тестирование Дека
			SetConsoleTitle("TEST: Data structures: Deque"); // Новый заголовок
			system("cls"); // Очистка консоли

			testDeque(); // Тестирование Дека

			SetConsoleTitle("TEST: Data structures"); // Возвращаем заголовок
			system("cls"); // Очистка консоли

			cout << helpMsg; // Сообщение с подсказкой
			break;
		case '3': // Тестирование АВЛ-дерева
			SetConsoleTitle("TEST: Data structures: AVL-Tree"); // Новый заголовок
			system("cls"); // Очистка консоли

			testAVLTree(); // Тестирование АВЛ-дерева

			SetConsoleTitle("TEST: Data structures"); // Возвращаем заголовок
			system("cls"); // Очистка консоли

			cout << helpMsg; // Сообщение с подсказкой
			break;
		default: // Ничего из выше перечисленного
			cout << helpMsg; // Сообщение с подсказкой
		}

		cout << endl << endl << "Select: ";
		cin >> action; // Считывание действия
		cin.ignore(); // Очистка ввода (след алгоритмы будут считывать строку (до \n))
	}
}

// Тестирование Стека
void testStack()
{
	// Сообщение с подсказкой
	const char *helpMsg = "Help message:\n\
	push N    - put N at the top of the Stack\n\
	peek      - Element at the top of the Stack\n\
	pop       - Remove element from the top of the Stack\n\
	clear     - Remove all elements from Stack\n\
	len       - Number of elements in the stack\n\
	h or help - Show this message again\n\
	q or quit - Back to Data struct menu";

	Stack<int> stack; // Стек целых чисел
	string action = "h"; // Действие по умолчанию

	while (action != "q" && action != "quit") // Пока действие не q или quit
	{
		try
		{
			if (action == "push") // push - добавление в стек
			{
				int data; // эл-т для добавления

				cin >> data;
				stack.push(data); // Добавление эл-та
			}
			else if (action == "peek") // peek - Просмотр эл-та на вершине стека
				cout << "Output: " << stack.peek() << endl;
			else if (action == "pop") // pop - Просмотр и удаление эд-та на вершине стека
				cout << "Output: " << stack.pop() << endl;
			else if (action == "clear") // clear - очистка стека
				stack.clear();
			else if (action == "len") // len - кол-во эл-в в стеке
				cout << "Output: " << stack.len() << endl;
			else if (action == "h" || action == "help") // Запрос сообщения с подсказкой
				cout << helpMsg << endl;
			else // Неизвестное действие
			{
				while (cin.get() != '\n'); // Очистка потока ввода
				cout << "Error: Unknown command. Use \"h\" or \"help\" to get help message." << endl;
			}
		}
		catch (exception &e) // Если возникла ошибка
		{
			cout << "Error: " << e.what() << endl;
		}

		cout << endl << "Input: ";
		cin >> action; // Считывание действия
	}
}

// Тестирование Очереди
void testQueue()
{
	// Сообщение с подсказкой
	const char *helpMsg = "Help message:\n\
	put N     - put N in a Queue\n\
	peek      - First element in the Queue\n\
	get       - Remove element from the Queue\n\
	clear     - Remove all elements from Queue\n\
	h or help - Show this message again\n\
	q or quit - Back to Data struct menu";

	Queue<int> queue; // Очередь целых чисел
	string action = "h"; // Действие по умолчанию

	while (action != "q" && action != "quit") // Пока действие не q или quit
	{
		try
		{
			if (action == "put") // put - добавление эл-та в очередь
			{
				int data; // Эл-т для добавления

				cin >> data;
				queue.put(data); // Добавление эл-та в очередь
			}
			else if (action == "peek") // peek - Просмотр первого в очереди эл-та
				cout << "Output: " << queue.peek() << endl;
			else if (action == "get") // get - Взятие первого эл-та из очереди
				cout << "Output: " << queue.get() << endl;
			else if (action == "clear") // clear - Очистка очереди
				queue.clear();
			else if (action == "h" || action == "help") // Запрос сообщения с подсказкой
				cout << helpMsg << endl;
			else // Ничего из выше перечисленного
			{
				while (cin.get() != '\n'); // Очистка потока ввода
				cout << "Error: Unknown command. Use \"h\" or \"help\" to get help message." << endl;
			}
		}
		catch (exception &e) // Если возникла ошибка
		{
			cout << "Error: " << e.what() << endl;
		}

		cout << endl << "Input: ";
		cin >> action; // Считываем действие
	}
}

// Тестирование Дека (двойной/двусторонней очереди)
void testDeque()
{
	// Сообщение с подсказкой
	const char *helpMsg = "Help message:\n\
	append     - Put element at the right end of the Deque\n\
	appendleft - Put element at the left end of the Deque\n\
	clear      - Remove all elements from Deque\n\
	peek       - Element at the right end of the Deque\n\
	peekleft   - Element at the left end of the Deque\n\
	pop        - Remove element from the right end of the Deque\n\
	popleft    - Remove element from the left end of the Deque\n\
	h or help  - Show this message again\n\
	q or quit  - Back to Data struct menu";

	Deque<int> deque; // Дек целых чисел
	string action = "h"; // Действие по умолчанию

	while (action != "q" && action != "quit") // Пока действие не q или quit
	{
		try
		{
			if (action == "append") // append - Добавить в Дек справа
			{
				int data; // Эл-т для добавления

				cin >> data;
				deque.append(data); // Добавление эл-та в правый конец дека
			}
			else if (action == "appendleft") // appendleft - Добавить в Дек слева
			{
				int data; // Эл-та для добавления

				cin >> data;
				deque.appendleft(data); // Добавление эл-та в левый конец дека
			}
			else if (action == "clear") // clear - Очистка дека
				deque.clear();
			else if (action == "peek") // peek - Просмотр правого эл-та дека
				cout << "Output: " << deque.peek() << endl;
			else if (action == "peekleft") // peekleft - Просмотр левого эл-та дека
				cout << "Output: " << deque.peekleft() << endl;
			else if (action == "pop") // pop - Удаление правого эл-та дека
				cout << "Output: " << deque.pop() << endl;
			else if (action == "popleft") // popleft - Удаление левого эл-та дека
				cout << "Output: " << deque.popleft() << endl;
			else if (action == "h" || action == "help") // Запрос сообщения с подсказкой
				cout << helpMsg << endl;
			else // Ничего из выше перечисленного
			{
				while (cin.get() != '\n'); // Очистка потока ввода
				cout << "Error: Unknown command. Use \"h\" or \"help\" to get help message." << endl;
			}
		}
		catch (exception &e) // Если возникла ошибка
		{
			cout << "Error: " << e.what() << endl;
		}

		cout << endl << "Input: ";
		cin >> action; // Считываем действие
	}
}

// Тестирование АВЛ-дерева
void testAVLTree()
{
	// Сообщение с списком допустимых команд
	char helpMsg[] = "Help message:\n\
	append N  - Add number to AVL-Tree\n\
	remove N  - Removing N from Tree\n\
	print     - Printing Tree(recommended only for small trees)\n\
	clear     - Clear tree\n\
	h or help - Show this message again\n\
	q or quit - Quit";


	Tree<int> tree; // Дерево
	string action = "h"; // Действие

	while (action != "q" && action != "quit") // Пока действие != q или quit (завершение работы)
	{
		if (action == "append") // Добавление
		{
			int data; // Эл-т для добавления
			cin >> data;

			tree.append(data); // Добавление эл-та
		}
		else if (action == "remove") // Удаление
		{
			int data; // Эл-та для удаления
			cin >> data;

			tree.remove(data); // Удаления эл-та
		}
		else if (action == "clear") // Очистка
			tree.clear();
		else if (action == "print") // Вывод
		{
			cout << "Output:" << endl << endl;
			printTree(tree); // Вывод дерева
			cout << endl;
		}
		else if (action == "h" || action == "help") // Вывод вспомогательного сообщения
			cout << helpMsg << endl;
		else
		{
			while (cin.get() != '\n'); // Очистка потока ввода
			cout << "Error: Unknown command. Use \"h\" or \"help\" to get help message." << endl;
		}

		cout << endl << "Input: ";
		cin >> action; // Считываем действие (одно слово)
	}
}


// Тестирование Польской нотации
void testPN()
{
	SetConsoleTitle("TEST: Polish Notation"); // Заголовок консоли
	system("cls"); // Очистка консоли

	// Сообщение с подсказкой
	const char *helpMsg = "Syntax:\n\
	Built-in Operators: + - * / ^ ( )\n\
	Statment sin + 2 : sin - variable\n\
	Statment sin(2)  : sin - function\n\
	(variable and function names should be [a-zA-Z])\n\
	Spacing and recurring brackets is not improtant:\n\
		cos(2) ~ cos ( (2 ))  and  5+5 ~ 5 +5\n\
	Unary minus : -5 ~ 0 - 5  and  2 + (-3) ~ 2 + (0 - 3)\n\
	h or help : Show this message again\n\
	q or quit : Back to Main menu";


	cin.ignore(); // Очистка потока ввода
	char expr[255] = "h"; // Выражение (Первый раз выведется сообщение с подсказкой)
	while (strcmp(expr, "q") && strcmp(expr, "quit")) // Пока пользователь не ввел q или quit
	{
		// Вывод сообщения с подсказкой
		if (!strcmp(expr, "h") || !strcmp(expr, "help"))
			cout << helpMsg << endl << endl;
		else if (expr[0] != '\0') // Если выражение не пустое
		{
			cout << "Polish Notation: ";

			try
			{
				cout << toPN(expr) << endl << endl; // Перевод в Польскую Нотацию
			}
			catch (exception &e) // Если произошла ошибка
			{
				cout << e.what() << endl << endl; // Вывести ее пользователю
			}
		}

		cout << "Your expression: ";
		cin.getline(expr, 255); // Выражение пользователя
	}
}