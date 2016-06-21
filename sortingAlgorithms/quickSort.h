#pragma once

/* Быстрая сортировка
 * Принимает указатель на первый эл-т массива, длину массива
 * start - дополнительный параметр, для сортировки подмассивов
 *  (индекс эл-а с к-го нужно начать сортировку) */
void quickSort(int *Arr, int n, int start = 0);
