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
#include "Matrix.hpp"
#include <vector>
#include <fstream>
#include <string>
#include <iostream>

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
void genGauss2D(size_t count, const Matrix& mean, const Matrix& covm, int id, std::string dest) {
	// Open output file
	std::ofstream outFile;
	outFile.open(dest, std::ofstream::app);

	for(int i = 0; i < count; i++) {
		point newPoint;
		newPoint.x = box_muller(mean.get(0,0), covm.get(0,0));
		newPoint.y = box_muller(mean.get(1,0), covm.get(1,1));
		
		outFile << newPoint.x
			<< " "
			<< std::to_string(newPoint.y)
			<< " "
			<< id
			<< std::endl;
	}

	outFile.close();
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
void save2D(std::vector<point>& source1, std::vector<point>& source2, std::string fname) {
	// Open output file
	std::ofstream outFile;
	outFile.open(fname);

	// Save the first set of data
	for(int i = 0; i < source1.size(); i++) {
		point p = source1[i];
		outFile << std::to_string(p.x)
			<< " "
			<< std::to_string(p.y)
			<< " "
			<< std::to_string(p.id)
			<< std::endl;
	}

	// Save the second set of data
	for(int i = 0; i < source2.size(); i++) {
		point p = source2[i];
		outFile << std::to_string(p.x)
			<< " "
			<< std::to_string(p.y)
			<< " "
			<< std::to_string(p.id)
			<< std::endl;

	}

	// Close the opened file
	outFile.close();
}

#endif
