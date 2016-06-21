#pragma once

/* Длинна строки
 * При передаче пустого указателя вернет 0 */
int strlen(char *str);

/* Посимвольное копирование строки source в dest
 * Указатели source и dest должны быть не пустыми */
void strcpy(char *dest, char *source);

/* Сравнение 2-х строк
 * Указатели должны быть не пустыми
 * s > p  |  1
 * s = p  |  0
 * s < p  |  -1   */
int cmp(char *s, char *p);

/* Возвращает развернутую строку строку
 * например "abc" -> "cba" (с \0) */
char *revstr(char *str);
