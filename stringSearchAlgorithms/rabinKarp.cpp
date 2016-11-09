#include <stdexcept>
#include "..\dataStructures\list.h"


/* ��� �������                                     *
 * ��������� ������, � ������ ��-�� �������� ��-�  *
 * (������� ��� �� ���������)                      */
int hash(char * str, int start = 0, int len = 1)
{
	int h = 0; // �������� ��� �������
	for (int i = start; i < start + len; i++) // �������� �� ���� ��-���
		h += str[i];  // ��������� � ���������� ��� ������� ��������� �� ��� ������ � ������

	return h;
}


/* �������� ������ ������� ��������� ��������� � ������ ������-�����               *
 * ��������� ������(haystack) � ������(needle)                                     *
 * ���������� ������ ������� ��������� ��� -1, ���� ��������� ����������� � ������ */
List *rabinKarp(char * haystack, char * needle)
{
	List *entry = new List();

	int haystackLen = strlen(haystack); // ����� ������
	int needleLen = strlen(needle);     // ����� �������

	// ���� ������ ��� ������ ������
	if (needleLen <= 0 || haystackLen <= 0)
		std::logic_error("Empty string");
	
	int needleHash = hash(needle, 0, needleLen);   // ��� �� �������
	int haystackHash = hash(needle, 0, needleLen); // ��� �� ���������(������ ����� �������)

	// ���� �� ������ ���� �� ��������� �����
	for (int shift = 0; shift <= haystackLen - needleLen; shift++)
	{
		// ���� ��� �� ��������� = ���� �� �������
		if (needleHash == haystackHash)
		{
			// ����������� ��������� ��������� �� ������
			int match = 0; // ���-�� ���������
			// ���� ��������� � �� ��������� �����
			while (match < needleLen && needle[match] == haystack[shift + match])
				match++; // ����������� ���-�� ���������

			// ���� ��� �������
			if (match == needleLen)
				*entry += shift;
		}
		else
		{
			// ���� ���� �� ������� ��������� ����� �������� ��� �-�� �� ���������
			haystackHash -= hash(haystack, shift);
			haystackHash += hash(haystack, shift + needleLen);
		}
	}

	return entry; // ���������� ������ ������� ���������
}
