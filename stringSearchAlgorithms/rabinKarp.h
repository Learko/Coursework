#pragma once
#include "..\dataStructures\list.h"

/* Алгоритм поиска первого вхождения подстроки в строку Рабина-Карпа  *
 * Принимает строку(haystack) и шаблон(needle)                        *
 * Возвращает список из всех вхождений                                */
List *rabinKarp(char *haystack, char *needle);