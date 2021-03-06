#include <iostream>
#include <sstream>
#include <cmath>
#include <fstream>

using namespace std;

/*Ввод реализован в виде:
A.txt
+
B.txt
*/

class matrix_t {
public:
	int ** data;
	unsigned int rows;
	unsigned int columns;
	matrix_t() {
		data = nullptr;
		rows = 0;
		columns = 0;
	}
	ifstream & read(ifstream & stream, string fileName) {
		stream.open(fileName.c_str());
		char op;
		if (stream.is_open() &&
			stream >> rows &&
			stream >> op && op == ',' &&
			stream >> columns) {
			data = new int *[rows];
			for (unsigned int i = 0; i < rows; ++i) {
				data[i] = new int[columns];
				for (unsigned int j = 0; j < columns; ++j) {
					stream >> data[i][j];
				}
			}
		}
		else {
			cout << "Error";
		}
		return stream;
	}
	ostream & write(ostream & stream) {
		stream << endl;
		for (unsigned int i = 0; i < rows; i++) {
			for (unsigned int j = 0; j < columns; j++) {
				if (data[i][j] == -0) {
					stream << 0 << " ";
				}
				else {
					stream << data[i][j] << " ";
				}
			}
			stream << endl;
		}
		return stream;
	}
	matrix_t add(matrix_t const & other) const {
		if (rows == other.rows && columns == other.columns) {
			for (unsigned int i = 0; i < rows; ++i) {
				for (unsigned int j = 0; j < columns; ++j) {
					other.data[i][j] = data[i][j] + other.data[i][j];
				}
			}
		}
		else {
			cout << "Something went wrong :(";
		}
		return other;
	}
	matrix_t sub(matrix_t const & other) const {
		if (rows == other.rows && columns == other.columns) {
			for (unsigned int i = 0; i < rows; ++i) {
				for (unsigned int j = 0; j < columns; ++j) {
					other.data[i][j] = data[i][j] - other.data[i][j];
				}
			}
		}
		else {
			cout << "Something went wrong :(";
		}
		return other;
	}
	matrix_t mul(matrix_t const & other) const {
		matrix_t result;
		int res = 0;
		if (columns == other.rows) {
			result.rows = rows;
			result.columns = other.columns;
			result.data = new int *[rows];
			for (unsigned int i = 0; i < rows; ++i) {
				result.data[i] = new int[other.columns];
			}
			for (unsigned int i = 0; i < rows; i++) {
				for (unsigned int j = 0; j < columns; j++) {
					res = 0;
					for (unsigned int k = 0; k < rows; k++) {
						res += data[i][k] * other.data[k][j];
						result.data[i][j] = res;
					}
				}
			}
		}
		else {
			cout << "Something went wrong :(";
		}
		return result;
	}
	matrix_t trans() const {
		matrix_t result;
		result.rows = rows;
		result.columns = columns;
		result.data = new int *[rows];
		for (unsigned int i = 0; i < rows; ++i) {
			result.data[i] = new int[columns];
		}
		for (unsigned int i = 0; i < columns; i++) {
			for (unsigned int j = 0; j < rows; j++) {
				result.data[i][j] = data[j][i];
			}
		}
		return result;
	}
	matrix_t(const matrix_t & matrix) {
		rows = matrix.rows;
		columns = matrix.columns;
		data = new int *[rows];
			for (unsigned int i = 0; i < rows; ++i) {
				data[i] = new int[columns];
				for (unsigned int j = 0; j < columns; ++j) {
					data[i][j] = matrix.data[i][j];
				}
			}
        }
	matrix_t & operator=(const matrix_t & matrix) {
		if (this != &matrix) {
				for (unsigned int i = 0; i < rows; ++i) {
						delete[] data[i];
				}
				delete[] data;
				rows = matrix.rows;
				columns = matrix.columns;
				data = new int * [rows];
				for (unsigned int i = 0; i < rows; ++i) {
						data[i] = new int[columns];
						for (unsigned int j = 0; j < columns; ++j) {
								data[i][j] = matrix.data[i][j];
						}
				}
	}			
	else {
		return *this;
	}
        }
	~matrix_t() {
		for (unsigned int i = 0; i < rows; ++i) {
			delete[] data[i];
		}
		delete[] data;
	}
};

bool readFileName(string &fileName) {
	bool result = true;
	string string;
	getline(cin, string);
	istringstream stream(string);
	if (!(stream >> fileName)) {
		result = !result;
	}
	return result;
}


int main() {
	matrix_t matrix1, matrix2, result;
	char op;
	string fileName1, fileName2;
	ifstream streamA, streamB;
	if (readFileName(fileName1)) {
		matrix1.read(streamA, fileName1);
		std::cin >> op;
		std::cin.get();
		if (op == 'T') {
				result = matrix1.trans();
				result.write(cout);
		}
		else if (matrix1.rows == matrix1.columns && (op == '-' || op == '+' || op == '*')) {
			if (readFileName(fileName2)) {
				matrix2.read(streamB, fileName2);
				switch (op) {
				case '+': {
					result = matrix1.add(matrix2);
					result.write(cout);
					break;
				}
				case '-': {
					result = matrix1.sub(matrix2);
					result.write(cout);
					break;
				}
				case '*': {
					result = matrix1.mul(matrix2);
					result.write(cout);
					break;
				}
				default:
					cout << "An error has occured while reading input data";
				}
				
			}
		else cout << "An error has occured while reading input data";
		}
	}
	std::cin.get();
}
