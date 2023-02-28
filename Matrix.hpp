#ifndef _MATRIX_HPP_
#define _MATRIX_HPP_

// Libraries
#include <vector>

// Declarations
class Matrix {
	public:
		// Attributes
		int rows;
		int cols;
		std::vector<float> elements;

		// Constructors
		Matrix();
		Matrix(int r, int c);

		// Methods
		float get(int r, int c) const;
		void set(int r, int c, float val);
		void matMul(const Matrix& operand2, Matrix& dest);
};

// Matrix implementation
Matrix::Matrix() {
	this->rows = 0;
	this->cols = 0;
	this->elements = std::vector<float>(0);
}

Matrix::Matrix(int r, int c) {
	this->rows = r;
	this->cols = c;
	this->elements = std::vector<float>(r * c);
}

float Matrix::get(int r, int c) const {
	return this->elements[(r * this->cols) + c];
}

void Matrix::set(int r, int c, float val) {
	this->elements[(r * this->cols) + c] = val;
}

void Matrix::matMul(const Matrix& operand2, Matrix& dest) {
	// Test for pre-requisites
	if(this->cols != operand2.rows) return;

	// Perform operation
	for(int i = 0; i < this->rows; i++) {
		for(int j = 0; j < this->cols; j++) {
			for(int k = 0; k < operand2.rows; k++) {
				float val = (get(i, j)) * operand2.get(k, j);
				dest.set(i, k, val);
			}
		}
	}
}

#endif
