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
#include "Eigen/Dense"
#include "dataGen.hpp"
#include "point.h"

// Macros
#define OUTFILE "A.txt"		// The name of the file to output 2D values to.
#define D1_COUNT 60000		// The number of values to generate for one dataset, d1.
#define D2_COUNT 140000		// The number of values to generate for one dataset, d2.

int main() {
	// Variables
	Eigen::Matrix<float, 2, 1> mu1;
	Eigen::Matrix<float, 2, 1> mu2;
	Eigen::Matrix2f covm1;
	Eigen::Matrix2f covm2;

	// Define mean matrices
	mu1 << 3, 6;
	mu2 << 3, -2;

	// Define covariance matrices
	covm1 << 1, 0,
	      0, 1;
	covm2 << 1, 0,
	      0, 1;

	genGauss2D(D1_COUNT, mu1, covm1, 1, OUTFILE);
	genGauss2D(D2_COUNT, mu2, covm2, 2, OUTFILE);

	return 1;
}
