/* main.cpp:
 * 	Generate normally distributed values for Gaussian
 * 	classification.
 * authors:
 * 	Froilan Luna-Lopez
 * 		University of Nevada, Reno
 * 		CS 479 - Pattern Recognition
 * date:
 * 	23 February 2023
 */

// Libraries
#include <vector>
#include <iostream>
#include "dataGen.hpp"
#include "point.h"
#include "Matrix.hpp"

// Macros
#define OUTFILE "A.txt"		// The name of the file to output 2D values to.
#define D1_COUNT 60000		// The number of values to generate for one dataset, d1.
#define D2_COUNT 140000		// The number of values to generate for one dataset, d2.

int main() {
	// Variables
	//std::vector<point> d1Values(D1_COUNT);
	//std::vector<point> d2Values(D1_COUNT);
	Matrix mu1;
	Matrix mu2;
	Matrix covm1;
	Matrix covm2;

	// Define mean matrix for d1
	mu1 = Matrix(2, 1);
	mu1.set(0, 0, 3);
	mu1.set(1, 0, 6);

	// Define mean matrix for d2
	mu2 = Matrix(2, 1);
	mu2.set(0, 0, 3);
	mu2.set(1, 0, -2);

	// Define covariance matrix for d1
	covm1 = Matrix(2, 2);
	for(int i = 0; i < covm1.rows; i++) {
		for(int j = 0; j < covm1.cols; j++) {
			if(i == j) {
				covm1.set(i, j, 1);
			}
			else {
				covm1.set(i, j, 0);
			}
		}
	}

	// Define covariance matrix for d2
	covm2 = Matrix(2, 2);
	for(int i = 0; i < covm2.rows; i++) {
		for(int j = 0; j < covm2.cols; j++) {
			if(i == j) {
				covm2.set(i, j, 1);
			}
			else {
				covm2.set(i, j, 0);
			}
		}
	}

	// Generate values for datasets
	genGauss2D(D1_COUNT, mu1, covm1, 1, OUTFILE);
 	genGauss2D(D2_COUNT, mu2, covm2, 2, OUTFILE);

	return 1;
}
