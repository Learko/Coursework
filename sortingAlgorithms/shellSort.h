#pragma once

/* Сортировка Шелла
 * На вход массив и кол-во эл-в */
void shellSort(int *Arr, int n);

/* Сортировка Вставками
 * На вход массив, кол-во эл-в, сдвиг, шаг */
void insertSort(int *Arr, int n, int shift, int step = 1);
