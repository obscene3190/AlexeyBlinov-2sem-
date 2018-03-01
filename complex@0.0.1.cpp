#include <iostream>
#include <sstream>
#include <cstdlib>
using namespace std;

#include <iostream>
#include <sstream>
using namespace std;

struct complex_t {
	float real;
	float imag;
	complex_t() {
		real = 0.0f;
		imag = 0.0f;
	}
	complex_t add(complex_t other) const { 
		complex_t complex;
		complex.real = this->real + other.real;
		complex.imag = this->imag + other.imag;
		return complex;
	}
	complex_t sub(complex_t other) const {
		complex_t complex;
		complex.real = this->real - other.real;
		complex.imag = this->imag - other.imag;
		return complex;
	}
	complex_t mul(complex_t other) const {
		complex_t complex;
		complex.real = this->real * other.real - this->imag * other.imag;
		complex.imag = this->imag * other.real + this->real * other.imag;
		return complex;
	}
	complex_t div(complex_t other) const {
		complex_t complex;
		complex.real = (this->real * other.real + this->imag * other.imag) /
			(other.real * other.real + other.imag * other.imag);
		complex.imag = (this->imag * other.real - this->real * other.imag) /
			(other.real * other.real + other.imag * other.imag);
		return complex;
	}
	ostream & write(ostream &stream) { 
		return stream << '(' << this->real << ',' << this->imag << ')' << endl;
	}
	bool read(istream & stream) {
		char ch;
		bool res = true;
		float real, imag;
		if (stream >> ch && ch == '(' &&
			stream >> real &&
			stream >> ch && ch == ',' &&
			stream >> imag &&
			stream >> ch && ch == ')') {
			this->real = real;
			this->imag = imag;
		}
		else { 
			res = false; cout << "An error has occured while reading input data" << endl; 
		}
		return res;
	}
	~complex_t() {

	}
};

int main() {
	complex_t cm1, cm2, itog;
	string string;
	getline(cin, string);
	istringstream stream(string);
	char op;
	if (cm1.read(stream) && stream >> op && cm2.read(stream)) {
		switch (op) {
		case '+': {itog = cm1.add(cm2);
			break; };
		case '-': {itog = cm1.sub(cm2);
			break; };
		case '*': {itog = cm1.mul(cm2);
			break; };
		case '/': {itog = cm1.div(cm2);
			break; };
		default: {cout << "Incorrect operation" << endl;
			break; }
		}
		itog.write(cout);
	}
}
