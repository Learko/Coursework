#include "boyerMoore.h"
#include "..\dataStructures\list.h"
#include "..\string.h"


/* The Bad Character Rule                                                          *
 * ���������� ������� ���� ��������, �� ���� ������                                *
 * �������� ������� �� ���������� �������:                                         *
 * ������� ������� ��������(���� �������) �������� � ������������                  *
 * ������ ��� ���������� ��������� � ������(�� �������� ��������� ������ �������)  *
 * ���� ������� �������� ��� � �������, ��� � ������������ �������� -1             */
int *genStopCharTable(char *needle)
{
	int *table = new int[256]; // ������� �� 256 ��������(�������)
	for (int i = 0; i < 256; i++)
		table[i] = -1; // ��������� -1

	// ���� �� �������������� ��-�� � ���������� � ������ � ����� ������� ������(����� � �������)
	for (int i = 0; needle[i + 1] != '\0'; i++)
		table[needle[i]] = i;

	return table; // ���������� ��������� �� �������
}

/* The Good Suffix Rule                                                     *
 * ���������� ������� ���������, �� ���� ������                             *
 * �������� ������� �� ���������� �������:                                  *
 * ������� ���������� �������� ������ ��������                              *
 * �������� � ������������ �������� - �� ������� ����� ������� ������� ���  *
 * ����� ������� ������ � ��������� ���������� � �������, ������ ��������   *
 * ��� ��� ��������� ������                                                 */
int *genSuffixTable(char *needle)
{
	int needleLen = strlen(needle);      // ������ �������
	int *table = new int[needleLen + 1]; // ������� ���������

	table[0] = 1; // ���� ������� ������, ����� = 1
	for (int sufflen = 1; sufflen <= needleLen; sufflen++) // ����������� ������ �������
	{
		bool found = false; // ���������(�������) ������
		int shift; // �����
		// �� ������ �������� �� ������ �������
		for (shift = needleLen - sufflen - 1; !found && shift >= 0; shift--)
		{
			if (needle[shift] == needle[needleLen - sufflen]) // ���� ������ ������ �������� ������ � �����-�� �������� ��
			{
				// ������� ���-�� ��������� ����
				int match; 
				for (match = 1; needle[shift + match] == needle[needleLen - sufflen + match] && match <= sufflen; match++);

				// ���� ���-�� ��������� ���� = ������ ��������
				if (match == sufflen)
					found = true; // ��������� �������
			}
		}

		// ���� �������
		if (found)
			table[sufflen] = needleLen - sufflen - shift - 1; // ����� = �������� ����� ������� �������� � ������� ��������� ���������
		else
			table[sufflen] = table[sufflen - 1]; // ���� ���, �� ����.
	}

	return table; // ���������� �������
}

/* �������� ������ ��������� � ������ ������-����             *
 * ��������� �� ����: haystack - ����� � needle - ������      *
 * ���������� ������ �������� ����� ���� ���������            *
 * ���� ������ ����������� � ������, ���������� ������ ������ */
List *boyerMoore(char *haystack, char *needle)
{
	List *entry = new List(); // ������� ���� ���������
	int *stopCharTable = genStopCharTable(needle); // ������� ���� �������� "The Bad Character Rule"
	int *suffixTable = genSuffixTable(needle);     // ������� ���������     "The Good Suffix Rule"

	int haystackLen = strlen(haystack); // ������ ������
	int needleLen = strlen(needle);     // ������ �������
	
	int shift = 0; // �����
	while (shift <= haystackLen - needleLen) // ���� ��������� �� ������� � ����� <= ����� ������ - ����� �������
	{
		int badChar; // ������ ������� ������������ ������� (� �����)
		for (badChar = needleLen - 1; haystack[shift + badChar] == needle[badChar] && badChar >= 0; badChar--);
		
		if (badChar == -1) // ���� = -1 ������ ������ ��������� ������
		{
			*entry += shift; // ������ = ������, ��������� ��� � ������
			shift++; // ���������� �� 1
		}
		else
		{
			int stop = shift + badChar; // ������ ������������ �������

			int shiftStop = badChar - stopCharTable[haystack[stop]]; // ����� �� ��������� ����-�������
			int shiftPref = suffixTable[needleLen - 1 - badChar];    // ����� �� ��������� ���������� ��������

			// ����� = ����������� �� ����
			if (shiftStop > shiftPref)
				shift += shiftStop;
			else
				shift += shiftPref;
		}
	}

	return entry; // ���������� ������� ���� ���������
}