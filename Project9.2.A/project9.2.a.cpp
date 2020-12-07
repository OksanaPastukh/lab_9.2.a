#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h> // забезпечення відображення кирилиці
using namespace std;
enum Specialty { ComputerScience, Informatics, Mathematics, Physics, Work };
string specialtyStr[] = { "Комп'ютерні науки", "Інформатика", "Матем.та економ.","Фізика та інформ.","Трудове навчання" };
struct Student
{
	string prizv;
	unsigned course;
	Specialty specialty;
	unsigned grades_in_physics;
	unsigned grades_in_mathematics;
	unsigned grades_in_informatic;
};
void Create(Student* p, const int N);
void Print(Student* p, const int N);
void Sort(Student* p, const int N);
int* IndexSort(Student* p, const int N);
void PrintIndexSorted(Student* p, int* I, const int N);
int BinSearch(Student* p, const int N, const string prizv, const unsigned grades_in_informatic, const unsigned course);
int main()
{
	SetConsoleCP(1251); // встановлення сторінки win-cp1251 в потік вводу
	SetConsoleOutputCP(1251); // встановлення сторінки win-cp1251 в потік виводу

	int N;
	cout << "Введіть кількість студентів N: "; cin >> N;

	Student* p = new Student[N];
	unsigned grades_in_informatic;
	unsigned course;
	string prizv;
	int found;
	int menuItem;
	do {
		cout << endl << endl << endl;
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;
		cout << " [3] - фізичне впорядкування даних" << endl << endl;
		cout << " [4] - індексне впорядкування та вивід даних"
			<< endl << endl;
		cout << " [5] - бінарний пошук працівника за посадою та прізвищем"
			<< endl << endl;
		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть значення: "; cin >> menuItem;
		cout << endl << endl << endl;
		switch (menuItem)
		{
		case 1:
			Create(p, N);
			break;
		case 2:
			Print(p, N);
			break;
		case 3:
			Sort(p, N);
			Print(p, N);
			break;
		case 4:
			PrintIndexSorted(p, IndexSort(p, N), N);
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cout << " оцінка з  з третього предмету: ";
			cin >> grades_in_informatic;
			cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
			cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядо
			cout << " курс: ";
			cin >> course;
			cin.get(); 
			cin.sync(); 
			cout << " прізвище: "; getline(cin, prizv);
			cout << endl;
			if ((found = BinSearch(p, N, prizv, grades_in_informatic,course)) != -1)
				cout << "Знайдено працівника в позиції " << found + 1 << endl;
			else
				cout << "Шуканого працівника не знайдено" << endl;
			break;


		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
	} while (menuItem != 0);
	return 0;
}
void Create(Student* p, const int N)
{
	int specialty;
	for (int i = 0; i < N; i++)
	{
		cout << "Студент № " << i + 1 << ":" << endl;
		cin.get(); // очищуємо буфер клавіатури – бо залишаються символи
		cin.sync(); // "кінець рядка", які не дають ввести наступний літерний рядок

		cout << " прізвище: "; getline(cin, p[i].prizv);
		cout << " курс: "; cin >> p[i].course;
		cout << "  спеціальність (0 -Комп'ютерні науки , 1 -Інформатика, 2 -Матем. та економ., 3 - Фізика та інформ., 4 - Трудове навчання): ";
		cin >> specialty;
		p[i].specialty = (Specialty)specialty;
		cout << "  оцінки з фізики: "; cin >> p[i].grades_in_physics;
		cout << "  оцінки з математики: "; cin >> p[i].grades_in_mathematics;
		cout << "  оцінки з інформатики: "; cin >> p[i].grades_in_informatic;
	}
}
void Print(Student* p, const int N)
{
	cout << "=================================================================================================="
		<< endl;
	cout << "|№  |Прізвище  |Курс|Cпеціальність    |Oцінки з фізики|Oцінки з математики|Oцінки з інформатики |"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{
		cout << "|" << setw(2) << right << i + 1 << " ";
		cout << "|" << setw(10) << left << p[i].prizv;
		cout << "|" << setw(3) << right << p[i].course << " ";
		cout << "|" << setw(17) << left << specialtyStr[p[i].specialty];
		cout << "|" << setw(14) << right << p[i].grades_in_physics << " ";
		cout << "|" << setw(18) << right << p[i].grades_in_mathematics << " ";
		cout << "|" << setw(20) << right << p[i].grades_in_informatic << " " << " |" << endl;
	}
	cout << "=================================================================================================="
		<< endl;
	cout << endl;
}
void Sort(Student* p, const int N)
{
	Student tmp;
	for (int i0 = 0; i0 < N - 1; i0++) // метод "бульбашки"
		for (int i1 = 0; i1 < N - i0 - 1; i1++)
			if ((p[i1].grades_in_informatic < p[i1 + 1].grades_in_informatic)
				||
				(p[i1].grades_in_informatic == p[i1 + 1].grades_in_informatic &&
					p[i1].course < p[i1 + 1].course)
				||
				(p[i1].course == p[i1 + 1].course &&
					p[i1].prizv < p[i1 + 1].prizv))
			{
				tmp = p[i1];
				p[i1] = p[i1 + 1];
				p[i1 + 1] = tmp;
			}
}
int* IndexSort(Student* p, const int N)
{ 
    int* I = new int[N]; // створили індексний масив
	for (int i = 0; i < N; i++)
		I[i] = i; // заповнили його початковими даними
	int i, j, value; // починаємо сортувати масив індексів
	for (i = 1; i < N; i++)
	{
		value = I[i];
		for (j = i - 1;
			j >= 0 && ((p[I[j]].grades_in_informatic < p[value].grades_in_informatic) ||
				(p[I[j]].grades_in_informatic == p[value].grades_in_informatic &&
					p[I[j]].course < p[value].course)
				||
				(p[I[j]].course == p[value].course &&
					p[I[j]].prizv > p[value].prizv));
			j--)
		{
			I[j + 1] = I[j];
		}
		I[j + 1] = value;
	}
	return I;
}
void PrintIndexSorted(Student* p, int* I, const int N)
{
	cout << "=================================================================================================="
		<< endl;
	cout << "|№  |Прізвище  |Курс|Cпеціальність    |Oцінки з фізики|Oцінки з математики|Oцінки з інформатики |"
		<< endl;
	cout << "--------------------------------------------------------------------------------------------------"
		<< endl;
	for (int i = 0; i < N; i++)
	{

		cout << "|" << setw(2) << right << i + 1 << " ";
		cout << "|" << setw(10) << left << p[I[i]].prizv;
		cout << "|" << setw(3) << right << p[I[i]].course << " ";
		cout << "|" << setw(17) << left << specialtyStr[p[I[i]].specialty];
		cout << "|" << setw(14) << right << p[I[i]].grades_in_physics << " ";
		cout << "|" << setw(18) << right << p[I[i]].grades_in_mathematics << " ";
		cout << "|" << setw(20) << right << p[I[i]].grades_in_informatic << " " << " |" << endl;
	}
	cout << "=================================================================================================="
		<< endl;
	cout << endl;
}
int BinSearch(Student* p, const int N, const string prizv, const unsigned grades_in_informatic, const unsigned course)
{ // повертає індекс знайденого елемента або -1, якщо шуканий елемент відсутній
	int L = 0, R = N - 1, m;
	do {
		m = (L + R) / 2;
		if (p[m].grades_in_informatic < grades_in_informatic)
		{
			R = m - 1;
		}
		else if(p[m].grades_in_informatic > grades_in_informatic)
		{
			L = m + 1;
		}
		else
		{
			// (p[m].grades_in_informatic == grades_in_informatic)
			if (p[m].course < course)
			{
				R = m - 1;
			}
			else if (p[m].course > course)
			{
				L = m + 1;
			}
			else
			{
				if (p[m].prizv > prizv)
				{
					L = m + 1;
			    }
				else if (p[m].prizv < prizv)
				{
					R = m - 1;
				}
				else
				{
					return m;
				}
			}
		}
	
	} while (L <= R);
	return -1;
}
