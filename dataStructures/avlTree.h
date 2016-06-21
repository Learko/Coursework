#pragma once

// Сбалансированное бинарное дерево (АВЛ-дерево)
template <typename T>
class Tree
{
public:
protected:
	T *data;     // Указатель на данные
	int height;  // Высота дерева
	Tree *left;  // Указатель на левого ребенка
	Tree *right; // Указатель на правого ребенка
	int bFactor(); // Разность высот между левым и правым ребенком
	int checkHeight(); // Возвращает корректное значение высоты (при условии, что значение у детей корректно)
	void rotateLeft();     // Малый поворот влево
	void rotateRight();    // Малый поворот вправо
	void bigRotateLeft();  // Большой поворот влево
	void bigRotateRight(); // Большой поворот вправо
	void balance();
public:
	Tree() : data(nullptr), height(0), left(nullptr), right(nullptr) {}; // Обнуление полей
	Tree(T _data) : data(new T(_data)), height(1), left(nullptr), right(nullptr) {}; // Заполнение поля data, обнуление оставшихся полей(высота = 1)
	T getData(); // Значение элемента в корне
	int getHeight(); // Высота
	Tree<T> *toLeft();  // Указатель на левого ребенка
	Tree<T> *toRight(); // Указатель на правого ребенка
	void append(T data); // Добавление значения в дерево
	void append(Tree tree); // Добавление дерева в дерево
	void clear(); // Очистка дерева
	void remove(T data); // Удаление значения из дерева
};


// Значение эл-та в корне
template<typename T>
inline T Tree<T>::getData() { return *data; }

// Высота дерева
template<typename T>
inline int Tree<T>::getHeight() { return height; }

// Указатель на левого ребенка
template<typename T>
inline Tree<T> * Tree<T>::toLeft() { return left; }

// Указатель на правого ребенка
template<typename T>
inline Tree<T> * Tree<T>::toRight() { return right; }

// Разность высот левого и правого поддеревьев
template<typename T>
int Tree<T>::bFactor()
{
	int hl = left ? left->height : 0;   // Если левый ребенок сущ-т => его высота, иначе 0
	int hr = right ? right->height : 0; // Если правый ребенок сущ-т => его высота, иначе 0

	return hl - hr; // Высота левого - высота правого
}

// Возвращает корректное значение высоты (при условии, что высота потомков - корректна)
template<typename T>
int Tree<T>::checkHeight()
{
	int hl = left ? left->height : 0;   // Если левый ребенок сущ-т => его высота, иначе 0
	int hr = right ? right->height : 0; // Если правый ребенок сущ-т => его высота, иначе 0

	return (hl > hr ? hl : hr) + 1; // Максимальная из высот + 1
}

// Малый поворот влево
template<typename T>
void Tree<T>::rotateLeft()
{
	Tree *newRoot = new Tree; // Новый корень
	*newRoot = *right; // Новый корень = правому ребенку (по значению)

	newRoot->left = new Tree; // Левое поддерево
	*newRoot->left = *this;   // Левое поддерево = текущему корню (по значению)

	newRoot->left->right = right->left; // Правое поддерево левого поддерева нового корня = левому поддереву правого поддерева текущего корня

	// Если левый ребенок сущ-т
	if (newRoot->left) 
		newRoot->left->height = newRoot->left->checkHeight(); // Устанавливаем корректное значение высоты левого поддерева

	// Если правый ребенок сущ-т
	if (newRoot->right)
		newRoot->right->height = newRoot->right->checkHeight(); // Устанавливае корректное значение высоты правого поддерева

	newRoot->height = newRoot->checkHeight(); // Устанавливаем корректное значение высоты нового корня

	delete right; // Удаляем правое поддерево
	*this = *newRoot; // Корень = новому корню (по значению)

	delete newRoot; // Удаляем временный корень
}

// Малый поворот вправо
template<typename T>
void Tree<T>::rotateRight()
{
	Tree *newRoot = new Tree; // Новый корень
	*newRoot = *left; // Новый корень = левому ребенку (по значению)

	newRoot->right = new Tree; // Правое поддерево
	*newRoot->right = *this;   // Правое поддерево = текущему корню (по значеню)

	newRoot->right->left = left->right; // Левое поддерево правого поддерева нового корня = правому поддереву левого дерева текущего корня

	// Если левый ребенок сущ-т
	if (newRoot->left)
		newRoot->left->height = newRoot->left->checkHeight(); // Устанавливаем корректное значение высоты левого поддерева

	// Если правый ребенок сущ-т
	if (newRoot->right)
		newRoot->right->height = newRoot->right->checkHeight(); // Устанавливаем корректное значение высоты правого поддерева

	newRoot->height = newRoot->checkHeight(); // Устанавливаем корректное значение высоты нового корня

	delete left; // Удаляем левое поддерево
	*this = *newRoot; // Корень = новому корню (по значению)

	delete newRoot; // Удаляем временный корень
}

// Большой поворот влево
template<typename T>
inline void Tree<T>::bigRotateLeft()
{
	right->rotateRight(); // Малый поворот правого поддерева вправо
	rotateLeft();         // Малый поворот влево
}

// Большой поворот вправо
template<typename T>
inline void Tree<T>::bigRotateRight()
{
	left->rotateLeft(); // Малый поворот левого поддерева влево
	rotateRight();      // Малый поворот вправо
}

// Добавление значения в дерево
template<typename T>
void Tree<T>::append(T _data)
{
	// Если в корень пуст
	if (!data) // height == 0
	{
		data = new T(_data);
		height = 1;
	}
	else
	{
		if (*data > _data) // Если значение меньше значения в корне
		{
			if (left) // Если левый ребенок сущ-т
				left->append(_data); // Рекурсивно добавляем в значение в левое поддерево
			else
				left = new Tree(_data); // Создаем новой поддерево, кладем в корень значение _data
		}
		else // Если значение >= значению в корне
		{
			if (right) // Если правый ребенок сущ-т
				right->append(_data); // Рекурсиво добавляем значение в правое поддерево
			else
				right = new Tree(_data); // Создаем новое поддерево, кладем в корент значение _data
		}

		height = checkHeight(); // Устанавливаем корректное значение высоты
		balance(); // Балансировка дерева (из текущего корня)
	}
}

// Добавление дерева в дерево
template<typename T>
void Tree<T>::append(Tree tree)
{
	if (tree.left) // Если левый ребенок сущ-т
		append(*tree.left); // Рекурсивно добавляем левое поддерево
	if (tree.right) // Если правый ребенок сущ-т
		append(*tree.right); // Рекурсивно добавляем правое поддерево
	if (tree.data) // Если есть данные (и уже нет левого и правого деревьев)
		append(*tree.data); // Добавляем значение
}

// Балансировка
template<typename T>
void Tree<T>::balance()
{
	// Если левое поддерево сущ-т и разность высот левого и правого поддеревьев = 2
	if (left && bFactor() == 2)
	{
		if (left->bFactor() < 0) // Если разность левого и правого поддеревьев Левого поддерева < 0
			bigRotateRight();    // Большой поворот вправо
		else
			rotateRight();       // Малый поворот вправо
	}
	// Если правое поддерево сущ-т и разность высот левого и правого поддеревьев = -2
	else if (right && bFactor() == -2)
	{
		if (right->bFactor() > 0) // Если разность высот левого и правого поддеревьев Правого поддерева > 0
			bigRotateLeft();      // Большой поворот влево
		else
			rotateLeft();         // Малый поворот влево
	}
}

// Очистка дерева (удаление всех эл-в)
template<typename T>
void Tree<T>::clear()
{
	if (left) // Если левый ребенок сущ-т
	{
		left->clear();  // Рекурсивно очищаем левое поддерево
		delete left;    // Удаление левого поддерева (освобождение памяти)
		left = nullptr; // Обнуляем указатель на левое поддерево
	}
	if (right) // Если правый ребенок сущ-т
	{
		right->clear();  // Рекурсивно очищаем правое поддерево
		delete right;    // Удаление правого поддерева (освобождение памяти)
		right = nullptr; // Обнуляем указатель на правое поддерево
	}
	if (data) // Если есть значение
	{
		delete data;    // Удаляем значение
		data = nullptr; // Обнуляем указатель на значение
		height = 0;     // Обнуляем высоту 
	}
}

// Удаление значения из дерева
template<typename T>
void Tree<T>::remove(T _data)
{
	// Если дерево не пусто
	if (data) // height != 0
	{
		if (*data == _data) // Если значения равны
		{
			if (!left && !right) // Если не сущ-т левое и не сущ-т правое поддеревья
			{
				delete data;    // Удаляем значение
				data = nullptr; // Обнуляем указатель
				height = 0;     // Обнуляем высоту
			}
			else if (bFactor() > 0) // Если высота левого поддерева больше правого
			{
				Tree<T> *tmp = left; // Указатель на левое поддерево

				// Поиск ближайшего значения (в левом поддереве)
				if (tmp->right) // Если сущ-т правое поддерево левого поддерева
				{
					// Необходимо остановиться заранее чтобы сохранить указатель на потомка для последующего удаления
					while (tmp->right->right)  // Если правое поддерево правого поддерева сущ-т
						tmp = tmp->right;      // Переход на след.
					*data = *tmp->right->data; // Выносим вверх ближайшее значение

					delete tmp->right;      // Удаляем ближайшее значение
					tmp->right = nullptr;   // Обнуляем указатель
					height = checkHeight(); // Устанавливаем корректное значение высоты
				}
				else // Если правое поддерево не сущ-т
				{
					// Сдвигаем левое поддерево вверх
					Tree<T> *tmpRight = right; // Временный указатель на правое поддерево
					Tree<T> *tmpLeft = left;   // Временный указатеьл на левое поддерево

					*this = *left;    // Корень = левому поддереву (по значению)
					right = tmpRight; // Правое поддерево

					delete tmpLeft; // Удаление левого поддерева
					height = checkHeight(); // Устанавливаем корректное значение высоты
				}
			}
			else // Если высота правого поддерева больше либо равна левого
			{
				Tree<T> *tmp = right; // Временный указатель на правое поддерево

				// Находим ближайшее значение в правом поддереве
				if (tmp->left) // Если левое поддерево сущ-т
				{
					// Необходимо остановиться заранее чтобы сохранить указатель на потомка для последующего удаления
					while (tmp->left->left)   // Если правое поддерево правого поддерева сущ-т
						tmp = tmp->left;      // Переход на след.
					*data = *tmp->left->data; // Выносим вверх ближайшее значение

					delete tmp->left;       // Удаляем ближайшее значение
					tmp->left = nullptr;    // Обнуляем указатель
					height = checkHeight(); // Устанавливаем корректное значение высоты
				}
				else // Если левого поддерева не сущ-т
				{
					// Сдвигаем правое поддерево вверх
					Tree<T> *tmpLeft = left;   // Временный указатель на левое поддерво
					Tree<T> *tmpRight = right; // Временный указатель на правое поддерево

					*this = *right; // Корень = правому поддереву (по значению)
					left = tmpLeft; // Левое поддерево

					delete tmpRight; // Удаление правого поддерева
					height = checkHeight(); // Устанавливаем корректное значение высоты
				}
			}
		}
		else if (left && *data > _data) // Если левый ребенок сущ-т и значение меньше значения в корне
		{
			left->remove(_data); // Рекурсивний вызов ф-ии от левого поддерева
			checkHeight();       // Устанавливаем корректное значение высоты

			if (left->height == 0) // Если левое поддерево пусто (после удаления)
			{
				delete left;    // Удаляем левое поддерево
				left = nullptr; // Обнуляем указатель
			}
		}
		else if (right && *data < _data) // Если правый ребенок сущ-т и значение больше значения в корне
		{
			right->remove(_data); // Рекурсивный вызов ф-ии от правого поддерева
			checkHeight();        // Устанавливаем корректное значение высоты

			if (right->height == 0) // Если правое поддерево пусто (после удаления)
			{
				delete right;    // Удаляем правое поддерево
				right = nullptr; // Обнуляем указатель
			}
		}
	}
}
