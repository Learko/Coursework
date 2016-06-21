#pragma once
#include <stdexcept>


// Очередь
template <typename T>
class Queue
{
protected:
	struct Node // Элемент очереди
	{
		Node() : next(nullptr) {}; // Убнуляем указатель
		Node(T data) : data(data), next(nullptr) {}; // Присваиваем значение и обнуляем указатель
		T data; // Значение
		Node *next; // Указатель на след.
	};
	Node *start; // Указатель на начало
	Node *end;   // Указатель на конец
	int length;      // Кол-во эл-в
public:
	Queue();  // Конструктор
	~Queue(); // Деструктор
	void clear(); // Очистка очереди
	T get();  // Вытскиваем эл-т
	T peek(); // Смотрим на первый эл-т 
	void put(T data); // Добавляем эл-т в очередь
};


/* Выделяем память под эл-т
 * Начало и конец очереди указывают на 1 эл-т
 * Длина равна 0 */
template<typename T>
inline Queue<T>::Queue() : start(new Node), end(start), length(0) {};

// Удаляем все эл-ты из очереди, и первый(пустой) эл-т
template<typename T>
inline Queue<T>::~Queue()
{
	clear();
	delete start;
}

// Очистка очереди
template<typename T>
inline void Queue<T>::clear()
{
	while (start != end) // Пока начало Очереди не совпало с концом(пока не оствался 1 пустой эл-т)
	{
		Node *tmp = start; // Временный указатель на начало
		start = start->next;   // Переходим к след эл-ту

		delete tmp; // Удаляем пред. эл-т
	}

	length = 0; // Обнуляем длину
}

// Берем первый эл-т из очереди и удаляем его
template<typename T>
inline T Queue<T>::get()
{
	// Если очередь пуста - бросаем исключение
	if (length == 0)
		throw std::exception("Get from empty queue");
	else
	{
		T data = start->data;  // Значение эл-та
		Node *tmp = start; // Временный указатель на начало
		start = start->next;   // Переходим к след.

		delete tmp;  // Удаляем пред. эл-т
		length--;    // Уменьшаем длину
		return data; // Возвращаем значение
	}
}

// Возвращаем значение 1-го эл-та из очереди, не удаляя его
template<typename T>
inline T Queue<T>::peek()
{
	// Если очередь пуста - бросаем исключение
	if (length == 0)
		throw std::exception("Peek from empty queue");
	else
		return start->data; // Иначе возвращаем значение
}

// Добавить эл-т в конец очереди
template<typename T>
inline void Queue<T>::put(T data)
{
	end->data = data; // Добавляем значение
	end->next = new Node; // Выделяем память под след. эл-т
	end = end->next; // Переходим к след. эл-ту

	length++; // Увеличиваем длину
}
