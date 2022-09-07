#include <iostream>
#include <istream>
#include <conio.h>

using namespace std;

void help();

int main()
{


	help();

	while (true)
	{
		char key{};

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
	cout << "명령어 설명" << endl;
	cout << "d : 문장 전체를 뒤집기" << endl;
	cout << "e : 동일한 간격으로 특정 문자 삽입" << endl;
	cout << "f : 띄어쓰기를 기준으로 문자 뒤집기" << endl;
	cout << "g : 원하는 문자를 다른 문자로 바꾸기" << endl;
	cout << "r : 앞에서부터 읽었을 때와 뒤에서부터 읽었을 때 같은 문자 출력하기" << endl;
	cout << "h : 명령어 설명" << endl;
	cout << "q : 프로그램 종료" << endl << endl;
}
