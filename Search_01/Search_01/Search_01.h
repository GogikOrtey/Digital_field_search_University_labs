#pragma once
#include <iostream>
#include <cmath>
#include <time.h>
#include <fstream> 

using namespace std;

class Search_01
{
public:
	struct Data
	{
		int dd;
		int mm;
		int gg;
	};

	Data data;

	struct Dann // Структура с необработанными данными, из текстового файла
	{
		string FIO;
		string Proff;
		Data Data;
		int Staj;
	};

	Dann dann;

	struct AQ // Стандартная структура нужных нам данных
	{
		string d;	// Должность
		int s;		// Стаж
		string fio; // ФИО
		int id = 0; // id
	};


	bool isCreateNewDataFile = false;	// Если true, то создастся новый файл данных, и уже он будет отсотрирован
										// Если false - то будет использоватся имеющийся файл данных. Если его не найдётся - выведется ошибка.

	// Генерирует значения, в текстовый файл, используя 4 других файла
	bool mainCreateData(int AllCount);
	
	// Загружает значения в массивы программы, из текстового файла
	bool Processing_data_from_the_input_file(Dann* mass);

	// Получаем на вход имя файла, и потом загружаем из него во внутренние массивы программы данные
	Search_01::AQ* Processing_data_from_the_input_file(string NameFile); 

	// Загружает значения в программу (Основная процедура)
	Dann* DataCreator(); 

	void coutM(AQ* mass, int n); // Выводим данные в консоль
	void coutQ(AQ mass); // Выводим в консоль только нужную нам строку данных 


	//// ----- БМХ-поиск:

		// Создаём таблицу сдвигов для паттерна
		int* BMH_CreateTablezOfShifts(string pat);

		// Тут мы ищем одновременно и по должности и по ФИО
		Search_01::AQ* BMH_Search_Post_And_FIO(Search_01::AQ* massNS, string patternPost, int* rtPost, int InkPost, string patternFio, int* rtFio, int InkFio);

		// Процедура, которая записывает выходные данные в файл
		bool PrintToFileBMH(Search_01::AQ* mass);

		// Основная процедура БМХ-поиска, со вводом и обработкой данных от пользователя
		void BMH(Search_01::AQ* massNS);

		// Основная процедура БМХ-поиска, с Inside-Code вводом данных
		void BMH(string NameFile, string PattPost, int KPost, string PattFio, int KFio);

	////


	//// ----- РК-поиск:

		int HeshSimv(string str); // Хеш для строки
		int HeshSimv(char str); // Для одиночных символов
		int HeshSimv(string str, int indStart, int length); // Хеш в строке со стартовой позицией и заданной длинной

		// Прямой поиск для РК-поиска
		bool ForwardSearchToRK(string str, string pat, int length, int startPos);

		// РК-поиск по должности и ФИО одновременно
		Search_01::AQ* RK_Search_Post_And_FIO(Search_01::AQ* massNS, string patternPost, int InkPost, string patternFio, int InkFio);

		// Вывод в файл результатов РК-поиска
		bool PrintToFileRK(Search_01::AQ* mass);

		// Основная процедура РК-поиска, со вводом и обработкой данных от пользователя
		void RK(Search_01::AQ* massNS);

		// Основная процедура РК-поиска, с Inside-Code вводом данных
		void RK(string NameFile, string PattPost, int KPost, string PattFio, int KFio);

	////

};

/*
	Создатель кода: Gogik Ortey (Орлов Георгий)
	https://vk.com/gog.ortey

	Этот код предоставляется на условиях открытого доступа.
	Все, кому нужно, могут скопировать и использовать его когда и где захотят.
*/

