#include "string.h"

// Длинна строки
int strlen(char * str)
{
	int len = 0;
	if (str)
		while (str[len] != '\0') // Увеличиваем длинну пока не дошли до конца('\0') 
			len++;

	return len;
}

// Копирование строки source в dest
void strcpy(char * dest, char * source)
{
	int i;
	for (i = 0; source[i] != '\0'; i++) // Посивольное копирование
		dest[i] = source[i];

	dest[i] = '\0'; // Дописываем '\0' в конец
}

/* Сравнение 2-х строк
 * s > p  |  1
 * s = p  |  0
 * s < p  |  -1   */
int cmp(char *s, char *p)
{
	return *s ? *p ? *s == *p ? cmp(++s, ++p) : *s > *p ? 1 : -1 : 1 : *p ? -1 : 0; // 53
}

// Возвращает развернутую строку строку
char * revstr(char * str)
{
	int len = strlen(str); // Находим длинну строки
	char *revstr = new char[len + 1]; // Выделям память в новой строке ( len(str1) + '\0' )

	for (int i = 0; i < len; i++) // До конца строки
		revstr[len - i - 1] = str[i]; // В конец перевернутой строки записываем символы от начала

	revstr[len] = '\0'; // Дописываем '\0' в конец

	return revstr; // Возвращаем перевернутую строку
}
