#pragma once
#include <stdexcept>


// Стек
template <typename T>
class Stack
{
protected:
	struct Node // Элемент стека
	{
		Node() : prev(nullptr) {}; // Обнуляем указатель на пред. эл-т
		Node(T data) : data(data), prev(nullptr) {}; // Присваиваем занчение и обнуляем указатель
		T data; // Значение
		Node *prev; // Указатель на пред. эл-т
	};
	Node *sp; // Указатель на вершину
	int length;   // Длина
public:
	Stack();  // Конструктор
	~Stack(); // Деструктор
	void clear(); // Очистка стека
	int len(); // Кол-во эл-в
	T peek();  // Посмотреть эл-т на вершине
	void push(T data); // Добавить эл-т в стек
	T pop(); // Вытищить эл-т с вершины стека
};


/* Выделяем память под 1-й эл-т                         *
 * sp - указывает на место под новый эл-т               *
 * т.е. в стека выделено памяти всегда на 1 эл-т больше */
template<typename T>
inline Stack<T>::Stack() : sp(new Node), length(0) {}

// Удаление стека
template<typename T>
inline Stack<T>::~Stack()
{
	clear();   // Удаление всех эл-в
	delete sp; // Удаление места под след. эл-т
}

// Очистка стека
template<typename T>
inline void Stack<T>::clear()
{
	while (sp->prev) // Пока есть пред. эл-т
	{
		Node *tmp = sp; // Временный указатель на текущий эл-т
		sp = sp->prev;      // Переходим к пред. эл-ту
		delete tmp;         // Удаляем эл-т
	}

	length = 0; // Обнуляем длину стека
}

// Длина стека
template<typename T>
inline int Stack<T>::len()
{
	return length;
}

/* Возвращает последний значение последнего эл-та стека не удаляя его
 * Если стек пусть, бросает исключение */
template<typename T>
inline T Stack<T>::peek()
{
	// Если стек пустой - бросаем исключение
	if (length == 0)
		throw std::exception("Peek from empty stack");
	else
		return sp->prev->data; // Возвращаем значение эл-та с вершины
}

// Добавить эл-т на вершину стека
template<typename T>
inline void Stack<T>::push(T data)
{
	sp->data = data; // Добавляем значение в стек
	Node *tmp = new Node; // Выделяем память под новый эл-т
	tmp->prev = sp; // "Связываем" новую вершину с старой
	sp = tmp; // Смещаем вершину

	length++; // Увеличиваем длину
}

/* Возвращаем эл-т с вершины стека и удаляем его
 * Если стек пуст - бросаем исключение */
template<typename T>
inline T Stack<T>::pop()
{
	// Если стек пуст
	if (length == 0)
		throw std::exception("Pop from empty stack");
	else
	{
		Node *tmp = sp; // Временный указатель на вершину
		sp = sp->prev; // Смещаем вершину

		delete tmp; // Удаляем пред. вершину
		length--; // Уменьшаем длину

		return sp->data; // Возвращаем значение
	}
}
