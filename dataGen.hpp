/* dataGen.hpp:
 * 	Library with tools for generating normally
 * 	distributed data.
 * authors:
 * 	Froilan Luna-Lopez
 * 		University of Nevada, Reno
 * 		CS 479 - Pattern Recognition
 * date:
 * 	27 February 2023
 */

#ifndef _DATAGEN_HPP_
#define _DATAGEN_HPP_

// Libraries
#include "boxmuller.c"
#include "point.h"
#include "Eigen/Dense"
#include <vector>
#include <fstream>
#include <string>

// Methods

/* genGauss():
 * 	Generates random values that are normally distributed
 * 	with a given set of mean and standard deviation.
 * args:
 * 	@count: The number of elements to generate.
 * 	@mean: The mean of the distributions.
 * 	@covm: The covariance matrix of the features.
 * 	@id: The id to classify the values to.
 * 	@dest: The location to save the generated values.
 * return:
 * 	@dest
 */
void genGauss2D(size_t count, 
		const Eigen::Matrix<float, 2, 1>& mean, 
		const Eigen::Matrix2f& covm, 
		int id, 
		std::string dest) {
	// Open output file
	std::ofstream outFile;
	outFile.open(dest, std::ofstream::app);

	for(int i = 0; i < count; i++) {
		point newPoint;
		newPoint.x = box_muller(mean(0,0), covm(0,0));
		newPoint.y = box_muller(mean(1,0), covm(1,1));
		
		outFile << newPoint.x
			<< " "
			<< newPoint.y
			<< " "
			<< id
			<< std::endl;
	}

	outFile.close();
}

#endif
