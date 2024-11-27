#include "Search_01.h"

#include <iostream>
#include <cmath>
#include <time.h>
#include <fstream> 
#include <stdlib.h>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>     
#include <errno.h>   

using namespace std;

// Если вам мешают уведомления об ошибках, то просто отключите их))
#pragma warning(disable : 4996)

// Главный счётчик для размеров всех массивов
// Столько записей мы будем создавать и сортировать
int const AllCount = 20;


// Генерируем данные текстового файла из 4х других текстовых файлов
bool Search_01::mainCreateData(int AllCount)
{
	const int size = 250; // Максимальная длинна строки (Имени или профессии)

	string S[size];
	string str;
	int n = 0;
	int r;
	bool genderMan = true;

	fstream OutFile("OutFile.txt", ios::out);  // открываем файл для записи в конец //app - в конец файла

	cout << "count = " << AllCount << endl;

	int turCount = 0;

	while (turCount < AllCount)
	{
		turCount++;

		fstream Famil("Rus Famil.txt", fstream::in);
		fstream ManName("Rus MenName.txt", fstream::in);
		fstream WomenName("Rus FaName.txt", fstream::in);
		fstream Prof("Proffesion.txt", fstream::in);

		if (Famil.is_open() && ManName.is_open() && WomenName.is_open() && Prof.is_open())
		{
			if ((rand() % 2 + 0) == 1)
			{
				genderMan = false;
			}

			r = rand() % 20 + 0;
			n = 0;
			while (!Famil.eof())
			{
				getline(Famil, S[n]);
				if (n == r)
				{
					if (genderMan == true) OutFile << S[n] << " ";
					else OutFile << S[n] << "а" << " ";
					break;
				}
				n++;
			}

			if (genderMan == true)
			{
				r = rand() % 25 + 0;
				n = 0;
				while (!ManName.eof())
				{
					getline(ManName, S[n]);
					if (n == r)
					{
						OutFile << S[n] << " ";
						break;
					}
					n++;
				}

				ManName.close(); WomenName.close();
				fstream ManName("Rus MenName.txt", fstream::in);
				fstream WomenName("Rus FaName.txt", fstream::in);

				r = rand() % 25 + 0;
				n = 0;
				while (!ManName.eof())
				{
					getline(ManName, S[n]);
					if (n == r)
					{
						OutFile << S[n] << "ович";
						break;
					}
					n++;
				}
			}
			else
			{
				r = rand() % 25 + 0;
				n = 0;
				while (!WomenName.eof())
				{
					getline(WomenName, S[n]);
					if (n == r)
					{
						OutFile << S[n] << " ";
						break;
					}
					n++;
				}

				ManName.close(); WomenName.close();
				fstream ManName("Rus MenName.txt", fstream::in);
				fstream WomenName("Rus FaName.txt", fstream::in);

				r = rand() % 25 + 0;
				n = 0;
				while (!WomenName.eof())
				{
					getline(WomenName, S[n]);
					if (n == r)
					{
						OutFile << S[n] << "овна";
						break;
					}
					n++;
				}
			}

			OutFile << ", ";

			r = rand() % 25 + 0;
			n = 0;
			while (!Prof.eof())
			{
				getline(Prof, S[n]);
				if (n == r)
				{
					OutFile << S[n];
					break;
				}
				n++;
			}

			//22.08.2020

			int dd, mm, gg;

			dd = rand() % 29 + 1;
			mm = 11; //rand() % 11 + 1;
			gg = 2021; //rand() % 20 + 2000;

			OutFile << ", " << dd << "." << mm << "." << gg;

			int MainDat = 2022 * 12 * 30;
			int AllDat = gg * 12 * 30 + mm * 30 + dd;
			int currStaj = MainDat - AllDat;

			OutFile << ", " << currStaj << " лет";

			OutFile << endl;

			Famil.close(); ManName.close(); WomenName.close(); Prof.close();
		}
		else return false;
	}

	OutFile.close();
	return true;
}


// Распознаём и записываем данные из файла во внутреннй массив программы, для дальнейшей сортировки
Search_01::AQ* Search_01::Processing_data_from_the_input_file(string NameFile)
{
	Search_01::AQ* mass = new Search_01::AQ[AllCount];

	Search_01 Search_01;


	string S[AllCount];
	int n = 0;

	if (Search_01.isCreateNewDataFile == true)
	{
		if (Search_01.mainCreateData(AllCount)) // Генерируем записи
		{
			cout << "Данные успешно сгенерированы" << endl;
			cout << endl;
		}
		else
		{
			//return false;
			cout << "Ошибка!" << endl;
			exit(000);
		}
	}

	NameFile = NameFile + ".txt";

	fstream DataFile(NameFile, fstream::in);

	if (DataFile.is_open())
	{
		string str = "";

		string nam, fam, oth;

		int intMass = 0;
		n = 0;

		while (n < AllCount) //(!DataFile.eof())
		{
			getline(DataFile, S[n]);
			//cout << S[n] << endl;

			string input = S[n];

			char r;
			int y = 0;

			str = "";
			r = input[y];

			while (r != ' ')
			{
				r = input[y];
				if (r != ' ')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Имя (str) = " << str << endl;

			nam = str;
			str = "";

			r = input[y];

			while (r != ' ')
			{
				r = input[y];
				if (r != ' ')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Фамилия (str) = " << str << endl;

			fam = str;
			str = "";

			r = input[y];

			while (r != ',')
			{
				r = input[y];
				if (r != ',')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Отество (str) = " << str << endl;
			oth = str;

			str = "";

			r = input[y];

			while (r != ',')
			{
				r = input[y];
				if (r != ',')
				{
					str = str + r;
				}
				y++;
			}

			mass[intMass].fio = nam + " " + fam + " " + oth;

			//cout << "Профессия (str) = " << str << endl;
			mass[intMass].d = str;

			str = "";
			y++;
			r = input[y];

			while (r != ' ')
			{
				r = input[y];
				if (r != ' ')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Стаж (str) = " << str << endl;

			char* strng = new char[str.length() + 1];
			strcpy(strng, str.c_str());

			mass[intMass].s = atoi(strng);

			n++;
			intMass++;
		}
	}
	else
	{
		cout << "Ошибка! Файл с именем " << NameFile << " не найден!" << endl;
		exit(000);
	}

	DataFile.close();
	return mass;
}

// Распознаём и записываем данные из файла во внутреннй массив программы, для дальнейшей сортировки
bool Search_01::Processing_data_from_the_input_file(Dann* mass)

{
	string S[AllCount];
	int n = 0;

	if (isCreateNewDataFile == true)
	{
		if (mainCreateData(AllCount)) // Генерируем записи
		{
			cout << "Данные успешно сгенерированы" << endl;
			cout << endl;
		}
		else
		{
			return false;
		}
	}

	fstream DataFile("OutFile.txt", fstream::in);

	if (DataFile.is_open())
	{
		string str = "";

		string nam, fam, oth;

		int intMass = 0;
		n = 0;

		while (n < AllCount) //(!DataFile.eof())
		{
			getline(DataFile, S[n]);
			//cout << S[n] << endl;

			string input = S[n];

			char r;
			int y = 0;

			str = "";
			r = input[y];

			while (r != ' ')
			{
				r = input[y];
				if (r != ' ')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Имя (str) = " << str << endl;

			nam = str;
			str = "";

			r = input[y];

			while (r != ' ')
			{
				r = input[y];
				if (r != ' ')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Фамилия (str) = " << str << endl;

			fam = str;
			str = "";

			r = input[y];

			while (r != ',')
			{
				r = input[y];
				if (r != ',')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Отество (str) = " << str << endl;
			oth = str;

			str = "";

			r = input[y];

			while (r != ',')
			{
				r = input[y];
				if (r != ',')
				{
					str = str + r;
				}
				y++;
			}

			mass[intMass].FIO = nam + " " + fam + " " + oth;

			//cout << "Профессия (str) = " << str << endl;
			mass[intMass].Proff = str;

			str = "";
			r = input[y];

			while (r != '.')
			{
				r = input[y];
				if (r != '.')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Число (str) = " << str << endl;

			char* strng = new char[str.length() + 1];
			strcpy(strng, str.c_str());

			mass[intMass].Data.dd = atoi(strng);

			str = "";
			r = input[y];

			while (r != '.')
			{
				r = input[y];
				if (r != '.')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Месяц (str) = " << str << endl;

			strng = new char[str.length() + 1];
			strcpy(strng, str.c_str());

			mass[intMass].Data.mm = atoi(strng);

			str = "";
			r = input[y];

			while (r != ',')
			{
				r = input[y];
				if (r != ',')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Год (str) = " << str << endl;

			strng = new char[str.length() + 1];
			strcpy(strng, str.c_str());

			mass[intMass].Data.gg = atoi(strng);

			str = "";
			y++;
			r = input[y];

			while (r != ' ')
			{
				r = input[y];
				if (r != ' ')
				{
					str = str + r;
				}
				y++;
			}

			//cout << "Стаж (str) = " << str << endl;

			strng = new char[str.length() + 1];
			strcpy(strng, str.c_str());

			mass[intMass].Staj = atoi(strng);

			n++;
			intMass++;
		}
	}
	else return false;

	DataFile.close();
	return true;
}

// Процедура для управления первыми двумя
// Возвращает NULL, если распознавание дало сбой, или что-то ещё произошло
Search_01::Dann* Search_01::DataCreator()
{
	setlocale(LC_ALL, "rus");
	srand(time(0));
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Dann* mass = new Dann[AllCount]; // Массив для храниения записей как структуру полей

	if (Processing_data_from_the_input_file(mass)) // Загружаем во внутренний массив записи из файла
	{
		cout << endl;
		cout << "Данные успешно обработаны" << endl;

		return mass;
	}
	else
	{
		cout << "Файл, необходимый для обработки записей, не открывается." << endl;
		return NULL;
	}
}






// Выводит данные в консоль
void Search_01::coutM(AQ* mass, int n)
{
	int f = 0;

	for (int i = 0; i < n; i++)
	{
		if (mass[i].d != "")
		{
			cout << "[" << mass[i].fio << ", " << mass[i].d << ", " << mass[i].s << " лет" << "]" << endl;
			f++;
		}
	}

	if (f == 0)
	{
		cout << "<Поиск не дал результатов>" << endl;
	}
}
// Выводит в консоль только нужную нам строку данных
void Search_01::coutQ(AQ mass)
{
	cout << "[" << mass.fio << ", " << mass.d << ", " << mass.s << " лет" << "]" << endl;
}







//// ----- БМХ-поиск:

// Создаём таблицу сдвигов для паттерна
int* Search_01::BMH_CreateTablezOfShifts(string pat)
{
	int s = 255; // Размер алфавита

	int m = pat.length();
	int* rt = new int[s]; // Таблица всех символов

	for (int i = 0; i < s; i++)
	{
		rt[i] = m;
	}

	//cout << "m-1 = " << m - 1 << endl;

	for (int i = 0; i < m - 1; i++)
	{
		// Преобразуем код символа в числовой, процедурой (int)(pat[i])
		rt[(int)(pat[i]) + 127] = m - i - 1;
		//cout << "Числовой код символа " << pat[i] << " = " << (int)(pat[i])+127 << endl;
	}

	return(rt);
}

// Тут мы ищем одновременно и по должности и по ФИО
Search_01::AQ* Search_01::BMH_Search_Post_And_FIO(Search_01::AQ* massNS, string patternPost, int* rtPost, int InkPost, string patternFio, int* rtFio, int InkFio)
{
	Search_01 Search_01;
	Search_01::AQ* massFS = new Search_01::AQ[AllCount];

	int m = patternPost.length(); // Длинна шаблона
	int mff = patternFio.length(); // Длинна шаблона

	int CurkPost = 0;
	int CurkFio = 0;
	int nnn = 0;

	for (int a = 0; a < AllCount; a++)
	{
		int n = massNS[a].d.length(); // Длинна входящей последовательности
		int i = 0;

		while (i <= (n - m))
		{
			int j = m - 1;
			while ((j >= 0) && (massNS[a].d[i + j] == patternPost[j]))
			{
				j = j - 1; // Идём справа налево по шаблону
			}
			if (j < 0) // Если дошли до конца шаблона, помещаем результат в ответ
			{
				CurkPost++;
				//cout << "[Должность]: Найдено совпадение в поле " << massNS[a].d << endl;
			}
			char c = massNS[a].d[i + m - 1];
			i = i + rtPost[(int)(c)+127]; // Шагаем дальше по последовательности, прибавляя нужное число символов
		}

		int nff = massNS[a].fio.length(); // Длинна входящей последовательности
		int iff = 0;

		while (iff <= (nff - mff))
		{
			int jff = mff - 1;
			while ((jff >= 0) && (massNS[a].fio[iff + jff] == patternFio[jff]))
			{
				jff = jff - 1; // Идём справа налево по шаблону
			}
			if (jff < 0) // Если дошли до конца шаблона, помещаем результат в ответ
			{
				CurkFio++;
				//cout << "[ФИО]: Найдено совпадение в поле  " << massNS[a].fio << endl;
			}
			//cout << "i + m - 1 = " << i + m - 1 << endl;
			char c = massNS[a].fio[iff + mff - 1];
			iff = iff + rtFio[(int)(c)+127]; // Шагаем дальше по последовательности, прибавляя нужное число символов
		}

		if ((CurkPost <= InkPost) && (CurkFio <= InkFio) && (CurkPost > 0) && (CurkFio > 0))
		{

			massFS[nnn] = massNS[a];
			nnn++;
		}

		CurkPost = 0;
		CurkFio = 0;
	}

	return(massFS);
}

// Процедура, которая записывает выходные данные в файл
bool Search_01::PrintToFileBMH(Search_01::AQ * mass)
{
	fstream OutSortFile1("ResultBMHSearch.txt", ios::out); // Удаляем все данные из файла
	(OutSortFile1).close();

	int n = AllCount;
	fstream OutSortFile("ResultBMHSearch.txt", ios::app); // Изменить на другие разные названия файлов

	OutSortFile << "БМХ-Поиск: " << endl;
	OutSortFile << "Количество записей: " << n << endl;
	OutSortFile << endl;
	OutSortFile << "Записи, которые есть одновременно в двух запросах: " << endl;

	OutSortFile << endl;

	int f = 0;

	for (int i = 0; i < n; i++)
	{
		if (mass[i].d != "")
		{
			OutSortFile << "[" << mass[i].fio << ", " << mass[i].d << ", " << mass[i].s << " лет" << "]" << endl;
			f++;
		}
	}

	if (f == 0)
	{
		OutSortFile << "<Поиск не дал результатов>" << endl;
	}

	OutSortFile << endl;
	OutSortFile << "-----------------" << endl;
	(OutSortFile).close();
	return(true);
}

// Основная процедура БМХ-поиска, со вводом и обработкой данных от пользователя
void Search_01::BMH(Search_01::AQ* massNS)
{
	Search_01 Search_01;

	string patternPost = "";
	string patternFio = "";

	int PostK;
	int FioK;

	Search_01::AQ* massIn = new Search_01::AQ[AllCount];	// По обоим запросам (смежный)

	cout << endl;
	cout << "Запускаем БМХ-поиск:" << endl;
	cout << endl;

	cout << "Введите шаблон для поля Должность: ";
	//cin >> patternPost;
	//cin.ignore();											// !!! // 
	getline(cin, patternPost);

	int* PostTabl = new int[AllCount];
	int* FioTabl = new int[AllCount];

	PostTabl = Search_01.BMH_CreateTablezOfShifts(patternPost); // Создаём таблицу сдвигов для шаблона	

	while (true)
	{
		cout << "Введите значение k для поиска этого шаблона \nДанный шаблон должен найтись в поле не более k раз: ";
		cin >> PostK;
		if (PostK <= 0)
		{
			cout << "Вы ввели неверные значения для k. Попробуйте ввести их в интевале от 1 до +inf" << endl;
		}
		else break;
	}

	cout << endl;
	cout << "Введите шаблон для поля ФИО: ";
	cin.ignore();
	getline(cin, patternFio);

	FioTabl = Search_01.BMH_CreateTablezOfShifts(patternFio); // Создаём таблицу сдвигов для шаблона

	while (true)
		// Переделать
	{
		cout << "Введите значение k для поиска этого шаблона: ";
		cin >> FioK;
		if (FioK <= 0)
		{
			cout << "Вы ввели неверные значения для k. Попробуйте ввести их в интевале от 1 до +inf" << endl;
		}
		else break;
	}

	massIn = Search_01.BMH_Search_Post_And_FIO(massNS, patternPost, PostTabl, PostK, patternFio, FioTabl, FioK);

	cout << endl;
	cout << "---------------" << endl;
	cout << endl;
	cout << "Общий результат поиска: " << endl;
	cout << endl;

	Search_01.coutM(massIn, AllCount);

	Search_01.PrintToFileBMH(massIn);
}

// Основная процедура БМХ-поиска, с Inside-Code вводом данных
void Search_01::BMH(string NameFile, string PattPost, int KPost, string PattFio, int KFio)
{
	Search_01 Search_01;

	Search_01::AQ* massNS = new Search_01::AQ[AllCount];
	//Search_01::AQ* massRes = new Search_01::AQ[AllCount];

	massNS = Search_01.Processing_data_from_the_input_file(NameFile);

	if (KPost < 0) KPost = 0;
	if (KFio < 0) KFio = 0;

	int* PostTabl = new int[AllCount];
	int* FioTabl = new int[AllCount];

	PostTabl = Search_01.BMH_CreateTablezOfShifts(PattPost); // Создаём таблицу сдвигов для шаблона	
	FioTabl = Search_01.BMH_CreateTablezOfShifts(PattFio); // Создаём таблицу сдвигов для шаблона

	massNS = Search_01.BMH_Search_Post_And_FIO(massNS, PattPost, PostTabl, KPost, PattFio, FioTabl, KFio);

	Search_01.PrintToFileBMH(massNS);

	delete[] massNS;
}








//// ----- РК-поиск:

// Хеш для строки
int Search_01::HeshSimv(string str)
{
	int r = 0;

	for (int i = 0; i < str.length(); i++)
	{
		r += (int)str[i] + 127;
		// В принципе то можно и не добавлять +127, но как показала практика,
		// В С++ символы кодируются от -127 до 128
		// И воспринимать неотрицательные коды визуально удобнее
	}
	return r;
}

// Для одиночных символов
int Search_01::HeshSimv(char str) // Для одиночных символов
{
	return (int)str + 127;
	// Можно эту строчку писать и в коде, но так будет красивее
}

// Хеш в строке со стартовой позицией и заданной длинной
int Search_01::HeshSimv(string str, int indStart, int length)
{
	int r = 0;

	for (int i = indStart; i <= length; i++)
	{
		r += (int)str[i] + 127;
	}
	return r;
}

// Прямой поиск для РК-поиска
bool Search_01::ForwardSearchToRK(string str, string pat, int length, int startPos)
{
	int y = 0;

	//cout << "startPos = " << startPos << " length = " << length << endl;

	for (int i = startPos; i <= length; i++)
	{
		if (str[i] != pat[y]) return false;
		//cout << "str[i] = " << str[i] << " pat[y] = " << pat[y] << endl;
		y++;
	}

	return true;
}
 
// РК-поиск по должности и ФИО одновременно
Search_01::AQ* Search_01::RK_Search_Post_And_FIO(Search_01::AQ* massNS, string patternPost, int InkPost, string patternFio, int InkFio)
{
	Search_01 Search_01;

	int n = 0;

	int CurkPost = 0;
	int CurkFio = 0;

	int lengthPatt = patternPost.length();
	int heshPatt = Search_01.HeshSimv(patternPost);

	int lengthPattF = patternFio.length();
	int heshPattF = Search_01.HeshSimv(patternFio);

	//cout << "heshPatt = " << heshPatt << endl;
	//cout << "lengthPatt = " << lengthPatt << endl;
	//cout << endl;

	Search_01::AQ* massFS = new Search_01::AQ[AllCount];

	int CurHech = 0;
	int CurHechF = 0;

	for (int m = 0; m < AllCount; m++)
	{
		CurHech = 0;

		if (lengthPatt <= massNS[m].d.length())
			// Если проверяемое слово вообще дилиннее шаблона
		{
			for (int i = 1; i < (massNS[m].d.length() - lengthPatt + 1); i++)
			{
				// Ищем от 1, потому что первый символ в поле - пробел

				// Мы будем идти от 1 до того момента, пока длинна шаблона будет больше, чем осталось до конца
				// Дальше шаблона мы всё равно не найдём

				// На этот кусок кода, кончено, было потрачено много времени

				if (i == 1)
				{
					CurHech = Search_01.HeshSimv(massNS[m].d, 1, lengthPatt); /// 
				}
				else
				{
					CurHech = CurHech - Search_01.HeshSimv(massNS[m].d[i - 1]) + Search_01.HeshSimv(massNS[m].d[i + lengthPatt - 1]);
				}

				if (heshPatt == CurHech)
				{
					if (Search_01.ForwardSearchToRK(massNS[m].d, patternPost, lengthPatt, i) == true)
					{
						CurkPost++;
						//cout << "[Должность]: Найдено совпадение в поле " + massNS[m].d << endl;
					}
				}

				//cout << "i = " << i << " " << massNS[m].d[i] << " CurHech =" << CurHech << endl;
			}
		}

		CurHechF = 0;

		if (lengthPattF <= massNS[m].fio.length())
			// Если проверяемое слово вообще дилиннее шаблона
		{
			for (int iF = 0; iF < (massNS[m].fio.length() - lengthPattF + 1); iF++)
			{
				if (iF == 0)
				{
					CurHechF = Search_01.HeshSimv(massNS[m].fio, 0, lengthPattF - 1); /// 
				}
				else
				{
					CurHechF = CurHechF - Search_01.HeshSimv(massNS[m].fio[iF - 1]) + Search_01.HeshSimv(massNS[m].fio[iF + lengthPattF - 1]);
				}

				if (heshPattF == CurHechF)
				{
					if (Search_01.ForwardSearchToRK(massNS[m].fio, patternFio, lengthPattF, iF) == true)
					{
						CurkFio++;
						//cout << "[ФИО]: Найдено совпадение в поле  " + massNS[m].fio << endl;
					}
				}

				//cout << "i = " << i << " " << massNS[m].fio[i] << " CurHech =" << CurHech << endl;
			}
		}

		if ((CurkPost <= InkPost) && (CurkPost > 0))
		{
			if ((CurkFio <= InkFio) && (CurkFio > 0))
			{
				massFS[n] = massNS[m];
				//Search_01.coutQ(massNS[m]);
				n++;
			}
		}

		CurkPost = 0;
		CurkFio = 0;
	}

	return(massFS);
}
 
// Вывод в файл результатов РК-поиска
bool Search_01::PrintToFileRK(Search_01::AQ* mass)
{
	fstream OutSortFile1("ResultRKSearch.txt", ios::out); // Удаляем все данные из файла
	(OutSortFile1).close();

	int n = AllCount;
	fstream OutSortFile("ResultRKSearch.txt", ios::app);

	OutSortFile << "РК-Поиск: " << endl;
	OutSortFile << "Количество записей: " << n << endl;
	OutSortFile << endl;
	OutSortFile << "Записи, которые есть одновременно в двух запросах: " << endl;

	OutSortFile << endl;

	int f = 0;

	for (int i = 0; i < n; i++)
	{
		if (mass[i].d != "")
		{
			OutSortFile << "[" << mass[i].fio << ", " << mass[i].d << ", " << mass[i].s << " лет" << "]" << endl;
			f++;
		}
	}

	if (f == 0)
	{
		OutSortFile << "<Поиск не дал результатов>" << endl;
	}

	OutSortFile << endl;
	OutSortFile << "-----------------" << endl;
	(OutSortFile).close();
	return(true);
}
 
// Основная процедура РК-поиска, со вводом и обработкой данных от пользователя
void Search_01::RK(Search_01::AQ* massNS)
{
	Search_01 Search_01;

	string patternPost = "";
	string patternFio = "";

	int PostK;
	int FioK;

	Search_01::AQ* massIn = new Search_01::AQ[AllCount];

	cout << endl;
	cout << "Запускаем РК-поиск:" << endl;
	cout << endl;

	cout << "Введите шаблон для поля Должность: ";
	//cin >> patternPost;
	cin.ignore();
	getline(cin, patternPost);

	int* massFS = new int[AllCount];

	while (true)
	{
		cout << "Введите значение k для поиска этого шаблона \nДанный шаблон должен найтись в поле не более k раз: ";
		cin >> PostK;
		if (PostK <= 0)
		{
			cout << "Вы ввели неверные значения для k. Попробуйте ввести их в интевале от 1 до +inf" << endl;
		}
		else break;
	}

	cout << endl;
	cout << "Введите шаблон для поля ФИО: ";
	//cin >> patternFio;
	cin.ignore();
	getline(cin, patternFio);

	while (true)
	{
		cout << "Введите значение k для поиска этого шаблона: ";
		cin >> FioK;
		if (FioK <= 0)
		{
			cout << "Вы ввели неверные значения для k. Попробуйте ввести их в интевале от 1 до +inf" << endl;
		}
		else break;
	}

	massIn = Search_01.RK_Search_Post_And_FIO(massNS, patternPost, PostK, patternFio, FioK);

	cout << endl;
	cout << "---------------" << endl;
	cout << endl;

	cout << "Общий результат поиска: " << endl;
	cout << endl;

	Search_01.coutM(massIn, AllCount);

	Search_01.PrintToFileRK(massIn);
}

// Основная процедура РК-поиска, с Inside-Code вводом данных
void Search_01::RK(string NameFile, string PattPost, int KPost, string PattFio, int KFio)
{
	Search_01 Search_01;

	Search_01::AQ* massNS = new Search_01::AQ[AllCount];

	massNS = Search_01.Processing_data_from_the_input_file(NameFile);

	if (KPost < 0) KPost = 0;
	if (KFio < 0) KFio = 0;

	massNS = Search_01.RK_Search_Post_And_FIO(massNS, PattPost, KPost, PattFio, KFio);

	Search_01.PrintToFileRK(massNS);
	delete[] massNS;
}