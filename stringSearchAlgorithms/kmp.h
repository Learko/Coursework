#pragma once
#include "..\dataStructures\list.h"


/* �������� ������ ������� ��������� ��������� � ������ �����-�������-������       *
 * ��������� ������(haystack) � ������(needle)                                     *
 * ���������� ������ �������� ����� ���� ���������                                 */
List *kmp(char *haystack, char *needle);