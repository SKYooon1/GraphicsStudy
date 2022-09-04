#include <iostream>
#include <vector>
#include <random>

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
		uniform_int_distribution<int> uid(0, 1);

		member_.clear();
		for (int i = 0; i < 9; ++i)
			member_.push_back(uid(gen));
		calculateDeterminant();
	}

	void print() const
	{
		for (int i{0}; i < 3; ++i)
		{
			cout << "| ";
			for (int j{ i * 3 }; j < i * 3 + 3; ++j)
				cout << member_[j] << " ";
			cout << "|" << endl;
		}
	}

	void transposeMatrix()
	{
		swap(member_[1], member_[3]);
		swap(member_[2], member_[6]);
		swap(member_[5], member_[7]);
	}

private:
	vector<int> member_;
	int determinant_;

	void calculateDeterminant()
	{
		determinant_ = 0;		// 계산식 추가 필요
	}
};

int main()
{
	Matrix a;
	a.print();
}
