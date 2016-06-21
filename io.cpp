#include <iostream>
#include "dataStructures\list.h"

using namespace std;


/* Ввод массива, на вход кол-во эл-в, возвращает указать на первый эл-т
 * Длина должна быть > 0     */
int * inputArray(int length)
{
	int *arr = new int[length]; // Выделение памяти
	for (int i = 0; i < length; i++) // Ввод
		cin >> arr[i];

	return arr; // Возвращает указатель на первый эл-т массива
}


// Вывод массива, на вход указатель на первый эл-т, кол-во эл-в, разделитель
void printArray(int *arr, int length, char *sep = " ")
{
	if (length > 0)
	{
		for (int i = 0; i < length - 1; i++)
			cout << arr[i] << sep;
		cout << arr[length - 1];
	}
}


// Вывод списка
void printList(List list)
{
	for (auto it : list)
		std::cout << *it.data << ' ';
}
