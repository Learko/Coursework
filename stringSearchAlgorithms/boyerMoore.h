#pragma once
#include "..\dataStructures\list.h"

/* �������� ������ ��������� � ������ ������-����             *
 * ��������� �� ����: haystack - ����� � needle - ������      *
 * ���������� ������ �������� ����� ���� ���������            *
 * ���� ������ ����������� � ������, ���������� ������ ������ */
List *boyerMoore(char *haystack, char *needle);