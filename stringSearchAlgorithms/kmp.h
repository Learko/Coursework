#pragma once
#include "..\dataStructures\list.h"


/* Алгоритм поиска первого вхождения подстроки в строку Кнута-Морриса-Пратта       *
 * Принимает строку(haystack) и шаблон(needle)                                     *
 * Возвращает список индексов начал всех вхождений                                 */
List kmp(char *haystack, char *needle);
