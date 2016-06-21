#pragma once

// Один эл-т списка
struct Node
{
	Node() : data(nullptr), next(nullptr), prev(nullptr) {} // Обнуляем все значения
	~Node() { delete data; } // при удалении эл-та очищаем данные
	int *data; // Ссылка на данные
	Node *next; // Ссылка на след. эл-т
	Node *prev; // Ссылк на предю эл-т
	Node &operator++() { *this = *this->next; return *this; }; // префикс инкремент, переходит и возвращает ссылку след. эл-т на след. эл-т
	Node &operator++(int) { Node *tmp = this; *this = *this->next; return *tmp; }; // постфикс инкремент, возвращает ссылку на текущий и переходит на след.
	bool operator!=(Node &node) { if (node.next != this->next) return true; return false; };
	Node &operator*() { return *this; };
};

// Список
class List
{
protected:
	Node *head; // Ссылка на начало списка
	Node *tail; // Ссылка на конец списка
	int length; // Длина списка
public:
	List(); // Конструктор
	void append(int data); // Добавление эл-та в конец списка
	int pop(int index = -1); // удаленяет и возращает эл-т из конца списка
	void remove(int data); // Удаление эл-та со значением
	void del(int index); // Удаление эл-та с индексом
	int get(int index); // Получение эл-та с индексом n
	void insert(int data, int index); // Вставка эл-та в список
	int len(); // Длина списка
	List operator+(List list);  // Сложение списков
	void operator+=(int data);  // append эл-т
	void operator+=(List list); // append список
	int &operator[](int index); // get
	Node &begin(); // Ссылка на 1-й эл-т списка
	Node &end(); // Ссылка на последний эл-т списка
};
