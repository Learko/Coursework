#include <iostream>
#include <stdexcept>
#include <windows.h>
#include "io.h"
#include "test.h"

/************ Sorting algorithms ***************/
#include "sortingAlgorithms\bubbleSort.h"
#include "sortingAlgorithms\shellSort.h"
#include "sortingAlgorithms\quickSort.h"
#include "sortingAlgorithms\radixSort.h"
#include "sortingAlgorithms\heapSort.h"

/********** String search algorithms ***********/
#include "stringSearchAlgorithms\boyerMoore.h"
#include "stringSearchAlgorithms\kmp.h"
#include "stringSearchAlgorithms\rabinKarp.h"

/*************** Data structures ***************/
#include "dataStructures\stack.h"
#include "dataStructures\queue.h"
#include "dataStructures\deque.h"
#include "dataStructures\avlTree.h"

/*********** Normal Polish Notation ************/
#include "polishNotation\polishNotation.h"

using namespace std;


// ������������ ���������� ����������
void testSort()
{
	SetConsoleTitle("TEST: Sorting Algorithms"); // ��������� ����
	system("cls"); // ������� ������

	// ��������� � ����������
	const char *helpMsg = "Help message:\n\
	0 - Bubble Sort\n\
	1 - Shell Sort\n\
	2 - Quick Sort\n\
	3 - Radix Sort\n\
	4 - Heap Sort\n\
	q - Back to Main menu";


	char action = NULL; // ��������

	while (action != 'q') // ���� �� ����� q
	{
		switch (action)
		{
		case '0': // ���������� ���������
			sortWrap(bubbleSort); 
			break;
		case '1': // ���������� �����
			sortWrap(shellSort);
			break;
		case '2': // ������� ����������
			sortWrap([](int *arr, int length) { quickSort(arr, length, 0); });
			break;
		case '3': // ����������� ����������
			sortWrap(radixSort);
			break;
		case '4': // ������������� ����������
			sortWrap(heapSort);
			break;
		default: // ������ �� ���� ��������������
			cout << helpMsg; // ������� ��������� � ����������
		}

		while (cin.get() != '\n'); // ������� ������ �����
		cout << endl << endl << "Select: ";
		cin >> action; // ���������� ��������
	}
}

/* ������� ��� ������� ���������� (���������)
 * ��������� �������� (�-� ����������)         */
void sortWrap(void sort(int *, int))
{
	int length; // ���-�� ��-�
	cout << "Number of elements: ";
	cin >> length;

	cout << "Your array: ";
	int *arr = inputArray(length); // ������������ �������

	sort(arr, length); // ���������� ������� ���������� �������

	cout << "Sorted array: ";
	printArray(arr, length); // ����� ������� ����� ������
}


// ������������ ���������� ������ ��������� � ������
void testStringSearch()
{
	SetConsoleTitle("TEST: String Search algorithms"); // ��������� �������
	system("cls"); // ������� ������

	// ��������� � ����������
	const char *helpMsg = "Help message:\n\
	0 - Knuth-Morris-Pratt string searching algorithm\n\
	1 - Boyer-Moore string search algorithm\n\
	2 - Rabin-Karp string search algorithm\n\
	q - Back to Main menu";


	char action = NULL; // ��������

	while (action != 'q') // ���� �� ����� q
	{
		switch (action)
		{
		case '0': // �������� �����-�������-������
			stringSearchWrap(kmp);
			break;
		case '1': // �������� ������-����
			stringSearchWrap(boyerMoore);
			break;
		case '2': // �������� ������-�����
			stringSearchWrap(rabinKarp);
			break;
		default: // ������ �� ���� ��������������
			cout << helpMsg; // ����� ��������� � ����������
		}

		cout << endl << endl << "Select: ";
		cin >> action; // ���������� ��������
		while (cin.get() != '\n'); // ������� ������ �����
	}
}

/* ������� ��� ������� ������ ��������� � ������ (���������)
 * ��������� �������� (�-� ������)                            */
void stringSearchWrap(List *searchFunc(char *, char *))
{
	char haystack[255]; // ������
	char needle[255];   // ������

	cout << "string: ";
	cin.getline(haystack, 255); // ��������� ������
	cout << "template: ";
	cin.getline(needle, 255);   // ��������� ������

	// ����� ��������� � ������ ���������� ����������
	List *entry = searchFunc(haystack, needle);

	// ������� ���� ��������� ����� ������
	cout << "Entry: ";
	if (entry->len() != 0)
		for (const auto &en : *entry)
			cout << *en.data << ' ';
	else
		cout << "Empty";
}


// ������������ �������� ������
void testDataStruct()
{
	SetConsoleTitle("TEST: Data structures"); // ��������� �������
	system("cls"); // ������� ������
	
	// ��������� � ����������
	const char *helpMsg = "Help message:\n\
	0 - Stack\n\
	1 - Queue\n\
	2 - Deque\n\
	3 - AVL-Tree\n\
	q - Back to Main menu";


	char action = NULL; // ��������

	while (action != 'q') // ���� �� ����� q (����������)
	{
		switch (action)
		{
		case '0': // ������������ �����
			SetConsoleTitle("TEST: Data structures: Stack"); // ����� ���������
			system("cls"); // ������� �������

			testStack(); // ������������ �������

			SetConsoleTitle("TEST: Data structures"); // ���������� ���������
			system("cls"); // ������� �������

			cout << helpMsg; // ��������� � ����������
			break;
		case '1': // ������������ �������
			SetConsoleTitle("TEST: Data structures: Queue"); // ����� ���������
			system("cls"); // ������� �������

			testQueue(); // ������������ �������

			SetConsoleTitle("TEST: Data structures"); // ���������� ���������
			system("cls"); // ������� �������

			cout << helpMsg; // ��������� � ����������
			break;
		case '2': // ������������ ����
			SetConsoleTitle("TEST: Data structures: Deque"); // ����� ���������
			system("cls"); // ������� �������

			testDeque(); // ������������ ����

			SetConsoleTitle("TEST: Data structures"); // ���������� ���������
			system("cls"); // ������� �������

			cout << helpMsg; // ��������� � ����������
			break;
		case '3': // ������������ ���-������
			SetConsoleTitle("TEST: Data structures: AVL-Tree"); // ����� ���������
			system("cls"); // ������� �������

			testAVLTree(); // ������������ ���-������

			SetConsoleTitle("TEST: Data structures"); // ���������� ���������
			system("cls"); // ������� �������

			cout << helpMsg; // ��������� � ����������
			break;
		default: // ������ �� ���� ��������������
			cout << helpMsg; // ��������� � ����������
		}

		cout << endl << endl << "Select: ";
		cin >> action; // ���������� ��������
		cin.ignore(); // ������� ����� (���� ��������� ����� ��������� ������ (�� \n))
	}
}

// ������������ �����
void testStack()
{
	// ��������� � ����������
	const char *helpMsg = "Help message:\n\
	push N    - put N at the top of the Stack\n\
	peek      - Element at the top of the Stack\n\
	pop       - Remove element from the top of the Stack\n\
	clear     - Remove all elements from Stack\n\
	len       - Number of elements in the stack\n\
	h or help - Show this message again\n\
	q or quit - Back to Data struct menu";

	Stack<int> stack; // ���� ����� �����
	string action = "h"; // �������� �� ���������

	while (action != "q" && action != "quit") // ���� �������� �� q ��� quit
	{
		try
		{
			if (action == "push") // push - ���������� � ����
			{
				int data; // ��-� ��� ����������

				cin >> data;
				stack.push(data); // ���������� ��-��
			}
			else if (action == "peek") // peek - �������� ��-�� �� ������� �����
				cout << "Output: " << stack.peek() << endl;
			else if (action == "pop") // pop - �������� � �������� ��-�� �� ������� �����
				cout << "Output: " << stack.pop() << endl;
			else if (action == "clear") // clear - ������� �����
				stack.clear();
			else if (action == "len") // len - ���-�� ��-� � �����
				cout << "Output: " << stack.len() << endl;
			else if (action == "h" || action == "help") // ������ ��������� � ����������
				cout << helpMsg << endl;
			else // ����������� ��������
			{
				while (cin.get() != '\n'); // ������� ������ �����
				cout << "Error: Unknown command. Use \"h\" or \"help\" to get help message." << endl;
			}
		}
		catch (exception &e) // ���� �������� ������
		{
			cout << "Error: " << e.what() << endl;
		}

		cout << endl << "Input: ";
		cin >> action; // ���������� ��������
	}
}

// ������������ �������
void testQueue()
{
	// ��������� � ����������
	const char *helpMsg = "Help message:\n\
	put N     - put N in a Queue\n\
	peek      - First element in the Queue\n\
	get       - Remove element from the Queue\n\
	clear     - Remove all elements from Queue\n\
	h or help - Show this message again\n\
	q or quit - Back to Data struct menu";

	Queue<int> queue; // ������� ����� �����
	string action = "h"; // �������� �� ���������

	while (action != "q" && action != "quit") // ���� �������� �� q ��� quit
	{
		try
		{
			if (action == "put") // put - ���������� ��-�� � �������
			{
				int data; // ��-� ��� ����������

				cin >> data;
				queue.put(data); // ���������� ��-�� � �������
			}
			else if (action == "peek") // peek - �������� ������� � ������� ��-��
				cout << "Output: " << queue.peek() << endl;
			else if (action == "get") // get - ������ ������� ��-�� �� �������
				cout << "Output: " << queue.get() << endl;
			else if (action == "clear") // clear - ������� �������
				queue.clear();
			else if (action == "h" || action == "help") // ������ ��������� � ����������
				cout << helpMsg << endl;
			else // ������ �� ���� ��������������
			{
				while (cin.get() != '\n'); // ������� ������ �����
				cout << "Error: Unknown command. Use \"h\" or \"help\" to get help message." << endl;
			}
		}
		catch (exception &e) // ���� �������� ������
		{
			cout << "Error: " << e.what() << endl;
		}

		cout << endl << "Input: ";
		cin >> action; // ��������� ��������
	}
}

// ������������ ���� (�������/������������ �������)
void testDeque()
{
	// ��������� � ����������
	const char *helpMsg = "Help message:\n\
	append     - Put element at the right end of the Deque\n\
	appendleft - Put element at the left end of the Deque\n\
	clear      - Remove all elements from Deque\n\
	peek       - Element at the right end of the Deque\n\
	peekleft   - Element at the left end of the Deque\n\
	pop        - Remove element from the right end of the Deque\n\
	popleft    - Remove element from the left end of the Deque\n\
	h or help  - Show this message again\n\
	q or quit  - Back to Data struct menu";

	Deque<int> deque; // ��� ����� �����
	string action = "h"; // �������� �� ���������

	while (action != "q" && action != "quit") // ���� �������� �� q ��� quit
	{
		try
		{
			if (action == "append") // append - �������� � ��� ������
			{
				int data; // ��-� ��� ����������

				cin >> data;
				deque.append(data); // ���������� ��-�� � ������ ����� ����
			}
			else if (action == "appendleft") // appendleft - �������� � ��� �����
			{
				int data; // ��-�� ��� ����������

				cin >> data;
				deque.appendleft(data); // ���������� ��-�� � ����� ����� ����
			}
			else if (action == "clear") // clear - ������� ����
				deque.clear();
			else if (action == "peek") // peek - �������� ������� ��-�� ����
				cout << "Output: " << deque.peek() << endl;
			else if (action == "peekleft") // peekleft - �������� ������ ��-�� ����
				cout << "Output: " << deque.peekleft() << endl;
			else if (action == "pop") // pop - �������� ������� ��-�� ����
				cout << "Output: " << deque.pop() << endl;
			else if (action == "popleft") // popleft - �������� ������ ��-�� ����
				cout << "Output: " << deque.popleft() << endl;
			else if (action == "h" || action == "help") // ������ ��������� � ����������
				cout << helpMsg << endl;
			else // ������ �� ���� ��������������
			{
				while (cin.get() != '\n'); // ������� ������ �����
				cout << "Error: Unknown command. Use \"h\" or \"help\" to get help message." << endl;
			}
		}
		catch (exception &e) // ���� �������� ������
		{
			cout << "Error: " << e.what() << endl;
		}

		cout << endl << "Input: ";
		cin >> action; // ��������� ��������
	}
}

// ������������ ���-������
void testAVLTree()
{
	// ��������� � ������� ���������� ������
	char helpMsg[] = "Help message:\n\
	append N  - Add number to AVL-Tree\n\
	remove N  - Removing N from Tree\n\
	print     - Printing Tree(recommended only for small trees)\n\
	clear     - Clear tree\n\
	h or help - Show this message again\n\
	q or quit - Quit";


	Tree<int> tree; // ������
	string action = "h"; // ��������

	while (action != "q" && action != "quit") // ���� �������� != q ��� quit (���������� ������)
	{
		if (action == "append") // ����������
		{
			int data; // ��-� ��� ����������
			cin >> data;

			tree.append(data); // ���������� ��-��
		}
		else if (action == "remove") // ��������
		{
			int data; // ��-�� ��� ��������
			cin >> data;

			tree.remove(data); // �������� ��-��
		}
		else if (action == "clear") // �������
			tree.clear();
		else if (action == "print") // �����
		{
			cout << "Output:" << endl << endl;
			printTree(tree); // ����� ������
			cout << endl;
		}
		else if (action == "h" || action == "help") // ����� ���������������� ���������
			cout << helpMsg << endl;
		else
		{
			while (cin.get() != '\n'); // ������� ������ �����
			cout << "Error: Unknown command. Use \"h\" or \"help\" to get help message." << endl;
		}

		cout << endl << "Input: ";
		cin >> action; // ��������� �������� (���� �����)
	}
}


// ������������ �������� �������
void testPN()
{
	SetConsoleTitle("TEST: Polish Notation"); // ��������� �������
	system("cls"); // ������� �������

	// ��������� � ����������
	const char *helpMsg = "Syntax:\n\
	Built-in Operators: + - * / ^ ( )\n\
	Statment sin + 2 : sin - variable\n\
	Statment sin(2)  : sin - function\n\
	(variable and function names should be [a-zA-Z])\n\
	Spacing and recurring brackets is not improtant:\n\
		cos(2) ~ cos ( (2 ))  and  5+5 ~ 5 +5\n\
	Unary minus : -5 ~ 0 - 5  and  2 + (-3) ~ 2 + (0 - 3)\n\
	h or help : Show this message again\n\
	q or quit : Back to Main menu";


	cin.ignore(); // ������� ������ �����
	char expr[255] = "h"; // ��������� (������ ��� ��������� ��������� � ����������)
	while (strcmp(expr, "q") && strcmp(expr, "quit")) // ���� ������������ �� ���� q ��� quit
	{
		// ����� ��������� � ����������
		if (!strcmp(expr, "h") || !strcmp(expr, "help"))
			cout << helpMsg << endl << endl;
		else if (expr[0] != '\0') // ���� ��������� �� ������
		{
			cout << "Polish Notation: ";

			try
			{
				cout << toPN(expr) << endl << endl; // ������� � �������� �������
			}
			catch (exception &e) // ���� ��������� ������
			{
				cout << e.what() << endl << endl; // ������� �� ������������
			}
		}

		cout << "Your expression: ";
		cin.getline(expr, 255); // ��������� ������������
	}
}