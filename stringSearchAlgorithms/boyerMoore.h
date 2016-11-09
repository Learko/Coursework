#pragma once
#include "..\dataStructures\list.h"

/* Алгоритм поиска подстроки в строке Бойера-Мура             *
 * Принимает на вход: haystack - сроку и needle - шаблон      *
 * Возвращает список индексов начал всех вхождений            *
 * если шаблон отсутствует в строке, возвращает пустой список */
List *boyerMoore(char *haystack, char *needle);