#include <iostream>
#include <fstream>
#include <conio.h>
#include <sstream>

using namespace std;

void help();

int main()
{
	char key{};
	string str{};

	cout << "Input the file's name: ";
	cin >> str;

	ifstream myFile{ str };

	while (!myFile.is_open())
	{
		cout << "The file is not exist. Input the file's name: ";
		cin >> str;
		myFile.open(str);
	}

	while (true)
	{
		help();
		cout << "Input command";
		key = _getch();

		switch (key)
		{
		case 'q':
		case 0x1B:
			return {};
		case 'h':
			help();
			break;
		default:
			cout << "Wrong command" << endl;
			break;
		}
	}
}

void help()
{
	cout << "��ɾ� ����" << endl;
	cout << "d : ���� ��ü�� ������" << endl;
	cout << "e : ������ �������� Ư�� ���� ����" << endl;
	cout << "f : ���⸦ �������� ���� ������" << endl;
	cout << "g : ���ϴ� ���ڸ� �ٸ� ���ڷ� �ٲٱ�" << endl;
	cout << "r : �տ������� �о��� ���� �ڿ������� �о��� �� ���� ���� ����ϱ�" << endl;
	cout << "h : ��ɾ� ����" << endl;
	cout << "q : ���α׷� ����" << endl << endl;
}
