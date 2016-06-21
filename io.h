#pragma once
#include "dataStructures\avlTree.h"
#include "dataStructures\list.h"


/* Ввод массива, на вход кол-во эл-в, возвращает указать на первый эл-т
 * Длина должна быть > 0     */
int * inputArray(int n);


/* Вывод массива, на вход кол-во эл-в, указатель на первый эл-т, разделитель
 * Во избежание ошибок, переданная длина массива должна быть не больше
 * реального размера массива     */
void printArray(int *arr, int length, char *sep = " ");


// Вывод списка, в том числе пустого
void printList(List list);


//Вывод дерева, в том числе пустого
template <typename T>
void printTree(Tree<T> tree)
{
	if (tree.getHeight())
	{
		HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE); // Структура для работы с текущей консолью
		CONSOLE_SCREEN_BUFFER_INFO csbi; // Структура с информацией от текущем состоянии консоли
		GetConsoleScreenBufferInfo(hStdout, &csbi); // Состояние текущей консоли
		COORD cPos = csbi.dwCursorPosition; // Текущие координаты курсора

		cout << tree.getData(); // Выводим значение в вершине

		if (tree.toLeft() && tree.toRight()) // Если есть оба потомка
		{
			cPos.Y++; // переход на новую строку
			SetConsoleCursorPosition(hStdout, cPos);
			cout << '|';

			cPos.Y++; // переход на новую строку
			SetConsoleCursorPosition(hStdout, cPos);
			cout << "+ -- "; // Для правого ребенка

			// (до этого сдвинулись на 5 выводя ребро)
			cPos.X += 5; // Рекурсивный вывод правого потомка
			printTree(*tree.toRight());
			cPos.X -= 5; // Отходим назад

			GetConsoleScreenBufferInfo(hStdout, &csbi); // Состояние консоли
			COORD curCPos; // Текущее положение курсора
			curCPos.Y = csbi.dwCursorPosition.Y; // Текущее положение курсора по оси У
			
			while (cPos.Y < curCPos.Y + 1) // Выводим левое ребро
			{
				cPos.Y++; // Переход на новую строку
				SetConsoleCursorPosition(hStdout, cPos);
				cout << '|';
			}

			cPos.Y++; // Переход на новую строку
			SetConsoleCursorPosition(hStdout, cPos);

			printTree(*tree.toLeft()); // Вывод правого
		}
		else if (tree.toRight()) // Если есть только правый потомок
		{
			cPos.Y++; // Переход на новую строку
			SetConsoleCursorPosition(hStdout, cPos);
			cout << '|'; // Вывод ребра

			cPos.Y++; // Переход на новую строку
			SetConsoleCursorPosition(hStdout, cPos);
			
			cout << "- -- " << tree.toRight()->getData(); // Вывод одного правого ребра
		}
		else if (tree.toLeft()) // Если есть только левый
		{
			cPos.Y++; // Переход на новую строку и вывод ребра
			SetConsoleCursorPosition(hStdout, cPos);
			cout << '|';

			cPos.Y++; // Переход на новую строку и вывод эл-та
			SetConsoleCursorPosition(hStdout, cPos);
			cout << tree.toLeft()->getData();
		}
	}
}
