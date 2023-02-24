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
#include "boxmuller.c"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

// Macros
#define OUTFILE "normal.txt"	// The name of the file to output 2D values to.
#define X_COUNT 10		// The number of X values to generate.
#define Y_COUNT 10		// The number of Y values to generate.

/* genGauss():
 * 	Generates random values that are normally distributed
 * 	with a given set of mean and standard deviation.
 * args:
 * 	@count: Number of elements to generate.
 * 	@mean: The mean of the distribution.
 * 	@sd: The standard deviation of the distribution.
 * 	@dest: The location to save the generated values.
 * return:
 * 	@dest
 */
void genGauss(int count, float mean, float sd, std::vector<float>& dest) {
	for(int i = 0; i < count; i++) {
		dest.push_back(box_muller(mean, sd));
	}
}

/* save2D():
 * 	Saves two sets of vectors in a file.
 * args:
 * 	@source1: A vector with values to grab from.
 * 	@source2: A vector with values to grab from.
 * 	@fname: The name of the file to save to.
 * return:
 * 	void
 */
void save2D(std::vector<float>& source1, std::vector<float>& source2, std::string fname) {
	std::ofstream outFile;
	outFile.open(fname);

	for(int i = 0; i < source1.size(); i++) {
		outFile << std::to_string(source1[i]) 
			<< ", " 
			<< std::to_string(source2[i])
			<< std::endl;
	}

	outFile.close();
}

int main() {
	std::vector<float> xValues;
	std::vector<float> yValues;

	genGauss(X_COUNT, 5, 1, xValues);
	genGauss(Y_COUNT, 0, 1, yValues);

	save2D(xValues, yValues, OUTFILE);

	return 1;
}
