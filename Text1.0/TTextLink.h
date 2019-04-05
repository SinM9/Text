#pragma once
#include <iostream>
using namespace std;
#include "TTextMem.h"
#include "TText.h"
#include <string.h>
class TTextLink
{
protected:
	TStr Str; // ���� ��� �������� ������ ������
	PTTextLink pNext, pDown;  // ��������� �� ���.������� � �� ����������
	static TTextMem MemHeader; //������� ���������� �������
	virtual void Print(ostream &os) { os << Str; }
	friend class TText;
public:
	static void InitMemSystem(int size = MemSize); // ������������� ������
	static void PrintFreeLink(void); // ������ ��������� �������
	void * operator new (size_t size); // ��������� �����
	void operator delete (void *pM);   // ������������ �����
	void MemCleaner(TText &txt); // ������ ������
	TTextLink(TStr s = NULL, PTTextLink pn = NULL, PTTextLink pd = NULL) { pNext = pn; pDown = pd; if (s != NULL) strcpy_s(Str, s); else 	Str[0] = '\0'; }
	~TTextLink() {}
	int IsAtom() { return pDown == NULL; } // �������� ����������� �����
	void PrintStr() { puts(Str); }
	PTTextLink GetNext() { return pNext; }
	PTTextLink GetDown() { return pDown; }
	PTTextLink GetCopy() { return new TTextLink(Str, pNext, pDown); }

};

