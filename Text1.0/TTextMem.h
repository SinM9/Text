#pragma once
#define TextLineLength 20
#define MemSize 20
class TTextLink;
typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];
class TTextMem
{
	PTTextLink pFirst;     // ��������� �� ������ �����
	PTTextLink pLast;      // ��������� �� ��������� �����
	PTTextLink pFree;      // ��������� �� ������ ��������� �����
	friend class TTextLink;
};
typedef TTextMem *PTTextMem;

