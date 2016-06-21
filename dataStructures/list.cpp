#include <stdexcept>
#include "list.h"


/* Конструктор, обнуляем переменные(св-ва класса)
 * (ссылка на начало списка, ссылка на конец списка и длина) */
List::List() : head(new Node), tail(new Node), length(0)
{
	head->next = tail;
	tail->prev = head;
}

// Добавляем в конец списка data
void List::append(int data)
{
	if (length > 0) // Если список не пуст
	{
		tail->next = new Node; // Выделяем память под новый эл-т списка
		tail->data = new int(data); // Выделям память под данные и заполняем значение
		tail->next->prev = tail; // у нового эл-т поле prev равно текущемему эл-ту
		tail = tail->next; // Смещаем конец списка
	}
	else // Если список пуст
	{
		head->data = new int(data); // Выделяем память под данные и заполняем
	}

	length++; // Увеличиваем длину списка
}

/* Удаляем и возвращаем эл-т списка с заданным индексом(по умолчанию последний)
 * также поддерживаются отрицательные индексы(-1 - последний, -2 - предпоследний, ...) */
int List::pop(int index)
{
	// Если переданный индекс по модулю больше длинны массива, бросаем исключение
	if (index >= length || index <= -length)
		throw std::out_of_range("Index out of range");

	int result; // Значение эл-та с заданным индексом
	if (index > 0) // Если переданный индекс > 0
	{
		Node *tmp = head; // Временнй указатель на начало списка
		for (int i = 0; i < index; i++, tmp = tmp->next); // Перебираем эл-ты до переданного индекса
		result = *tmp->data; // Складываем значение из списка в возвращаемую переменную

		tmp->prev->next = tmp->next;

		delete tmp; // Удаляем временный указатель(и сам эл-т)
	}
	else if (index < 0) // Если переданный индекс < 0
	{
		if (index == -1) // Если переданный индекс = -1 (последнему эл-ту)
		{
			// Этот случай удобно рассмотреть отдельно, чтобы избежать проблем с концом списка
			result = *tail->prev->data; // Возвращаемое значение
			tail = tail->prev; // Перемещаем конец на пред. эл-т списка
			delete tail->next; // Удалям конец
			tail->next = nullptr; // Удалям указатель на конец
		}
		else // Если индекс != -1
		{
			Node *tmp = tail->prev; // Создаем временный указатель на конец списка
			for (int i = -1; i > index; i--, tmp = tmp->prev); // Движемся от конца списка к началу
			result = *tmp->data; // Возвращаемое значение

			// Удаляем эл-т
			if (tmp != head) // Если эл-т не явл-я началом списка
			{
				tmp->prev->next = tmp->next; // Удаляем(заменяем) указатель на этот эл-т у след. эл-та
				tmp->next->prev = tmp->prev; // Удаляем(заменяем) указатель на этот эл-т у пред. эл-та
			}
			else // Если указатель смотри на начало списка
			{
				head = head->next; // Смещаем начало списка
				head->prev = nullptr; // Удаляем указатель на пред-ее начало
			}

			delete tmp; // Удаляем эл-т
		}
	}
	else if (index == 0) // Если индекс = 0 (удалить первый эл-т списка)
	{
		result = *head->data; // Возвращаемое значение
		if (head->next != tail) // Если в списке больше одного эл-та
		{
			head = head->next; // Смещаем начало
			delete head->prev; // Удаляем пред. эл-т
			head->prev = nullptr; // Удаляем указатель
		}
		else // Если эл-т в списке один
		{
			delete head; // Удаляем его
			head = new Node;
			head->next = tail;
		}
	}

	length--; // Уменьшаем длину списка
	return result; // Возвращаем рузультат - значение эл-та по переданному индексу
}

// Удаление эл-та с определенным значением из списка
void List::remove(int data)
{
	bool found = false; // Был ли найден эл-т
	Node *tmp = head; // Временный указатель на начало списка
	for (int i = 0; i < length && !found; i++) // Идем до конца списка пока эл-т с заданным значением не найден
		if (*tmp->data == data) // Если значения равны
			found = true; // Эл-т найден
		else
			tmp = tmp->next; // Рассматриваем след. эл-т

	if (found) // Если эл-т найден
	{
		if (tmp == head) // Если эл-т равен первый
			if (tmp->next == tail) // и последний (в списке всего 1 эл-т)
			{
				delete head; // Удалеям его
				head = new Node;
				head->next = tail;
			}
			else // Если первый но не последний
			{
				head = head->next; // Смещаем начало списка
				delete head->prev; // Удаляем пред. эл-т
				head->prev = nullptr; // Удаляем указатель на него
			}
		else if (tmp->next == tail) // Последний и не первый
		{
			tail = tail->prev; // Смещаем конец списка
			delete tail->next; // Удаляем след. эл-т
			tail->next = nullptr; // Удаляем указатель
		}
		else // Не первый и не последний
		{
			tmp->prev->next = tmp->next; // Заменяем указатель у пред. эл-та
			tmp->next->prev = tmp->prev; // Заменяем указатель у след. эл-та
			delete tmp; // Удаляем эл-т
		}

		length--; // Уменьшаем длину списка
	}
	else // Если эл-т не найден
		throw "ValueError: List.remove(x): x not in List"; // Бросаем исключение
}

// Удаление эл-т с заданным индексом
void List::del(int index)
{
	// Если переданный индекс по модулю больше длинны массива, бросаем исключение
	if (index >= length || index <= -length)
		throw std::out_of_range("Index out of range");

	else if (index > 0) // Если переданный индекс > 0
	{
		Node *tmp = head; // Временный указатель на начало списка
		for (int i = 0; i < index; i++, tmp = tmp->next); // Перебираем эл-т до переданного индекса

		if (tmp->next != tail) // Если эл-т не последний
			tmp->prev->next = tmp->next; // Удаляем указатели на этот эл-т
		else // Если последний
		{
			tail->prev->next = nullptr; // Удаляем указатель у пред. эл-та на след.
			tail = tail->prev; // Смещаем конец
		}

		delete tmp; // Удаляем эл-т
	}
	else if (index < 0) // Если переданный индекс < 0
	{
		if (index == -1) // Если индекс = -1 (удалить последний эл-т)
		{
			tail = tail->prev; // Смещаем конец списка
			delete tail->next; // Удаляем эл-т
			tail->next = nullptr; // Удаляем указатель на него
		}
		else // Если != -1
		{
			Node *tmp = tail; // Временный указатель на конец списка
			for (int i = -1; i > index; i--, tmp = tmp->prev); // Перебираем эл-т от конца к началу необходимое кол-во раз

			if (tmp != head) // Если эл-т не первый
			{
				tmp->prev->next = tmp->next; // Удаляем указатели на этот эл-т
				tmp->next->prev = tmp->prev; // Удаляем указатели на этот эл-т
			}
			else // Если эл-т первый
			{
				head = head->next; // Смещаем начало списка
				head->prev = nullptr; // Удаляем указатель
			}

			delete tmp; // Удаляем эл-т
		}
	}
	else if (index == 0) // Если индекс = 0 (удалить 1-й эл-т)
	{
		if (head->next != tail) // Если эл-т не единственный
		{
			head = head->next; // Смещаем начало
			delete head->prev; // Удаляем эл-т
			head->prev = nullptr; // Удаляем указатель
		}
		else // Если эл-т единсвенный
		{
			delete head; // Удаляем эл-т
			head = new Node;
			head->next = tail;
		}
	}

	length--; // Уменьшаем длину списка
}

// Возвращает значение эл-т по переданному индексу
int List::get(int index)
{
	// Если индекс > длины списка или < 0 
	if (index >= length || index < 0)
		throw std::out_of_range("Index out of range"); // Бросаем исключение

	Node *tmp = head; // Временный указатель на начало списка
	for (int i = 0; i < index; i++, tmp = tmp->next); // Перебираем эл-ты до переданного индекса

	return *tmp->data; // Возвращаем значение по заданному индексу
}

// Вставка в список, принимает данные и индекс места вставки
void List::insert(int data, int index)
{
	// Если индекс > длины или < 0
	if (index > length || index < 0)
		throw std::out_of_range("Index out of range"); // Бросаем исключение

	else if (index == 0) // Если индекс = 0
	{
		if (length > 0) // Если список не пуст
		{
			head->prev = new Node; // Выделяем память под новый эл-т
			head->prev->next = head; // Создаем указатель на след. эл-т
			head = head->prev; // Перемещаем начало списка
			head->data = new int(data); // Заполняем значение
		}
		else // Если список пуст
			head->data = new int(data); // Заполняем значение
	}
	else if (index < length) // Если индекс больше длины
	{
		Node *tmp = head; // Временный указатель на начало списка
		for (int i = 0; i < index; i++, tmp = tmp->next); // Пропускаем эл-ты до эл-та с заданным индексом

		tmp->prev->next = new Node; // Выделяем память под новый эл-т
		tmp->prev = tmp->prev->next; // Создаем указатель на пред. эл-т
		tmp->prev->data = new int(data); // Заполняем значение

	}
	else if (index == length) // Если индекс = длине - добавляем в конец
		append(data);

	length++; // Увеличиваем длину
}

// Возвращаем длину списка
int List::len() { return length; }

// Перегружаем оператор + (бинарный) для списков
List List::operator+(List list)
{
	List result = *this; // Результат (склееные 2 списка)

	// .begin() - возвращает указатель на 1-й эл-т списка
	for (auto &it : list) // Добавлям в 1 список эл-ты из другого
		append(*it.data);

	return result; // Склееные два списка
}

/* Перегруженный оператор += (список += данные)
 * Добавляем переданное значение в конец списка */
void List::operator+=(int data) { append(data); }

// Перегруженный оператор += (список += список)
void List::operator+=(List list)
{
	for (auto &it : list) // Идем от начала 2-го списка
		append(*it.data); // Добавляем эл-ты в конец 1-го
}

// Перегруженный оператор [], возвращает ссылку на значение эл-та по переданному индексу
int& List::operator[](int index)
{
	// Если индекс > длины или < 0
	if (index > length || index < 0)
		throw std::out_of_range("Index out of range"); // Бросаем исключение

	Node *tmp = head; // Временный указатель на начало списка
	for (int i = 0; i < index; i++, tmp = tmp->next); // Пропускаем эл-ты до заданного индекса

	return *tmp->data; // Возвращаем значение(по ссылке)
}

// Возвращаем указатель на начало списка
Node & List::begin() { return *head; }

// Возвращаем указатель на конец списка
Node & List::end() { return *tail; }
