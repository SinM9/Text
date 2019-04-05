
#include "pch.h"
#include "TText.h"


TText::TText(PTTextLink pl)
{
	if (pl == NULL)
		pl = PTTextLink();
	pFirst = pl;
}

int TText::GoFirstLink(void) // 1 - TextOK, 2 - TextError
{
	int RetCode;
	while (!Path.empty())
		Path.pop();
	pCurrent = pFirst;
	if (pCurrent == NULL)
		RetCode = 0;
	else
		RetCode = 1;
	return RetCode;
}

int TText::GoDownLink(void) // 1 - TextOK, 2 - TextError
{
	int RetCode = 0;
	if (pCurrent != NULL)
	{
		if (pCurrent->pDown != NULL)
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pDown;
			RetCode = 1;
		}
	}
	return RetCode;
}

int TText::GoNextLink(void) // 1 - TextOK, 2 - TextError
{
	int RetCode = 0;
	if (pCurrent != NULL)
	{
		if (pCurrent->pNext != NULL)
		{
			Path.push(pCurrent);
			pCurrent = pCurrent->pNext;
			RetCode = 1;
		}
	}
	return RetCode;
}

int TText::GoPrevLink(void) // 1 - TextOK, 2 - TextNoPrev
{
	int RetCode;
	if (Path.empty())
		RetCode = 0;
	else
	{
		pCurrent = Path.top();
		Path.pop();
		RetCode = 1;
	}
	return RetCode;
}

string TText::GetLine(void)
{
	if (pCurrent == NULL)
		return string("");
	else
		return string(pCurrent->Str);
}

void TText::SetLine(string s)
{
	if (pCurrent == NULL)
		cout << "TextError" << endl;
	else
		strncpy_s(pCurrent->Str, s.c_str(), TextLineLength);
	pCurrent->Str[TextLineLength - 1] = '\0';
}

void TText::InsDownLine(string s)//  вставка строки в подуровень
{
	if (pCurrent == NULL)
		cout << "TextError" << endl;
	else
	{
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink(NULL, pd, NULL);
		strncpy_s(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
	}
}

void TText::InsDownSection(string s)// вставка раздела в подуровень
{
	if (pCurrent == NULL)
		cout << "TextError" << endl;
	else
	{
		PTTextLink pd = pCurrent->pDown;
		PTTextLink pl = new TTextLink(NULL, NULL, pd);
		strncpy_s(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pDown = pl;
	}
}

void TText::InsNextLine(string s)// вставка строки в том же уровне
{
	if (pCurrent == NULL)
		cout << "TextError" << endl;
	else
	{
		PTTextLink pn = pCurrent->pNext;
		PTTextLink pl = new TTextLink(NULL, pn, NULL);
		strncpy_s(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
	}
}

void TText::InsNextSection(string s)// вставка раздела в том же уровне
{
	if (pCurrent == NULL)
		cout << "TextError" << endl;
	else
	{
		PTTextLink pn = pCurrent->pNext;
		PTTextLink pl = new TTextLink(NULL, NULL, pn);
		strncpy_s(pl->Str, s.c_str(), TextLineLength);
		pl->Str[TextLineLength - 1] = '\0';
		pCurrent->pNext = pl;
	}
}

void TText::DelDownLine(void)//  удаление строки в подуровне
{
	if (pCurrent == NULL)
		cout << "TextError" << endl;
	else
		if (pCurrent->pDown != NULL)
		{
			PTTextLink pl1 = pCurrent->pDown;
			PTTextLink pl2 = pl1->pNext;
			if (pl1->pDown == NULL)
				pCurrent->pDown = pl2;

		}
}

void TText::DelDownSection(void)// удаление раздела в подуровне
{
	if (pCurrent == NULL)
		cout << "TextError" << endl;
	else
		if (pCurrent->pDown != NULL)
		{
			PTTextLink pl1 = pCurrent->pDown;
			PTTextLink pl2 = pl1->pNext;
			pCurrent->pDown = pl2;
		}
}

void TText::DelNextLine(void)//   удаление строки в том же уровне
{
	if (pCurrent == NULL)
		cout << "TextError" << endl;
	else
		if (pCurrent->pNext != NULL)
		{
			PTTextLink pl1 = pCurrent->pNext;
			PTTextLink pl2 = pl1->pNext;
			if (pl1->pDown == NULL)
				pCurrent->pNext = pl2;
		}
}

void TText::DelNextSection(void)// удаление раздела в том же уровне
{
	if (pCurrent == NULL)
		cout << "TextError" << endl;
	else
		if (pCurrent->pNext != NULL)
		{
			PTTextLink pl1 = pCurrent->pNext;
			PTTextLink pl2 = pl1->pNext;
			pCurrent->pNext = pl2;
		}
}

int TText::Reset(void)
{
	while (!St.empty())
		St.pop();
	pCurrent = pFirst;
	if (pCurrent != NULL)
	{
		St.push(pCurrent);
		if (pCurrent->pNext != NULL)
			St.push(pCurrent->pNext);
		if (pCurrent->pDown != NULL)
			St.push(pCurrent->pDown);
	}
	return IsTextEnded();
}

int TText::IsTextEnded(void)const
{
	return !St.size();//возвращает 0, если в стеке что-то есть => 1, если пустой
}

int TText::GoNext(void)//переход к след записи
{
	if (!IsTextEnded())
	{
		pCurrent = St.top();//если после выборки стек пуст, значит первая строка текста уже была обработана
		St.pop();
		if (pCurrent != pFirst)
		{
			if (pCurrent->pNext != NULL)
				St.push(pCurrent->pNext);

			if (pCurrent->pDown != NULL)
				St.push(pCurrent->pDown);
		}
	}
	return IsTextEnded();
}

PTTextLink TText::GetFirstAtom(PTTextLink pl)
{
	PTTextLink tmp = pl;
	while (!tmp->IsAtom())
	{
		St.push(tmp);
		tmp = tmp->GetDown();
	}
	return tmp;
}

PTText TText::GetCopy()
{
	TStr c = "copy";
	PTTextLink pl1, pl2, pl = pFirst, cpl = NULL;
	if (pFirst != NULL)
	{
		while (!St.empty())
			St.pop();
		while (1)
		{
			if (pl != NULL)
			{
				pl = GetFirstAtom(pl);
				St.push(pl);
				pl = pl->GetDown();
			}
			else
				if (St.empty())
					break;
				else
				{
					pl1 = St.top();
					St.pop();
					if (strstr(pl1->Str, c) == NULL)
					{
						pl2 = new TTextLink(c, pl1, cpl);
						St.push(pl2);
						pl = pl1->GetNext();
						cpl = NULL;
					}
					else
					{
						pl2 = pl1->GetNext();
						strcpy_s(pl1->Str, pl2->Str);
						pl1->pNext = cpl;
						cpl = pl1;
					}
				}
		}
	}
	return new TText(cpl);
}

void TText::Print(void)
{
	TextLevel = 0;
	PrintText(pFirst);
}

void TText::PrintText(PTTextLink ptl)
{
	if (ptl != NULL)
		for (int i = 0; i < TextLevel; i++)
			cout << "  ";
	ptl->PrintStr();
	TextLevel++;
	if (ptl->GetNext() != NULL)
	{
		PrintText(ptl->GetNext());
	}
	if (ptl->GetDown() != NULL)
	{
		PrintText(ptl->GetDown());
	}
	TextLevel--;
}

void TText::Read(char *pFileName)
{
	ifstream TxtFile(pFileName);
	TextLevel = 0;
	while (!St.empty())
		St.pop();
	if (TxtFile)
		pFirst = ReadText(TxtFile);
}

void TText::Write(char* pFileName)
{
	ofstream TxtFile(pFileName);
	TxtFile << "Part";
	TxtFile << "{";
	TxtFile << "Section";
	TxtFile << "}";
	TxtFile.close();
}

PTTextLink TText::ReadText(ifstream &TxtFile)
{
	int flag = 2;
	char Strbuf[50];
	PTTextLink pHead, ptl, p;
	pHead = ptl = p = new TTextLink();
	while (TxtFile.eof() == 0)
	{
		TxtFile.getline(Strbuf, 50, '\n');
		if (Strbuf[0] == '}')
		{
			if (flag == 0)
			{
				St.pop();
			}
			TextLevel++;
			p = St.top();
			St.pop();
			p->pDown = ReadText(TxtFile);
		}
		else
		{
			if (Strbuf[0] != '{')
			{
				if (flag == 0)
				{
					St.pop();
				}
				ptl->pNext = new TTextLink(Strbuf, NULL, NULL);
				ptl = ptl->pNext;
				St.push(ptl);
				flag = 0;
			}
			else
			{
				flag = 1;
			}
		}
	}
	ptl = pHead;
	if (pHead->pDown == NULL)
	{
		pHead = pHead->pNext;
		delete ptl;
	}
	return pHead;
}

void TText::PrintLink(void)
{
	if (pCurrent == NULL)
		cout<<"";
	else
		cout<< (pCurrent->Str);

}