#pragma once
#include <iostream>
using namespace std;
#include "TTextMem.h"
#include "TText.h"
#include <string.h>
class TTextLink
{
protected:
	TStr Str; // поле для хранения строки текста
	PTTextLink pNext, pDown;  // указатели по тек.уровень и на подуровень
	static TTextMem MemHeader; //система управления памятью
	virtual void Print(ostream &os) { os << Str; }
	friend class TText;
public:
	static void InitMemSystem(int size = MemSize); // инициализация памяти
	static void PrintFreeLink(void); // печать свободных звеньев
	void * operator new (size_t size); // выделение звена
	void operator delete (void *pM);   // освобождение звена
	void MemCleaner(TText &txt); // сборка мусора
	TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL) { pNext = pn; pDown = pd; if (s != NULL) strcpy_s(Str, s); else 	Str[0] = '\0'; }
	~TTextLink() {}
	int IsAtom() { return pDown == NULL; } // проверка атомарности звена
	void PrintStr() { puts(Str); }
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }
	PTTextLink GetCopy() { return new TTextLink(Str, pNext, pDown); }

};

