#include <iostream>
#include <string>
#include <vector>
#include <ctime>  

#include "City_struct.h"
#include "Timer.h"

using namespace std;

void printMenu(vector<city>& cities);

void printCitiesList(vector<city>& cities);

void generateCitiesList(vector<city>& cities, size_t new_size);

void searchingHub(vector<city>& cities, size_t givenKey);

size_t linearSearch(vector<city>& cities, size_t givenKey);

size_t barierSearch(vector<city>& cities, size_t givenKey);

size_t fibonaccianSearch(vector<city>& cities, size_t givenKey);

vector<city> shellSort(vector<city> cities);




int main()
{
	setlocale(LC_ALL, "ru");
	srand(time(0));

	// Главные переменные
	vector<city> cities;

	//Переменные для пользовательского выбора.
	int userMenuChoice = -1;
	size_t userSize;
	size_t userIndex;

	// Главный меню-цикл.
	while (userMenuChoice != 0)
	{
		system("cls");
		printMenu(cities);

		cin >> userMenuChoice;
		cin.ignore();

		switch (userMenuChoice)
		{
		case 1:
			cities.clear();
			cout << "Введите размер таблицы: ";
			cin >> userSize;
			generateCitiesList(cities, userSize);

			system("pause");
			break;
		case 2:

			if (cities.size())
			{
				cout << "Введите ключ, по которому хотите найти запись в таблице: ";
				cin >> userIndex;
				searchingHub(cities, userIndex);
			}
			else
			{
				cout << "Действие невозможно. Заполните таблицу.\n";
			}

			system("pause");
			break;

		case 0:
			cout << "\nДо свидания!\n";
			userMenuChoice = 0;

			cout << '\n';
			system("pause");
			break;

		case 2022:
			cout << "\nПасхалочка :D\n";

			system("pause");
			break;

		default:
			cout << "\nЯ не понимаю вас.\n";
			cin.clear();

			cout << '\n';
			system("pause");
			break;
		}
	}

	return 0;
}


void printMenu(vector<city>& cities)
{
	cout << "Практическая работа #9 ИКБО-03-21 Мазанов А.Е. Вариант 17\n\n"
		"Задание - Алгоритмы поиска.\n"
		"~~~~~~~~~~~~~~~~~Меню~~~~~~~~~~~~~~~\n"
		"Таблица:\n";
	if (cities.size() <= 10)
	{
		printCitiesList(cities);
	}
	else
	{
		cout << "Сформирована и хранится в памяти.\nРазмер: " 
			<< cities.size() << '\n';
	}

	cout << "\nВведите [1], чтобы сформировать таблицу.\n"
		"Введите [2], чтобы произвести поиск элемента.\n"
		"Введите [0], чтобы закончить работу программы.\n";
	cout << "\nВаш выбор: ";
}

void searchingHub(vector<city>& cities, size_t givenKey)
{
	size_t foundIndex;
	string notFoundString = "Ничего не найдено.\n";

	cout << "\nПоиск элемента по ключу " << givenKey 
		<< " при помощи линейного алгоритма:\n";
	foundIndex = linearSearch(cities, givenKey);
	if (foundIndex < cities.size())
	{
		cout << "Найден элемент с индексом " << foundIndex 
			<< " и инф.значением: " << cities.at(foundIndex).m_name << '\n';
	}
	else
	{
		cout << notFoundString;
	}

	cout << "\nПоиск элемента по ключу " << givenKey 
		<< " при помощи барьерного алгоритма:\n";
	foundIndex = barierSearch(cities, givenKey);
	if (foundIndex < cities.size())
	{
		cout << "Найден элемент с индексом " << foundIndex 
			<< " и инф.значением: " << cities.at(foundIndex).m_name << '\n';
	}
	else
	{
		cout << notFoundString;
	}

	cout << "\nПоиск элемента по ключу " << givenKey
		<< " при помощи алгоритма Фибоначи:\n"
		<< "(индекс элемента будет отличаться от индекса исходной таблицы из-за особенности поиска)\n";
	vector<city> sortedCities = shellSort(cities);

	foundIndex = fibonaccianSearch(sortedCities, givenKey);
	if (foundIndex < cities.size())
	{
		cout << "Найден элемент с индексом " << foundIndex 
			<< " и инф.значением: " << sortedCities.at(foundIndex).m_name << '\n';
	}
	else
	{
		cout << notFoundString;
	}
}


void printCitiesList(vector<city>& cities)
{
	size_t size = cities.size();
	
	if (size)
	{
		cout << "Код региона | Название города\n";
		for (size_t i = 0; i < size; i++)
		{
			cout.width(12);
			cout << cities.at(i).m_key;
			cout << "|";
			cout.width(16);
			cout << cities.at(i).m_name;
			cout << endl;
		}
	}
	else
	{
		cout << "Пуста.\n";
	}
	
}


void generateCitiesList(vector<city>& cities, size_t new_size)
{
	vector<string> cities_names
	{
		"Омск", "Москва", "Рязань", "Казань", "Элиста",
		"Сергиев Посад", "Мирный", "Череповец", "Обнинск",
		"Грозный", "Нальчик", "Сургут"
	};

	vector<size_t> codes;
	for (size_t i = 1; i <= new_size; i++)
	{
		codes.push_back(i);
	}

	size_t randomIndex;
	for (size_t i = 0; i < new_size; i++)
	{
		randomIndex = rand() % codes.size();
		cities.push_back(city(codes.at(randomIndex), cities_names.at(rand() % cities_names.size())));
		codes.erase(codes.begin() + randomIndex);
	}
}


// Простейший поиск - перебор всего массива, если найден элемент с иск.значением - возврат индекса
size_t linearSearch(vector<city>& cities, size_t givenKey)
{
	Timer newTimer;

	for (size_t i = 0; i < cities.size(); i++)
	{
		if (cities.at(i).m_key == givenKey)
		{
			return i;
		}
	}

	return cities.size();
}


// Барьерный поиск - практически то же самое, что и линейный
// Отличие - перебор имеет ограничивающее условие - нахождение искомого значения
// Для этого в конце массива добавляется фиктивный элемент с нужным значением, чтобы ограничить поиск
// Суть оптимизации - сокращение проверок при одной итерации.
size_t barierSearch(vector<city>& cities, size_t givenKey)
{
	// Добавление фиктивного элемента
	cities.push_back(city(givenKey, ""));

	Timer* newTimer = new Timer();

	size_t i = 0;
	for (; givenKey != cities.at(i).m_key; i++) {}

	delete newTimer;

	cities.erase(cities.end() - 1);

	return i;
}


// Фибоначи-поиск. Если запись найдена - возвращает индекс, иначе: размер вектора + 1
size_t fibonaccianSearch(vector<city>& cities, size_t givenKey)
{
	Timer newTimer;

	// Иннициализация переменной-размера массива
	size_t size = cities.size();

	// Стартовое задание чисел фибоначи с инд. m, m-1, m-2
	// где m'ый - макс. число фибоначи,меньшее либо равное размеру массива.
	size_t fib_ind_m2 = 0; // m-2'ое число Фиибоначи.
	size_t fib_ind_m1 = 1; // m-1'ое число Фиибоначи.
	size_t fib_ind_m = fib_ind_m2 + fib_ind_m1; // m'ое число Фиибоначи.

	// Поиск такого m'ого числа фибоначи, оно макс.число фибоначи, меньшее либо равное размеру массива.
	while (fib_ind_m < size) 
	{
		fib_ind_m2 = fib_ind_m1;
		fib_ind_m1 = fib_ind_m;
		fib_ind_m = fib_ind_m2 + fib_ind_m1;
	}

	// Иннициализация индекса - ограничителя.
	int offset = -1;

	// Пока не упёрлись в границы, т.е пока возможен поиск и сокращение числа фибоначи.
	while (fib_ind_m > 1) 
	{
		// Проверка на то, чтобы m-2'ое число фибоначи подходило по размеру
		size_t i = min(offset + fib_ind_m2, size - 1);

		// Если х меньше, чем значение по индексу fib_ind_m2,
		// рассматриваем часть массива с индексами: offset до i
		if (cities.at(i).m_key < givenKey)
		{
			fib_ind_m = fib_ind_m1;
			fib_ind_m1 = fib_ind_m2;
			fib_ind_m2 = fib_ind_m - fib_ind_m1;
			offset = i;
		}

		// Если х меньше, чем значение по индексу fib_ind_m2,
		// рассматриваем часть массива, начинающегося с индекса i + 1
		else if (cities.at(i).m_key > givenKey)
		{
			fib_ind_m = fib_ind_m2;
			fib_ind_m1 = fib_ind_m1 - fib_ind_m2;
			fib_ind_m2 = fib_ind_m - fib_ind_m1;
		}

		// Искомое значение найдено, возврат индекса i
		else
			return i;
	}

	// Проверка последнего элемента с искомым.
	if (fib_ind_m1 && cities.at(offset + 1).m_key == givenKey)
		return offset + 1;

	// Искомое значение не найдено, возврат размера массива
	return cities.size() + 1;
}


vector<city> shellSort(vector<city> cities)
{
	size_t size = cities.size();
	for (size_t d = size / 2; d > 0; d /= 2)
	{
		for (size_t i = d; i < size; ++i)
		{
			for (int j = i - d; j >= 0 && cities.at(j).m_key > cities.at(j + d).m_key; j -= d)
			{
				std::swap(cities.at(j), cities.at(j + d));
			}
		}
	}
	return cities;
}