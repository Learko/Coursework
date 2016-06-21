#include <stdexcept>
#include "..\dataStructures\list.h"


/* Хэш функция                                     *
 * Принимает строку, с какого эл-та сколькло эл-в  *
 * (считает хэш от подстроки)                      */
int hash(char * str, int start = 0, int len = 1)
{
	int h = 0; // Значение хэш функции
	for (int i = 0; i < len; i++) // Проходим по всем эл-там
		h += str[start + i] * (start + i);  // Добавляем к результату код символа умноженый на его индекс в строке

	return h;
}


/* Алгоритм поиска первого вхождения подстроки в строку Рабина-Карпа               *
 * Принимает строку(haystack) и шаблон(needle)                                     *
 * Возвращает индекс первого вхождения или -1, если подстрока отсутствует в строке */
List rabinKarp(char * haystack, char * needle)
{
	List entry = List();

	int haystackLen = strlen(haystack); // Длина строки
	int needleLen = strlen(needle);     // Длина шаблона

	// Если строка или шаблон пустые
	if (needleLen <= 0 || haystackLen <= 0)
		std::logic_error("Empty string");
	
	int needleHash = hash(needle, 0, needleLen);   // Хэш от шаблона
	int haystackHash = hash(needle, 0, needleLen); // Хэш от подстроки(равной длине шаблона)

	// Идем по строке пока не достигнут конец
	for (int shift = 0; shift <= haystackLen - needleLen; shift++)
	{
		// Если хэш от подстроки = хэшу от шаблона
		if (needleHash == haystackHash)
		{
			// Посимвольно проверяем совпадают ли строки
			int match = 0; // кол-во совпавших
			// Пока совпадают и не достигнут конец
			while (match < needleLen && needle[match] == haystack[shift + match])
				match++; // Увеличиваем кол-во совпавших

			// Если все совпали
			if (match == needleLen)
				entry += shift;
		}
		else
		{
			// Если хэши не совпали вычисляем новое значение хэш ф-ии от подстроки
			haystackHash -= hash(haystack, shift);
			haystackHash += hash(haystack, shift + needleLen);
		}
	}

	return entry; // Возвращаем индекс первого вхождения
}
