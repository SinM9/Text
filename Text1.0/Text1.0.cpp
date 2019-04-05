// Text1.0.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
using namespace std;
#include "TTextLink.h"
#include "TText.h"

TTextMem TTextLink::MemHeader;
void Menu(TText Text);
int main()
{
	setlocale(0, "");
	char Str[] = "Text.txt";
	string strs[100];
	int ns;
	TTextLink A;
	A.InitMemSystem();
	TText Text, pText;
	Text.Read(Str);
	//Text.Write(Str);
	Text.Print();
	cout << endl;
	Text.GoFirstLink();
	Menu(Text);


	//Text.DelNextLine();
	//A.MemCleaner(Text);
	//A.PrintFreeLink();
	//Text.Print();

	ns = 0;
	for (Text.Reset(); !Text.IsTextEnded(); Text.GoNext())
		strs[ns++] = Text.GetLine();

	Text.GoFirstLink();
	pText = *Text.GetCopy();
	cout << "Копия текста: " << endl;
	pText.Print();
	system("pause");
	return 0;
}

void Menu(TText Text)
{
	while (1)
	{
		TTextLink A;
		char S[100];
		int k;
		cout <<endl<< "Текущий уровень:  ";
		Text.PrintLink();
		cout << endl << " 1 - навигация" << endl << " 2 - замена текущей строки" << endl << " 3 - вставка" << endl << " 4 - удаление" << endl << " 0 - выход" << endl;
		cin >> k;
		switch (k)
		{
		case 1:
			cout << " 1 - переход к первой строке" << endl << " 2 - переход к следующей строке по Down" << endl << " 3 - переход к следующей строке по Next" << endl << " 4 - переход к предыдущей позиции в тексте " << endl;
			cin >> k;
			switch (k)
			{
			case 1:
				Text.GoFirstLink();
				break;
			case 2:
				if (Text.GoDownLink())
				{ 
					cout << "Переход на:  ";
					Text.PrintLink();
				}
				else
					cout << "Ниже перейти нельзя" << endl;
				break;
			case 3:
				if (Text.GoNextLink())
				{
					cout << "Переход на:  ";
					Text.PrintLink();
				}	
				else
					cout << "Дальше перейти нельзя" << endl;
				break;
			case 4:

				if (Text.GoPrevLink())
				{
					cout << "Переход на:  ";
					Text.PrintLink();
				}
				else
					cout << "Предыдущей позиции нет" << endl;
				break;
			default:
				cout << "Неверное значение" << endl;
				break;
			}
			break;
		case 2:
			cout << " >>   ";
			cin >> S;
			Text.SetLine(S);
			break;
		case 3:
			cout << " 1 - вставка строки в подуровень" << endl << " 2 - вставка раздела в подуровень" << endl << " 3 - вставка строки в том же уровне" << endl << " 4 - вставка раздела в том же уровне " << endl;
			cin >> k;
			switch (k)
			{
			case 1:
				cout << " >>   ";
				cin >> S;
				Text.InsDownLine(S);
				Text.Print();
				cout << endl;
				break;
			case 2:
				cout << " >>   ";
				cin >> S;
				Text.InsDownSection(S);
				Text.Print();
				cout << endl;
				break;
			case 3:
				cout << " >>   ";
				cin >> S;
				Text.InsNextLine(S);
				Text.Print();
				cout << endl;
				break;
			case 4:
				cout << " >>   ";
				cin >> S;
				Text.InsNextSection(S);
				Text.Print();
				cout << endl;
				break;
			default:
				cout << "Неверное значение" << endl;
				break;
			}
			break;
		case 4:
			cout << " 1 - удаление строки в подуровене" << endl << " 2 - удаление раздела в подуровене" << endl << " 3 - удаление строки в том же уровне" << endl << " 4 - удаление раздела в том же уровне " << endl;
			cin >> k;
			switch (k)
			{
			case 1:
				k = -2;
				Text.DelDownLine();
				Text.Print();
				cout << endl;
				break;
			case 2:
				k = -2;
				Text.DelDownSection();
				Text.Print();
				cout << endl;
				break;
			case 3:
				k = -2;
				Text.DelNextLine();
				Text.Print();
				cout << endl;
				break;
			case 4:
				k = -2;
				Text.DelNextSection();
				Text.Print();
				cout << endl;
				break;
			default:
				cout << "Неверное значение" << endl;
				break;
			}
		case 0:
			k = -1;
		default:
			break;
		}
		if (k == -2)
		{
			A.MemCleaner(Text);
			//A.PrintFreeLink();
		}
		if (k == -1)
			break;
	}
}

