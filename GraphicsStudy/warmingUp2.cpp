#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>

using namespace std;

void readFile(ifstream& in, string& fileName, vector<string>& strings);
void countWord(const vector<string>& strings, int& wordCount, int& numberCount);
bool isNumeric(std::string const& str);
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
	string fileName{};
	ifstream in{};
	int wordCount{};
	int numberCount{};
	vector<string> strings{ 10, " " };

	readFile(in, fileName, strings);



	cout << "word count: " << wordCount << endl;
	cout << "number count: " << numberCount << endl << endl;

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

void readFile(ifstream& in, string& fileName, vector<string>& strings)
{
	cout << "Input the file's name: ";
	cin >> fileName;

	in.open(fileName);

	while (!in.is_open())
	{
		cout << "The file is not exist. Input the file's name: ";
		cin >> fileName;
		in.open(fileName);
	}

	for (int i{}; i < 10; ++i) {
		getline(in, strings.at(i));
	}

	cout << endl;

	for (const string& str : strings)
		cout << str << endl;

	cout << endl;
}

void countWord(const vector<string>& strings, int& wordCount, int& numberCount)
{
	for (string str : strings)
	{
		string s = str.substr(str.find(' '));
		if (isNumeric(s))
			++numberCount;
		else ++wordCount;
		str.erase(0, str.find(' '));

	}
}

bool isNumeric(std::string const& str)
{
	string::const_iterator it = str.begin();
	while (it != str.end() && std::isdigit(*it))
		++it;
	
	return !str.empty() && it == str.end();
}
