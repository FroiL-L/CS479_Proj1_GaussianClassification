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
#include "Eigen/Dense"
#include "dataGen.hpp"
#include "point.h"
#include "classification.hpp"

// Macros
#define A_OUTFILE "A.txt"	// The name of the file to output 2D values to.
#define A_CLASSFILE "A_BC.txt"	// The name of the file to output the Bayes classifications to.
#define A_EUCFILE "A_Euc.txt"	// The name of the file to output the Euclidian classifications to.
#define B_OUTFILE "B.txt"	// The name of the file to output 2D values to.
#define B_CLASSFILE "B_BC.txt"	// The name of the file to output the Bayes classifications to.
#define B_EUCFILE "B_Euc.txt"	// The name of the file to output the Euclidian classifications to.
#define D1_COUNT 60000		// The number of values to generate for one dataset, d1.
#define D2_COUNT 140000		// The number of values to generate for one dataset, d2.

int main() {
	//////////////////////////////
	// Dataset A
	//////////////////////////////
	std::cout << std::endl << std::endl << "Now working on dataset A" << std::endl;

	// Variables
	Eigen::Matrix<float, 2, 1> mu1;
	Eigen::Matrix<float, 2, 1> mu2;
	Eigen::Matrix2f covm1;
	Eigen::Matrix2f covm2;
	float priorOne = 0.3;
    	float priorTwo = 0.7;
	std::vector<int> misclassCounts = std::vector<int>(2);
	std::vector<int> misclassCountsEuc = std::vector<int>(2);

	// Define mean matrices
	mu1 << 1, 1;
	mu2 << 4, 4;

	// Define covariance matrices
	covm1 << 1, 0,
	      0, 1;
	covm2 << 1, 0,
	      0, 1;

	// Generate data
	std::cout << "Generating data..." << std::endl;
	//genGauss2D(D1_COUNT, mu1, covm1, 1, A_OUTFILE);
	//genGauss2D(D2_COUNT, mu2, covm2, 2, A_OUTFILE);

	// Classify
	std::cout << "Classifying with case I..." << std::endl;
	bayesCaseOne(mu1,mu2,covm1(0,0),covm2(0,0),priorOne,priorTwo,A_OUTFILE, A_CLASSFILE);

	std::cout << "Classifying with Euclidean distance..." << std::endl;
	classifyEuclidean(mu1, mu2, A_OUTFILE, A_EUCFILE);

	// Count misclassifications
	std::cout << "Counting misclassifications..." << std::endl;
	misclassifyCount(A_OUTFILE, A_CLASSFILE, misclassCounts);
	misclassifyCount(A_OUTFILE, A_EUCFILE, misclassCountsEuc);

	std::cout << std::endl << "Misclassifications (case I):" << std::endl;
	std::cout << "ID=1: " << misclassCounts[0] << std::endl;
	std::cout << "ID=2: " << misclassCounts[1] << std::endl;

	std::cout << std::endl << "Misclassifications (Euclidean):" << std::endl;
	std::cout << "ID=1: " << misclassCountsEuc[0] << std::endl;
	std::cout << "ID=2: " << misclassCountsEuc[1] << std::endl;

	//////////////////////////////
	// Dataset B
	//////////////////////////////
	std::cout << std::endl << std::endl << "Now working on dataset B" << std::endl;

	// Variables
	Eigen::Matrix2f covmB2;
	misclassCounts = std::vector<int>(2, 0);
	misclassCountsEuc = std::vector<int>(2, 0);

	// Define new covariances
	covmB2 << 4, 0,
	       0, 8;

	// Generate data
	std::cout << "Generating data..." << std::endl;
	//genGauss2D(D1_COUNT, mu1, covm1, 1, B_OUTFILE);
	//genGauss2D(D2_COUNT, mu2, covmB2, 2, B_OUTFILE);

	// Classify
	std::cout << "Classifying with case three..." << std::endl;
	bayesCaseThree(mu1,mu2,covm1,covmB2,priorOne,priorTwo,B_OUTFILE, B_CLASSFILE);

	std::cout << "Classifying with Euclidean distance..." << std::endl;
	classifyEuclidean(mu1, mu2, B_OUTFILE, B_EUCFILE);

	// Count misclassifications
	std::cout << "Counting misclassifications..." << std::endl;
	misclassifyCount(B_OUTFILE, B_CLASSFILE, misclassCounts);
	misclassifyCount(B_OUTFILE, B_EUCFILE, misclassCountsEuc);

	std::cout << std::endl << "Misclassifications (case III):" << std::endl;
	std::cout << "ID=1: " << misclassCounts[0] << std::endl;
	std::cout << "ID=2: " << misclassCounts[1] << std::endl;

	std::cout << std::endl << "Misclassifications (Euclidean):" << std::endl;
	std::cout << "ID=1: " << misclassCountsEuc[0] << std::endl;
	std::cout << "ID=2: " << misclassCountsEuc[1] << std::endl;


	return 0;
}
