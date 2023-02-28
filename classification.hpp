/* classification.hpp:
 * 	A library that contains tools for classification.
 * authors:
 *	Froilan Luna-Lopez
 *		University of Nevada, Reno
 *		CS 479 - Pattern Recognition
 * date:
 * 	27 February 2023
 */

#ifndef _CLASSIFICATION_H_
#define _CLASSIFICATION_H_

// Libraries
#include <string>
#include <fstream>
#include <iostream>

#include "Eigen/Dense"

/* classifyCaseI():
 * 	Classifies points within a file between two classes, 1 and 2.
 * 	Classification is based on minimizing the Euclidean distance
 * 	with the feature and mean values.
 * args:
 * 	@means1: Set of mean values for features in class 1.
 * 	@means2: Set of mean vluaes for features in class 2.
 * 	@sourceFile: Path to the file with the data to classify.
 * 	@destFile: Path to the file to write the classifications to.
 * return:
 * 	@destFile
 */
void classifyEuclidean(Eigen::Matrix<float, 2, 1> means1,
		Eigen::Matrix<float, 2, 1> means2,
		std::string sourceFile,
		std::string destFile) {
	// Open file for reading feature sets
	std::ifstream inFile;
	inFile.open(sourceFile);

	// Open file for writing classifications to
	std::ofstream outFile;
	outFile.open(destFile);

	// Read features from source file
	float xf, yf, _f;
	while(inFile >> xf >> yf >> _f) {
		// Compute distance from first mean
		float dist1 = std::pow((xf - means1(0, 0)), 2)
			+ std::pow((yf - means1(1, 0)), 2);

		// Compute distance from second mean
		float dist2 = std::pow((xf - means2(0, 0)), 2)
			+ std::pow((yf - means2(1, 0)), 2);

		// Save choice
		outFile << xf << " " << yf << " ";
		if(dist1 < dist2) {
			outFile << "1";
		}
		else {
			outFile << "2";
		}
		outFile << std::endl;
	}

	// Close files
	inFile.close();
	outFile.close();
}

#endif
