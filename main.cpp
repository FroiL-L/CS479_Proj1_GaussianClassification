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
#include "dataGen.hpp"

// Macros
#define OUTFILE "A.txt"		// The name of the file to output 2D values to.
#define D1_COUNT 10		// The number of values to generate for one dataset, d1.
#define D2_COUNT 10		// The number of values to generate for one dataset, d2.

int main() {
	// Variables
	std::vector<float> d1Values;
	std::vector<float> d2Values;

	// Generate values for datasets
	genGauss(D1_COUNT, 5, 1, d1Values);
	genGauss(D2_COUNT, 0, 1, d2Values);

	// Save generated values
	save2D(d1Values, d2Values, OUTFILE);

	return 1;
}
