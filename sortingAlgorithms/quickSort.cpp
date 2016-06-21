#include <stdexcept>


/* Быстрая сортировка
 * Принимает указатель на первый эл-т массива, длину массива 
 * start - дополнительный параметр, для сортировки подмассивов
 * (индекс эл-а с к-го нужно начать сортировку необходим для рекурсивного выхова этой ф-ии) */
void quickSort(int *Arr, int length, int start = 0)
{
	// Если кол-во эл-в отрицательное значение, 
	if (length < 0)
		throw std::out_of_range("Negative value of length");

	else if (length > 2)
	{
		/* Поиск эл-та для разбиения
		 * Сортируем 0, length / 2 и length эл-ты
		 * Выбираем эл-т length / 2(0 <= length/2 <= length) за опорное значение */
		int mid = start + length / 2;
		int end = start + length - 1;
		if (Arr[start] > Arr[mid])
			std::swap(Arr[start], Arr[mid]);
		if (Arr[mid] > Arr[end])
			std::swap(Arr[mid], Arr[end]);
		if (Arr[start] > Arr[mid])
			std::swap(Arr[start], Arr[mid]);

		int borderStart = mid;         // Индекс начала границы
		int borderEnd = borderStart;   // Индекс последнего эл-та границы
		int border = Arr[borderStart]; // Опорное значение

		// Перестановка
		int i = start;
		while (i <= end) // Идем до конца массива
		{
			// Если эл-т попал на границу, сразу переходим к концу границы
			if (i == borderStart)
				i = borderEnd + 1;

			else if (i < borderStart) // Если эл-т стоит слева от границы
			{
				/* Если эл-т больше опорного и находится слева от границы,
				 * перемещаем его в правую часть
				 * Меняем его с эл-том стоящим до границы
				 * и затем с эл-м последним в границе
				 * тем самым смещая границу на 1 влево */
				if (Arr[i] > border)
				{
					int tmp = Arr[i];
					Arr[i] = Arr[borderStart - 1];
					Arr[borderStart - 1] = Arr[borderEnd];
					Arr[borderEnd] = tmp;

					borderStart--;
					borderEnd--;
				}
				/* Если эл-т равен опорному и находится слева от границы,
				 * Меняем его с эл-том стоящим до границы
				 * Уменьшаем индекс первого эл-та границы */
				else if (Arr[i] == border)
				{
					std::swap(Arr[i], Arr[borderStart - 1]);
					borderStart--;
				}
				else
					i++; // Эл-т стоит на "своем" месте смотрим на следующий
			}
			else if (i > borderEnd) // Если эл-т стоит справа от границы
			{
				/* Если эл-т меньше опорного и находится справа от границы,
				 * перемещаем его в левую часть
				 * Меняем его с эл-том стоящим после границы
				 * и затем с первым опорным эл-м
				 * тем самым сдвигая границу на 1 вправо */
				if (Arr[i] < border)
				{
					int tmp = Arr[i];
					Arr[i] = Arr[borderEnd + 1];
					Arr[borderEnd + 1] = Arr[borderStart];
					Arr[borderStart] = tmp;

					borderStart++;
					borderEnd++;
				}
				/* Если эл-т равен опорному и находится справа от границы,
				 * Меняем его с эл-том стоящим после границы
				 * и увеличиваем длину границы(увеличиваем индекс конца границы) */
				else if (Arr[i] == border)
				{
					std::swap(Arr[i], Arr[borderEnd + 1]);
					borderEnd++;
				}

				i++; // Эл-т стоит на "своем" месте смотрим на следующий
			}
		}

		quickSort(Arr, borderStart - start, start);     // Сортировка эл-в до границы
		quickSort(Arr, end - borderEnd, borderEnd + 1); // Сортировка эл-в после границы
	}
	else if (length == 2 && Arr[start] > Arr[start + 1])
		std::swap(Arr[start], Arr[start + 1]); // Если эл-та два, наибольший ставим на 1-е место
	// Если length == 1 или 0 тогда этот подмассив отсортирован
}
