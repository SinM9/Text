#pragma once
#define TextLineLength 20
#define MemSize 20
class TTextLink;
typedef TTextLink *PTTextLink;
typedef char TStr[TextLineLength];
class TTextMem
{
	PTTextLink pFirst;     // указатель на первое звено
	PTTextLink pLast;      // указатель на последнее звено
	PTTextLink pFree;      // указатель на первое свободное звено
	friend class TTextLink;
};
typedef TTextMem *PTTextMem;

