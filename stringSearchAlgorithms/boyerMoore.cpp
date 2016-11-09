#include "boyerMoore.h"
#include "..\dataStructures\list.h"
#include "..\string.h"


/* The Bad Character Rule                                                          *
 * Генерируем таблицу Стоп Символов, на вход шаблон                                *
 * Строится таблица по следующему правилу:                                         *
 * Каждому символу алфавита(коду символа) ставится в соответствие                  *
 * индекс его последнего вхождения в шаблон(не учитывая последний символ шаблона)  *
 * Если символа алфавита нет в шаблоне, ему в соответствие ставится -1             */
int *genStopCharTable(char *needle)
{
	int *table = new int[256]; // Таблица из 256 символов(алфавит)
	for (int i = 0; i < 256; i++)
		table[i] = -1; // Заполняем -1

	// Идем до предпоследнего эл-та и записываем в ячейку с кодом символа индекс(место в шаблоне)
	for (int i = 0; needle[i + 1] != '\0'; i++)
		table[needle[i]] = i;

	return table; // Возвращаем указатель на таблицу
}

/* The Good Suffix Rule                                                     *
 * Генерируем таблицу суффиксов, на вход шаблон                             *
 * Строится таблица по следующему правилу:                                  *
 * Каждому возможному значению длинны суффикса                              *
 * ставится в соответствие значение - на сколько можно сдинуть суффикс так  *
 * чтобы суффикс совпал с последней подстрокой в шаблоне, равной суффиксу   *
 * или его последней частью                                                 */
int *genSuffixTable(char *needle)
{
	int needleLen = strlen(needle);      // Длинна шаблона
	int *table = new int[needleLen + 1]; // Таблица суффиксов

	table[0] = 1; // Если суффикс пустой, сдвиг = 1
	for (int sufflen = 1; sufflen <= needleLen; sufflen++) // Увеличиваем длинну суффкса
	{
		bool found = false; // Подстрока(суффикс) найден
		int shift; // Сдвиг
		// От начала суффикса до начала шаблона
		for (shift = needleLen - sufflen - 1; !found && shift >= 0; shift--)
		{
			if (needle[shift] == needle[needleLen - sufflen]) // Если первый символ суффикса совпал с каким-то символом до
			{
				// Считаем кол-во совпавших букв
				int match; 
				for (match = 1; needle[shift + match] == needle[needleLen - sufflen + match] && match <= sufflen; match++);

				// Если кол-во совпавших букв = длинне суффикса
				if (match == sufflen)
					found = true; // Подстрока найдена
			}
		}

		// Если найдена
		if (found)
			table[sufflen] = needleLen - sufflen - shift - 1; // Сдвиг = разность между началом суффикса и началом найденной подстроки
		else
			table[sufflen] = table[sufflen - 1]; // Если нет, то пред.
	}

	return table; // Возвращаем таблицу
}

/* Алгоритм поиска подстроки в строке Бойера-Мура             *
 * Принимает на вход: haystack - сроку и needle - шаблон      *
 * Возвращает список индексов начал всех вхождений            *
 * если шаблон отсутствует в строке, возвращает пустой список */
List *boyerMoore(char *haystack, char *needle)
{
	List *entry = new List(); // Индексы всех вхождений
	int *stopCharTable = genStopCharTable(needle); // Таблица стоп символов "The Bad Character Rule"
	int *suffixTable = genSuffixTable(needle);     // Таблица суффиксов     "The Good Suffix Rule"

	int haystackLen = strlen(haystack); // Длинна строки
	int needleLen = strlen(needle);     // Длинна шаблона
	
	int shift = 0; // Сдвиг
	while (shift <= haystackLen - needleLen) // Пока подстрока не найдена и сдвиг <= длины строки - длина шаблона
	{
		int badChar; // Индекс первого несовпавшего символа (с конца)
		for (badChar = needleLen - 1; haystack[shift + badChar] == needle[badChar] && badChar >= 0; badChar--);
		
		if (badChar == -1) // Если = -1 значит шаблон полностью совпал
		{
			*entry += shift; // Индекс = сдвигу, добавляем его в список
			shift++; // Сдвигаемся на 1
		}
		else
		{
			int stop = shift + badChar; // Индекс несовпавшего символа

			int shiftStop = badChar - stopCharTable[haystack[stop]]; // Сдвиг по эвристике стоп-символа
			int shiftPref = suffixTable[needleLen - 1 - badChar];    // Сдвиг по эвристике совпавшего суффикса

			// Сдвиг = наибольшему из двух
			if (shiftStop > shiftPref)
				shift += shiftStop;
			else
				shift += shiftPref;
		}
	}

	return entry; // Возвращаем индексы всех вхождений
}