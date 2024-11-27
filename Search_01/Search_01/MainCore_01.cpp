#include <iostream>
#include <cmath>
#include <time.h>
#include <fstream> 
#include "Search_01.h"
#include <string>
# include <limits.h>
# include <string.h>
# include <stdio.h>

using namespace std;

int const AllCount = 20; 

void main()
{
	Search_01 Search_01;

	setlocale(LC_ALL, "rus");
	srand(time(0));

	Search_01.BMH("OutFile", "а", 1, "а", 5);
	Search_01.RK("OutFile", "а", 1, "а", 5);

	cout << "Поиск успешно завершён." << endl;
}



void maina()
{
	Search_01 Search_01;

	setlocale(LC_ALL, "rus");
	srand(time(0));

	//Search_01.BMH("OutFile", "а", 1, "а", 5);
	//Search_01.RK("OutFile", "а", 1, "а", 5);

	Search_01.BMH("OutFile", "Хирург", 1, "Семёнова", 1);
	Search_01.RK("OutFile", "о", 1, "Морозова", 5);

	cout << "Поиск успешно завершён." << endl;

	// Отчёт + тесты (7шт.)
}