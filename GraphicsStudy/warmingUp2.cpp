#include <iostream>
#include <fstream>
#include <conio.h>
#include <sstream>

using namespace std;

void readFile(ifstream& in, string& str);
int countWord(const string& str);
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

int main()
{
	char key{};
	string str{};
	ifstream in{};
	int count{};

	readFile(in, str);

	cout << "word count: " << countWord(str) << endl;

	while (true)
	{
		help();
		cout << "Input command" << endl;
		key = _getch();
		cout << key << endl;

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

void readFile(ifstream& in, string& str)
{
	cout << "Input the file's name: ";
	cin >> str;

	in.open(str);

	while (!in.is_open())
	{
		cout << "The file is not exist. Input the file's name: ";
		cin >> str;
		in.open(str);
	}

	in.seekg(0, std::ios::end);

	const int size = in.tellg();

	in.seekg(0, std::ios::beg);

	str.resize(size);

	in.read(&str[0], size);

	cout << endl << str << endl << endl;
}

int countWord(const string& str)
{
	int count{};



	return count;
}
