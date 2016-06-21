#pragma once


// Двунаправленная(двусторонняя) очередь (дек)
template <typename T>
class Deque
{
protected:
	struct Node // Эл-т двунаправленной(двусторонней) очереди
	{
		Node() : next(nullptr), prev(nullptr) {}; // Обнуляем указатели
		Node(T data) : data(data), next(nullptr), prev(nullptr) {}; // Присваиваем значение, обнуляем указатели
		T data; // Значение эл-та
		Node *next; // Указатель на след. эл-т
		Node *prev; // Указатель на пред. эл-т
	};
	Node *start; // Указатель на начало
	Node *end;   // Указатель на конец
	int length;       // Кол-во эл-в
public:
	Deque();  // Конструктор
	~Deque(); // Деструктор
	void clear(); // Очистка дека
	void append(T data); // Добавить эл-т в конец
	void appendleft(T data); // Добавить эл-т в начало
	T popleft();  // Вытащить эл-т с начала
	T pop();      // Выташить эл-т с конца
	T peekleft(); // Посмотреть на первый эл-т
	T peek();     // Посмотреть на последний эл-т
};


/* Выделяем память под начало и под конец (два различных эл-т) *
 * Обнуляем длину.                                             *
 * После инициализации первый эл-т указывает на последний,     *
 * а последний на первый                                       */
template<typename T>
inline Deque<T>::Deque() : start(new Node), end(new Node), length(0)
{
	start->next = end;
	end->prev = start;
}

// Удаляем все эл-ты из дека + начало ии конец
template<typename T>
inline Deque<T>::~Deque()
{
	clear();
	delete start;
	delete end;
}

// Очистка дека
template<typename T>
inline void Deque<T>::clear()
{
	while (end->prev != start) // Пока пред. эл-т - не начало дека
	{
		end = end->prev;  // Переходим к пред.
		delete end->next; // Удаляем след.
	}

	length = 0; // Обнуляем длину
}

// Добавляем эл-т в начало
template<typename T>
inline void Deque<T>::appendleft(T data)
{
	start->data = data; // Присваиваем значение
	start->prev = new Node; // Выделяем память под новый эл-т
	start->prev->next = start; // "Связываем" новое начало со старым
	start = start->prev; // Переходим к новому эл-ту

	length++; // Увеличмваем длину
}

// Добавляем эл-т в конец
template<typename T>
inline void Deque<T>::append(T data)
{
	end->data = data; // Присваиваем значение
	end->next = new Node; // Выделяем память под новый эл-т
	end->next->prev = end; // Связываем новый эл-т с пред концом
	end = end->next; // Переходим к новому эл-ту

	length++; // Увеличиваем длину
}

// Удаляем эл-т с начала
template<typename T>
inline T Deque<T>::popleft()
{
	// Если дек пуст - бросаем исключение
	if (length == 0)
		throw std::exception("Pop from empty deque");
	else
	{
		start = start->next;   // Сдвигаем начало
		delete start->prev;    // Удаляем пред. эл-т
		start->prev = nullptr; // Обнуляем указатель на пред. начало

		length--;
		return start->data; // Возвращаем значение
	}
}

// Удаляем эл-т с конца
template<typename T>
inline T Deque<T>::pop()
{
	// Если дек пуст - бросаем исключение
	if (length == 0)
		throw std::exception("Pop from empty deque");
	else
	{
		end = end->prev;     // Сдвигаем конец
		delete end->next;    // Удаляем пред. последний эл-т
		end->next = nullptr; // Обнуляем указатель

		length--;
		return end->data; // Возвращаем значение
	}
}

// Возвращаем значение первого эл-та, не удаляя его
template<typename T>
inline T Deque<T>::peekleft()
{
	// Если дек пуст - бросаем исключение
	if (length == 0)
		throw std::exception("Peek from empty deque");
	else
		return start->next->data; // Иначе возвращаем значение
}

// Возвращаем значение последнего эл-та
template<typename T>
inline T Deque<T>::peek()
{
	// Если дек пуст - бросаем исключение
	if (length == 0)
		throw std::exception("Peek from empty deque");
	else
		return end->prev->data; // Иначе возвращаем значение
}
