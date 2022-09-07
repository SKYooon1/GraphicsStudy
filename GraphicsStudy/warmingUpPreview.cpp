#include <iostream>
#include <vector>
#include <random>
#include <conio.h>

using namespace std;

class Matrix
{
public:
	Matrix()
	{
		initialize();
	}

	void initialize()
	{
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<int> uid(0, 2);

		member_.clear();
		for (int i = 0; i < 9; ++i)
			member_.push_back(uid(gen));
		calculateDeterminant();
	}

	void printMatrix() const
	{
		for (int i{0}; i < 3; ++i)
		{
			cout << "| ";
			for (int j{ i * 3 }; j < i * 3 + 3; ++j)
				cout << member_[j] << " ";
			cout << "|" << endl;
		}
	}

	void printExpandedMatrix() const
	{
		for (int i{ 0 }; i < 3; ++i)
		{
			cout << "| ";
			for (int j{ i * 3 }; j < i * 3 + 3; ++j)
				cout << member_[j] << " ";
			cout << 0 << " ";
			cout << "|" << endl;
		}

		cout << "| 0 0 0 1 |" << endl;
	}

	void transposeMatrix()
	{
		swap(member_[1], member_[3]);
		swap(member_[2], member_[6]);
		swap(member_[5], member_[7]);
	}

	void printDeterminant() const
	{
		cout << "The determinant is " << determinant_ << endl;
	}

	int member(const int i) const { return member_[i]; }

	void inputValue(const int position, const int value)
	{
		member_[position] = value;
	}

private:
	vector<int> member_;
	int determinant_;

	void calculateDeterminant()
	{
		int determinant{};
		for (int i = 0; i < 3; ++i)
			determinant += member_[i] * (member_[3 + ((i + 1) % 3)] * member_[6 + ((i + 2) % 3)]
				- member_[3 + ((i + 2) % 3)] * member_[6 + ((i + 1) % 3)]);
		determinant_ = determinant;
	}
};

void multiplyMatrix(const Matrix& a, const Matrix& b);
void addMatrix(const Matrix& a, const Matrix& b);
void subtractMatrix(const Matrix& a, const Matrix& b);
void transposeMatrix(Matrix& a, Matrix& b);
void expandMatrix(const Matrix& a, const Matrix& b);
void help();

int main()
{
	Matrix a, b;

	cout << "Matrix A" << endl;
	a.printMatrix();
	cout << "Matrix B" << endl;
	b.printMatrix();
	cout << endl;

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
		case 'm':
			multiplyMatrix(a, b);
			break;
		case 'a':
			addMatrix(a, b);
			break;
		case 's':
			subtractMatrix(a, b);
			break;
		case 'd':
			cout << "The determinants of Matrices" << endl;
			cout << "Matrix A" << endl;
			a.printMatrix();
			a.printDeterminant();
			cout << endl << "Matrix B" << endl;
			b.printMatrix();
			b.printDeterminant();
			cout << endl;
			break;
		case 't':
			transposeMatrix(a, b);
			break;
		case 'e':
			expandMatrix(a, b);
			break;
		case 'r':
			cout << "Make new matrices" << endl;
			a.initialize();
			b.initialize();
			cout << "Matrix A" << endl;
			a.printMatrix();
			cout << "Matrix B" << endl;
			b.printMatrix();
			cout << endl;
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
	cout << "m : 행렬의 곱셈" << endl;
	cout << "a : 행렬의 덧셈" << endl;
	cout << "s : 행렬의 뺄셈" << endl;
	cout << "d : 각 행렬식의 값" << endl;
	cout << "t : 전치행렬과 행렬식의 값" << endl;
	cout << "e : 4x4로 변환된 행렬과 그 행렬식의 값" << endl;
	cout << "r : 행렬의 값 랜덤 재설정" << endl;
	cout << "h : 명령어 설명" << endl;
	cout << "q : 프로그램 종료" << endl << endl;
}

void multiplyMatrix(const Matrix& a, const Matrix& b)
{
	Matrix mul;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int sum{};
			for (int k = 0; k < 3; k++)
			{
				sum += a.member((i * 3) + k) * b.member((k * 3) + j);
			}
			mul.inputValue((i * 3) + j, sum);
		}
	}

	cout << "Matrix A * Matrix B" << endl;
	a.printMatrix();
	cout << "*" << endl;
	b.printMatrix();
	cout << "=" << endl;
	mul.printMatrix();
	cout << endl;
}

void addMatrix(const Matrix& a, const Matrix& b)
{
	Matrix add;

	for (int i{ 0 }; i < 9; ++i)
	{
		add.inputValue(i, a.member(i) + b.member(i));
	}

	cout << "Matrix A + Matrix B" << endl;
	a.printMatrix();
	cout << "+" << endl;
	b.printMatrix();
	cout << "=" << endl;
	add.printMatrix();
	cout << endl;
}

void subtractMatrix(const Matrix& a, const Matrix& b)
{
	Matrix sub;

	for (int i{ 0 }; i < 9; ++i)
	{
		sub.inputValue(i, a.member(i) - b.member(i));
	}

	cout << "Matrix A - Matrix B" << endl;
	a.printMatrix();
	cout << "-" << endl;
	b.printMatrix();
	cout << "=" << endl;
	sub.printMatrix();
	cout << endl;
}

void transposeMatrix(Matrix& a, Matrix& b)
{
	cout << "Transposed Matrix" << endl;

	cout << "Matrix A" << endl;

	a.printMatrix();
	a.transposeMatrix();
	cout << "->" << endl;
	a.printMatrix();
	a.printDeterminant();

	cout << endl << "Matrix B" << endl;

	b.printMatrix();
	b.transposeMatrix();
	cout << "->" << endl;
	b.printMatrix();
	b.printDeterminant();

	a.transposeMatrix();
	b.transposeMatrix();
	cout << endl;
}

void expandMatrix(const Matrix& a, const Matrix& b)
{
	cout << "Expanded Matrix" << endl;

	cout << "Matrix A" << endl;

	a.printMatrix();
	cout << "->" << endl;
	a.printExpandedMatrix();
	a.printDeterminant();

	cout << endl << "Matrix B" << endl;

	b.printMatrix();
	cout << "->" << endl;
	b.printExpandedMatrix();
	a.printDeterminant();
	cout << endl;
}
