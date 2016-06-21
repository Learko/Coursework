/* Сортировка Вставками
 * На вход массив, кол-во эл-в, сдвиг, шаг */
void insertSort(int *Arr, int n, int shift = 0, int step = 1)
{
	for (int i = shift + step; i < n; i += step) // Шаг через к-й нужно брать эл-ты
	{
		int j = i;         // Индекс текущего эл-та
		int key = Arr[i];  // Запоминаем значение эл-та

		// Сдвигаем значения в массиве до тех пор пока не найдем место для key
		while (key < Arr[j - step] && j > shift)
		{
			Arr[j] = Arr[j - step]; // Сдвигаем эл-т
			j -= step; // Индекс пред эл-та
		}

		// Вставляем значение в нужное место в массиве
		Arr[j] = key;
	}
}


/* Сортировка Шелла
 * На вход массив и кол-во эл-в */
void shellSort(int *Arr, int n)
{
	for (int step = n / 2; step > 0; step /= 2) // Шаг с к-м нужно перебирать эл-ты
		for (int shift = 0; shift < step; shift++) // Сдвиг
			insertSort(Arr, n, shift, step); // Сортируем часть эл-в вставками
}
