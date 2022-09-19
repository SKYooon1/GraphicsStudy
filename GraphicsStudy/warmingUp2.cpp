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
	cout << "명령어 설명" << endl;
	cout << "d : 문장 전체를 뒤집기" << endl;
	cout << "e : 동일한 간격으로 특정 문자 삽입" << endl;
	cout << "f : 띄어쓰기를 기준으로 문자 뒤집기" << endl;
	cout << "g : 원하는 문자를 다른 문자로 바꾸기" << endl;
	cout << "r : 앞에서부터 읽었을 때와 뒤에서부터 읽었을 때 같은 문자 출력하기" << endl;
	cout << "h : 명령어 설명" << endl;
	cout << "q : 프로그램 종료" << endl << endl;
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
