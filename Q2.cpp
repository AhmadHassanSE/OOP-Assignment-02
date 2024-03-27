#include<iostream>
#include<fstream>
using namespace std;
class SparseMatrix {
private:

	int rows; // Number of rows in the matrix
	int cols; // Number of columns in the matrix
	int** sparseMatrix; //Compressed Matrix


public:
	// Exercise 01
	// Constructors
	SparseMatrix()
	{
		rows = 0;
		cols = 0;
		sparseMatrix = nullptr;
	}
	//Exercise 02
	SparseMatrix(const std::string& filename)
	{
		int rows1 = 0, cols1 = 0;
		ifstream file(filename);
		file >> rows1;
		file >> cols1;
		int** sparsematrix1 = new int* [rows];
		for (int i = 0; i < rows1; i++)
		{
			sparsematrix1[i] = new int[cols1];
		}
		for (int i = 0; i < rows1; i++)
		{
			for (int j = 0; j < cols1; j++)
			{
				file >> sparsematrix1[i][j];
			}
		}
		int nonzero = 0;
		sparseMatrix = new int* [3];
		for (int i = 0; i < rows1; i++)
		{
			for (int j = 0; j < cols1; j++)
			{
				if (sparsematrix1[i][j] != 0)
				{
					nonzero++;
				}
			}
		}
		for (int i = 0; i < 3; i++)
		{
			sparseMatrix[i] = new int[nonzero];
		}
		int l = 0;
		for (int i = 0; i < rows1; i++)
		{
			for (int j = 0; j < cols1; j++)
			{
				if (sparsematrix1[i][j] != 0)
				{
					sparseMatrix[0][l] = i;

					sparseMatrix[1][l] = j;

					sparseMatrix[2][l] = sparsematrix1[i][j];
					l++;
				}
			}
		}
		cout << "Outputing Compressed Matrix: " << endl;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < nonzero; j++)
			{
				cout << sparseMatrix[i][j] << '\t';

			}
			cout << endl;
		}
		rows = 3;
		cols = nonzero;
	}
	//Exercise 03
	SparseMatrix(const SparseMatrix& other)
	{
		this->rows = other.rows;
		this->cols = other.cols;
		this->sparseMatrix = new int* [3];
		for (int i = 0; i < 3; i++)
		{
			this->sparseMatrix[i] = new int[other.cols];
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				this->sparseMatrix[i][j] = other.sparseMatrix[i][j];
			}
		}
		cout << "---------------------------------------------------------" << endl;
		cout << "Outputting copied object by copy constructor: " << endl;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				cout << this->sparseMatrix[i][j] << '\t';
			}
			cout << endl;
		}
	}
	//Exercise 04
	~SparseMatrix()
	{
		cout << "destructor called..............!" << endl;
		for (int i = 0; i < rows; i++)
		{
			delete sparseMatrix[i];
			sparseMatrix[i] = nullptr;
		}
		sparseMatrix = nullptr;
	}
	//Exercise 05
	SparseMatrix& operator=(const SparseMatrix& other)
	{
		cout << "Calling assignment operator............!" << endl;
		this->rows = other.rows;
		this->cols = other.cols;
		this->sparseMatrix = new int* [3];
		for (int i = 0; i < 3; i++)
		{
			sparseMatrix[i] = new int[cols];
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < other.cols; j++)
			{
				this->sparseMatrix[i][j] = other.sparseMatrix[i][j];
			}
		}
		return *this;
	}
	//Exercise 06
	SparseMatrix operator+(const SparseMatrix& other) const
	{
		cout << "------------------------------------------" << endl;
		int count = 0;
		cout << "Calling + operator............!" << endl;
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (this->sparseMatrix[i][j] == other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] != other.sparseMatrix[i + 1][j])
				{
					count++;
				}
				else if (this->sparseMatrix[i][j] != other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] == other.sparseMatrix[i + 1][j])
				{
					count++;
				}
				else if (this->sparseMatrix[i][j] != other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] != other.sparseMatrix[i + 1][j])
				{
					count++;
				}

			}
		}
		SparseMatrix temp;
		temp.sparseMatrix = new int* [3];
		for (int i = 0; i < 3; i++)
		{
			temp.sparseMatrix[i] = new int[other.cols + count];
		}

		for (int i = 0; i < 1; i++)
		{
			for (int j = 0, k = 0; k < cols + count; j++, k++)
			{
				if (this->sparseMatrix[i][j] == other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] == other.sparseMatrix[i + 1][j])
				{
					temp.sparseMatrix[i][k] = this->sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = this->sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = this->sparseMatrix[i + 2][j] + other.sparseMatrix[i + 2][j];
				}
				if (this->sparseMatrix[i][j] == other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] != other.sparseMatrix[i + 1][j])
				{
					temp.sparseMatrix[i][k] = this->sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = this->sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = this->sparseMatrix[i + 2][j];
					k++;
					temp.sparseMatrix[i][k] = other.sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = other.sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = other.sparseMatrix[i + 2][j];
				}
				if (this->sparseMatrix[i][j] != other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] == other.sparseMatrix[i + 1][j])
				{
					temp.sparseMatrix[i][k] = this->sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = this->sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = this->sparseMatrix[i + 2][j];
					k++;
					temp.sparseMatrix[i][k] = other.sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = other.sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = other.sparseMatrix[i + 2][j];
				}
				if (this->sparseMatrix[i][j] != other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] != other.sparseMatrix[i + 1][j])
				{
					temp.sparseMatrix[i][k] = this->sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = this->sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = this->sparseMatrix[i + 2][j];
					k++;
					temp.sparseMatrix[i][k] = other.sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = other.sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = other.sparseMatrix[i + 2][j];
				}
			}
		}
		cout << "After adding two objects: " << endl;
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < cols + count; k++)
			{
				cout << temp.sparseMatrix[i][k] << '\t';
			}
			cout << endl;
		}
		return temp;
	}
	//Exercise 07
	SparseMatrix operator-(const SparseMatrix& other) const
	{
		cout << "------------------------------------------" << endl;
		int count = 0;
		cout << "Calling - operator............!" << endl;
		for (int i = 0; i < 1; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (this->sparseMatrix[i][j] == other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] != other.sparseMatrix[i + 1][j])
				{
					count++;
				}
				else if (this->sparseMatrix[i][j] != other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] == other.sparseMatrix[i + 1][j])
				{
					count++;
				}
				else if (this->sparseMatrix[i][j] != other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] != other.sparseMatrix[i + 1][j])
				{
					count++;
				}

			}
		}
		SparseMatrix temp;
		temp.sparseMatrix = new int* [3];
		for (int i = 0; i < 3; i++)
		{
			temp.sparseMatrix[i] = new int[other.cols + count];
		}

		for (int i = 0; i < 1; i++)
		{
			for (int j = 0, k = 0; k < cols + count; j++, k++)
			{
				if (this->sparseMatrix[i][j] == other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] == other.sparseMatrix[i + 1][j])
				{
					temp.sparseMatrix[i][k] = this->sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = this->sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = this->sparseMatrix[i + 2][j] - other.sparseMatrix[i + 2][j];
				}
				if (this->sparseMatrix[i][j] == other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] != other.sparseMatrix[i + 1][j])
				{
					temp.sparseMatrix[i][k] = this->sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = this->sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = this->sparseMatrix[i + 2][j];
					k++;
					temp.sparseMatrix[i][k] = other.sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = other.sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = other.sparseMatrix[i + 2][j];
				}
				if (this->sparseMatrix[i][j] != other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] == other.sparseMatrix[i + 1][j])
				{
					temp.sparseMatrix[i][k] = this->sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = this->sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = this->sparseMatrix[i + 2][j];
					k++;
					temp.sparseMatrix[i][k] = other.sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = other.sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = other.sparseMatrix[i + 2][j];
				}
				if (this->sparseMatrix[i][j] != other.sparseMatrix[i][j] && this->sparseMatrix[i + 1][j] != other.sparseMatrix[i + 1][j])
				{
					temp.sparseMatrix[i][k] = this->sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = this->sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = this->sparseMatrix[i + 2][j];
					k++;
					temp.sparseMatrix[i][k] = other.sparseMatrix[i][j];
					temp.sparseMatrix[i + 1][k] = other.sparseMatrix[i + 1][j];
					temp.sparseMatrix[i + 2][k] = other.sparseMatrix[i + 2][j];
				}
			}
		}

		cout << "After Subtracting two objects: " << endl;
		for (int i = 0; i < 3; i++)
		{
			for (int k = 0; k < cols + count; k++)
			{
				cout << temp.sparseMatrix[i][k] << '\t';
			}
			cout << endl;
		}
		return temp;
	}
   //Exercise 08
	SparseMatrix operator*(const SparseMatrix& other) const
	{
		cout << "------------------------------------------" << endl;
		cout << "Calling * operator............!" << endl;

		SparseMatrix multiplied;
		multiplied.rows = rows;
		multiplied.cols = other.cols;

		// Initialize result sparse matrix
		multiplied.sparseMatrix = new int* [3];
		for (int i = 0; i < 3; ++i) 
		{
			multiplied.sparseMatrix[i] = new int[multiplied.cols];
		}

		// Initialize result matrix with zeros
		for (int i = 0; i < multiplied.cols; ++i)
		{
			multiplied.sparseMatrix[0][i] = 0;
			multiplied.sparseMatrix[1][i] = 0;
			multiplied.sparseMatrix[2][i] = 0;
		}

		// Perform matrix multiplication
		for (int j = 0; j < cols; ++j) 
		{
			for (int k = 0; k < other.cols; ++k) 
			{
				for (int l = 0; l < cols; ++l) 
				{
					if (sparseMatrix[0][l] == j && other.sparseMatrix[1][l] == k) 
					{
						multiplied.sparseMatrix[0][k] = j;  // Row index
						multiplied.sparseMatrix[1][k] = k;  // Column index
						multiplied.sparseMatrix[2][k] += sparseMatrix[2][l] * other.sparseMatrix[2][l];
					}
				}
			}
		}

		// Output result
		cout << "Result of matrix multiplication: " << endl;
		for (int i = 0; i < 3; ++i)
		{
		for (int j = 0; j < multiplied.cols; ++j)
		{
			cout << multiplied.sparseMatrix[i][j] << '\t';
		}
		cout << endl;
	}

	return multiplied;
}

	//Exercise 09
	bool operator==(const SparseMatrix& other) const
	{
		cout << "Calling boolean operator to check if both matrixes are equal or not.....!" << endl;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				if (this->sparseMatrix[i][j] != other.sparseMatrix[i][j])
				{
					return false;
				}
			}
		}
		return true;
	}
	//Exercise 10
	bool operator<(const SparseMatrix& other) const
	{
		cout << "Calling < operator to check if object 1 is less than object 2 or not.....!" << endl;
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				sum1 = sum1 + this->sparseMatrix[i][j];
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < other.cols; j++)
			{
				sum2 = sum2 + other.sparseMatrix[i][j];
			}
		}
		if (sum1 < sum2)
		{
			return true;
		}
		else
			return false;
	}
	//Exercise 11
	bool operator>=(const SparseMatrix& other) const
	{
		cout << "Calling >= operator to check if object 1 is greater or equal to object 2 or not.....!" << endl;
		int sum1 = 0, sum2 = 0;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				sum1 = sum1 + this->sparseMatrix[i][j];
			}
		}
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < other.cols; j++)
			{
				sum2 = sum2 + other.sparseMatrix[i][j];
			}
		}
		if (sum1 >= sum2)
		{
			return true;
		}
		else
			return false;
	}
	//Exercise 12
	void transpose()
	{
		int nonZeroCount = 0;
		// Count the number of non-zero elements
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				if (sparseMatrix[i][j] != 0)
				{
					nonZeroCount++;
				}
			}
		}

		// Allocate memory for temp based on the number of non-zero elements
		int** temp = new int* [3];
		for (int i = 0; i < 3; i++)
		{
			temp[i] = new int[nonZeroCount];
		}

		// Fill temp with transposed values
		int l = 0;
		for (int i = 0; i < cols; i++)
		{
			for (int j = 0; j < rows; j++)
			{
				if (sparseMatrix[j][i] != 0)
				{
					temp[0][l] = i;
					temp[1][l] = j;
					temp[2][l] = sparseMatrix[j][i];
					l++;
				}
			}
		}

		// Output transposed matrix
		cout << "Outputting Transposed matrix in compressed form!" << endl;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < nonZeroCount; j++)
			{
				cout << temp[i][j] << '\t';
			}
			cout << endl;
		}

		// Deallocate memory for temp
		for (int i = 0; i < 3; i++)
		{
			delete[] temp[i];
		}
		delete[] temp;
	}

	//Exercise 13
	friend istream& operator>> (std::istream& input, SparseMatrix& matrix);
	//Exercise 14
	friend ostream& operator<< (std::ostream& output, const SparseMatrix& matrix);
	//Exercise 15
	int* operator[](int index)
	{
		return sparseMatrix[index];
	}
};
//Exercise 13
istream& operator>> (std::istream& input, SparseMatrix& matrix)
{
	int rowsi = 0;
	int colsi = 0;
	cout << "Enter number of rows: " << endl;
	input >> matrix.rows;
	if (matrix.rows < 0)
	{
		while (matrix.rows < 0)
		{
			cout << "Error! enter positive value";
			cin >> matrix.rows;
		}
	}
	cout << "Enter number of cols: " << endl;
	input >> matrix.cols;
	if (matrix.cols < 0)
	{
		while (matrix.cols < 0)
		{
			cout << "Error! enter positive value";
			cin >> matrix.cols;
		}
	}
	int**matrix1= new int* [matrix.rows];
	for (int i = 0; i < matrix.rows; i++)
	{
		matrix1[i] = new int[matrix.cols];
	}
	cout << "Input values of matrix:" << endl;
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			input >> matrix1[i][j];
		}
	}
	int nonzero = 0;
	matrix.sparseMatrix = new int* [3];
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			if (matrix1[i][j] != 0)
			{
				nonzero++;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		matrix.sparseMatrix[i] = new int[nonzero];
	}
	int l = 0;
	for (int i = 0; i < matrix.rows; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			if (matrix1[i][j] != 0)
			{
				matrix.sparseMatrix[0][l] = i;

				matrix.sparseMatrix[1][l] = j;

				matrix.sparseMatrix[2][l] = matrix1[i][j];
				l++;
			}
		}
	}
	matrix.cols = nonzero;
	return input;
}
//Exercise 14
ostream& operator<< (std::ostream& output, const SparseMatrix& matrix)
{

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < matrix.cols; j++)
		{
			output << matrix.sparseMatrix[i][j]<<'\t';
		}
		output << endl;
	}
	return output;
}
int main()
{
	const string filename = "matrix.txt";
	SparseMatrix s1(filename);
	SparseMatrix temp(s1);
	//Exercise 05
	SparseMatrix s2;
	s2 = s1;
	//Exercise 06
	SparseMatrix s3 = s1 + s2;
	//Exercise 07
	SparseMatrix s4 = s2 - s1;
	//Exercise 08
	SparseMatrix s5 = s1 * s2;
	cout << "----------------------------------------" << endl;
	//Exercise 09
	if ((s1 == s2) == 1)
	{
		cout << "Both Sparse matrix are equal!" << endl;
	}
	else
	{
		cout << "Sparse matrix are not equal!" << endl;
	}
	cout << "----------------------------------------" << endl;
	//Exercise 10
	if ((s1 < s2) == 1)
	{
		cout << "Object 1 is less than object 2!" << endl;
	}
	else
		cout << "Object 1 is not less than object 2!" << endl;
	cout << "----------------------------------------" << endl;
	//Exercise 11
	if ((s1 >= s2) == 1)
	{
		cout << "Object 1 is greater than or equal to object 2!" << endl;
	}
	else
		cout << "Object 1 is not greater than or equal to object 2!" << endl;
	cout << "----------------------------------------" << endl;
	//Exercise 12
	s1.transpose();
	cout << "----------------------------------------" << endl;
	//Exercise 13
	SparseMatrix spd;
	cin >> spd;
	cout << "----------------------------------------" << endl;
	//Exercise 14
	cout << "Entered Matrix in compressed form is: " << endl;
	cout << spd;
	//Exercise 15
	cout << "----------------------------------------" << endl;
	cout << "Sparse matrix before updating any index by overloading subscript operator " << endl;
	cout << s2;
	cout << "Sparse matrix after updating any index by overloading subscript operator " << endl;
	s2[0][1] = 100;
	cout << s2;
	
	

}