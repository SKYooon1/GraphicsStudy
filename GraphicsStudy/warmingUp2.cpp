#include <iostream>
#include <fstream>
#include <conio.h>
#include <sstream>

using namespace std;

void readFile(ifstream& in, string& str);
int countWord(const string& str);
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
