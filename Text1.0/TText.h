
#pragma once
#include <iostream>
using namespace std;
#include "TTextLink.h"
#include <stack>
#include <fstream>
class TText;
typedef TText * PTText;
class TText
{
protected:
	int TextLevel;
	PTTextLink pFirst;
	PTTextLink pCurrent;
	stack<PTTextLink> Path;
	stack<PTTextLink> St;
	PTTextLink GetFirstAtom(PTTextLink pl); //����� ������� �����
	void PrintText(PTTextLink ptl); // ������ ������ �� ����� ptl
	PTTextLink ReadText(ifstream &TxtFile); // ������ ������ �� �����
public:
	TText(PTTextLink pl = NULL);
	~TText() { pFirst = NULL; }
	PTText GetCopy(); // ���������
	int GoFirstLink(void); // ������� � ������ ������
	int GoDownLink(void); // ������� � ��������� ������ �� Down 
	int GoNextLink(void); // ������� � ��������� ������ �� Next
	int GoPrevLink(void); // ������� � ���������� ������� � ������
	// ������
	string GetLine(void);// ������ ������� ������
	void SetLine(string s); // ������ ������� ������
	// �����������
	void InsDownLine(string s); // ������� ������ � ����������
	void InsDownSection(string s); // ������� ������� � ����������
	void InsNextLine(string s); // ������� ������ � ��� �� ������
	void InsNextSection(string s); // ������� ������� � ��� �� ������
	void DelDownLine(void); // �������� ������ � ���������
	void DelDownSection(void); // �������� ������� � ���������
	void DelNextLine(void); // �������� ������ � ��� �� ������
	void DelNextSection(void); // �������� ������� � ��� �� ������
	// ��������
	int Reset(void); // ���������� �� ������ �������
	int IsTextEnded(void)const;  // ����� ��������?
	int GoNext(void); // ������� � ��������� ������
	// ������ � �������
	void Read(char* pFileName); // ���� ������ �� �����
	void Write(char* pFileName); // ����� ������ � ����
	// ������
	void Print(void); // ������ ������

	void PrintLink(void);
};
