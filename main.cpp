/* main.cpp:
 * 	Generate normally distributed values for Gaussian
 * 	classification.
 * authors:
 * 	Froilan Luna-Lopez
 * 	Aaron Ramirez
 * 		University of Nevada, Reno
 * 		CS 479 - Pattern Recognition
 * date:
 * 	23 February 2023
 */

// Libraries
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include "dataGen.hpp"
#include "point.h"
#include "classification.hpp"

// Macros
#define OUTFILE "A.txt"		// The name of the file to output 2D values to.
#define CLASSFILE "A_BC.txt"	// The name of the file to output the Bayes classifications to.
#define D1_COUNT 60000		// The number of values to generate for one dataset, d1.
#define D2_COUNT 140000		// The number of values to generate for one dataset, d2.

int main() {
	// Variables
	Eigen::Matrix<float, 2, 1> mu1;
	Eigen::Matrix<float, 2, 1> mu2;
	Eigen::Matrix2f covm1;
	Eigen::Matrix2f covm2;
	float priorOne = 0.5;
    float priorTwo = 0.5;

	// Define mean matrices
	mu1 << 1, 1;
	mu2 << 4, 4;

	// Define covariance matrices
	covm1 << 1, 0,
	      0, 1;
	covm2 << 1, 0,
	      0, 1;

	// Generate data
	genGauss2D(D1_COUNT, mu1, covm1, 1, OUTFILE);
	genGauss2D(D2_COUNT, mu2, covm2, 2, OUTFILE);

	// Classify
	bayesCaseOne(mu1,mu2,covm1(0,0),covm2(0,0),priorOne,priorTwo,OUTFILE, CLASSFILE);

	classifyEuclidean(mu1, mu2, OUTFILE, CLASSFILE);

	return 0;
}
