#include <utility>


/* Частичное просеивание сверху вниз (по одной ветке)        *
 * На вход указатель на первый эл-т массива, кол-во эл-в     *
 * и индекс родителя, с которого нужно начинать просеивание  */
void shiftDown(int *Arr, int length, int parentIndex = 0)
{
	int leftChildIndex = 2 * parentIndex + 1; // Индекс левого ребенка
	int rightChildIndex = leftChildIndex + 1; // Индекс правого ребенка (2 * parentIndex + 2)

	// Если правый ребенок существует( => существует и левый)
	if (rightChildIndex < length)
	{
		// Если левый ребенок больше правого и больше родителя
		if (Arr[leftChildIndex] > Arr[rightChildIndex] && Arr[leftChildIndex] > Arr[parentIndex])
		{
			std::swap(Arr[leftChildIndex], Arr[parentIndex]); // Меняем их местами
			shiftDown(Arr, length, leftChildIndex);           // Просеиваем по одной ветке вниз
		}
		// Иначе, если правый ребенок больше родителя
		else if (Arr[rightChildIndex] > Arr[parentIndex])
		{
			std::swap(Arr[rightChildIndex], Arr[parentIndex]); // Меняем их местами
			shiftDown(Arr, length, rightChildIndex);           // Просеиваем по одной ветке вниз
		}
	}
	// Если правого не существует(последний эл-т в дереве) тогда
	// Если левый ребенок сущ-т и больше родителя
	else if (leftChildIndex < length && Arr[leftChildIndex] > Arr[parentIndex])
		std::swap(Arr[leftChildIndex], Arr[parentIndex]); // Меняем их местами
}


/* Полное просеивание снизу вверх
 * На вход указатель на первый эл-т массива и кол-во эл-в */
void shiftUp(int *Arr, int length)
{
	// Перебираем все вершины, у к-х есть хотя бы 1 ребенок
	for (int parentIndex = length / 2 - 1; parentIndex >= 0; parentIndex--)
	{
		int leftChildIndex = 2 * parentIndex + 1; // Индекс левого ребенка
		int rightChildIndex = leftChildIndex + 1; // Индекс правого ребенка (2 * parentIndex + 2)

		int leftChild = Arr[leftChildIndex]; // Значение левого ребенка
		int rightChild; // Значение правого ребенка

		// Если правый ребенок сущ-т тогда берем его значение, иначе берем значение левого - 1
		(rightChildIndex < length) ? rightChild = Arr[rightChildIndex] : rightChild = leftChild - 1;

		// Если значение левого больше правого(правый сущ-т) и больше родителя
		if (leftChild > rightChild && leftChild > Arr[parentIndex])
		{
			std::swap(Arr[leftChildIndex], Arr[parentIndex]); // Меняем их местами
			shiftDown(Arr, length, leftChildIndex);           // Просеиваем по одной ветке вниз
		}
		// Иначе, если правый больше родителя
		else if (rightChild > Arr[parentIndex])
		{
			std::swap(Arr[rightChildIndex], Arr[parentIndex]); // Меняем их местами
			shiftDown(Arr, length, rightChildIndex);           // Просеиваем по одной ветке вниз
		}
	}
}


/* Пирамидальная сортировка
 * На вход указатель на первый эл-т массива и кол-во эл-в */
void heapSort(int *Arr, int length)
{
	shiftUp(Arr, length); // Полное просеивание снизу вверх
	std::swap(Arr[0], Arr[length - 1]); // Вытаскиваем наибольший(первый) эл-т в конец

	// На каждой итерации цикла вытаскиваем наибольший эл-т в конец
	// и уменьшаем длину рассматриваемого массива
	for (int len = length - 1; len > 0; len--)
	{
		shiftDown(Arr, len); // Частичное просеивание вниз по одной ветке
		std::swap(Arr[0], Arr[len - 1]); // Вытаскиваем наибольший(первый) эл-т в конец
	}
}
